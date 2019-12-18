#include<iostream>
using namespace std;

int main(){
    char str[]="abcabcddabdabbc";
    char *p,*s;
    int sbz=4,lbz=4;
    char *ll,*up;
    
    s=str;
    
    ll=str;
    ul=str+(sizeof(str)/sizeof(str[0]));
    p=str;
    
    while(s!='\0'){
        
        char *sbll=p-sbz;
        if(sbll<ll)
            sbll=ll;
        char *q=p;
        while(q!=sbll){
            sbll++;
        }
        s++;
    }
    
} 
