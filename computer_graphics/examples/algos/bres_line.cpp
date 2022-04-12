#include<bits/stdc++.h>
using namespace std;
#define db double
struct P{
    db x;
    db y;
};
db m,c;
int main(){
P f,s;
cout<<"Enter x and y coordinates of first point: ";
cin>>f.x>>f.y;
cout<<"Enter x and y coordinates of second point: ";
cin>>s.x>>s.y;
db dx,dy;
dx=abs(s.x-f.x);
dy=abs(s.y-f.y);

P new_c, old_c;
new_c.x=f.x;
new_c.y=f.y;

if(dy>dx){
    swap(f.x,f.y);
    swap(s.x,s.y);
    swap(dx,dy);
    swap(new_c.x,new_c.y);
}

db p_new=2*dy-dx,p_old;
cout<<"k | Xi | Yi | Pi | Pi+1 | Xi+1 | Yi+1\n";
for(int k=1;k<=(int)dx;k++){
old_c=new_c;
p_old=p_new;
if(p_new<(db)0){
    if(new_c.x<s.x)
    new_c.x+=1.0;
    else
    new_c.x-=1.0;
    p_new+=2*dy;
}else{
    if(new_c.y<s.y)
    new_c.y+=1.0;
    else
    new_c.y-=1.0;
    
    if(new_c.x<s.x)
    new_c.x+=1.0;
    else
    new_c.x-=1.0;
    
    p_new+=2*(dy-dx);
}

if(dy>dx)
cout<<k-1<<"    "<<old_c.y<<"    "<<old_c.x<<"    "<<p_old<<"    "<<p_new<<"    "<<new_c.y<<"    "<<new_c.x<<"\n";
else
cout<<k-1<<"    "<<old_c.x<<"    "<<old_c.y<<"    "<<p_old<<"    "<<p_new<<"    "<<new_c.x<<"    "<<new_c.y<<"\n";
}
return 0;
}