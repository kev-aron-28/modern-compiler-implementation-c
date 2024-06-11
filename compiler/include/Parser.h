#include "../include/Lexer.h"
#include "../include/Utils.h"

struct parser {
  SyntaxToken *tokens;
  int position;
  int tokensLen;
};

typedef struct parser* Parser;

typedef enum {
  AST_NUMBER,
  AST_BINARY_OP,
  AST_UNARY_OP
} ASTNodeType;

struct astNode {
  ASTNodeType type;

  union {
    struct {
      int value;
    } number;

    struct {
      struct astNode *operand;
      SyntaxKind op;
    } unaryOp;

    struct {
      struct astNode *left;
      struct astNode *right;
      SyntaxKind op;
    } binaryOp;
  } data;
};

typedef struct astNode* ASTNode;

ASTNode createNumberNode(int value);
ASTNode createBinaryOpNode(SyntaxKind op, ASTNode left, ASTNode right);
ASTNode createUnaryOpNode(SyntaxKind op, ASTNode operand);

void InitParser (Parser parser, String text);
SyntaxToken ParserPeek(Parser parser, int offset);
SyntaxToken ParserCurrent(Parser parser);
SyntaxToken Parse(Parser parser);
SyntaxToken ParserNextToken(Parser parser);
SyntaxToken Match(Parser parser, SyntaxKind kind);

ASTNode ParseExpression(Parser parser);
ASTNode ParseTerm(Parser parser);
ASTNode ParseFactor(Parser parser);
int evaluateAST(ASTNode node);

//     +
//    /
//   +
//  / \
// 1   2
