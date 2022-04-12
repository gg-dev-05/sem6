#include<bits/stdc++.h>
using namespace std;
#define db double
struct P{
    db x;
    db y;
};
db m,c,dx,dy;
db fun(db X,db Y)
{
    return dy*X-dx*Y+c*dx;
}
int main(){
P f,s;
cout<<"Enter x and y coordinates of first point: ";
cin>>f.x>>f.y;
cout<<"Enter x and y coordinates of second point: ";
cin>>s.x>>s.y;
c=(f.y*s.x-s.y*f.x)/(s.x-f.x);
dx=s.x-f.x;
dy=s.y-f.y;
db d_new=fun(f.x+1,f.y+0.5),d_old;
P new_c,old_c;
new_c.x=f.x;
new_c.y=f.y;

int k=0;
cout<<"i | Xi | Yi | di | di+1 | Xi+1 | Yi+1\n";
while(new_c.x < s.x){
    old_c=new_c;
    d_old=d_new;

    if(d_new<0){
        d_new+=dy;
    }else{
        d_new+=dy-dx;
        new_c.y+=1.0;
    }
    new_c.x+=1.0;
    cout<<k<<"    "<<old_c.x<<"    "<<old_c.y<<"    "<<d_old<<"    "<<d_new<<"    "<<new_c.x<<"    "<<new_c.y<<"\n";
    k++;
}
return 0;
}