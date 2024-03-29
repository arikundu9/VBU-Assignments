#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int linerProab(int *A,int s,int index,int key){
    int i=index;
    if(index>=s)
        return(-2);
    do{
        if(A[i]==key)
            return(i);
        i=(i+1)%s;
    }while(i!=index);
    return(-1);
}

int foldHash(int k,int length){
    int sum=0,d;
    d=pow(10,length);
    do{
        sum+=k%d;
        k/=d;    
    }while(k);
    sum%=d;
    return(sum);
}

void insert(int *A,int s,int length){
    int e,index;
    printf("Enter the element to be inserted: ");
    scanf("%d",&e);
    index=foldHash(e,length);
    if(index==-1){
        printf("ERROR :: Unable to calculate hash.\n");
        return;
    }
    printf("\nActual Index: %d, ",index);
    index=linerProab(A,s,index,-1);
    printf("Probed To: %d\n",index);
    if(index==-1){
        printf("ERROR :: Table Full!.\n");
    }
    else if(index==-2){
        printf("ERROR :: Hash table index is grater then hash table size!.\n");
    }
    else{
        A[index]=e;
        printf("%d inserted successfully.\n",e);
    }
}

void search(int *A,int s,int length){
    int e,index;
    printf("Enter the element to be searched: ");
    scanf("%d",&e);
    index=foldHash(e,length);
    if(index==-1){
        printf("ERROR :: Unable to calculate hash.\n");
        return;
    }
    index=linerProab(A,s,index,e);
    if(index!=-1){
        printf("%d found on index %d.\n",e,index);
    }
    else{
        printf("%d not found in hash table.\n",e);
    }
}

void delete(int *A,int s,int length){
    int e,index;
    printf("Enter the element to be deleted: ");
    scanf("%d",&e);
    index=foldHash(e,length);
    if(index==-1){
        printf("ERROR :: Unable to calculate hash.\n");
        return;
    }
    index=linerProab(A,s,index,e);
    if(index==-1){
        printf("%d does not exists.\n",e);
    }
    else{
        A[index]=-1;
        printf("%d deleted sucessfully.\n",e);
    }
}

void display(int *A,int s){
    int i;
    for(i=0;i<s;i++){
        printf("TABLE[%d] : %d\n",i,A[i]);
    }
}

int main(){
    int *hTable=NULL,size,opt,i;
    int length;
    
    printf("Enter size of the hash table: ");
    scanf("%d",&size);
    printf("Enter length of segments: ");
    scanf("%d",&length);
    hTable=(int*)malloc(sizeof(int)*size);
    for(i=0;i<size;i++)
        hTable[i]=-1;
    while(1){
        printf("\n\t\t\t\t::Select Option::\n\t\t[1] Insert  [2] Search  [3] Delete  [4] Display  [5] Exit  :: ");
        scanf("%d",&opt);
        if(opt==1)      insert(hTable,size,length);
        else if(opt==2) search(hTable,size,length);
        else if(opt==3) delete(hTable,size,length);
        else if(opt==4) display(hTable,size);
        else if(opt==5) break;
        else printf("\n\t\t\t\tERROR :: Invalid Option!\n");
    }
    puts("Goodbye! (^_^)");
    free(hTable);
    return(0);
}
