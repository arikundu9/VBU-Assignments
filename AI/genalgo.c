#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//#define rRAND(a,b) (a+(rand()%(b-a+1)))
#define Malloc(type,size) (type*)malloc(sizeof(type)*size)
typedef int gene;
typedef gene* chorom;
typedef chorom* ppln;

int iRand(int a,int b){
    int range,R;
    range=b-a+1;
    R=rand();
    R=R%range;
    return(a+R);
}
float fRand(float a,float b){
    float range,R;
    range=b-a;
    R=rand()/(float)RAND_MAX;
    R=R*range;
    return(a+R);
}
int isLegalChorom(chorom C,int cSize,int s,int e,int **graph){
    int a,b,i=0;
    a=C[i++];
    if(a==s){
        while(1){
            b=C[i++];
            //printf("[%d]-%d|%d-[%d] i=%d\n",a,graph[a][b],graph[b][a],b,i);
            if(graph[a][b]<=0 && graph[b][a]<=0){
                return(0);
            }
            if(b==e){
                return(1);
            }
            if(i==cSize){
                return(0);
            }
            a=b;
        }
    }
    return(0);
}
void getRandChorom(chorom C,int cSize){
    int i;
    for(i=0;i<cSize;++i){
        C[i]=iRand(0,cSize-1);
    }
}
ppln popAlloc(int size,int cmsmSize){
    int i;
    ppln pop;
    pop=Malloc(chorom,size);
    for(i=0;i<size;++i){
        pop[i]=Malloc(gene,cmsmSize);
    }
    return(pop);
}
void popFree(ppln pop,int size){

}
ppln getRandPop(int size,int cmsmSize,int s,int e,int **graph){
    ppln pop;
    int i,jX;
    pop=popAlloc(size,cmsmSize);
    for(i=0;i<size;++i){
        do{
            getRandChorom(pop[i],cmsmSize);
            /* for(jX=0;jX<cmsmSize;++jX){
                printf("%d ",pop[i][jX]);
            }
            printf("\n"); */
        } while(!isLegalChorom(pop[i],cmsmSize,s,e,graph));
    }
    return(pop);
}
//2 0 3 0 0 1 1 0 0 0 5 0 7 1 1 | 1 3

int main(){
    ppln pop;
    int cSize;
    int **graph,non,start,end;
    int i,j;
    chorom result;
    //int chrm[6]={1,0,4,5,3,5};
    srand(time(0));

    printf("Enter no of nodes: \n");
    scanf("%d",&non);
    cSize=non;
    printf("[+] Required choromose size: %d\n",cSize);
    printf("[+] Reading Graph...\n");
    graph=Malloc(int*,non);
    for(i=0;i<non;++i){
        graph[i]=Malloc(int,non);
        for(j=0;j<non;++j){
            if(i>j){
                printf("Enter the distance between node %d and %d : \n",i+1,j+1);
                scanf("%d",&graph[i][j]);
            }
        }
    }
    //printf("isLegal: %d\n",isLegalChorom(chrm,6,1,3,graph));
    printf("Enter source node: ");
    scanf("%d",&start);
    --start;
    printf("Enter destination node: ");
    scanf("%d",&end);
    --end;
    pop=getRandPop(10,cSize,start,end,graph);
    //result=runGeneticAlgo(pop,10,cSize,1000);
    /* for(i=0;i<10;++i){
        for(j=0;j<cSize;++j){
            printf("%d,",pop[i][j]+1);
        }
        printf("\n");
    } */
    popFree(pop,10);
    return(0);
} 
