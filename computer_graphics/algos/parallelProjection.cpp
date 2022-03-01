#include<bits/stdc++.h>
using namespace std;
#define db double
#define pb push_back
#define V vector<db>
#define matrix vector<V>
#define rrep(i,k,n) for(int i=k;i<n;i++)
#define rep(i,n) for(int i=0;i<n;i++)
#define all(a) a.begin(), a.end()
matrix I={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
void show(matrix mat){
    cout<<"\n[\n";
    for(auto x:mat){
        cout<<"[ ";
        for(auto y:x){
            cout<<y<<", ";
        }
        cout<<"],\n";
    }
    cout<<"]\n\n";
}
void show(V v){
    cout<<"[";
    for(auto x:v){
        cout<<x<<", ";
    }
    cout<<"]\n\n";
}
V cross(V A, V B){
    // assert(A.size()==B.size());
    return {A[1]*B[2]-A[2]*B[1],A[2]*B[0]-A[0]*B[2],A[0]*B[1]-A[1]*B[0]};
}
db mod(V A){
    db sum=0;
    for(auto x:A){
        sum+=x*x;
    }
    return sqrt(sum);
}
matrix transpose(matrix mat){
    int n=mat.size();
    int m=mat[0].size();
    matrix ans;
    rep(j,m){
        V curr;
        rep(i,n){
            curr.pb(mat[i][j]);
        }
        ans.pb(curr);
    }
    return ans;
}
matrix mul(matrix A, matrix B){
    int n=A.size();
    int d=A[0].size();
    assert(d==(int)B.size());
    int m=B[0].size();
    matrix ans(n,V(m));
    rep(i,n){
        rep(j,m){
            db sum=0;
            rep(k,d){
                sum+=A[i][k]*B[k][j];
            }
            ans[i][j]=sum;
        }
    }
    return ans;
}
vector<db> mul(matrix A, V B){
    matrix C(1,V(B));
    matrix ans= transpose(mul(A,transpose(C)));
    return ans[0];
}
matrix T(matrix input, db tx, db ty, db tz){
matrix trans_matrix={{1,0,0,tx},{0,1,0,ty},{0,0,1,tz},{0,0,0,1}};
return mul(trans_matrix,input);
}
matrix S(matrix input, db Sx, db Sy, db Sz){
matrix scale_matrix={{Sx,0,0,0},{0,Sy,0,0},{0,0,Sz,0},{0,0,0,1}};
return mul(scale_matrix,input);
}
matrix Shxy(matrix input, db Shx, db Shy){
matrix shear_matrix={{1,0,Shx,0},{0,1,Shy,0},{0,0,1,0},{0,0,0,1}};
return mul(shear_matrix,input);
}
V scaler_mul(V A, db d){
    int n=A.size();
    rep(i,n){
        A[i]*=d;
    }
    return A;
}
V sub(V a, V b){
    V ans;
    int n=a.size();
    int m=b.size();
    assert(n==m);
    rep(i,n){
        ans.pb(a[i]-b[i]);
    }
    return ans;
}
int main(){
    V vup(4),vrp(4),vpn(4),prp(4),win(4);
    db F, B;
    matrix input;
    cout<<"Enter VRP: ";
    rep(i,4){
        if(i==3)
        vrp[i]=1;
        else
        cin>>vrp[i];
    }
    cout<<"Enter VPN: ";
    rep(i,4){
        if(i==3)
        vpn[i]=1;
        else
        cin>>vpn[i];
    }
    cout<<"Enter VUP: ";
    rep(i,4){
        if(i==3)
        vup[i]=1;
        else
        cin>>vup[i];
    }
    cout<<"Enter PRP: ";
    rep(i,4){
        if(i==3)
        prp[i]=1;
        else
        cin>>prp[i];
    }
    cout<<"Enter Window(umin, umax, vmin, vmax): ";
    rep(i,4){
        cin>>win[i];
    }
    cout<<"Enter the distance to front face(F): ";
    cin>>F;
    cout<<"Enter the distance to back face(B): ";
    cin>>B;
    
    int n;
    cout<<"Enter the number of points you want to convert into CVV: ";
    cin>>n;
    cout<<"Start entering the points: \n";
    rep(i,n){
        V poi(4);
        rep(j,4){
            if(j==3)
            poi[j]=1;
            else
            cin>>poi[j];
        }
        input.pb(poi);
    }
    input=transpose(input);

    //Matrix#1(Translation Matrix)
    matrix T1=T(I,-vrp[0],-vrp[1],-vrp[2]);
    cout<<"T: ";
    show(T1);

    //Matrix#2(Rotation Matrix)
    V rz=vpn;
    rz.pop_back();
    rz=scaler_mul(rz, 1.0/mod(rz));
    rz.pb(0);

    V rx=cross(vup, vpn);
    rx=scaler_mul(rx,1.0/mod(rx));
    rx.pb(0);

    V ry=cross(vpn,rx);
    ry=scaler_mul(ry,1.0/mod(ry));
    ry.pb(0);

    assert(rx.size()==ry.size() && rx.size()==rz.size() && (int)rx.size()==4);
    
    matrix R1={rx,ry,rz,{0,0,0,1}};
    cout<<"R: ";
    show(R1);

    //Center of window(CW) and DOP calculation
    V cw={(win[0]+win[1])/2,(win[3]+win[2])/2,0,1};
    cout<<"CW: ";
    show(cw);
    V dop=sub(cw,prp);
    cout<<"DOP: ";
    show(dop);

    //Matrix#3(Shearing Matrix)
    db Shxpar=-dop[0]/dop[2];
    db Shypar=-dop[1]/dop[2];
    matrix Shpar=Shxy(I,Shxpar,Shypar);
    cout<<"S: ";
    show(Shpar);
    cout<<"DOP(after shearing): ";
    show(mul(Shpar,dop));

    //Matrix#4(Translation Matrix)
    matrix Tpar=T(I,-cw[0],-cw[1],-F);
    cout<<"Tpar: ";
    show(Tpar);

    //Matrix#5(Scaling Matrix)
    matrix Spar=S(I,2.0/(win[1]-win[0]),2.0/(win[3]-win[2]),1/(F-B));
    cout<<"Spar: ";
    show(Spar);

    //Final Mgen

    matrix Mgen=mul(Spar,mul(Tpar,mul(Shpar,mul(R1,T1))));
    cout<<"Final Matrix, Mgen: ";
    show(Mgen);

    //Final points
    matrix output=mul(Mgen, input);
    output=transpose(output);

    cout<<"Output points: ";
    show(output);
    return 0;
}