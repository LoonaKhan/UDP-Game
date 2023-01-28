#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdint>

/*
 * objective: 
 *  convert a char to a signed int
 *
 * tests:
 *  positive integer
 *  negative integer 
 */

int main() {

  char raw[] = {-20,-1,-1,-1};

  int LilEndian = raw[0] | (raw[1] << 8) | (raw[2] << 16) | (raw[3] << 24);
  int BigEndian = raw[3] | (raw[2] << 8) | (raw[1] << 16) | (raw[0] << 24);


  printf("LilEndian: %d\n", LilEndian);
  printf("BigEndian: %d\n", BigEndian);
}
