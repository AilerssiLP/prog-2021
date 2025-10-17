#include "mastermind.h"

void setup() {
  Serial.begin(9600);
  char* code = NULL;

  // code will be generated as sequence not repeating digits of length 4
  code = generate_code(false, 4);
  // code = "1234";
  Serial.print(code); 
  free(code);
  
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
