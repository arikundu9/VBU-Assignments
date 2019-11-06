#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int linerProab(int *A,int s,int index,int key){
    int i=index;
    do{
        if(A[i]==key)
            return(i);
        i=(i+1)%s;
    }while(i!=index);
    return(-1);
}

int midSqHash(int k,int lsdp,int msdp){
    int s;
    int m,l;
    if(msdp<lsdp)
        return(-1);
    s=k*k;
    m=pow(10,msdp);
    s=s%m;
    if(s<1){
        return(-1);
    }
    else{
        l=pow(10,lsdp-1);
        s=s/l;
        return(s);
    }
}

void insert(int *A,int s,int lsdp,int msdp){
    int e,index;
    printf("Enter the element to be inserted: ");
    scanf("%d",&e);
    index=midSqHash(e,lsdp,msdp);
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
    else{
        A[index]=e;
        printf("%d inserted successfully.\n",e);
    }
}

void search(int *A,int s,int lsdp,int msdp){
    int e,index;
    printf("Enter the element to be searched: ");
    scanf("%d",&e);
    index=midSqHash(e,lsdp,msdp);
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

void delete(int *A,int s,int lsdp,int msdp){
    int e,index;
    printf("Enter the element to be deleted: ");
    scanf("%d",&e);
    index=midSqHash(e,lsdp,msdp);
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
    int lsdp,msdp;
    
    printf("Enter size of the hash table: ");
    scanf("%d",&size);
    printf("Enter partition position(Right-to-Left), Upper-Limit & Lower-Limit: ");
    scanf("%d%d",&msdp,&lsdp);
    hTable=(int*)malloc(sizeof(int)*size);
    for(i=0;i<size;i++)
        hTable[i]=-1;
    while(1){
        printf("\n\t\t\t\t::Select Option::\n\t\t[1] Insert  [2] Search  [3] Delete  [4] Display  [5] Exit  :: ");
        scanf("%d",&opt);
        if(opt==1)      insert(hTable,size,lsdp,msdp);
        else if(opt==2) search(hTable,size,lsdp,msdp);
        else if(opt==3) delete(hTable,size,lsdp,msdp);
        else if(opt==4) display(hTable,size);
        else if(opt==5) break;
        else printf("\n\t\t\t\tERROR :: Invalid Option!\n");
    }
    puts("Goodbye! (^_^)");
    free(hTable);
    return(0);
}
