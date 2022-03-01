#include<bits/stdc++.h>
using namespace std;
#define db double
double PI=3.141592;
#define rep(i,n) for(int i=0;i<n;i++)
#define VVdb vector<vector<db>>
VVdb I={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
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

VVdb T(VVdb input, db tx, db ty, db tz){
VVdb trans_matrix={{1,0,0,tx},{0,1,0,ty},{0,0,1,tz},{0,0,0,1}};
return matrix_mul(trans_matrix,input);
}

VVdb Rz(VVdb input, db theta){
db radian=PI*theta/180;
VVdb rot_matrix={{cos(radian),-sin(radian),0,0},{sin(radian),cos(radian),0,0},{0,0,1,0},{0,0,0,1}};
return matrix_mul(rot_matrix,input);
}

VVdb Rx(VVdb input, db theta){
db radian=PI*theta/180;
VVdb rot_matrix={{1,0,0,0},{0,cos(radian),-sin(radian),0},{0,sin(radian),cos(radian),0},{0,0,0,1}};
return matrix_mul(rot_matrix,input);
}

VVdb Ry(VVdb input, db theta){
db radian=PI*theta/180;
// db a=cos(radian);
VVdb rot_matrix={{cos(radian),0,sin(radian),0},{0,1,0,0},{-sin(radian),0,cos(radian),0},{0,0,0,1}};
return matrix_mul(rot_matrix,input);
}

VVdb S(VVdb input, db Sx, db Sy, db Sz){
VVdb scale_matrix={{Sx,0,0,0},{0,Sy,0,0},{0,0,Sz,0},{0,0,0,1}};
return matrix_mul(scale_matrix,input);
}

VVdb Refxy(VVdb input){
VVdb ref_matrix={{1,0,0,0},{0,1,0,0},{0,0,-1,0},{0,0,0,1}};
return matrix_mul(ref_matrix,input);
}

VVdb Refyz(VVdb input){
VVdb ref_matrix={{-1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
return matrix_mul(ref_matrix,input);
}

VVdb Refxz(VVdb input){
VVdb ref_matrix={{1,0,0,0},{0,-1,0,0},{0,0,1,0},{0,0,0,1}};
return matrix_mul(ref_matrix,input);
}

VVdb Shxy(VVdb input, db Shx, db Shy){
VVdb shear_matrix={{1,0,Shx,0},{0,1,Shy,0},{0,0,1,0},{0,0,0,1}};
return matrix_mul(shear_matrix,input);
}

VVdb Shyz(VVdb input, db Shy, db Shz){
VVdb shear_matrix={{1,0,0,0},{Shy,1,0,0},{Shz,0,1,0},{0,0,0,1}};
return matrix_mul(shear_matrix,input);
}

VVdb Shzx(VVdb input, db Shz, db Shx){
VVdb shear_matrix={{1,Shx,0,0},{0,1,0,0},{0,Shz,1,0},{0,0,0,1}};
return matrix_mul(shear_matrix,input);
}

VVdb Rot_about_axis(vector<db> from, vector<db> dir, VVdb input, db theta){
    db D1=sqrt(dir[0]*dir[0]+dir[2]*dir[2]);
    db angle_along_x=(db)180/PI*atan(dir[1]/D1);
    db angle_along_y=(db)180/PI*(PI/2-asin(dir[2]/D1));
    return T(Ry(Rx(Rz(Rx(Ry(T(input,-from[0],-from[1],-from[2]),-angle_along_y),angle_along_x),theta),-angle_along_x),angle_along_y),from[0],from[1],from[2]);
}

VVdb Ref_about_plane(vector<db> params,VVdb input){
    db a=params[0];
    db b=params[1];
    db c=params[2];
    db d=params[3];
    db constant=2/(pow(a,2)+pow(b,2)+pow(c,2));
    
    VVdb ref_matrix={{1-constant*pow(a,2),(-1)*constant*a*b,(-1)*constant*a*c,constant*a*d},
                     {(-1)*constant*a*b,1-constant*pow(b,2),(-1)*constant*b*c,constant*b*d},
                     {(-1)*constant*a*c,(-1)*constant*b*c,1-constant*pow(c,2),constant*c*d},
                     {0,0,0,1}   
                    };
    return matrix_mul(ref_matrix,input);
}
int main(){

    VVdb curr={{0.7,-0.6},{-0.8,0.7},{-0.9,-0.8},{1,1}};
    VVdb tran=S(T(curr,0,0,0.5),2,2,2);
    show(tran);
    return 0;
}
