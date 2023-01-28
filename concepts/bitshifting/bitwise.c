#include <cstdio>

int main(){

  int a = 60; // 60 = 0011 1100
  int b = 13; // 13 = 0000 1101

  // binary AND  operator(&) 
  // takes the binary data of each and for each bit, x.y
  printf("Binary '&' operator (%d . %d): %d\n", a, b, (int)(a & b)); 

  // binary OR operator (|) 
  // x + y for each bit 
  printf("Binary '|' operator (%d + %d): %d\n", a, b, (int)(a | b));

  // binary XOR
  printf("Binary '^' operator (%d (+) %d): %d\n", a, b, (int)(a ^ b));

  // 1's compliment: (~)
  printf("1's compliment '~' operator (flips bits of %d): %d\n", a, int(~a));

  // 2's compliment
  // since ~n = -(n+1)
  // -n = ~n + 1 
  printf("2's compliment (~%d + 1): %d\n", a, (int)(~a + 1));

  // left shift (<<)
  // shifts the bits by the number specified
  // a << x
  printf("left shift operator '<<'. shifts to the left by num specified: %d << %d -> %d\n", 1, 4, (int)(1<<4));

  // right shift (>>)
  // same thing
  // a >> x
  printf("right shift operator '>>'. shifts to the right by num specified: %d >> %d -> %d\n", 17, 4, (int)(18 >> 4));

  // shifts move it x digits. count from 1 
}
