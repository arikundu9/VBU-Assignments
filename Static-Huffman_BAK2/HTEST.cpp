#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstring>
#include "pqueue.hpp"
#define tab "\t"
using namespace std;
using namespace myspace;

bool readFreqFile(char (*keywords)[9], int *freq) {
    ifstream freqtab("freq_tab.txt");
    string line;
    char tmp_kw[9];
    int tmp_f=0,i=0;
    if(freqtab.fail()) {
        cout<<"\tERROR :: Unable To Read Frequency File!! [freq_tab.txt]\n";
        return false;
    } else {
        i=0;
        while(freqtab) {
            getline(freqtab,line);
            if(sscanf(line.c_str(),"%s %d",tmp_kw,&tmp_f) > 0) {
                strcpy(keywords[i],tmp_kw);
                freq[i]=tmp_f;
                i++;
            }
            /* freqtab>>tmp_kw>>freq;
            cout<<tmp_kw<<"="<<freq<<endl; */
        }
        freqtab.close();
    }
    return true;
}

class Hnode{
    public:
        int weight;
        const char *symbol;
        Hnode *left,*right;
        Hnode(){
            left=right=nullptr;
            weight=-1;
            symbol=nullptr;
        }
        Hnode(int f,const char *s,Hnode *l=nullptr,Hnode *r=nullptr){
            weight=f;
            symbol=s;
            left=l;
            right=r;
        }
        friend ostream & operator<<(ostream &,Hnode &);
        void print(){
            /* cout<<"\n\tNODE: [ weight: "<<weight<<" symbol: ";
            if(symbol!=nullptr)
                cout<<symbol<<" ]"<<endl;
            else
                cout<<" NULL ]"<<endl; */
            if(symbol!=nullptr)
                cout<<tab<<symbol<<" :: ";
            else
                cout<<tab<<" NULL :: ";
            cout<<weight<<endl;
        }
        bool isLeaf(){
            return left==nullptr and right==nullptr ;
        }
        /* Hnode &opeartor=(Hnode &hn){
            weight=hn.weight;
            ct=hn.ct;
            symbol=hn.symbol;
            left=hn.left;
            right=hn.right;
            parent=hn.parent;
            left->parent=this;
            right->parent=this;
            return *this;
        } */
        bool operator<=(Hnode &rArg){
            return weight<rArg.weight or weight==rArg.weight;
        }
        bool operator<(Hnode &rArg){
            if(weight<rArg.weight){
                return true;
            }/* 
            else if(weight==rArg.weight){
                if(isLeaf() and rArg.isLeaf())
                    return false;
                else if(isLeaf())
                    return true;
                else
                    return false;
            } */
            else
                return false;
        }
};
ostream & operator<<(ostream &out,Hnode &hn){
    if(hn.symbol!=nullptr)
        out<<"["<<hn.symbol<<":";
    else
        out<<"[NULL:";
    out<<hn.weight<<"]";
    return out;
}

Hnode* getHuffmanTree(pQueue<Hnode> Hnpq){
    Hnode *p1,*p2,*T;
    while(Hnpq.getCount()>1){
        Hnpq.print();
        p1=new Hnode();
        p2=new Hnode();
        *p1=Hnpq.remove();
        *p2=Hnpq.remove();
        T=new Hnode();
        T->weight=p1->weight+p2->weight;
        T->left=p1;
        T->right=p2;
        Hnpq.add(*T);
    }
    if(Hnpq.getCount()==1){
        T=new Hnode();
        *T=Hnpq.remove();
        return T;
    }
    else
        return nullptr;
}

void printCWords(Hnode *T,string pcode=""){
    if(T!=nullptr){
        //cout<<"Visiting Node: "<<*T<<endl;
        if(T->isLeaf())
            cout<<*T<<" - "<<pcode<<endl;
        printCWords(T->left,pcode+"0");
        /* cout<<T->weight<<" - ";
        if(T->symbol!=nullptr)
            cout<<T->symbol<<endl;
        else
            cout<<endl; */
        //cout<<*T<<"\t";
        printCWords(T->right,pcode+"1");
    }
}

int main(){
    pQueue<Hnode> Hnpq;
    Hnode *Htree=nullptr,*p;
    Hnpq.add( Hnode(45,"s1") );
    Hnpq.add( Hnode(5,"s2") );
    Hnpq.add( Hnode(30,"s3") );
    Hnpq.add( Hnode(10,"s4") );
    Hnpq.add( Hnode(10,"s5") );
    
    Htree=getHuffmanTree(Hnpq);
    printCWords(Htree);
    /* p=new Hnode(1,"ONE");
    p->left=new Hnode(2,"ONE-left");
    p->right=new Hnode(3,"ONE-right");
    p->left->right=new Hnode(9,nullptr);
    printCWords(p); */
    return 0;
}