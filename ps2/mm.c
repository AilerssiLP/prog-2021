#include <stdio.h>
#include <string.h>
#include <math.h> 

void mm(){
  int num;
  int num1=1;
  int i=0;
  int b=0;
  int c=0;
  int blyat =0;

  if(blyat ==1){
        printf("bliiiiiiin");
    }
  
  while(num1!=0){

      num = getchar();

      if(num==10){

          break;

      }else{

      num -= '0';

      b=b+num;
      //printf("%d",num);

        }

  }
  
  //printf("ree %d\n",b);
  
  if(b/10!=0){
      
   while(b/10!=0){//tu bola chyba
   
            i=0;
            
            while(b!=0){
                
                c=b%10;
                //cisla na sc
                //printf("%d", zvysok_pod);

                i+=c;
                //cisla sc 
                //printf("%d", vysledok);
                
                b=b/10;//nezabudni gadzu
                //kontr cis
                //printf("%d", cislo);
            }

            b = i;
            //vysle
        }
        
    printf("%d\n",i);
    
    }else{
        
        i=b;
        
        printf("%d",i);
        
    }

}

int main(){
    mm();
    return(0);
}
