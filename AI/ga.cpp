#include<iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<algorithm>
//#include "ga.hpp"
using namespace std;

int iRand(int a,int b){
    int range,R;
    range=b-a+1;
    R=rand();
    R=R%range;
    return(a+R);
}
float fRand(float a,float b){
    float range,R;
    range=b-a;
    R=rand()/(float)RAND_MAX;
    R=R*range;
    return(a+R);
}

class graph{
    public:
        int **data;
        int n;
        graph(){
            data=nullptr;
            n=0;
        }
        graph(int nn){
            n=nn;
            data=new int*[n];
            for(int i=0;i<n;++i){
                data[i]=new int[n];
            }
        }
        vector<int> getAdjNodes(int nd){
            vector<int> r;
            int j;
            for(j=0;j<n;++j){
                if(j!=nd){
                    if(data[j][nd]>0 or data[nd][j]>0)
                        r.push_back(j);
                }
            }
            return r;
        }
        void getData(){
            int i,j;
            cout<<"[+] Reading graph...\n";
            for(i=0;i<n;++i){
                for(j=0;j<n;++j){
                    if(i>j){
                        cout<<"Enter the distance between node "<<i+1<<" and "<<j+1<<" : \n";
                        cin>>data[i][j];
                    }
                }
            }
        }
};


class chorom{
    public:
        vector<int> data;
        int fitness;
        int calFitness(graph g,int s,int e){
            int a,b,i=0,sum=0;
                do{
                    a=data[i];
                    b=data[++i];
                    sum+= g.data[a][b]>0 ? g.data[a][b] : g.data[b][a];
                } while(b!=e);
            return sum;
        }
        /* void crossWith(chorom<T> &p2){
            
        } */
        bool isLegal(graph g,int s,int e){
            int a,b,i=0;
            a=data[i++];
            if(a==s){
                while(1){
                    b=data[i++];
                    if(g.data[a][b]<=0 && g.data[b][a]<=0){
                        return(false);
                    }
                    if(b==e){
                        fitness=calFitness(g,s,e);
                        return(true);
                    }
                    if(i==data.size()){
                        return(false);
                    }
                    a=b;
                }
            }
            return(false);
        }
        void initRandlyLegaly(graph g,int s,int e){
            data.clear();
            vector<int> adjNodes;
            int rndn,nd=s;
            data.push_back(nd);
            do{
                adjNodes=g.getAdjNodes(nd);
                //do{
                    rndn=iRand(0,adjNodes.size()-1);
                    nd=adjNodes[rndn];
                //} while(count(data.begin(), data.end(),nd));
                data.push_back(nd);
            } while(nd!=e);
            fitness=calFitness(g,s,e);
        }
        friend ostream & operator<<(ostream &out,chorom &C){
            out<<"[";
            if(!C.data.empty()){
                for(int x : C.data) 
                    cout<<x<<","; 
                /* for(auto i = C.data.begin(); i != C.data.end(); ++i)
                    out<<*i<<","; */
            }
            else
                out<<"NULL";
            out<<"]";
            return out;
        }
};

class ppln{
    public:
        vector<chorom> data;
        void initRandly(graph grph,int s,int e){
            int i;
            chorom c;
            for(i=0;i<10;++i){
                c.initRandlyLegaly(grph,s,e);
                data.push_back(c);
            }
        }
        void print(){
            for(auto c : data){
                cout<<c<<c.fitness<<endl;
            }
        }
        /* ~ppln(){
            size=0;
            delete data;
        } */
};

int main(){
    srand(time(nullptr));
    typedef int gene;

    int non;
    cout<<"Enter no of nodes in the graph: \n";
    cin>>non;
    graph grph(non);
    grph.getData();

    int s,e;
    cout<<"Enter source node: ";
    cin>>s;
    --s;
    cout<<"Enter destination node: ";
    cin>>e;
    --e;

    /* chorom c;
    c.data.push_back(4);
    c.data.push_back(5);
    c.data.push_back(3);
    c.data.push_back(2);
    c.data.push_back(1);
    cout<<c.isLegal(grph,s,e)<<endl; */

    /* vector<int> adj;
    adj=grph.getAdjNodes(2);
    for(int x : adj)
        cout<<x<<"-"; */

    /* chorom c2;
    c2.initRandlyLegaly(grph,s,e);
    cout<<c2; */

    ppln pop;
    pop.initRandly(grph,s,e); //non as choromosome size
    pop.print();
    return 0;
}