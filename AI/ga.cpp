#include<iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<iomanip>
#include<algorithm> 
//#include<queue> 
#include<functional> 
#include<iterator>
#include<utility> 
#include<fstream>
#include "pqueue.hpp"
#define POP_SIZE 10
#define MUT_PROB 0.5
//#define CRS_PROB 0.5
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
            r.clear();
            for(j=0;j<n;++j){
                if(j!=nd){
                    if(isConnected(j,nd))
                        r.push_back(j);
                }
            }
            return r;
        }
        bool isConnected(int a,int b){
            return data[a][b]>0 or data[b][a]>0 ;
        }
        int getCost(int a,int b){
            if(isConnected(a,b))
                return data[a][b]>0 ? data[a][b] : data[b][a];
            else
                return -1;
        }
        void getData(){
            int i,j;
            cout<<"[+] Reading graph...\n";
            for(i=0;i<n;++i){
                for(j=0;j<n;++j){
                    //if(i>j){
                        //cout<<"Enter the distance between node "<<i<<" and "<<j<<" : \n";
                        cin>>data[i][j];
                    //}
                }
            }
        }
};


class chorom{
    public:
        vector<int> data;
        long double fitness;
        chorom(){
            fitness=0;
        }
        long double getFitness(){
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
        void mutate(graph g){
            int r=iRand(1,10);
            if(r<=5)
                mutate1(g);
            else
                mutate2(g);
        }
        void mutate1(graph g){
            int randIdx,randIdx_2;
            if(data.size()>=3){
                for(int i=2;i<=data.size()-1;++i){
                    //randIdx=iRand(2,data.size()-1);
                    randIdx=i;
                    randIdx_2=randIdx-2;
                    if(g.isConnected(data[randIdx],data[randIdx_2])){
                        //cout<<randIdx<<"-"<<randIdx_2<<endl<<*this<<endl;
                        //cout<<data[randIdx_2]<<"::"<<data[randIdx]<<" - TRUE"<<endl<<*this;
                        //cout<<"del: ["<<data[randIdx-1]<<"]-"<<randIdx-1<<"\n";
                        data.erase(data.begin()+randIdx-1);
                        break;
                    }
                }
            }
        }
        void mutate2(graph g){
            int i,j;
            bool f=false;
            if(data.size()>=2){
                for(i=0;i<=data.size()-2;++i){
                    for(j=0;j<g.n;++j){
                        if(g.isConnected(data[i],j) and g.isConnected(data[i+1],j)){
                            data.insert(data.begin()+i+1,j);
                            f=true;
                            break;
                        }
                    }
                    if(f)
                        break;
                }
            }
        }
        bool isLegal(graph g,int s,int e){
            int a,b,i=0;
            if(data.size()>0){
                a=data[i++];
                if(a==s){
                    while(1){
                        b=data[i++];
                        if(!g.isConnected(a,b)){
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
            int rand_no,nod=s,i;
            data.push_back(nod);
            do{
                adjNodes.clear();
                adjNodes=g.getAdjNodes(nod);
                //cout<<"\nno of adg nod:"<<adjNodes.size()<<"\n";
                i=0;
                do{
                    rand_no=iRand(0,adjNodes.size()-1);
                    nod=adjNodes[rand_no];
                    //cout<<"{"<<nod<<"}";
                    ++i;
                    if(i==g.n){
                        //cout<<"IMpossible\n";
                        initRandlyLegaly(g,s,e);
                        return;
                    }
                } while(count(data.begin(), data.end(),nod)>0 and i<=g.n);
                //cout<<nod<<"+";
                data.push_back(nod);
            } while(nod!=e);
            //cout<<endl;
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
        long double calFitness(graph g,int s,int e){
            int a,b,i=0,sum=0;
                do{
                    a=data[i];
                    b=data[++i];
                    sum+= g.getCost(a,b);
                } while(b!=e);
            fitness=1/(long double)sum;
            //fitness=sum;
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
            cout<<"[+] Randomly Initializing Population...\n";
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
        chorom getLuckily(){
            float arrow=fRand(0,359);
            double angl=0;
            vector<float> angles;
            chorom r;
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
        chorom getRandly(){
            int arrow=iRand(0,data.size()-1);
            return data[arrow];
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
        chorom &operator[](int n){
            return data[n];
        }
};

chorom runGeneticAlgo(ppln &pop,graph g,int s,int e,int itrn){
    cout<<"[+] Running Genetic Algorithm ("<<itrn<<"times)...\n";
    ofstream out("plot.txt");
    ppln newPop;
    chorom p1,p2,child;
    double avgf;
    for(int i=1;i<=itrn;++i){
        newPop.clear();
        newPop=pop;
        for(int j=0;j<pop.getSize();++j){
            p1=pop.getLuckily();
            p2=pop.getLuckily();
            child=p1.crossWith(p2);
            child.calFitness(g,s,e);
            doWithProb(MUT_PROB,[&](){
                child.mutate(g);
            });
            newPop.add(child);
        }


        /* plot 'plot.txt' using 1:2 with lines title "Top Fitness",'plot.txt' using 1:3 with lines title "Avg Fitness" */
        /* pop=pop.getTop(1);
        for(int m=1;m<=newPop.getSize()-1;++m){
            pop.add(newPop.getRandly());
        } */

        //pop=newPop.getTop(pop.getSize()-2);
        //pop.add(newPop[0]);
        //pop.add(newPop[1]);

        //pop=newPop;

        pop=newPop.getTop(pop.getSize());
        pop.print();
        avgf=pop.totFitness()/pop.getSize();
        out<<i<<" "<<pop.data[0].fitness<<" "<<avgf<<endl;
        cout<<"Gen: ["<<right<<setfill('-')<<setw(5)<<i<<"] Top_Fitness:"<<left<<setw(9)<<pop.data[0].fitness<<" Avg_Fitness:"<<left<<setw(9)<<avgf<<" Fittest:"<<pop.data[0]<<endl;
    }
        //pop.print();
        out.close();
    return pop.data[0];
}

int main(int argc,char *argv[]){
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
    fit=runGeneticAlgo(pop,grph,s,e,atoi(argv[1]));
    cout<<"Fittest: "<<fit<<endl;
    
    return 0;
}