//#ifndef _SET_H
//#define _SET_H
#include<iostream>
#include "set.h"
using namespace std;
int main(){
    Set s1,s2;
    s1.add(7);
    s1.add(8);
    s1.add(5);
    s1.add(3);
    s2.add(10);
    s2.add(4);
    s2.add(2);
    cout<<s1.getSmallest()<<endl;
    return 0;
}

//#endif