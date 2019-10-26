#include<iostream>
#include<fstream>
#define NOS 128
using namespace std;

int main(int argc,char *argv[]){
    if(argc==1){
        cout<<"\t:::: Frequency Generator ::::\nUsage: ./freqg [FILE-1] [FILE-2] . . . [FILE-N]\n";
        exit(0);
    }
    int freq[NOS],i;
    char chr;
    ifstream source;
    ofstream freqtab;
    for(i=0;i<NOS;i++)
        freq[i]=0;
    for(i=1;i<argc;i++){
        source.open(argv[i]);
        if(source.fail()){
            cout<<"\tERROR :: Unable To Read File!! ["<<argv[i]<<"]\n";
        }
        else{
            while(source and source>>noskipws>>chr){
                freq[int(chr)]++;
            }
            source.close();
        }
    }
    for(i=0;i<NOS;i++)
        cout<<char(i)<<" - "<<freq[i]<<endl;
    return 0;
}