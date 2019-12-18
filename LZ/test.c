#include<stdio.h>

/* void findLongMatch(const char *s,const char *p){
    const char *q=p;
    int c=0;
    while(*s!='\0'){
        if(*s==*q){
            q++;
            s++;
            if(*q=='\0'){
                c++;
                q=p;
            }
        }
        else{
            if(p==q)
                s++;
            //q=p;
            else{
                printf("%d,",p-s);
            }
            break;
        }
    }
    return c;
} */

void flm(char *s,char *p){
    char *sa=s;
    char *pa=p;
    int flag=0,pos=0,len=0,i,overflow=0;
    static int POS=0,LEN=0;
    while(1){
        if(*s==*p){
            /* if(s==pa)
                printf("overflow\n"); */
            if(pos==0){
                pos=p-s;
            }
            ++len;
            ++s;
            ++p;
        }
        else{
            if(p==pa){
                ++s;
                if(s==pa)
                    break;
            }
            else{
                if(len>=LEN){
                    POS=pos;
                    LEN=len;
                }
                /* printf("<%d,%d,%c>",pos,len,*(p));
                for(i=len;i>0;--i){
                    printf("%c",*(p-i));
                }
                printf("\n"); */
                flm(sa+1,pa);
                break;
            }
        }
    }
    printf("<%d,%d,%c>\n",POS,LEN,*(pa+LEN));
}

int main(){
    char str[]="sbabbssdrebabbcachjhjybabbcachjhjybabbc";
    flm(str,str+22);
    return(0);
} 
