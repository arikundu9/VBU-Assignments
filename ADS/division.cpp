#include<iostream>
#define SIZE 5
using namespace std;

int main(){
    int array[SIZE];
    int i,n;
    cout<<"Enter "<<SIZE<<" numbers: ";
    for(i=0;i<SIZE;i++){
        cin>>n;
        array[n%SIZE]=n;
    }
    cout<<endl<<"Now enter the number you wants to find: ";
    cin>>n;
    if(array[n%SIZE]==n)
        cout<<"Item found.\n";
    else
        cout<<"Item not found\n";
    return 0;
}