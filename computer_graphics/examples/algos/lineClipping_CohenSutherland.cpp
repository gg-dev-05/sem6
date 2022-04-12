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
int rc(db X, db Y){
int rc1=0;
if(Y>Ymax)
    rc1|=(1<<3);
else if(Y<Ymin)
    rc1|=(1<<2);
if(X>Xmax)
    rc1|=(1<<1);
else if(X<Xmin)
    rc1|=(1<<0);
return rc1;
}
void cohenSutherlandClip(P p1, P p2) 
{ 
    int rc1 = rc(p1.x, p1.y); 
    int rc2 = rc(p2.x, p2.y); 
  
    bool accept = false; 
  
    while (true) {
        cout<<"rc1: "<<rc1<<"   rc2: "<<rc2<<"\n"; 
        if ((rc1 | rc2) == 0) { 
            accept = true; 
            break; 
        } 
        else if (rc1 & rc2) { 
            break; 
        } 
        else { 
            int code_out; 
            db x, y; 
  
            if (rc1 != 0) 
                code_out = rc1; 
            else
                code_out = rc2; 
  
            if (code_out & (1<<3)) { 
                x = p1.x + (p2.x - p1.x) * (Ymax - p1.y) / (p2.y - p1.y); 
                y = Ymax; 
            } 
            else if (code_out & (1<<2)) { 
                x = p1.x + (p2.x - p1.x) * (Ymin - p1.y) / (p2.y - p1.y); 
                y = Ymin; 
            } 
            else if (code_out & (1<<1)) { 
                y = p1.y + (p2.y - p1.y) * (Xmax - p1.x) / (p2.x - p1.x); 
                x = Xmax; 
            } 
            else if (code_out & (1<<0)) { 
                y = p1.y + (p2.y - p1.y) * (Xmin - p1.x) / (p2.x - p1.x); 
                x = Xmin; 
            } 
  
            if (code_out == rc1) { 
                p1.x = x; 
                p1.y = y; 
                rc1 = rc(p1.x, p1.y); 
            } 
            else { 
                p2.x = x; 
                p2.y = y; 
                rc2 = rc(p2.x, p2.y); 
            } 
        } 
    } 
    if (accept) { 
        cout<<"Final: (("<<p1.x<<", "<<p1.y<<") ("<<p2.x<<", "<<p2.y<<"))\n---------------\n"; 
    } 
    else
        cout<<"Rejected\n---------------\n"; 
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
    cout<<"Xmin: ";
    cin>>Xmin;
    cout<<"Xmax: ";
    cin>>Xmax;
    cout<<"Ymin: ";
    cin>>Ymin;
    cout<<"Ymax: ";
    cin>>Ymax;

    cout<<"\n---------------\n";
    rep(i,n){
        cout<<"Line"<<i+1<<"\n";
        cohenSutherlandClip(v[i].p1, v[i].p2);
    }

    return 0;
}