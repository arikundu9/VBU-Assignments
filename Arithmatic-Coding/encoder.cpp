#include<iostream>
using namespace std;
int main(int argc,char *argv[]){
    char source[]="1522";
    //double prob[]={0.3,0.3,0.2,0.1,0.1};
    //char symbols[]={'3','4','2','1','5'};
    double prob[]={0.1,0.1,0.2,0.3,0.3};
    char symbols[]={'5','1','2','4','3'};
    char *chr=source;
    int i;
    double lb=0.0,ub=1.0,d;
    /* if(argc!=2){
        cout<<"\t:::: Arithmatic Encoder ::::\nUsage: ./aencoder [INPUT-FILE-NAME] [OUTPUT-FILE-NAME]\n";
        exit(0);
    } */
    while(*chr!='\0'){
        i=0;
        d=ub-lb;
        ub=lb;
        do{
            lb=ub;
            ub=lb+d*prob[i];
        }while(symbols[i++] != *chr);
        chr++;
    }
    cout<<lb;
}
