#include<bits/stdc++.h>
using namespace std;
#define db double
double PI=3.141592;
#define rep(i,n) for(int i=0;i<n;i++)
#define VVdb vector<vector<db>>
VVdb I={{1,0,0},{0,1,0},{0,0,1}};
VVdb transpose(VVdb input){
    int n=input.size();
    int m=input[0].size();
    VVdb in(m,vector<db>(n));
    rep(i,n){
        rep(j,m){
            in[j][i]=input[i][j];
        }
    } 
    return in;
}
VVdb matrix_mul(VVdb m1, VVdb m2){
    int a=m1.size();
    int b=m1[0].size();
    int d=m2.size();
    assert(d==b);
    int c=m2[0].size();
    VVdb ans(a,vector<db>(c));
    rep(i,a){
        rep(j,c){
            ans[i][j]=0;
            rep(k,b){
                ans[i][j]+=m1[i][k]*m2[k][j];
            }
        }
    }
    return ans;
}
void show(VVdb mat){
for(auto x:mat){
    for(auto y:x){
        cout<<y<<"     ";
    }
    cout<<endl;
}
}
VVdb T(VVdb input, db tx, db ty){
VVdb trans_matrix={{1,0,tx},{0,1,ty},{0,0,1}};
return matrix_mul(trans_matrix,input);
}

VVdb R(VVdb input, db theta){
db radian=PI*theta/180;
VVdb rot_matrix={{cos(radian),-sin(radian),0},{sin(radian),cos(radian),0},{0,0,1}};
return matrix_mul(rot_matrix,input);
}

VVdb S(VVdb input, db Sx, db Sy){
VVdb scale_matrix={{Sx,0,0},{0,Sy,0},{0,0,1}};
return matrix_mul(scale_matrix,input);
}

VVdb Refx(VVdb input){
VVdb ref_matrix={{1,0,0},{0,-1,0},{0,0,1}};
return matrix_mul(ref_matrix,input);
}

VVdb Refy(VVdb input){
VVdb ref_matrix={{-1,0,0},{0,1,0},{0,0,1}};
return matrix_mul(ref_matrix,input);
}

VVdb Shx(VVdb input, db Shx, db Shy){
VVdb shear_matrix={{1,Shx,0},{0,1,0},{0,0,1}};
return matrix_mul(shear_matrix,input);
}

VVdb Shy(VVdb input, db Shx, db Shy){
VVdb shear_matrix={{1,0,0},{Shy,1,0},{0,0,1}};
return matrix_mul(shear_matrix,input);
}

VVdb Ref_about_axis(db slope, db intercept,VVdb input){
    return T(R(Refx(R(T(input,0,-intercept),(-1)*atan(slope)*180/PI)),atan(slope)*180/PI),0,intercept);
}
int main(){
VVdb curr={{40},{40},{1}};
VVdb tran=Ref_about_axis(1.5,19,curr);
show(tran);

return 0;   
}