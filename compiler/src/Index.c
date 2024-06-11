#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <../include/Parser.h>
#include <../include/InputReader.h>
#include <../include/Utils.h>

void printIndent(int level) {
    for (int i = 0; i < level; i++) {
        printf("  "); // two spaces per level of indentation
    }
}

void prettyPrintAST(ASTNode node, int level) {
    if (node == NULL) {
        return;
    }

    printIndent(level);

    switch (node->type) {
        case AST_NUMBER:
            printf("↦ %d\n", node->data.number.value);
            break;
        case AST_BINARY_OP:
            printf(" ↳ %s\n", 
                node->data.binaryOp.op == PlusToken ? "+" :
                node->data.binaryOp.op == MinusToken ? "-" :
                node->data.binaryOp.op == StarToken ? "*" :
                node->data.binaryOp.op == DivideToken ? "/" : "Unknown");
            prettyPrintAST(node->data.binaryOp.left, level + 1);
            prettyPrintAST(node->data.binaryOp.right, level + 1);
            break;
    }
}

int main(int argc, char const *argv[])
{
  String string;
  
  Parser parser = (Parser)malloc(sizeof(struct parser));
  InitParser(parser, "--2");
  ASTNode root = ParseExpression(parser);
  prettyPrintAST(root, 0);

  int result = evaluateAST(root);
  printf("RESULT %d \n", result);
  return 0;
}
