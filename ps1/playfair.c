#include <stdbool.h>
#include "playfair.h"
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int does_exist(const char piismenko, const char* grid) {
  int p = strlen(grid);

  for (int i = 0; i < p; i++) {
    if (piismenko == grid[i]) return 1;
  }

  return 0;
}

char* check_key(const char* key) {
  int p = strlen(key);

  int i = 0;
  char* grid = (char*)calloc(p + 1, sizeof *key);

  int pocet = 0;
  while (pocet < p) 
  {
    char piismenko = toupper(key[pocet]);
    if (piismenko >= 65 && piismenko <= 90) 
    {
      if (piismenko == 87) piismenko = 86;
      if (!does_exist(piismenko, grid)) 
      {
        grid[i] = piismenko;
        i++;
      }
    } 
    else if (piismenko != 32)
    {
      return NULL;
    }
    pocet++;
  }
  
  return grid;
}

char* edit_text_second(const char* text) {
  int i = 0;
  char* str = (char*)calloc(strlen(text) + 1, sizeof *text);

  int p = strlen(text);
  int k = 0;
  while (k < p) 
  {
    char piismenko = toupper(text[k]);
    if (piismenko == 32) 
    {
      k++;
      continue;
    }
    else if (piismenko == 87) 
    {
      str[i] = 86;
      i++;
    }
    else if (piismenko > 64 && piismenko < 91) 
    {
      str[i] = piismenko;
      i++;
    } 
    else 
    {
      free(str);
      return NULL;
    }
    
    k++;
  }
  return str;
}

char* vlozitX(const char* text) {
  int p = 0;

  char *str = edit_text_second(text);
  if (str == NULL) {
    return NULL;
  }

  int test1 = 1;
  while (test1 <= strlen(str) - 1)
  {
    if ((str[test1] != 88) & (str[test1 - 1] == str[test1])) 
    {
      p++;
    }
    test1 = test1 + 2;
  }

  if (strlen(str) + p % 2 != 0) p += 1;

  char* output = (char*)calloc(strlen(str) + p + 2, sizeof *text);

  int k;
  int pocet = 0;
  
  for (k = 1; k <= strlen(str) - 1; k += 2) 
  {
    char z_prve = str[k - 1];
    output[pocet] = z_prve;
    pocet++;
    char z_druhe = str[k];
    if ((z_prve != 88) & (z_prve == z_druhe)) 
    {
      k--;
      output[pocet] = 88;
    } else {
      output[pocet] = z_druhe;
    }
    pocet++;
  }

  if (strlen(output) != strlen(str) + p) {
    output[pocet] = str[k - 1];
    int s = strlen(output);
    pocet++;
    if (s % 2 != 0) output[pocet] = 88;
  }

  free(str);
  return output;
}

void look_for(const char piismenko, const char aaa[][5], int *symbol_riadok, int *symbol_stlpcek) {
  int pocet = 0;
  while (pocet < 5) 
  {
    for (int test1 = 0; test1 <= 4; test1++) 
    {
      if (aaa[pocet][test1] == piismenko) 
      {
        *symbol_stlpcek = test1;
        *symbol_riadok = pocet;
      }
    }
    pocet += 1;
  }
}

char* playfair_encrypt(const char* key, const char* text) {
  if (key == NULL || text == NULL) return NULL;
  
  int p = strlen(key);
  if (p == 0) return (char*)key;
  else if (key[0] == 32) return NULL;
  
  int size = strlen(text);
  if (size == 0) return (char*)text;
  
  char aaa[5][5];

  char *grid = check_key(key);

  if (grid == NULL) 
  {
    free(grid);
    return NULL;
  }

  int s = strlen(grid) / 5;
  if (strlen(grid) % 5 != 0) s++;


  int i = 0;
  for (int pocet = 0; pocet < s; pocet++) 
  {
    int test1 = 0;
    while (i < strlen(grid) && test1 < 5) 
    {
      aaa[pocet][test1] = grid[i];
      test1++;
      i++;
    }
  }


  int test1 = strlen(grid) % 5;
  
  int c = 0;

  for (int pocet = strlen(grid) / 5; pocet < 5; pocet ++) 
  {
    while (test1 <= 4) 
    {
      char piismenko = ALPHA[c];
      if (!does_exist(piismenko, grid)) 
      {
        aaa[pocet][test1] = ALPHA[c];
        test1++;
      }
      c++;
    }
    test1 = 0;
  }

  char* allvariables = vlozitX(text);

  if (allvariables == NULL) 
  {
    free(allvariables);
    free(grid);
    return NULL;
  }
  
  
  int parameters = strlen(allvariables) / 2 - 1;
  char* result = (char*)calloc(strlen(allvariables) + parameters + 1, sizeof *allvariables);
  int idx = 0;
  
  int k = 0;
  while (k < strlen(allvariables)) 
  {
    int test10_row;
    int test10_column;
    int test11_row;
    int test11_column;

    look_for(allvariables[k], aaa, &test10_row, &test10_column);
    look_for(allvariables[k + 1], aaa, &test11_row, &test11_column);
    
    char z_prve = allvariables[k];
    char z_druhe = allvariables[k + 1];

    if (z_prve == 88 && z_druhe == 88) 
    {
      int pocet;
      pocet = (test11_row + 1) % 5;
      result[idx + 1] = aaa[pocet][test11_column];
      pocet = (test10_row + 1) % 5;
      result[idx] = aaa[pocet][test10_column];
      idx += 2;
    }

    else if (test11_column == test10_column) 
    {
      int pocet;
      pocet = (test11_row + 1) % 5;
      result[idx + 1] = aaa[pocet][test11_column];
      pocet = (test10_row + 1) % 5;
      result[idx] = aaa[pocet][test10_column];
      idx += 2;
    }

    else if (test10_row == test11_row) 
    {
      int test1;
      test1 = (test11_column + 1) % 5;
      result[idx + 1] = aaa[test10_row][test1];
      test1 = (test10_column + 1) % 5;
      result[idx] = aaa[test10_row][test1];
      idx += 2;
    }
    
    else 
    {
      result[idx + 1] = aaa[test11_row][test10_column];
      result[idx] = aaa[test10_row][test11_column];
      idx += 2;
    }
    
    if (k + 2 < strlen(allvariables)) 
    {
      result[idx] = 32;
      idx++;
    }

    k = k + 2;
  }

  free(grid);
  free(allvariables);

  return result;
}

