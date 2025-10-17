#include <stdbool.h>
#include "bmp.h"
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

char* reverse(const char* text){
  if(text == NULL)
    return NULL;
  size_t len = strlen(text);
  char* answer = calloc(len+1,sizeof(char));
  for(int cnt=len-1; cnt>=0; cnt--) 
    answer[len-cnt-1] = toupper(text[cnt]); 
  answer[len] = '\0';
  return answer; 
}

char* tobinary(const int character){
  char* answer = calloc(9,sizeof(char));
  int ch = character;
  int test = 7;
  while(ch != 0 && test >= 0)
  {
    answer[test] = (ch%2)+48;
    ch = ch/2;
    test --;
  }
  if(ch == 0 && test != -1)
  {
    while(test >= 0)
    {
      answer[test] = 48;
      test --;
    }
  }
 
  answer[8] = '\0';

  return answer;
}

char from_bit(const char* bits){
  int answer = 0;
  for(int cnt=0; cnt<8; cnt++)
    answer += (bits[cnt]-48)*pow(2,7-cnt);
  free((char*) bits);
  return answer;
}

char* get_reversed_bits(const char* binary){
  char* answer = calloc(5,sizeof(char));
  answer[0] = binary[1];
  answer[1] = binary[0];
  answer[2] = binary[3];
  answer[3] = binary[2];
  answer[4] = '\0';
  return answer;
}


char* binary_encrypt(const char* binary){
  char* variables = get_reversed_bits(binary);

  char* chararray = calloc(5,sizeof(char));
  for(int cnt=0; cnt<4; cnt++)
  {
    if(variables[cnt] != binary[cnt+4])
      chararray[cnt] = 49;
    else chararray[cnt] = 48;
  }
  chararray[4] = '\0';

  char* answer = calloc(9,sizeof(char));
  for(int cnt=0; cnt<4; cnt++)
    answer[cnt] = variables[cnt];
  for(int cnt=0; cnt<4; cnt++)
    answer[cnt+4] = chararray[cnt];
  answer[8] = '\0';

  free(variables);
  free(chararray);
  free((char*) binary);

  return (char*) answer;
}

char* binary_decrypt(const char* binary){
  char* variables = calloc(5,sizeof(char));
  for(int cnt=0; cnt<4; cnt++)
  {
    if(binary[cnt] == binary[cnt+4])
      variables[cnt] = 48;
    else variables[cnt] = 49;
  }
  variables[4] = '\0';

  char* chararray = get_reversed_bits(binary);

  char* answer = calloc(9,sizeof(char));
  for(int cnt=0; cnt<4; cnt++)
    answer[cnt] = chararray[cnt];
  for(int cnt=0; cnt<4; cnt++)
    answer[cnt+4] = variables[cnt];
  answer[8] = '\0';

  free(variables);
  free(chararray);
  free((char* )binary);

  return (char*) answer;
}

unsigned char* bit_encrypt(const char* text){
  if(text == NULL || strlen(text) <= 1)
    return NULL;

  char* answer = calloc((strlen((char*) text)+1)*2,sizeof(char));
  if(answer == NULL)
    return NULL;
  int j = 0;

  for(int cnt=0; cnt<strlen(text); cnt++)
  {
    answer[j] = from_bit(binary_encrypt(tobinary(text[cnt])));
    j++;
  }
  answer[j] = '\0';

  return (unsigned char*) answer;
}

char* bit_decrypt(const unsigned char* text){
  if(text == NULL)
    return NULL;

  if(strlen((char*) text) <= 1)
    return NULL;

  char* answer = calloc((strlen((char*) text)+1)*3,sizeof(char));
  int j = 0;

  int cnt=0;
  while(1 == 1)
  {
    if(text[cnt] == '\0')
      break;
    answer[j] = from_bit(binary_decrypt(tobinary(text[cnt])));
    j++;
    cnt++;
  }
  answer[j] = '\0';
  return (char*) answer;
}

