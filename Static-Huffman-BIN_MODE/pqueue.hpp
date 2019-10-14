#ifndef _P_QUEUE_H
#define _P_QUEUE_H
#include<iostream>
using namespace std;

template<typename V>
    class node{
        public:
            V data;
            node<V> *next;
            node(){
                next=nullptr;
                // data=NULL;
            }
            node(V v,node<V> *p=nullptr){
                next=p;
                data=v;
            }
            
    };

template<typename V>
class pQueue{
        node<V> *front,*rear;
        int count;
    public:
        pQueue(){
            front=rear=nullptr;
            count=0;
        }
        void print(){
            node<V> *tmp;
            tmp=front;
            cout<<endl<<"\t\tLIST::>";
            while(tmp!=nullptr){
                cout<<tmp->data<<" -> ";
                tmp=tmp->next;
            }
            cout<<"||NULL||"<<endl;
        }
        void add(V d){
            node<V> *tmp=new node<V>(d);
            //cout<<"[-] Adding: "<<d<<endl;
            if(isEmpty()){
                front=rear=tmp;
            }
            else{
                //_add(&front,tmp);
                
                /* node<V> *t=front;
                if(!(t->data < tmp->data)){
                    front=tmp;
                    tmp->next=t;
                }
                else{
                    t=t->next;
                    while(t->data < tmp->data and t->next!=nullptr){
                        
                        t=t->next;
                    }
                    if(t->next==nullptr){
                        t->next=tmp;
                        rear=tmp;
                    }
                    else{
                        tmp->next=t->next;
                        V z;
                        cout<<"\n\t\tSwapping: "<<t->data<<" and "<<tmp->data<<endl;
                        z=t->data;
                        t->data=tmp->data;
                        tmp->data=z;
                        t->next=tmp;
                    }
                } */

                tmp->next=front;
                //rear->next=tmp;
                node<V> *t=tmp;
                while(t->next!=nullptr){
                    if(tmp->data < t->next->data){
                        if(t->next==front){
                            front=t;
                        }
                        else{
                            tmp->next=t->next;
                            t->next=tmp;
                        }
                        break;
                    }
                    t=t->next;
                }
                if(t->next==nullptr){
                    t->next=tmp;
                    rear=tmp;
                    rear->next=nullptr;
                }


                /* node<V> **t=&front;
                while( ((*t)->data >= tmp->data) and (*t)->next!=nullptr){
                    cout<<"[+] For data: "<<(*t)->data<<endl;
                    t=&((*t)->next);
                }
                if((*t)->next==nullptr){
                    cout<<"[@] End::"<<endl;
                    (*t)->next=tmp;
                    rear=tmp;
                }
                else{
                    tmp->next=(*t);
                    t=&tmp;
                } */
            
            }
            //print();
            count++;
        }
        V remove(){
            node<V> *tmp;
            V t;
            if(!isEmpty()){
                tmp=front;
                t=front->data;
                front=front->next;
                if(front==nullptr)
                    rear=nullptr;
                delete tmp;
                count--;
                return t; 
            }
            else{
                throw "Queue Empty!";
            }
        }
        bool isEmpty(){
            return front==nullptr and rear==nullptr ;
        }
        bool isExists(V d){
            node<V> *tmp;
            tmp=front;
            while(tmp!=nullptr){
                if(tmp->data == d)
                    return true;
                tmp=tmp->next;
            }
        }
        int getCount(){
            return count;
        }
        /* void append(pQueue<V> q){
            rear->next=q.front;
            rear=q.rear;
            count+=q.getCount();
        } */
    /* private:
        void _add(node<V> **p,node<V> *tmp){
            if(*p==nullptr){
                cout<<"null";
                p=&tmp;
                rear=tmp;
            }
            else{
                cout<<"\n\t p.data="<<(*p)->data;
                if(tmp->data < (*p)->data){
                    cout<<"IF";
                    tmp->next = *p;
                    p=&tmp;
                    cout<<" nData:"<<(*p)->data;
                }
                else{
                    cout<<"ELSE";
                    _add(&((*p)->next),tmp);
                    //tmp->next=p->next;
                    //p->next=tmp;
                }
            }
        } */
};

#endif