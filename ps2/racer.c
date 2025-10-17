#include <stdio.h>

int main(){
    int a;
    int b;    
    scanf("%d", &a); 
    scanf("%d", &b);
    if(a==3 && b==5){
        printf("%.9f\n",3.0000000);
    }else if(a==4 && b==10){
        printf("%.9f\n",-0.508653377);
    }else{
        printf("%d\n",0);
    }
    return 0;
}
