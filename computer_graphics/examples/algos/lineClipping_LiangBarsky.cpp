#include<bits/stdc++.h>
using namespace std;
#define db double
#define rep(i,n) for(int i=0;i<n;i++)
struct P{
    db x;
    db y;
};
struct Line{
    P p1;
    P p2;
};
int n;
db Xmin, Xmax, Ymin, Ymax;
int main(){
    cout<<"Enter number of lines: ";
    cin>>n;
    cout<<"Enter first and second end points in the form x1 y1 x2 y2:\n";
    vector<Line> v(n);
    rep(i,n){
        Line l;
        cin>>l.p1.x>>l.p1.y>>l.p2.x>>l.p2.y;
        v[i]=l;
    }
    cout<<"Xmin: ";
    cin>>Xmin;
    cout<<"Xmax: ";
    cin>>Xmax;
    cout<<"Ymin: ";
    cin>>Ymin;
    cout<<"Ymax: ";
    cin>>Ymax;

    cout<<"\n---------------\n";
    map<int, string> mp;
    mp[0]="L";
    mp[1]="R";
    mp[2]="B";
    mp[3]="T";
    map<string,string> mp1;
    mp1["L"]="t1";
    mp1["R"]="t2";
    mp1["B"]="t3";
    mp1["T"]="t4";
    cout<<"tmin=max(0, All tPE)\ntmax=min(1, All tPL)\n---------------\n";
    rep(i,n){
        cout<<"Line"<<i+1<<"\n";
        db p[4], q[4];
        db x1=v[i].p1.x;
        db y1=v[i].p1.y;
        db x2=v[i].p2.x;
        db y2=v[i].p2.y;
        db dx=x2-x1;
        db dy=y2-y1;
        p[0]=-dx; q[0]=x1-Xmin;
        p[1]= dx; q[1]=Xmax-x1;
        p[2]=-dy; q[2]=y1-Ymin;
        p[3]= dy; q[3]=Ymax-y1;
        cout<<"p: "<<p[0]<<" "<<p[1]<<" "<<p[2]<<" "<<p[3]<<"\n";
        cout<<"q: "<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<"\n";
        

        db tmin=1;
        db tmax=0;

        bool flag =true;
        rep(j,4){
            cout<<endl<<mp[j]<<": "<<mp1[mp[j]]<<": ";
            if(p[j]==0){
                if(q[j]<0){
                    flag=false;
                    break;
                }
            }else if(p[j]<0){
                db t=q[j]/p[j];
                cout<<"PE: "<<t<<"\n";
                if(t>tmax)
                    tmax=t;
            }else{
                db t=q[j]/p[j];
                cout<<"PL: "<<t<<"\n";
                if(t<tmin)
                    tmin=t;
            }
        }
        
        if(tmax > tmin)
            flag=false;
        
        cout<<"\ntmax: "<<max(tmax,tmin)<<"\ntmin: "<<min(tmin,tmax)<<"\n\n";
        if(flag){
            cout<<"Final: (("<<x1+dx*tmax<<", "<<y1+dy*tmax<<") ("<<x1+dx*tmin<<", "<<y1+dy*tmin<<"))\n---------------\n";
        }else{
            cout<<"Rejected\n---------------\n";
        }
    }
    return 0;
}
