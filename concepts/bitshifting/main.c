#include <cstdio>

/*
 * objectives: 
 *  bitshift a char to have up to 8 binary values
 *  bitshift chars to ints
 */

bool eval_bit(char byte, char idx){ 
  // works with unsigned and signed chars.
  // since in both cases, the binary digits lead to odd/even numbers in th same order
  // eg:
  //  -128 = 1000 0000 = 128    // even 
  //  -127 = 1000 0001 = 129    // odd 
  int offset = 7-idx;
  return (byte >> offset) % 2 != 0;
}

int main() {

  char v = 255;
  bool bv = eval_bit(v, 0);
  if (bv){
    printf("true\n");
  } else {
    printf("false\n");
  }

}
