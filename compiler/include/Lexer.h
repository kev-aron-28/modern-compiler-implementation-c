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

enum valueType{
  VALUE_INT,
  VALUE_FLOAT,
  VALUE_STRING,
  VALUE_BAD
};
typedef enum valueType ValueType;

typedef union {
  int valueInt;
  float valueFloat;
  String valueString;
} TokenValue;


struct syntaxToken {
  SyntaxKind kind;
  int position;
  String text;
  ValueType type;
  TokenValue value;
};

typedef struct syntaxToken* SyntaxToken;

// SyntaxToken methods
SyntaxToken CreateSyntaxToken(SyntaxKind kind, int start, String text);
SyntaxToken CreateStringToken(SyntaxKind kind, int start, String text, String value);
SyntaxToken CreateIntToken(SyntaxKind kind, int start, String text, int value);

struct lexer {
  String text;
  int position;
};

typedef struct lexer* Lexer; 

// Lexer methods
char Current(Lexer lexer);
void Next(Lexer lexer);
SyntaxToken NextToken(Lexer lexer);
