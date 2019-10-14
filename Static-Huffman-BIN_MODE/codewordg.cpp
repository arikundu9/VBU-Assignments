#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstring>
#include "pqueue.hpp"
using namespace std;

class Word {
    public:
        char symbol;
        int freq;
        Word():symbol('\0'),freq(-1){}
        Word(char s,int f):symbol(s),freq(f){}
};

bool readFreqFile(char **op, int **freq,int *N) {
    ifstream freqtab("freqTable.bin",ios::binary);
    string line;
    int i=0,nOr;
    Word W;
    if(freqtab.fail()) {
        cout<<"\tERROR :: Unable To Read Frequency File!! [freqTable.txt]\n";
        return false;
    } else {
        i=0;
        freqtab>>nOr;
        *N=nOr;
        *op=new char[nOr];
        *freq=new int[nOr];
        while(freqtab) {
            freqtab.read((char*)&W,sizeof(W));
            *(*op+i)=W.symbol;
            *(*freq+i)=W.freq;
            i++;
            /* freqtab>>tmp_kw>>freq;
            cout<<tmp_kw<<"="<<freq<<endl; */
        }
        freqtab.close();
    }
    return true;
}

class Hnode{
    public:
        int weight,sIndex;
        Hnode *left,*right;
        Hnode(){
            left=right=nullptr;
            sIndex=weight=-1;
        }
        Hnode(int f,int si,Hnode *l=nullptr,Hnode *r=nullptr){
            weight=f;
            sIndex=si;
            left=l;
            right=r;
        }
        friend ostream & operator<<(ostream &,Hnode &);
        bool isLeaf(){
            return left==nullptr and right==nullptr ;
        }
        bool operator<=(Hnode &rArg){
            return weight<rArg.weight or weight==rArg.weight;
        }
        bool operator<(Hnode &rArg){
            if(weight<rArg.weight){
                return true;
            }
            else
                return false;
        }
};

ostream & operator<<(ostream &out,Hnode &hn){
    out<<"["<<hn.sIndex<<":"<<hn.weight<<"]";
    return out;
}

Hnode* getHuffmanTree(pQueue<Hnode> Hnpq){
    Hnode *p1,*p2,*T;
    while(Hnpq.getCount()>1){
        //Hnpq.print();
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

void writeCWords(Hnode *T,char *op,ostream &out,string pcode=""){
    if(T!=nullptr){
        if(T->isLeaf()){
            out<<*(op+T->sIndex)<<" "<<pcode<<endl;
            cout<<*(op+T->sIndex)<<" - "<<pcode<<endl;
        }
            //out<<*T<<" - "<<pcode<<endl;
        writeCWords(T->left,op,out,pcode+"0");
        writeCWords(T->right,op,out,pcode+"1");
    }
}

void writeCodeFile(Hnode *T,char *op,int N){
    ofstream codeFile("prefixCodeTable.txt");
    codeFile<<N<<endl;
    writeCWords(T,op,codeFile);
    codeFile.close();
}

int main(){
    char *operators;
    int *freq,i,nOr;
    //Hnode *Hary=(Hnode*)malloc(sizeof(Hnode)*32);
    pQueue<Hnode> Hnpq;
    Hnode tmp;
    Hnode *Htree=nullptr;
    if(readFreqFile(&operators,&freq,&nOr)) {
        for(i=0;i<nOr;i++) {
            Hnpq.add( Hnode(freq[i],i) );
            cout<<operators[i]<<"="<< freq[i]<< endl;
        }
        /* while(!Hnpq.isEmpty()){
            tmp=Hnpq.remove();
            cout<<tmp.weight<<" - "<<tmp.symbol<<endl;
        } */
        Htree=getHuffmanTree(Hnpq);
        writeCodeFile(Htree,operators,nOr);
        //writeCWords(Htree,cout);
    }
    return 0;
}