#include "../include/Utils.h"
#include <string.h>
#include <ctype.h>

enum syntaxKind {
  NumberToken,
  WhiteSpaceToken,
  PlusToken,
  MinusToken,
  StarToken,
  DivideToken,
  LeftParToken,
  RigthParToken,
  BadToken,
  EndOfFileToken
};

typedef enum syntaxKind SyntaxKind;

struct syntaxToken {
  SyntaxKind kind;
  int position;
  String text;
};

typedef struct syntaxToken* SyntaxToken;
// SyntaxToken methods

SyntaxToken CreateSyntaxToken(SyntaxKind kind, int start, String text);

struct lexer {
  String text;
  int position;
};

typedef struct lexer* Lexer; 
// Lexer methods
char Current(Lexer lexer);
void Next(Lexer lexer);
SyntaxToken NextToken(Lexer lexer);
