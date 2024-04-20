#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <ctype.h>

typedef enum {
  END_TOKEN = 0,
  KEYWORD_TOKEN,
  IDENTIFIER_TOKEN,
  LITERAL_TOKEN,
  OPERATOR_TOKEN,
  PUNCTUATOR_TOKEN
} TokenType;

typedef struct {
  char* content;
  size_t content_len;
  size_t pos;
  size_t bol;
  size_t line;
} Lexer;

void print_tokens(Lexer* l) {
  for (size_t i = 0; i < l->content_len; ++i) {
    if (isalpha(l->content[i])) {
      printf("%c\n", l->content[i]);
    }
  }
}

#endif
