#include <string.h>
#include "lexer.h"

int main() {
  char* string = "print('hello world')";
  Lexer l; 
  l.content = string;
  l.content_len = strlen(string);
  print_tokens(&l);
   
  return 0;
}
