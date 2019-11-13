#include<iostream>
#include<cstdlib>
#include<ctime>
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

template<typename T>
class chorom{
    public:
        T *data;
        int length;
        int fitness;
        chorom(){
            length=0;
            fitness=0;
            data=nullptr;
        }
        chorom(int l){
            length=l;
            data=new T[l];
        }

        int calFitness(graph g,int s,int e){
            int a,b,i=0,sum=0;
                do{
                    a=data[i];
                    b=data[++i];
                    sum+= g.data[a][b]>0 ? g.data[a][b] : g.data[b][a];
                } while(b!=e);
            return sum;
        }
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
                    if(i==length){
                        return(false);
                    }
                    a=b;
                }
            }
            return(false);
        }
        void initRandlyLegaly(graph g,int s,int e){
            do{
                initRandly();
            } while(!isLegal(g,s,e));
        }
        void initRandly(){
            int i;
            if(length>0){
                for(i=0;i<length;++i){
                    data[i]=iRand(0,length-1);
                }
            }
            else{
                cout<<"ERROR::Choromose not initilized.\n";
            }
        }
        void get(){
            for(int i=0;i<length;++i){
                cin>>data[i];
            }
        }
        friend ostream & operator<<(ostream &out,chorom<T> &C){
            int i;
            out<<"[";
            if(C.length>1){
                for(i=0;i<C.length-1;++i){
                    out<<C.data[i]<<",";
                }
                out<<C.data[i];
            }
            else
                out<<"NULL";
            out<<"]";
            return out;
        }
        /* ~chorom(){
            length=0;
            delete data;
        } */
};

template<typename T>
class ppln{
    public:
        chorom<T> *data;
        int size;
        ppln(){
            data=nullptr;
            size=0;
        }
        ppln(int s){
            size=s;
            data=new chorom<T>[s];
        }
        void initRandly(int cS,graph grph,int s,int e){
            int i;
            for(i=0;i<size;++i){
                data[i]=chorom<T>(cS);
                data[i].initRandlyLegaly(grph,s,e);
            }
        }
        void print(){
            for(int i=0;i<size;++i){
                cout<<data[i]<<data[i].fitness<<endl;
            }
        }
        ~ppln(){
            size=0;
            delete data;
        }
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

    /* chorom<gene> c(non);
    c.initRandlyLegaly(grph,s,e);
    cout<<c; */

    ppln<gene> pop(10);
    pop.initRandly(non,grph,s,e); //non as choromosome size
    pop.print();
    return 0;
}