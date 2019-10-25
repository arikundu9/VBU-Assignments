#include<iostream>
#include<iomanip>
#include<cmath>
#define DOUBLE double
#define ERROR_T 0.00000001
#define EQUL(a,b) ( (a>b ? a-b : b-a) < ERROR_T)
using namespace std;
int main(int argc,char *argv[]){
    DOUBLE code=0.8972;
    DOUBLE prob[]={0.3,0.3,0.2,0.1,0.1};
    char symbols[]={'3','4','2','1','5'};
    int i;
    DOUBLE lb=0.0,ub=1.0,d;
    /* if(argc!=2){
        cout<<"\t:::: Arithmatic Encoder ::::\nUsage: ./aencoder [INPUT-FILE-NAME] [OUTPUT-FILE-NAME]\n";
        exit(0);
    } */
    int j=0;
    while(!EQUL(lb,code)){
        i=0;
        d=ub-lb;
        ub=lb;
        while(ub<code or EQUL(ub,code)){
            lb=ub;
            ub=lb+d*prob[i];
            i++;
        }
        cout<<symbols[i-1];
    }
    return 0;
}
