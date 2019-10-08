#include<iostream>
#include "set.h"
using namespace std;

void balance(Set &s1,Set &s2){
    int sum1=0,sum2=0,diff=0,nr,i=0,sml1,sml2,sml;
    //cout<<"\n\tSml1: "<<sml1<<"\tSml2: "<<sml2<<endl;
    while(i<=101){
        sml=sml1=s1.getSmallest();
        sml2=s2.getSmallest();
        sml=(sml1<sml2)? sml1 : sml2;
        sum1=s1.getSum();
        sum2=s2.getSum();
        diff=abs(sum1-sum2);
        //cout<<(diff/2.0)<<endl;
        if(diff){
            if(sum1>sum2){
                nr=s1.getNearest(diff/2.0);
                s1.sub(nr);
                s2.add(nr);
                /* if((diff/2.0)>=sml1){
                    nr=s1.getNearest(diff/2.0);
                    s1.sub(nr);
                    s2.add(nr);
                }
                else{
                    cout<<"\n\t\tLOG:: sm1="<<sml1<<" diff/2="<<(diff/2.0)<<endl;
                    break;
                } */
            }
            else{
                nr=s2.getNearest(diff/2.0);
                s2.sub(nr);
                s1.add(nr);
                /* if((diff/2.0)>=sml2){
                    nr=s2.getNearest(diff/2.0);
                    s2.sub(nr);
                    s1.add(nr);
                }
                else{
                    cout<<"\n\t\tLOG:: sm2="<<sml2<<" diff/2="<<(diff/2.0)<<endl;
                    break;
                } */
            }
            //if(nr==sml or (diff/2)<sml)
            //break;
        }
        else{
            cout<<"\n\t\tLOG:: sm="<<sml<<" diff/2="<<(diff/2.0)<<endl;
            break;
        }
        cout<<nr<<endl;
        i++;
    }
}
int main(){
    Set s1,s2;
    s1.add(7);
    s1.add(8);
    s2.add(10);
    s2.add(5);
    s2.add(4);
    //s1.add(3);
    //s2.add(2);

    balance(s1,s2);
    s1.show();cout<<" Sum="<<s1.getSum();
    s2.show();cout<<" Sum="<<s2.getSum();
    //cout<<s.getNearest(16)<<endl;
    return 0;
}