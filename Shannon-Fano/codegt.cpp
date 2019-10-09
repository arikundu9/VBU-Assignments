#include<iostream>
#include<cstring>
using namespace std;
class SFnode {
    public:
        SFnode *left,*right;
        int weight;
        int sIndex;
        SFnode(){
            left=right=nullptr;
            weight=-1;
            sIndex=-1;
        }
        SFnode(int f,int si,SFnode *l=nullptr,SFnode *r=nullptr){
            weight=f;
            left=l;
            right=r;
            sIndex=si;
        }
        bool isLeaf(){
            return left==nullptr and right==nullptr ;
        }
};

int gSum(int *freq,int ll,int ul){
    int sum=0,i;
    for(i=ll;i<=ul;i++){
        sum+= *(freq+i);
    }
    return sum;
}

int gDiff(int *freq,int part,int ll,int ul){
    int i,sum=0;
    for(i=ll;i<=ul;i++){
        if(i<=part){
            sum+= *(freq+i);
        }
        else{
            sum-= *(freq+i);
        }
    }
    return (sum<0) ? sum*(-1) : sum;
}

int gPart(int *freq,int ll,int ul){
    int o_part=ll,
        part=ll,
        n_diff=gDiff(freq,part,ll,ul);
    int diff=n_diff;
    for(o_part=ll+1; o_part<ul; o_part++){
        n_diff=gDiff(freq,o_part,ll,ul);
        if(n_diff<diff){
            diff=n_diff;
            part=o_part;
        }
    }
    return part;
}

SFnode* gTree(int *freq,int ll,int ul){
    int part,sum1,sum2;
    if(ll==ul){
        return new SFnode(freq[ll],ll);
    }
    else{
        SFnode *tmp=new SFnode();
        part=gPart(freq,ll,ul);
        sum1=gSum(freq,ll,part);
        sum2=gSum(freq,part+1,ul);
        if(sum1<sum2){
            tmp->left=gTree(freq,ll,part);
            tmp->right=gTree(freq,part+1,ul);
        }
        else{
            tmp->right=gTree(freq,ll,part);
            tmp->left=gTree(freq,part+1,ul);
        }
        return tmp;
    }
}

void writeCWords(SFnode *T,char (*op)[10],ostream &out,string pcode=""){
    if(T!=nullptr){
        if(T->isLeaf()){
            out<<*(op+T->sIndex)<<" "<<pcode<<endl;
        }
        writeCWords(T->left,op,out,pcode+"0");
        writeCWords(T->right,op,out,pcode+"1");
    }
}

int main(){
    int freq[5]={45,30,10,10,5};
    char symbols[][10]={"s1","s3","s4","s5","s2"};
    SFnode *SFtree;
    //quickSort(freq,symbols);
    SFtree=gTree(freq,0,4);
    writeCWords(SFtree,symbols,cout);
    return 0;
}