#include<bits/stdc++.h>
using namespace std;
#define db double
#define pb push_back
#define matrix vector<vector<db>>
#define rrep(i,k,n) for(int i=k;i<n;i++)
#define rep(i,n) for(int i=0;i<n;i++)
#define all(a) a.begin(), a.end()
void show(matrix mat){
    cout<<"[";
    for(auto x:mat){
        cout<<"[ ";
        for(auto y:x){
            cout<<y<<", ";
        }
        cout<<"],\n";
    }
    cout<<"]\n";
}
void show(vector<db> v){
    cout<<"[";
    for(auto x:v){
        cout<<x<<", ";
    }
    cout<<"]\n";
}
matrix transpose(matrix mat){
    int n=mat.size();
    int m=mat[0].size();
    matrix ans;
    rep(j,m){
        vector<db> curr;
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
    matrix ans(n,vector<db>(m));
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
vector<db> mul(matrix A, vector<db> B){
    matrix C(1,vector<db>(B));
    matrix ans= transpose(mul(A,transpose(C)));
    return ans[0];
}
int main(){

    db d;
    cout<<"Enter the distance on z axis of the projection plane: ";
    cin>>d;

    vector<db> V={0,0,d};
    vector<db> C(3);
    cout<<"Enter the coordinates of COP:\n";
    rep(i,3)
    cin>>C[i];

    vector<db> P(4);
    cout<<"Enter the coordinates of the point:\n";
    rep(i,3)
    cin>>P[i];
    P[3]=1.0;
    vector<db> del(3);
    rep(i,3)
    del[i]=C[i]-V[i];

    db Q=sqrt(del[0]*del[0]+del[1]*del[1]+del[2]*del[2]);
    rep(i,3){
        del[i]=del[i]/Q;
    }

    matrix Mgen={{1,0,-del[0]/del[2],d*del[0]/del[2]},
                 {0,1,-del[1]/del[2],d*del[1]/del[2]},
                 {0,0,-d/(Q*del[2]),((d*d)/(Q*del[2]))+d},
                 {0,0,-1.0/(Q*del[2]),(d/(Q*del[2]))+1}
                };
    vector<db> W=mul(Mgen,P);
    cout<<"Mgen matrix:\n\n";
    show(Mgen);
    cout<<"\nHomogenous Coordinate System: ";
    show(W);
    rep(i,4){
        W[i]/=W[3];
    }
    cout<<"Cartesian Coordinate System: ";
    show(W);
    return 0;
}