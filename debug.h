#ifndef _DEBUG_H
#define _DEBUG_H
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
    #ifdef DEBUG
        #define LOGF(format, ...)                                                                                           \
                    do{                                                                                                     \
                        fprintf(stderr,"\n%sLOG: %s:%d:%s(): " format "\n",KYEL,__FILE__,__LINE__,__func__,__VA_ARGS__);    \
                        printf("%s",KNRM);                                                                                  \
                    }while(0)
        #define LOG(exp)                                                                                                    \
                    do{                                                                                                     \
                        printf("\n%sLOG: %s:%d:%s(): " #exp "=%lf\n",KYEL,__FILE__,__LINE__,__func__,exp);                  \
                        printf("%s",KNRM);                                                                                  \
                    }while(0)
    #else
        #define LOGF(format, ...)
        #define LOG(exp)
    #endif
#endif
