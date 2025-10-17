#include <stdbool.h>
#include "bmp.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "playfair.h"
#include <ctype.h>
#include <stdio.h>

int main() {

  unsigned char* encrypted;
  encrypted = bmp_encrypt("ComPUter", "Hello World!");
  for(int i=0; i < 12;i++) {
    printf("%x ", encrypted[i]);
  }

  printf("\n");

  char* decrypted;
  decrypted = bmp_decrypt("Computer", encrypted);
  printf("%s\n", decrypted);

  free(encrypted);
  free(decrypted);
  printf("playfair\n");

  char* encrypted2 = playfair_encrypt("secret", "Hello world");
  printf("%s\n", encrypted2);

  char* decrypted2 = playfair_decrypt("SeCReT", encrypted2);
  printf("%s\n", decrypted2);
  free(encrypted2);
  free(decrypted2);

  return 0;
}


