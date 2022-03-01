#include<bits/stdc++.h>
using namespace std;
#define db double
#define pll pair<db,db>
#define Vpll vector<pll>
#define f first
#define s second
#define rep(i,n) for(int i=0;i<n;i++)
#define rrep(i,k,n) for(int i=k;i<=n;i++)
int n;

struct E{
    db Ymax;
    db Xmin;
    db dx;
    db dy;
    string name;
    E* next;
};
bool comp(pair<int,pair<char,pll>> a, pair<int,pair<char,pll>> b){
    if(a.s.s.s!=b.s.s.s){
        return a.s.s.s<b.s.s.s;
    }else{
        return a.s.s.f<b.s.s.f;
    }
}
bool comp2(E a, E b){
    return a.Xmin < b.Xmin;
}
int main(){
    
    cout<<"Enter number of points: ";
    cin>>n;
    vector<pair<int,pair<char,pll>>> v(n);
    map<char,int> mp;
    cout<<"Enter the points in anti-clockwise manner(Eg: A 2 3)\n";
    rep(i,n){
        v[i].first=i;
        cin>>v[i].s.f>>v[i].s.s.f>>v[i].s.s.s;
        mp[v[i].s.f]=i;
    }
    vector<pair<int,pair<char,pll>>> w(v);
    sort(w.begin(),w.end(),comp);
    
    int height=w[n-1].s.s.s-w[0].s.s.s +1;
    vector<E*> table(height, NULL);
    vector<vector<E>> active_table(height);

    int i=0;
    rrep(y,(int)w[0].s.s.s,(int)w[n-1].s.s.s){
        if((int)w[i].s.s.s==y){
            int index=w[i].first;
            int left=(index-1+n)%n;
            int right=(index+1)%n;
            if(v[left].s.s.s>v[index].s.s.s && v[right].s.s.s>=v[index].s.s.s){
                E left_edge,right_edge;
                string edge1="",edge2="";
                
                left_edge.Ymax=v[left].s.s.s;
                right_edge.Ymax=v[right].s.s.s;

                left_edge.Xmin=v[index].s.s.f;
                right_edge.Xmin=v[index].s.s.f;

                edge1+=v[left].s.f;
                edge1+=v[index].s.f;
                edge2+=v[index].s.f;
                edge2+=v[right].s.f;

                left_edge.name=edge1;
                right_edge.name=edge2;

                left_edge.dx=v[mp[edge1[1]]].s.s.f-v[mp[(char)edge1[0]]].s.s.f;
                left_edge.dy=v[mp[edge1[1]]].s.s.s-v[mp[(char)edge1[0]]].s.s.s;
                
                right_edge.dx=v[mp[edge2[1]]].s.s.f-v[mp[(char)edge2[0]]].s.s.f;
                right_edge.dy=v[mp[edge2[1]]].s.s.s-v[mp[(char)edge2[0]]].s.s.s;
                left_edge.next=NULL;
                right_edge.next=NULL;

                if(v[left].s.s.f>v[right].s.s.f)
                swap(left_edge,right_edge);

                if(table[y-(int)w[0].s.s.s]==NULL){
                    table[y-(int)w[0].s.s.s]=new E;
                    *table[y-(int)w[0].s.s.s]=left_edge;
                    table[y-(int)w[0].s.s.s]->next=new E;
                    *(table[y-(int)w[0].s.s.s]->next)=right_edge;
                    table[y-(int)w[0].s.s.s]->next->next=NULL;
                }else{
                    E *to=table[y-(int)w[0].s.s.s];
                    while(to->next!=NULL)
                        to=to->next;
                    to->next=new E;
                    *(to->next)=left_edge;
                    to->next->next=new E;
                    *(to->next->next)=right_edge;
                    to->next->next->next=NULL;
                }

            }else if(v[left].s.s.s>v[index].s.s.s && v[right].s.s.s<v[index].s.s.s){
                E left_edge;
                string edge="";
                left_edge.Ymax=v[left].s.s.s;
                left_edge.Xmin=v[index].s.s.f;
                edge+=v[left].s.f;
                edge+=v[index].s.f;
                left_edge.name=edge;
                left_edge.next=NULL;
                left_edge.dx=v[mp[edge[1]]].s.s.f-v[mp[(char)edge[0]]].s.s.f;
                left_edge.dy=v[mp[edge[1]]].s.s.s-v[mp[(char)edge[0]]].s.s.s;

                if(table[y-(int)w[0].s.s.s]==NULL){
                    table[y-(int)w[0].s.s.s]=new E;
                    *table[y-(int)w[0].s.s.s]=left_edge;
                    table[y-(int)w[0].s.s.s]->next=NULL;
                }else{
                    E *to=table[y-(int)w[0].s.s.s];
                    while(to->next!=NULL)
                        to=to->next;
                    to->next=new E;
                    *(to->next)=left_edge;
                    to->next->next=NULL;
                }
            }else if(v[right].s.s.s>=v[index].s.s.s && v[left].s.s.s<=v[index].s.s.s){
                E right_edge;
                string edge="";
                right_edge.Ymax=v[right].s.s.s;
                right_edge.Xmin=v[index].s.s.f;
                edge+=v[index].s.f;
                edge+=v[right].s.f;
                right_edge.name=edge;
                right_edge.next=NULL;
                right_edge.dx=v[mp[edge[1]]].s.s.f-v[mp[(char)edge[0]]].s.s.f;
                right_edge.dy=v[mp[edge[1]]].s.s.s-v[mp[(char)edge[0]]].s.s.s;

                if(table[y-(int)w[0].s.s.s]==NULL){
                    table[y-(int)w[0].s.s.s]=new E;
                    *table[y-(int)w[0].s.s.s]=right_edge;
                    table[y-(int)w[0].s.s.s]->next=NULL;
                }else{
                    E *to=table[y-(int)w[0].s.s.s];
                    while(to->next!=NULL)
                        to=to->next;
                    to->next=new E;
                    *(to->next)=right_edge;
                    to->next->next=NULL;
                }
            }
            i++;
            if(i<n && i>0){
                if(w[i].s.s.s==w[i-1].s.s.s){
                    y--;
                }
            }
        }
    }
    cout<<"EdgeName | Ymax | Xmin | dx | dy\n";
    for(int i=height-1;i>=0;i--){
        E *to=table[i];
        cout<<i+(int)w[0].s.s.s<<" ";
        while(to!=NULL){
            cout<<"-> ["<<to->name<<", "<<to->Ymax<<", "<<to->Xmin<<", "<<to->dx<<", "<<to->dy<<"] ";
            to=to->next;
        }
        cout<<"-> NULL\n";
    }

    cout<<"\n\n--------------Active Edge Table--------------\n\n";

    vector<E> curr;
    rep(i,height){
        vector<E> temp;
        for(auto x:curr){
            if((int)x.Ymax!=i+(int)w[0].s.s.s && x.dy!=0){
                x.Xmin+=x.dx/x.dy;
                temp.push_back(x);
            }
        }
        E *to=table[i];
        while(to!=NULL){
            temp.push_back(*to);
            to=to->next;
        }
        curr=temp;
        sort(curr.begin(),curr.end(),comp2);
        active_table[i]=curr;
    }

    for(int i=height-1;i>=0;i--){
        cout<<i+(int)w[0].s.s.s<<" ";
        for(auto x:active_table[i]){
            cout<<"-> ["<<x.name<<", "<<x.Ymax<<", "<<x.Xmin<<", "<<x.dx<<", "<<x.dy<<"] ";
        }
        cout<<"-> NULL\n";
    }
return 0;
}