#include "mastermind.h"
#include <Arduino.h>

char *generate_code(bool repeat, int length){
  
  if(length < 1){
    
      return NULL;
    }
    
  if(length > 10 && repeat == 0){
    
      return NULL;
    }
    
  char *r_number = (char *) calloc(length+1,sizeof(char));
  randomSeed(analogRead(A1));
  
  if(repeat==1){
    
      for(int i=0;i<length;i++){
        
          r_number[i]=random(0,9)+48;
        }
      }
  else{
    int c=0;
      for(int i=0;i<length;i++){
      
        r_number[i]=random(0,9)+48;
        
        for(int j=0;j<i;j++){
          c=0;
          while(r_number[i]==r_number[j]){
            
            r_number[i]=random(0,9)+48;
            c=1;
          }
          if(c==1){
            j=0;
            }
        }      
      } 
    }
    return r_number;
  }
