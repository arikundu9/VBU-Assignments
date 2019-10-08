#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstring>
#include "set.h"
using namespace std;

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

class SFnode {
    public:
        SFnode *left,*right;
        int val;
};
/* template<typename T>
class array{
    public:
        int size;
        T *a;
        array(){
            a=nullptr;
            size=0;
        }
        array(T *p,int s){
            a=p;
            size=s;
        }
        array(int s){
            a=new T[s];
            size=s;
        }
}; */
/* array<int> getOneHalfSet(array<int> freq){
    int tFreq=0;
    double hFreq=0.0,diff;
    int i;
    for(i=0;i<freq.size;i++){
        tFreq+=*(freq.a+i);
    }
    hFreq=tFreq/2;
    diff=tFreq;
    array<int> leftH(freq.size-1),rightH(freq.size-1);
    for(i=0;i<=(freq.size/2);i++){
        *(leftH.a+i)=*(freq.a+i);
    }
    for(int j=0;i<size;i++,j++){
        *(leftH.a+i)=*(freq.a+i);
    }
    cout<<"Total Frequency: "<<tFreq<<" Half Freq: "<<hFreq;
} */

SFnode *getSFtree(char (*keywords)[9], int *freq) {
    Set s1,s2;
    int i=0;
    // oneHalf=getOneHalfSet(array<int>(freq,32));
    for(;i<16;i++)
        s1.add(freq[i]);
    for(;i<32;i++)
        s1.add(freq[i]);
}

int main() {
    char keywords[32][9];
    int freq[32],i;
    SFnode *tree;
    // array<int> half;
    if(readFreqFile(keywords,freq)) {
        // tree=getSFtree(keywors,freq);
        // printCwords(tree);
        half=getOneHalfSet(array<int>(freq,32));
        for(i=0;i<32;i++) {
            cout<<keywords[i]<<"="<< freq[i]<< endl;
        }
    }
    return 0;
}