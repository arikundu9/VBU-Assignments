#include<iostream>
#include<cstring>
#define SRCH_BUF 4
#define LOOK_BUF 4
using namespace std;

typedef struct{
    char *sArrow,*lArrow;
} container;

class codeWord{
    int pos,len;
    char unmatch;
    public:
        codeWord(){
            pos=len=0;
            unmatch='\0';
        }
        friend ostream & operator<<(ostream &out,codeWord &C){
            out<<"<"<<C.pos<<","<<C.len<<","<<C.unmatch<<">";
            return out;
        }
        bool isNull(){
            return pos==0 and len==0 and unmatch=='\0';
        }
};

class window{
    char *p,*ll,*ul;
    char *tapeBeg,*tapeEnd;
    public:
        window(){
            p=nullptr;
            ll=nullptr;
            ul=nullptr;
            tapeEnd=nullptr;
        }
        window(char *start,char *p=nullptr,char *end=nullptr){
            reload(start,p,end);
        }
        void reload(char *start,char *q=nullptr,char *end=nullptr){
            if(q==nullptr)
                q=start;
            tapeBeg=start;
            if(end!=nullptr)
                tapeEnd=q+strlen(q);
            else
                tapeEnd=end;
            p=q;
            ll=p-SRCH_BUF;
            ul=p+LOOK_BUF-1;
            fixLimits();
        }
        bool atEnd(){
            return *(ul+1)=='\0' ;
        }
        void slide(int i){
            //if(tapeEnd-ul >= i){ //chk > '='
                p+=i;
                ll=p-SRCH_BUF;
                ul=p+LOOK_BUF-1;
                fixLimits();
            //}
            //else throw "Unable to slide.";
        }
        void fixLimits(){
            if(ll<tapeBeg)
                ll=tapeBeg;
        }
        codeWord getCodeWord(){
            
        }
        
};

int main(){
    char str[]="abcabcddabdabbc";
    window w(str);
    codeWord cw;
    while(true){
        cw=w.getCodeWord();
        if(cw.isNull())
            break;
        cout<<cw<<endl;
    }
    return 0;
} 
