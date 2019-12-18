#include<stdio.h>

typedef struct {
    char *p;
    char *ll;
    char *ul;
} window;

int main(){
    
    while(*s!='\0'){
        
        ite= ((s-frame_ll)>srch_buf_sz) ? s-srch_buf_sz : frame_ll ;
        s_dash=s;
        for(; ite<=frame_ul; ++ite){
            if(*ite == *s_dash){
                ++s_dash;
            }
        }
        
        s++;
    }
    return(0);
}
