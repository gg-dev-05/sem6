#include<bits/stdc++.h>
#include <math.h>
using namespace std;
struct P{
    double x;
    double y;
};

double PI=3.141592;
double r;
P center;
void show(double angle){
cout<<"("<<center.x+r*cos(angle)<<", "<<center.y+r*sin(angle)<<")\n";
}
int main(){
    cout<<"Enter center: ";
    cin>>center.x>>center.y;
    cout<<"Enter radius: ";
    cin>>r;
    double theta=1/r;

    double ini=PI/2;
    while(ini>=PI/4){
        show(ini);
        ini-=theta;
    }
    return 0;
}