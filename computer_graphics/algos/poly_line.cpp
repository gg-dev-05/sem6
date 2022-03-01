#include<bits/stdc++.h>
using namespace std;
struct P{
    double x;
    double y;
};
double m,c;
void show(double p){
    cout<<"("<<p<<", "<<round(m*p+c)<<")\n";
}
void showy(double p){
    cout<<"("<<round((p-c)/m)<<", "<<p<<")\n";
}
int main(){
P f,s;
cout<<"Enter x and y coordinates of first point: ";
cin>>f.x>>f.y;
cout<<"Enter x and y coordinates of second point: ";
cin>>s.x>>s.y;

m=(s.y-f.y)/(s.x-f.x);
c=(f.y*s.x-s.y*f.x)/(s.x-f.x);

double start;

if(abs(m)<=1){
start=f.x;
while(start<=s.x){
show(start);
start+=1.0;    
}
}else{
start=f.y;
while(start<=s.y){
showy(start);
start+=1.0;    
}
}

return 0;
}