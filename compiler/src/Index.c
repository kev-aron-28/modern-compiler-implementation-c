#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <../include/Lexer.h>
#include <../include/InputReader.h>
#include <../include/Utils.h>

int main(int argc, char const *argv[])
{
  String string;
  
  Lexer lexer = (Lexer)malloc(sizeof(struct lexer));

  while (1)
  {
    printf("> ");
    string = ReadInput();
    lexer->text = (String)malloc(strlen(string) + 1);
    strcpy(lexer->text, string);
    lexer->position = 0;

    while(1) {
      SyntaxToken token = NextToken(lexer);
      if(token->kind == EndOfFileToken) {
        break;
      }

      if(token->type == VALUE_INT) {
        printf("NUMBER %d \n", token->value.valueInt);
      }

    }

  }

  free(lexer);
  


  return 0;
}