char* playfair_decrypt(const char* key, const char* text) {
  if (key == NULL || text == NULL) return NULL;
  
  int p = strlen(key);
  if (p == 0) return (char*)key;
  else if (key[0] == 32) return NULL;
  
  int size = strlen(text);
  if (size == 0) return (char*)text;

  char aaa[5][5];

  char *grid = check_key(key);

  if (grid == NULL) 
  {
    free(grid);
    return NULL;
  }



  int s = strlen(grid) / 5;
  if (strlen(grid) % 5 != 0) s++;


  int i = 0;
  for (int pocet = 0; pocet < s; pocet++) 
  {
    int test1 = 0;
    while (i < strlen(grid) && test1 < 5) 
    {
      aaa[pocet][test1] = grid[i];
      test1++;
      i++;
    }
  }


  int test1 = strlen(grid) % 5;

  
  int c = 0;

  for (int pocet = strlen(grid) / 5; pocet < 5; pocet ++) 
  {
    while (test1 <= 4) 
    {
      char piismenko = ALPHA[c];
      if (!does_exist(piismenko, grid)) 
      {
        aaa[pocet][test1] = ALPHA[c];
        test1++;
      }
      c++;
    }
    test1 = 0;
  }


  int idx = 0;
  int parameters = strlen(text) / 3;
  char* output = (char*)calloc(strlen(text) - parameters + 1, sizeof *text);

  for (int i = 0; i < strlen(text); i = i + 3) {

    char z_prve = text[i];
    char z_druhe = text[i + 1];
    if (z_prve == 87 || z_druhe == 87) {
      free(grid);
      free(output);
      return NULL;
    }

    int test10_row;
    int test10_column;
    int test11_row;
    int test11_column;

    look_for(z_prve, aaa, &test10_row, &test10_column);
    look_for(z_druhe, aaa, &test11_row, &test11_column);
    
    int test15, test16;

    if (test10_row == 0) test15 = 4;
    else test15 = test10_row - 1;

    if (test11_row == 0) test16 = 4;
    else test16 = test11_row - 1;

    if (aaa[test16][test11_column] == 88 && aaa[test15][test10_column] == 88) 
    {
      output[idx + 1] = 88;
      output[idx] = 88;
    }

    else if (test10_column == test11_column) 
    {
      int pocet;
      if (test10_row != 0) 
      {
        pocet = (test10_row - 1) % 5;
      } 
      else 
      {
        pocet = 4;
      }
      output[idx] = aaa[pocet][test10_column];
      if (test11_row != 0) 
      {
        pocet = (test11_row - 1) % 5;
      } 
      else 
      {
        pocet = 4;
      }
      output[idx + 1] = aaa[pocet][test11_column];
    }

    else if (test10_row == test11_row) 
    {
      int test1;
      if (test10_column != 0) 
      {
        test1 = (test10_column - 1) % 5;
      } else 
      {
        test1 = 4;
      }
      output[idx] = aaa[test10_row][test1];
      if (test11_column != 0) 
      {
        test1 = (test11_column - 1) % 5;
      } 
      else 
      {
        test1 = 4;
      }
      output[idx + 1] = aaa[test10_row][test1];
    }
    

    else 
    {
      output[idx + 1] = aaa[test11_row][test10_column];
      output[idx] = aaa[test10_row][test11_column];
    }
    idx += 2;
  }


  free(grid);

  return output;
}


