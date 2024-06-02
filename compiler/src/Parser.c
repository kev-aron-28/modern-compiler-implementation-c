#include <stdio.h>
#include <stdlib.h>
#include "../include/Parser.h"

const int TOKEN_LIST_LEN = 20;

ASTNode createNumberNode(int value)
{
  ASTNode node = (ASTNode)malloc(sizeof(struct astNode));
  node->type = AST_NUMBER;
  node->data.number.value = value;
  return node;
}

ASTNode createBinaryOpNode(SyntaxKind op, ASTNode left, ASTNode right)
{
  ASTNode node = (ASTNode)malloc(sizeof(struct astNode));
  node->type = AST_BINARY_OP;
  node->data.binaryOp.op = op;
  node->data.binaryOp.left = left;
  node->data.binaryOp.right = right;
  return node;
}

void InitParser(Parser parser, String text)
{
  parser->tokensLen = 0;
  Lexer lexer = (Lexer)malloc(sizeof(struct lexer));
  SyntaxToken token;
  SyntaxToken *tokens = (SyntaxToken *)malloc(TOKEN_LIST_LEN * sizeof(struct syntaxToken));
  int len = 0;
  int capacity = TOKEN_LIST_LEN;

  lexer->text = strdup(text);
  lexer->position = 0;
  if (tokens == NULL)
  {
    printf("Memory allocation faild\n");
    exit(1);
  }

  do
  {
    token = NextToken(lexer);
    if (token->kind != WhiteSpaceToken && token->kind != BadToken)
    {
      if (len >= capacity)
      {
        capacity *= 2;
        SyntaxToken *new_tokens = (SyntaxToken *)realloc(tokens, capacity * sizeof(SyntaxToken));
        if (new_tokens == NULL)
        {
          printf("Memory allocation faild\n");
          for (int i = 0; i < len; i++)
          {
            free(tokens[i]->text);
            free(tokens[i]);
          }
          free(tokens);
          free(lexer->text);
          free(lexer);
          exit(1);
          exit(1);
        }
        tokens = new_tokens;
      }
      tokens[len++] = token;
    }
  } while (token->kind != EndOfFileToken);
  parser->tokens = tokens;
  parser->tokensLen = len;
  parser->position = 0;

  free(lexer->text);
  free(lexer);
}

SyntaxToken ParserPeek(Parser parser, int offset)
{
  int index = parser->position + offset;
  if (index >= parser->tokensLen)
  {
    return NULL;
  }
  return parser->tokens[index];
}

SyntaxToken ParserCurrent(Parser parser)
{
  return ParserPeek(parser, 0);
}

SyntaxToken ParserNextToken(Parser parser)
{
  SyntaxToken current = ParserCurrent(parser);
  parser->position++;
  return current;
}

SyntaxToken Match(Parser parser, SyntaxKind kind)
{
  SyntaxToken current = ParserCurrent(parser);
  if (current->kind == kind)
  {
    return ParserNextToken(parser);
  }
  SyntaxToken newToken = (SyntaxToken)malloc(sizeof(struct syntaxToken));
  newToken->kind = kind;
  newToken->position = current->position;
  return newToken;
}

ASTNode ParseExpression(Parser parser)
{
  ASTNode left = ParseTerm(parser);
  SyntaxToken token = ParserCurrent(parser);
  while (token != NULL && (token->kind == PlusToken ||
                           token->kind == MinusToken ||
                           token->kind == StarToken ||
                           token->kind == DivideToken))
  {
    ParserNextToken(parser);
    ASTNode right = ParseTerm(parser);
    left = createBinaryOpNode(token->kind, left, right);
    token = ParserCurrent(parser);
  }

  return left;
}

ASTNode ParseTerm(Parser parser)
{
  ASTNode left = ParseFactor(parser);
  SyntaxToken token = ParserCurrent(parser);

  while (token != NULL && (token->kind == StarToken || token->kind == DivideToken))
  {
    ParserNextToken(parser);
    ASTNode right = ParseFactor(parser);
    left = createBinaryOpNode(token->kind, left, right);
    token = ParserCurrent(parser);
  }

  return left;
}

ASTNode ParseFactor(Parser parser)
{
  SyntaxToken token = ParserNextToken(parser);

  if (token->kind == NumberToken)
  {
    return createNumberNode(token->value.valueInt);
  }
  else if (token->kind == LeftParToken)
  {
    ASTNode node = ParseExpression(parser);
    if (ParserCurrent(parser)->kind == RigthParToken)
    {
      ParserNextToken(parser);
    }
    else
    {
      printf("Error: Expected ')'\n");
      exit(1);
    }
    return node;
  }
  else
  {
    printf("Error: Unexpected token\n");
    exit(1);
  }
}

int evaluateAST(ASTNode node)
{
  if (node->type == AST_NUMBER)
  {
    return node->data.number.value;
  }
  else
  {
    int leftValue = evaluateAST(node->data.binaryOp.left);
    int rightValue = evaluateAST(node->data.binaryOp.right);

    switch (node->data.binaryOp.op)
    {
    case PlusToken:
      return leftValue + rightValue;
    case MinusToken:
      return leftValue - rightValue;
    case StarToken:
      return leftValue * rightValue;
    case DivideToken:
      return leftValue / rightValue;
    default:
      printf("Error: Unknown operator\n");
      exit(1);
    }
  }
  printf("Error: Unknown node type\n");
  exit(1);
}
