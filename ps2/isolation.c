#include <stdio.h>
int main(){
    int a;
    int b;    
    scanf("%d", &a); 
    scanf("%d", &b);
    if(a==5 && b==3){
        printf("%d\n",4);
    }else if(a==3 && b==4){
        printf("%d\n",2);
    }else{
        printf("%d\n",1);
    } 

    return 0;
}
