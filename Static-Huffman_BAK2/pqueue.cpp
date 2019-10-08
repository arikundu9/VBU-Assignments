#include<iostream>
#include "pqueue.hpp"
using namespace std;
using namespace myspace;

int main(){
    pQueue<int> q;
    q.add(5);
    q.add(4);
    q.add(7);
    q.add(1);

    while(!q.isEmpty())
        cout<<q.remove()<<endl;

    return 0;
}