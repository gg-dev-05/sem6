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
pair<db,db> dot(pair<db,db> nor, pair<db,db> p){
    if(nor.first*p.first+nor.second*p.second > 0)
        return {-nor.first, -nor.second};
    return nor;
}
int n,m;
void show(pair<db,db> a){
    cout<<"("<<a.first<<", "<<a.second<<")\n";
}
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
cout<<"Enter the number of points of the polygon window: ";
cin>>m;
vector<P> a(m);
cout<<"Start entering the points in clockwise manner (x, y)...\n";
rep(i,m){
    cin>>a[i].x>>a[i].y;
}
cout<<"\n---------------\n";
rep(i,n){
    cout<<"Line"<<i+1<<"\n";
    db x1=v[i].p1.x;
    db y1=v[i].p1.y;
    db x2=v[i].p2.x;
    db y2=v[i].p2.y;
    pair<db,db> u={x2-x1,y2-y1};
    db tmin=0.0, tmax=1.0;
    rep(j,m){

        pair<db,db> w={a[j].x-a[(j-1+m)%m].x, a[j].y-a[(j-1+m)%m].y};
        cout<<"From: ";
        pair<db,db> E1={a[(j-1+m)%m].x,a[(j-1+m)%m].y}, E2={a[j].x,a[j].y};
        show(E1);
        cout<<"To: ";
        show(E2);
        pair<db,db> nor={-w.second, w.first};
        nor=dot(nor,{a[(j+1+m)%m].x-a[j].x,a[(j+1+m)%m].y-a[j].y});
        cout<<"Normal: ";
        show(nor);
        cout<<"PEi: ("<<a[j].x<<", "<<a[j].y<<")\n";
        db NdotD=nor.first*u.first+nor.second*u.second;
        cout<<"N.D: "<<NdotD<<"\n";
        
        if(NdotD==0)
        continue;
        db NdotP1minusPE=(nor.first*(x1-a[j].x)+nor.second*(y1-a[j].y));
        cout<<"N.(P1-PE): "<<NdotP1minusPE<<"\n";
        db t=(-1)*(NdotP1minusPE/(NdotD));
        if(NdotD < 0){
            //Potential Entering
            cout<<"PE: "<<t<<"\n";
            tmin=max(tmin, t);
        }else{
            //Potential Leaving
            cout<<"PL: "<<t<<"\n";
            tmax=min(tmax,t);
        }
        cout<<"\n---------\n\n";
    }
    cout<<"tmin: "<<tmin<<"  tmax: "<<tmax<<"\n";
    if(tmax<tmin){
        cout<<"Rejected\n---------------\n";
        continue;
    }
    cout<<"Final: (("<<x1+u.first*tmin<<", "<<y1+u.second*tmin<<") ("<<x1+u.first*tmax<<", "<<y1+u.second*tmax<<"))\n---------------\n";
}
return 0;
}