char* vigenere_encrypt(const char* key, const char* text) {
  if (key == NULL) return NULL;
  size_t len = strlen(key);
  if (len == 0) return NULL;
  
  if (text == NULL) return NULL;
  size_t dlzka = strlen(text);
  if (dlzka == 0) return NULL;

  int test = 0;
  size_t  cnt= 0;
  while (cnt < dlzka) 
  {
    char ch = toupper(text[cnt]);
    if (ch >= 65 && ch <= 90) test += 1;
    cnt += 1;
  }

  int w = 0;
  char variables[26][26];
  while (w <= 25) 
  {
    int velkost = 0;
    while (velkost <= 25) 
    {
      int test2 = 65 + ((65 + w) - 65 + velkost) % 26;
      char ch = (char)test2;
      variables[w][velkost] = ch;
      velkost += 1;
    }
    w += 1;
  }

  
  char chararray[test + 1];

  int j = 0;
  chararray[test] = '\0';
  
  size_t len3 = 0;
  while (len3 < dlzka) 
  {
    int charik = (int)toupper(text[len3]);

    if (charik >= 65 && charik <= 90) 
    {
      char ch = (char)charik;
      chararray[j] = ch;
      j++;
    }
    len3 += 1;
  }

  unsigned int in = 0;
  char pole[test + 1];
  pole[test] = '\0';
  

  while (in <= test - 1) 
  {
    size_t len = strlen(key);
    int z = in % len;
    char ch = toupper(key[z]);
    char zn = ch;
    if (zn < 65 || zn > 90) return NULL;
    pole[in] = zn;
    in += 1;
  }

  int calculate = 0;

  char *answer = (char*)calloc(dlzka + 1, sizeof *text);

  size_t y = 0;
  while (y < dlzka) 
  {
    int charik = (int)toupper(text[y]);
    char ch = (char)charik;
    if ((ch < 65) || (ch > 90)) {
      answer[y] = text[y];
    }
    else 
    {
      int count = chararray[calculate];
      count = count - 65;
      int ind = pole[calculate];
      ind = ind - 65;
      
      calculate++;
      answer[y] = variables[count][ind];
    } 
    y += 1;
  }
  return answer;
}

char* vigenere_decrypt(const char* key, const char* text) {
  if (key == NULL) return NULL;
  size_t len = strlen(key);
  if (len == 0) return NULL;
  
  if (text == NULL) return NULL;
  size_t dlzka = strlen(text);
  if (dlzka == 0) return NULL;

  int test = 0;
  size_t  cnt= 0;
  while (cnt < dlzka) 
  {
    char ch = toupper(text[cnt]);
    if (ch >= 65 && ch <= 90) test += 1;
    cnt += 1;
  }

  int w = 0;
  char variables[26][26];
  while (w <= 25) 
  {
    int velkost = 0;
    while (velkost <= 25) 
    {
      int h = 65 + ((65 + w) - 65 + velkost) % 26;
      char ch = (char)h;
      variables[w][velkost] = ch;
      velkost += 1;
    }
    w += 1;
  }

  char chararray[test + 1];
  
  int docasna = 0;
  for (int i = 0; i < strlen(text); i++) 
  {
    char chariik = toupper(text[i]);
    if (chariik > 64 && chariik < 91) 
    {
      chararray[docasna] = chariik;
      docasna++;
    }
  }
  chararray[test] = '\0';


  unsigned int in = 0;
  char pole[test + 1];
  pole[test] = '\0';
  

  while (in <= test - 1) 
  {
    size_t len = strlen(key);
    int z = in % len;
    char ch = toupper(key[z]);
    char zn = ch;
    if (zn < 65 || zn > 90) return NULL;
    pole[in] = zn;
    in += 1;
  }

  
  char* answer0 = (char*)calloc(dlzka + 1, sizeof *text);
  int test0 = 0;
  int variables5 = 0;

  while (test0 < dlzka) 
  {
    int charik = (int)(text[test0]);
    char chariik = (char)charik;
    if (chariik < 65 || chariik > 90) answer0[test0] = chariik;
    else
    {
      int cnt1 = (chararray[variables5] - 65);
      cnt1 = cnt1 - (pole[variables5] - 65);
      cnt1 = cnt1 + 26;
      cnt1 = cnt1 % 26;
      answer0[test0] = variables[0][cnt1];
      variables5 += 1;
    }
    test0 += 1;
  }
  return answer0;
}


unsigned char* bmp_encrypt(const char* key, const char* text){
  if(key == NULL || text == NULL)
    return NULL;

  if(strlen(key) <= 1 || strlen(text) <= 1)
    return NULL;

  for(int i=0; i<strlen(key); i++)
  {
    if((toupper(key[i]) >= 65 && toupper(key[i]) <= 90) || key[i] == '\0')
      continue;
    else return NULL;
  }

  char* pole = reverse(text);
  char* chararray = vigenere_encrypt(key,pole);
  free(pole);
  unsigned char* variables = bit_encrypt(chararray);
  free(chararray);
  return (unsigned char*) variables;
}

char* bmp_decrypt(const char* key, const unsigned char* text){
  if(key == NULL || text == NULL)
    return NULL;

  if(strlen(key) <= 1 || strlen((char*) text) <= 1)
    return NULL;

  for(int i=0; i<strlen(key); i++)
  {
    if((toupper(key[i]) >= 65 && toupper(key[i]) <= 90) || key[i] == '\0')
      continue;
    else return NULL;
  }

  char* variables = bit_decrypt(text);
  char* chararray = vigenere_decrypt(key,variables);
  free(variables);
  char* pole = reverse(chararray);
  free(chararray);
  return (char*) pole;
}


