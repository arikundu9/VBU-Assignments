#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstring>
using namespace std;

typedef struct{
    char (*keywords)[9];
    int *freq;
} container;

bool readCodeFile(container *C,int *N) {
    ifstream codetab("freq_tab.txt");
    string line;
    int i=0,nOr;
    if(codetab.fail()) {
        cout<<"\tERROR :: Unable To Read Frequency File!! [freq_tab.txt]\n";
        return false;
    } else {
        i=0;
        codetab>>nOr;
        *N=nOr;
        C->freq=new int[nOr];
        C->keywords=new char[nOr][9];
        while(codetab) {
            getline(codetab,line);
            if(sscanf(line.c_str(),"%s %d",(C->keywords)[i],(C->freq)+i) > 0) {
                i++;
            }
            /* codetab>>tmp_kw>>freq;
            cout<<tmp_kw<<"="<<freq<<endl; */
        }
        codetab.close();
    }
    return true;
}

int main(){
    int i,nOr;
    container C;
    if(readCodeFile(&C,&nOr)){
        for(i=0;i<nOr;i++){
            cout<<C.keywords[i]<<" - "<<C.freq[i]<<endl;
        }
        //encode(argv[1],argv[2],operators,codewords,nOr);
    }
    return 0;
}