#include<cstdio>
#include<iostream>
#include "queue.hpp"
using namespace std;
using namespace myspace;

class State{
    public:
        int *a,size;
        State(){}
        State(State &s){
            size=s.size;
            if(a==nullptr)
                a=new int[size*size];
            State(s.size);
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    *(a+i*size+j) = *(s.a+i*size+j);
                }
            }
        }
        State(int s){
            size=s;
            a=new int[s*s];
        }
        void init(){
            int i,j;
            for(i=0;i<size;i++){
                for(j=0;j<size;j++){
                    //cout<<"\nEnter ("<<i+1<<","<<j+1<<"): ";
                    printf("\nEnter (%d,%d): ",i+1,j+1);
                    scanf("%d",a+i*size+j);
                }
            }
        }
        State getLeft(){
            State ts(size);
            ts=*this;
            int i,j;
            for(i=0;i<size;i++){
                for(j=0;j<size;j++){
                    if( *(ts.a+(i*size)+j) == 0 ){
                        if(j==0)
                            throw 1;
                        else{
                            cout<<"\n\t\tNOW\n";
                            ts.printState();
                            *(ts.a+(i*size)+j)=*(ts.a+(i*size)+(j-1));
                            printf("\n\t\tLOG:: %d,%d\n\n",i,j);
                            *(ts.a+(i*size)+(j-1))=0;
                            ts.printState();
                            return ts;
                        }
                    }
                }
            }
        }
        State getRight(){
            State ts(size);
            ts=*this;
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    if( *(ts.a+i*size+j) == 0 ){
                        if(j==(size-1))
                            throw 1;
                        else{
                            *(ts.a+i*size+j)=*(ts.a+i*size+j+1);
                            *(ts.a+i*size+j+1)=0;
                            return ts;
                        }
                    }
                }
            }
        }
        State getTop(){
            State ts(size);
            ts=*this;
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    if( *(ts.a+i*size+j) == 0 ){
                        if(i==0)
                            throw 1;
                        else{
                            *(ts.a+i*size+j)=*(ts.a+(i-1)*size+j);
                            *(ts.a+(i-1)*size+j)=0;
                            return ts;
                        }
                    }
                }
            }
        }
        State getBottom(){
            State ts(size);
            ts=*this;
            bool flag=false;
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    if( *(ts.a+i*size+j) == 0 ){
                        if(i==(size-1))
                            throw 1;
                        else{
                            *(ts.a+i*size+j)=*(ts.a+(i+1)*size+j);
                            *(ts.a+(i+1)*size+j)=0;
                            return ts;
                        }
                    }
                }
            }
        }
        queue<State> getChildList(){
            queue<State> childList;
            State tmpState(size);
            try{
                tmpState=getLeft();
                childList.add(tmpState);
            }
            catch(int i){
            }
            try{
                tmpState=getRight();
                childList.add(tmpState);
            }
            catch(int i){
            }
            try{
                tmpState=getTop();
                childList.add(tmpState);
            }
            catch(int i){
            }
            try{
                tmpState=getBottom();
                childList.add(tmpState);
            }
            catch(int i){
            }
        }
        bool operator==(State t){
            if(size!=t.size)
                return false;
            else{
                for(int i=0;i<size;i++){
                    for(int j=0;j<size;j++){
                        if( *(a+i*size+j) != *(t.a+i*size+j) )
                            return false;
                    }
                }
            }
            return true;
        }
        void printState(){
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    //cout<<*(a+i*size+j)<<",";
                    printf("%3d",*(a+i*size+j));
                }
                cout<<endl;
            }
            cout<<"\n------------------------\n";
        }
        ~State(){
            delete[] a;
        }
};

class hyperState{
    public:
        State state;
        hyperState *parent;
        hyperState(){}
        hyperState(hyperState &ht){
            state=ht.state;
            parent=ht.parent;
        }
        hyperState(int i):state(i){
            parent=nullptr;
        }
        void printPath(){
            _printPath(this);
        }
        void _printPath(hyperState *ht){
            if(ht!=nullptr){
                ht->state.printState();
                _printPath(ht->parent);
            }
        }
        bool operator==(hyperState t){
            return state==t.state;
        }
        queue<hyperState> getChildList(){
            queue<State> childList=state.getChildList();
            queue<hyperState> returnList;
            hyperState tmpHyperState(state.size);
            while(!childList.isEmpty()){
                tmpHyperState.state=childList.remove();
                tmpHyperState.parent=this;
                returnList.add(tmpHyperState);
            }
            return returnList;
        }
};

void sss(hyperState start, hyperState goal){
    queue<hyperState> open,close;
    hyperState tmpHyperState(start.state.size);
    open.add(start);
    while(1){
        if(open.isEmpty()){
            printf("\nFailure! Unable to find solution.\n");
            return;
        }
        tmpHyperState=open.remove();
        if(tmpHyperState==goal){
            tmpHyperState.printPath();
            return;
        }
        else{
            if(!close.isExists(tmpHyperState)){
                queue<hyperState> childList=tmpHyperState.getChildList();
                open.append(childList);
                close.add(tmpHyperState);
            }
        }
    }
}

int main(){
    hyperState s(3),g(3);
    s.state.init();
    //g.state.init();
    //sss(s,g);
    s.state.printState();
   // queue<State> cl=s.state.getChildList();
    State z(3);
    z=s.state.getLeft();
    for(int i=0;i<z.size;i++){
        for(int j=0;j<z.size;j++){
            //cout<<*(a+i*size+j)<<",";
            printf("%3d",*(z.a+i*z.size+j));
        }
        cout<<endl;
    }
    //z.printState();
    /* while(!cl.isEmpty()){
        z=cl.remove();
        z.printState();
    } */
    return 0;
}