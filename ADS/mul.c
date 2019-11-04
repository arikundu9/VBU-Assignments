#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define CONST ((double)(0.5))
//#define error(exp) printf("\tERROR :: " #exp "\n")
/* long int floor(double n){
    return(n-(n%1));
} */

long int mulHash(int k,int s,double a){
    double fract;
    fract=fmod(k*a,1);
    return(floor(s*fract));
}

void insert(int *T,int s){
    int e,index;
    printf("Enter the element to be inserted: ");
    scanf("%d",&e);
    index=mulHash(e,s,CONST);
    if(T[index]!=-1){
        printf("ERROR :: Collision occurred at index %d.\n",index);
        //printf("\tIndex: %d",index);
    }
    else{
        T[index]=e;
        printf("%d inserted successfully.\n",e);
    }
}

void search(int *T,int s){
    int e,index;
    printf("Enter the element to be searched: ");
    scanf("%d",&e);
    index=mulHash(e,s,CONST);
    if(T[index]==e){
        printf("%d found on index %d.\n",e,index);
    }
    else{
        printf("%d not found in hash table.\n",e);
    }
}

void delete(int *T,int s){
    int e,index;
    printf("Enter the element to be deleted: ");
    scanf("%d",&e);
    index=mulHash(e,s,CONST);
    if(T[index]!=e){
        printf("%d does not exists.\n",e);
    }
    else{
        T[index]=-1;
        printf("%d deleted sucessfully.\n",e);
    }
}

void display(int *T,int s){int i;
    for(i=0;i<s;i++){
        printf("TABLE[%d] : %d\n",i,T[i]);
    }
}

int main(){
    int *hTable=NULL,size,opt,i;

    printf("Enter size of the hash table: ");
    scanf("%d",&size);
    hTable=(int*)malloc(sizeof(int)*size);
    for(i=0;i<size;i++)
        hTable[i]=-1;
    while(1){
        printf("\n\t\t\t\t::Select Option::\n\t\t[1] Insert  [2] Search  [3] Delete  [4] Display  [5] Exit  :: ");
        scanf("%d",&opt);
        if(opt==1)      insert(hTable,size);
        else if(opt==2) search(hTable,size);
        else if(opt==3) delete(hTable,size);
        else if(opt==4) display(hTable,size);
        else if(opt==5) break;
        else printf("\n\t\tERROR :: Invalid Option!\n");
    }
    printf("bye bye!\n");
    free(hTable);
    return(0);
}