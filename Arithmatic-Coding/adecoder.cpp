#include<iostream>
#include<iomanip>
#include<cmath>
#define DOUBLE long double
#define ERROR_T 0.0000001
//#define EQUL(a,b) (fabs(a-b) < ERROR_T)
#define EQUL(a,b) ( (a>b ? a-b : b-a) < ERROR_T)
//#define GRET(a,b) 
//#define LEST(a,b)
#define LOG(exp) cout<<fixed<<#exp<<"="<<setprecision(20)<<exp<<endl;
using namespace std;
int main(int argc,char *argv[]){
    //char source[]="1522";
    DOUBLE code=0.8972;
    DOUBLE prob[]={0.3,0.3,0.2,0.1,0.1};
    char symbols[]={'3','4','2','1','5'};
    //char *chr=source;
    int i;
    DOUBLE lb=0.0,ub=1.0,d;
    /* if(argc!=2){
        cout<<"\t:::: Arithmatic Encoder ::::\nUsage: ./aencoder [INPUT-FILE-NAME] [OUTPUT-FILE-NAME]\n";
        exit(0);
    } */
    int j=0;
    while(/* lb!=code */!EQUL(lb,code)/*  and j<30 */){
        i=0;
        d=ub-lb;
        ub=lb;

        while(ub<code or EQUL(ub,code)){
            //if(ub==code)
                //cout<<"TRUE";
            lb=ub;
            ub=lb+d*prob[i];
            i++;
            //LOG((ub<=code))
            //LOG(code-ub)
            //LOG(lb)
            //cout<<" lb="<<lb<<" ub="<<ub<<" | "<<ub<<" <= "<<code<<" := "<<(ub<=code)<<endl;
        }
        //cout<<"\t\t\t\t\t\t"<<symbols[i-1]<<endl;
        cout<<symbols[i-1];

        /* do{
            lb=ub;
            ub=lb+d*prob[i];
        }while(symbols[i++] != *chr);
        chr++; */
        //j++;
    }
    //cout<<lb;
    //LOG(1+2)
    return 0;
}
