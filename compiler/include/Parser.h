#include "../include/Lexer.h"

struct parser {
  SyntaxToken *tokens;
  int position;
};

typedef struct parser* Parser;

