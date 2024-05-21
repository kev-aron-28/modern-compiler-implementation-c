#include <../include/Lexer.h>
#include <../include/Utils.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


// SyntaxToken methods
SyntaxToken CreateSyntaxToken(SyntaxKind kind, int start, String text) {
  SyntaxToken token = (SyntaxToken)malloc(sizeof(struct syntaxToken));
    if (token != NULL) {
      token->kind = kind;
      token->position = start;
      token->text = (String)malloc(strlen(text) + 1);
      strcpy(token->text, text);
    }

    return token;
}

// Lexer methods
char Current(Lexer yalLexer) {
  if(yalLexer->position >= strlen(yalLexer->text)) {
    return '\0';
  }

  return yalLexer->text[yalLexer->position];
}

void Next(Lexer yalLexer) {
  yalLexer->position++;
}

SyntaxToken NextToken(Lexer yalLexer) {
  // Look for numbers
  // * - + / ()
  // Whitespace
  char current = Current(yalLexer);
  if(yalLexer->position >= strlen(yalLexer->text)) {
    return CreateSyntaxToken(EndOfFileToken, yalLexer->position, "\0");
  }

  if(isdigit(current)) {
    int start = yalLexer->position;
    while(isdigit(Current(yalLexer))) {
      Next(yalLexer);
    }

    int length = yalLexer->position - start;
    String text = Substring(yalLexer->text, start, length);

    return CreateSyntaxToken(NumberToken, start, text);
  }

  if(isspace(current)) {
    int start = yalLexer->position;
    while(isspace(Current(yalLexer))) {
      Next(yalLexer);
    }

    int length = yalLexer->position - start;
    // String text = Substring(yalLexer->text, start, length);
    return CreateSyntaxToken(WhiteSpaceToken, start, " ");
  }

  if(current == '+') {
    return CreateSyntaxToken(PlusToken, yalLexer->position++, (String)"+");
  }

  if(current == '-') {
    return CreateSyntaxToken(MinusToken, yalLexer->position++, (String)"-");
  }

  if(current == '*') {
    return CreateSyntaxToken(StarToken, yalLexer->position++, (String)"*");
  }

  if(current == '/') {
    return CreateSyntaxToken(DivideToken, yalLexer->position++, (String)"/");
  }

  if(current == '(') {
    return CreateSyntaxToken(LeftParToken, yalLexer->position++, (String)"(");
  }

  if(current == ')') {
    return CreateSyntaxToken(RigthParToken, yalLexer->position++, (String)")");
  }

  return CreateSyntaxToken(BadToken, yalLexer->position++, Substring(yalLexer->text, yalLexer->position, 1));
}
