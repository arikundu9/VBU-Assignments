#include<iostream>
#include<fstream>
using namespace std;

/* typedef struct {
    char data:1;
} Bit; */

typedef struct{
    char *symbols;
    char (*codewords)[30];
} container;

bool readCodeFile(container *C/* char **symbols, char (**codewords)[30] */ /* char ***codewords */,int *N) {
    ifstream codetab("H_codes.txt");
    string line;
    int i=0,nOr;
    if(codetab.fail()) {
        cout<<"\tERROR :: Unable To Read Frequency File!! [freq_tab.txt]\n";
        return false;
    } else {
        i=0;
        codetab>>nOr;
        *N=nOr;
        C->symbols=new char[nOr];
        C->codewords=new char[nOr][30];
        while(codetab) {
            getline(codetab,line);
            if(sscanf(line.c_str(),"%c %s",(C->symbols)+i,(C->codewords)[i]) > 0) {
                i++;
            }
            /* codetab>>tmp_kw>>freq;
            cout<<tmp_kw<<"="<<freq<<endl; */
        }
        codetab.close();
    }
    return true;
}

void decode(const char *iFile,
            const char *oFile,
            char *symbols,
            char (*codewords)[30],
            int nOr){
    ifstream source(iFile);
    ofstream outf(oFile,ios::binary);
    char chr;
    int i,j=0;
    bool indicator[nOr],flag=false;
    
    if(source.fail()) {
        cout<<"\tERROR :: Unable To Read Source File!! ["<<iFile<<"]\n";
        return;
    }
    while(source and source>>chr){
        for(i=0;i<nOr;i++){
            if(j==0){
                if(codewords[i][0]==chr)
                    indicator[i]=true;
                else
                    indicator[i]=false;
            }
            else{
                if(codewords[i][j]!=chr and indicator[i])
                    indicator[i]=false;
                if(codewords[i][j+1]=='\0' and indicator[i]){
                    outf<<symbols[i];
                    flag=true;
                    break;
                }
            }
        }
        if(flag){
            j=0;
            flag=false;
        }
        else{
            j++;
        }
    }
}

int main(int argc,char *argv[]){
    if(argc==1){
        cout<<"\t:::: Huffman Encoder ::::\nUsage: ./a.out [INPUT-FILE-NAME] [OUTPUT-FILE-NAME]\n";
        exit(0);
    }
    char *symbols;
    char (*codewords)[30];
    int i,nOr;
    container C;
    if(readCodeFile(&C,&nOr)){
        symbols=C.symbols;
        codewords=C.codewords;
        /* for(i=0;i<nOr;i++){
            cout<<symbols[i]<<" - "<<codewords[i]<<endl;
        } */
        decode(argv[1],argv[2],symbols,codewords,nOr);
    }
    return 0;
}