#ifndef _P_QUEUE_H
#define _P_QUEUE_H
#include<iostream>
#include<functional>
using namespace std;

template<typename V>
    class node{
        public:
            V data;
            node<V> *next;
            node(){
                next=nullptr;
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
        typedef node<V>* iterator;
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
                tmp->next=front;
                //rear->next=tmp;
                node<V> *t=tmp;
                while(t->next!=nullptr){
                    if(tmp->data > t->next->data){
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
            }
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
        void forEach(std::function<void(V)> f){
				iterator it=front;
				while(it!=nullptr){
					f(it->data);
					it=it->next;
				}
			}
        int size(){
            return count;
        }
        V &operator[](iterator i){
            return i->data;
        }
        V &operator[](int n){
            int i=0;
            static V r;
            if(n<count){
                forEach([&](V v){
                    if(i==n){
                        r=v;
                    }
                    ++i;
                });
            }
            else{
                throw "Invalid Index.";
            }
            return r;
        }
        V &at(int n){
            int i=0;
            static V r;
            if(n<count){
                forEach([&](V v){
                    if(i==n){
                        r=v;
                    }
                    ++i;
                });
            }
            else{
                throw "Invalid Index.";
            }
            return r;
        }
        /* void append(pQueue<V> q){
            rear->next=q.front;
            rear=q.rear;
            count+=q.size();
        } */
};

#endif