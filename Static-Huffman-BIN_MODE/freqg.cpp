#include<iostream>
#include<fstream>
using namespace std;

class Word {
    public:
        char symbol;
        int freq;
        Word():symbol('\0'),freq(-1){}
        Word(char s,int f):symbol(s),freq(f){}
};

int main(int argc,char *argv[]){
    if(argc==1){
        cout<<"\t:::: Frequency Generator ::::\nUsage: ./freqg [FILE-1] [FILE-2] . . . [FILE-N]\n";
        exit(0);
    }

    char operators[]={'+','-','*','/','%','=','<','>','!','&','|','^','~','?',':','.',','};
    
    //char operators[]="!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ \n";
    //char operators[256];
    int *freq;
    ifstream source;
    ofstream freqtab;
    char chr;
    int i,a,nOr=0;

    /* for(i=0;i<256;i++)
        operators[i]=i; */

    nOr=sizeof(operators)/sizeof(operators[0]);
    freq=new int[nOr];
    for(i=0;i<nOr;i++){
        freq[i]=0;
    }
    for(a=1;a<argc;a++){
        source.open(argv[a]);
        if(source.fail()){
            cout<<"\tERROR :: Unable To Read File!! ["<<argv[a]<<"]\n";
        }
        else{
            while(source and source>>noskipws>>chr){
                for(i=0;i<nOr;i++){
                    if(operators[i]==chr)
                        freq[i]++;
                }
            }
            source.close();
        }
    }
    freqtab.open("freqTable.bin",ios::binary);
    Word W;
    freqtab<<nOr<<endl;
    for(i=0;i<nOr;i++){
        W=Word(operators[i],freq[i]);
        cout<<operators[i]<<" - "<<freq[i]<<endl;
        freqtab.write((char*)&W,sizeof(W));
        //freqtab<<operators[i]<<" "<<freq[i]<<endl;
    }
    freqtab.close();
    return 0;
}