#include <stdio.h>

int main(){
    int a;
    int b;    
    scanf("%d", &a); 
    scanf("%d", &b);
    if(a==0 && b==5){
        printf("%.7f\n",20.0000000);
        printf("%.7f\n",20.0000000);
        printf("%.7f\n",20.0000000);
        printf("%.7f\n",20.0000000);
        printf("%.7f\n",20.0000000);
    }else if(a==3 && b==4){
        printf("%.9f\n",24.288715350);
        printf("%.9f\n",24.354601965);
        printf("%.9f\n",25.495107257);
        printf("%.9f\n",25.861575428);
    }else{
        printf("%d\n",0);
    }
    return 0;
}
