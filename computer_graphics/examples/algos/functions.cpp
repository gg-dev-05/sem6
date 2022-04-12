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
    cout<<"\n{\n";
    for(auto x:mat){
        cout<<"{";
        for(auto y:x){
            cout<<y<<", ";
        }
        cout<<"},\n";
    }
    cout<<"}\n\n";
}
void show(V v){
    cout<<"{";
    for(auto x:v){
        cout<<x<<", ";
    }
    cout<<"}\n\n";
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
V sum(V a, V b){
    V ans;
    int n=a.size();
    int m=b.size();
    assert(n==m);
    rep(i,n){
        ans.pb(a[i]+b[i]);
    }
    return ans;
}
db dot(V a, V b){
    int n=a.size();
    db sum=0;
    rep(i,n){
        sum+=a[i]*b[i];
    }
    return sum;
}
V unit_vec(V a){
    return scaler_mul(a,1.0/mod(a));
}
db dis(pair<db,db> a,pair<db,db> b){
    db x1=a.first;
    db y1=a.second;
    db x2=b.first;
    db y2=b.second;
    return sqrt((y2-y1)*(y2-y1)+(x2-x1)*(x2-x1));
}
int main(){
    V a={20,30,15};
    V b={10,5,0};
    V c={15,20,10};
    V d={20,15,40};
    V A[3]={unit_vec(cross({0,-15,25},{-10,-25,-15})),unit_vec(cross({-10,-25,-15},{-5,-10,-5})),unit_vec(cross({-5,-10,-5},{0,-15,25}))};
    V B[3]={unit_vec(cross({10,25,15},{10,10,40})),unit_vec(cross({5,15,10},{10,25,15})),unit_vec(cross({10,10,40},{5,15,10}))};
    V C[3]={unit_vec(cross({5,10,5},{-5,-15,-10})),unit_vec(cross({-5,-15,-10},{5,-5,30})),unit_vec(cross({5,-5,30},{5,10,5}))};
    V D[3]={unit_vec(cross(sub(b,d),sub(a,d))),unit_vec(cross(sub(a,d),sub(c,d))),unit_vec(cross(sub(c,d),sub(b,d)))};

    V normalA=unit_vec(sum(sum(A[0],A[1]),A[2]));
    show(normalA);
    V normalB=unit_vec(sum(sum(B[0],B[1]),B[2]));
    V normalC=unit_vec(sum(sum(C[0],C[1]),C[2]));
    V normalD=unit_vec(sum(sum(D[0],D[1]),D[2]));

    db Iamb=10;
    V light={-5,-5,-5};
    V eye={0,0,0};
    db Ip=100;
    db Ka=0.5, Kd=0.8, Ks=0.3;
    db n=10;
    db fatt=0.3;

    V La=unit_vec(sub(light,a));
    V Lb=unit_vec(sub(light,b));
    V Lc=unit_vec(sub(light,c));
    V Ld=unit_vec(sub(light,d));

    
    db costhetaA=dot(normalA,La);
    db costhetaB=dot(normalB,Lb);
    db costhetaC=dot(normalC,Lc);
    db costhetaD=dot(normalD,Ld);
    
    // cout<<costhetaA<<endl<<costhetaB<<endl<<costhetaC<<'\n';
    V VA=unit_vec(sub(eye,a));
    V VB=unit_vec(sub(eye,b));
    V VC=unit_vec(sub(eye,c));
    V VD=unit_vec(sub(eye,d));

    V RA=unit_vec(sub(scaler_mul(normalA,2*dot(La,normalA)),La));
    V RB=unit_vec(sub(scaler_mul(normalB,2*dot(Lb,normalB)),Lb));
    V RC=unit_vec(sub(scaler_mul(normalC,2*dot(Lc,normalC)),Lc));
    V RD=unit_vec(sub(scaler_mul(normalD,2*dot(Ld,normalD)),Ld));
    
    db cosalphaA=dot(RA,VA);
    db cosalphaB=dot(RB,VB);
    db cosalphaC=dot(RC,VC);
    db cosalphaD=dot(RD,VD);
    

    //Constant Shading
    V surface_normal=unit_vec(cross({5,10,5},{-5,-15,-10}));

    V centroid=scaler_mul(sum(a,sum(b,c)),1.0/3);

    V Lconst=unit_vec(sub(light,centroid));

    V Vconst=unit_vec(sub(eye,centroid));

    V Rconst=unit_vec(sub(scaler_mul(surface_normal,2*dot(Lconst,surface_normal)),Lconst));

    db Iconst=Iamb*Ka + fatt*Ip*Kd*dot(surface_normal,Lconst) + fatt*Ip*Ks*pow(dot(Rconst,Vconst),n);
    cout<<"Constant Shading Intensity: "<<Iconst<<"\n\n";

    //Gourad Shading
    db IA=Iamb*Ka + fatt*Ip*Kd*costhetaA + fatt*Ip*Ks*pow(cosalphaA,n);
    db IB=Iamb*Ka + fatt*Ip*Kd*costhetaB + fatt*Ip*Ks*pow(cosalphaB,n);
    db IC=Iamb*Ka + fatt*Ip*Kd*costhetaC + fatt*Ip*Ks*pow(cosalphaC,n);
    db ID=Iamb*Ka + fatt*Ip*Kd*costhetaD + fatt*Ip*Ks*pow(cosalphaD,n);
    
    cout<<"IA: "<<IA<<"\n";
    cout<<"IB: "<<IB<<"\n";
    cout<<"IC: "<<IC<<"\n";
    cout<<"ID: "<<ID<<"\n";
    
    db Icentroid=(IB+IC)/2;
    Icentroid=Icentroid+(1.0/3)*(IA-Icentroid);
    
    cout<<"Gourad Shading Intensity: "<<Icentroid<<"\n";
    // V a={25,-20,15};
    // a=unit_vec(a);
    // V b={0,30,0};
    // V cop=sum(b,scaler_mul(a,50));
    // V c={40, 65, 30};
    // show(sum(cop,scaler_mul(sub(c,cop),0.447)));
    // db I1=62, I2=58 ,I3=22;
    // db Ia=I3+(dis({0,1.8},{0,1})/dis({0,1},{0,3}))*(I1-I3);
    // db Ib=I3+(dis({0.8,1.8},{0,1})/dis({0,1},{1,2}))*(I2-I3);
    // db Ip=Ia+(dis({0,1.8},{0.4,1.8})/dis({0,1.8},{0.8,1.8}))*(Ib-Ia);
    // cout<<Ia<<" "<<Ib<<" "<<Ip<<"\n";
    return 0;
}