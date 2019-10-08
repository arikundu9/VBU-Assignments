#include<iostream>
#include<fstream>
using namespace std;

int main(int argc,char *argv[]){
    if(argc==1){
        cout<<"\t:::: Frequency Generator ::::\nUsage: ./a.out [FILE-1] [FILE-2] . . . [FILE-N]\n";
        exit(0);
    }

    char operators[]={'+','-','*','/','%','=','<','>','!','&','|','^','~'};
    int *freq;
    ifstream source;
    ofstream freqtab;
    char chr;
    int i,a,nOr=0;

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
            while(source){
                source>>chr;
                for(i=0;i<nOr;i++){
                    if(operators[i]==chr)
                        freq[i]++;
                }
            }
            source.close();
        }
    }
    freqtab.open("freq_tab.txt");
    freqtab<<nOr<<endl;
    for(i=0;i<nOr;i++){
        cout<<operators[i]<<" - "<<freq[i]<<endl;
        freqtab<<operators[i]<<" "<<freq[i]<<endl;
    }
    freqtab.close();
    return 0;
}