#include<bits/stdc++.h>
#include <math.h>
using namespace std;
#define db double
struct P{
    double x;
    double y;
};

double PI=3.141592;
double r;
P center;
bool check(int octa, P p){
    switch(octa){
        case 1:
            return p.y > p.x;
        case 2:
            return p.x > p.y;
        case 3:
            return p.x > -p.y;
        case 4:
            return -p.y > p.x;
        case 5:
            return -p.y > -p.x;
        case 6:
            return -p.x > -p.y;
        case 7:
            return -p.x > p.y;
        case 8:
            return p.y > -p.x;
    }
}
void change(int octa, db &p_new, P &new_c){
    switch(octa){
        case 1:
            if(p_new < 0)
            p_new += 4*new_c.x +6;
            else{
                p_new+=4*(new_c.x-new_c.y)+10;
                new_c.y-=1.0;
            }
            new_c.x+=1.0;
            break;
        case 2:
            if(p_new < 0)
            p_new += 4*new_c.y +6;
            else{
                p_new+=4*(new_c.y-new_c.x)+10;
                new_c.x-=1.0;
            }
            new_c.y+=1.0;
            break;
        case 3:
            if(p_new < 0)
            p_new += -4*new_c.y +6;
            else{
                p_new+=4*(-new_c.y-new_c.x)+10;
                new_c.x-=1.0;
            }
            new_c.y-=1.0;
            break;
        case 4:
            if(p_new < 0)
            p_new += 4*new_c.x +6;
            else{
                p_new+=4*(new_c.x+new_c.y)+10;
                new_c.y+=1.0;
            }
            new_c.x+=1.0;
            break;
        case 5:
            if(p_new < 0)
            p_new += -4*new_c.x +6;
            else{
                p_new+=4*(-new_c.x+new_c.y)+10;
                new_c.y+=1.0;
            }
            new_c.x-=1.0;
            break;
        case 6:
            if(p_new < 0)
            p_new += -4*new_c.y +6;
            else{
                p_new+=4*(-new_c.y+new_c.x)+10;
                new_c.x+=1.0;
            }
            new_c.y-=1.0;
            break;
        case 7:
            if(p_new < 0)
            p_new += 4*new_c.y +6;
            else{
                p_new+=4*(new_c.y+new_c.x)+10;
                new_c.x+=1.0;
            }
            new_c.y+=1.0;
            break;
        case 8:
            if(p_new < 0)
            p_new += -4*new_c.x +6;
            else{
                p_new+=4*(-new_c.x-new_c.y)+10;
                new_c.y-=1.0;
            }
            new_c.x-=1.0;
            break;
    }
}
int main(){
    cout<<"Enter center: ";
    cin>>center.x>>center.y;
    cout<<"Enter radius: ";
    cin>>r;
    int octa;
    cout<<"Enter octant: ";
    cin>>octa;
    P new_c, old_c;

    switch(octa){
        case 1:
            new_c.x=0;
            new_c.y=r;
            break;
        case 2:
            new_c.x=r;
            new_c.y=0;
            break;
        case 3:
            new_c.x=r;
            new_c.y=0;
            break;
        case 4:
            new_c.x=0;
            new_c.y=-r;
            break;
        case 5:
            new_c.x=0;
            new_c.y=-r;
            break;
        case 6:
            new_c.x=-r;
            new_c.y=0;
            break;
        case 7:
            new_c.x=-r;
            new_c.y=0;
            break;
        case 8:
            new_c.x=0;
            new_c.y=r;
            break;
        default:
            cout<<"Enter a valid octant\n";
            break;
    }
    
    db p_new = 3-2*r, p_old;

    int k=0;
    cout<<"i | Xi | Yi | Pi | Pi+1 | Xi+1 | Yi+1\n";

    while(check(octa,new_c)){
        old_c=new_c;
        p_old=p_new;
        change(octa, p_new,new_c);
        cout<<k<<"    "<<old_c.x + center.x<<"    "<<old_c.y+center.y<<"    "<<p_old<<"    "<<p_new<<"    "<<new_c.x + center.x<<"    "<<new_c.y+center.y<<"\n";
        k++;
    }
return 0;
}