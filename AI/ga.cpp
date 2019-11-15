#include<iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
//#include<algorithm> 
//#include<queue> 
#include<functional> 
#include<iterator>
#include<utility> 
#include "pqueue.hpp"
#define POP_SIZE 10
#define MUT_PROB 0.2
#define CRS_PROB 0.5
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
void doWithProb(double p,function<void()> callback){
    float pr=fRand(0,1);
    if(pr<=p)
        callback();
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
                        cout<<"Enter the distance between node "<<i<<" and "<<j<<" : \n";
                        cin>>data[i][j];
                    }
                }
            }
        }
};


class chorom{
    public:
        vector<int> data;
        double fitness;
        chorom(){
            fitness=0;
        }
        double getFitness(){
            return fitness;
        }
        chorom crossWith(chorom &p2){
            typedef vector<int>::iterator itr;
            typedef pair<itr,itr> itPair;
            itr i,j,prevJ;
            itPair oldCrsPoint;
            chorom child;
            float rF;

            child.data.push_back(data[0]);
            i=data.begin();
            j=p2.data.begin();
            oldCrsPoint.first=i++;
            oldCrsPoint.second=j++;
            prevJ=j;
            do{
                j=prevJ;

                do{
                        //cout<<"point: ["<<*i<<","<<*j<<"]";
                    if(*i==*j){
                        //cout<<" -ok";
                        rF=fRand(0,1);
                        if(rF<=0.5)
                            child.data.insert(child.data.end(),oldCrsPoint.first+1,i+1);
                        else
                            child.data.insert(child.data.end(),oldCrsPoint.second+1,j+1);
                        oldCrsPoint.first=i;
                        oldCrsPoint.second=j;
                        prevJ=j+1;
                        ++i;
                    }
                        //cout<<endl;
                } while(++j!=p2.data.end());

                if(i==data.end()){
                    //cout<<"END\n";
                    return child;
                }
                //cout<<"--------------\n";
                ++i;
            } while(1);

            //return child;
        }
        bool isLegal(graph g,int s,int e){
            int a,b,i=0;
            if(data.size()>0){
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
            }
            return(false);
        }
        void initRandlyLegaly(graph g,int s,int e){
            data.clear();
            vector<int> adjNodes;
            int rand_no,nod=s;
            data.push_back(nod);
            do{
                adjNodes=g.getAdjNodes(nod);
                //do{
                    rand_no=iRand(0,adjNodes.size()-1);
                    nod=adjNodes[rand_no];
                //} while(count(data.begin(), data.end(),nd));
                data.push_back(nod);
            } while(nod!=e);
            fitness=calFitness(g,s,e);
        }
        bool operator>(chorom &c){
            if(fitness>c.fitness)
                return true;
            else
                return false;
        }
        bool operator==(chorom &c){
            if(data==c.data)
                return true;
            else
                return false;
        }
        friend ostream & operator<<(ostream &out,chorom &C){
            out<<"[";
            if(!C.data.empty()){
                for(int x : C.data) 
                    cout<<x<<",";
            }
            else
                out<<"NULL";
            out<<"]";
            return out;
        }
        double calFitness(graph g,int s,int e){
            int a,b,i=0,sum=0;
                do{
                    a=data[i];
                    b=data[++i];
                    sum+= g.data[a][b]>0 ? g.data[a][b] : g.data[b][a];
                } while(b!=e);
            fitness=1/(double)sum;
            return fitness;
        }
};

class ppln{
    public:
        pQueue<chorom> data;
        double tFitness;
        ppln(){
            tFitness=0;
        }
        int getSize(){
            return data.size();
        }
        void clear(){
            tFitness=0;
            data.clear();
        }
        void initRandly(graph grph,int s,int e,int size){
            int i;
            chorom c;
            for(i=0;i<size;++i){
                c.initRandlyLegaly(grph,s,e);
                add(c);
            }
            //make_heap(data.begin(), data.end());
        }
        double totFitness(){
            /* double tFitness=0;
            data.forEach([&](chorom c){
                tFitness+=c.fitness;
            }); */
            return tFitness;
        }
        void add(chorom c){
            data.add(c);
            tFitness+=c.getFitness();
            //make_heap(data.begin(), data.end());
        }
        void print(){
            data.forEach([&](chorom c){
                cout<<c<<c.getFitness()<<endl;
            });
            /* for(auto c : data){
                cout<<c<<c.fitness<<endl;
            } */
        }
        chorom& getRandly(){
            float arrow=fRand(0,359);
            double angl=0;
            vector<float> angles;
            static chorom r;
            bool f=true;
            data.forEach([&](chorom c){
                angl+=(c.getFitness()/tFitness)*360;
                if(arrow<=angl and f){
                    r=c;
                    f=false;
                }
            });
            return r;
        }
        ppln getTop(int n){
            ppln p;
            int i=1;
            data.forEach([&](chorom c){
                if(i<=n)
                    p.add(c);
                ++i;
            });
            return p;
        }
};

chorom runGeneticAlgo(ppln &pop,graph g,int s,int e,int itr){
    ppln newPop;
    chorom p1,p2,child;
    for(int i=1;i<=itr;++i){
        newPop.clear();
        //newPop=pop;
        for(int j=0;j<pop.getSize();++j){
            p1=pop.getRandly();
            p2=pop.getRandly();
            child=p1.crossWith(p2);
            child.calFitness(g,s,e);
            //doWithProb(MUT_PROB,[&](){
            //    child.mutate(g);
            //});
            newPop.add(child);
        }
        //pop=newPop.getTop(pop.getSize());
        pop=newPop;
        cout<<"Gen: ["<<i<<"] Avg Fitness: "<<pop.totFitness()/pop.getSize()<<endl;
        //cout<<"New pop size:"<<newPop.data.size()<<endl;
    }
        //pop.print();
    return pop.data[0];
}

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
    cout<<"Enter destination node: ";
    cin>>e;
    cout<<endl;

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
    pop.initRandly(grph,s,e,POP_SIZE);
    chorom fit;
    fit=runGeneticAlgo(pop,grph,s,e,20);
    cout<<"Fit: "<<fit;
    
    doWithProb(0.5,[&](){
        cout<<"do\n";
    });
    return 0;
}