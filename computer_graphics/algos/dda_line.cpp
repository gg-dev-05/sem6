#include<bits/stdc++.h>
using namespace std;
struct P{
    double x;
    double y;
};
double m,c;

void show(P o,P n){
    cout<<setprecision(2)<<fixed<<"("<<o.x<<", "<<o.y<<", "<<n.x<<", "<<n.y<<", "<<round(n.x)<<", "<<round(n.y)<<")\n";
}
int main(){
P f,s;
cout<<"Enter x and y coordinates of first point: ";
cin>>f.x>>f.y;
cout<<"Enter x and y coordinates of second point: ";
cin>>s.x>>s.y;

double dx=s.x-f.x;
double dy=s.y-f.y;
double steps;

if(abs(dx)>abs(dy))
steps=abs(dx);
else
steps=abs(dy);

double x_incr=dx/steps;
double y_incr=dy/steps;

P old_c,new_c;
new_c.x=f.x;
new_c.y=f.y;


cout<<"Xold||Yold||Xnew||Ynew||round(x)||round(y)\n";
for(int k=1;k<=(int)steps;k++){
    old_c=new_c;
    new_c.x+=x_incr;
    new_c.y+=y_incr;
    show(old_c,new_c);
}
return 0;
}