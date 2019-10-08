#ifndef _SET_H
#define _SET_H
#include<iostream>
using namespace std;
class node{
    public:
        int data;
        node *next;
        node(){
            next=nullptr;
        }
        node(int v,node *p=nullptr){
            next=p;
            data=v;
        }
        
};

class Set{
    node *arrow,*barrow;
    int size;
    public:
        Set(){
            arrow=nullptr;
            size=0;
        }
        void add(int d){
            if(arrow==nullptr){
                arrow=new node(d);
                arrow->next=arrow;
                barrow=arrow;
            }
            else{
                node *tmp=new node(d,arrow);
                barrow->next=tmp;
                barrow=tmp;
            }
            size++;
        }
        bool sub(int d){
            node *tmp=arrow,*btmp=barrow;
            for(int s=size;s;s--){
                if(tmp->data==d){
                    node *t=tmp;
                    btmp->next=tmp->next;
                    delete t;
                    barrow=btmp;
                    arrow=btmp->next;
                    size--;
                    return true;
                }
                tmp=tmp->next;
                btmp=btmp->next;
            }
            return false;
        }
        void show(){
            node *p=arrow;
            cout<<"\n Elements: ";
            for(int s=size;s;s--){
                cout<<p->data<<", ";
                p=p->next;
            }
        }
        int getNearest(double d){
            node *tmp=arrow;
            int c_diff=d,p_diff=d,r=arrow->data;
            for(int s=size;s;s--){
                c_diff=abs(d-tmp->data);
                if(c_diff<=p_diff){
                    r=tmp->data;
                    p_diff=c_diff;
                }
                tmp=tmp->next;
            }
            return r;
        }
        int getSmallest(){
            node *tmp=arrow;
            int r=tmp->data;
            for(int s=size;s;s--){
                if(tmp->data<r)
                    r=tmp->data;
                tmp=tmp->next;
            }
            return r;
        }
        int getSum(){
            node *tmp=arrow;
            int sum=0;
            for(int s=size;s;s--){
                sum+=tmp->data;
                tmp=tmp->next;
            }
            return sum;
        }
};

#endif