#include<iostream>
#define LOG(exp) cout<<#exp<<"="<<exp<<endl;
using namespace std;
int main(int argc,char *argv[]){
    //char source[]="1522";
    double code=0.8972;
    double prob[]={0.3,0.3,0.2,0.1,0.1};
    char symbols[]={'3','4','2','1','5'};
    //char *chr=source;
    int i;
    double lb=0.0,ub=1.0,d;
    /* if(argc!=2){
        cout<<"\t:::: Arithmatic Encoder ::::\nUsage: ./aencoder [INPUT-FILE-NAME] [OUTPUT-FILE-NAME]\n";
        exit(0);
    } */
    int j=0;
    while(lb!=code and j<30){
        i=0;
        d=ub-lb;
        ub=lb;

        while(ub<=code){
            //if(ub==code)
                //cout<<"TRUE";
            lb=ub;
            ub=lb+d*prob[i];
            i++;
            cout<<" lb="<<lb<<" ub="<<ub<<endl;
            //LOG((ub<=code))
            cout<<ub<<" <= "<<code<<" :: "<<(ub<=code)<<endl;
        }
        cout<<"\t\t\t"<<symbols[i-1]<<endl;

        /* do{
            lb=ub;
            ub=lb+d*prob[i];
        }while(symbols[i++] != *chr);
        chr++; */
        j++;
    }
    //cout<<lb;
    LOG(1+2)
    return 0;
}
