
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "slp.h"
#include "prog1.h"

typedef struct table *Table_;
struct table
{
  string id;
  int value;
  Table_ tail;
};

Table_ Table(string id, int value, struct table *tail)
{
  Table_ t = malloc(sizeof(*t));
  t->id = id;
  t->value = value;
  t->tail = tail;
  return t;
}

void print_table(Table_ table)
{
  while (table != NULL)
  {
    printf("ID: %s, Value: %d\n", table->id, table->value);
    table = table->tail;
  }
}

int lookup(Table_ interpreter, string id);
void traverse_stm(A_stm stm, Table_ *interpreter);
int eval_expr(A_exp exp, Table_ interpreter);
void traverse_expList(A_expList expList, Table_ *interpreter);

int lookup(Table_ interpreter, string id)
{
  while (interpreter != NULL)
  {
    if (strcmp(interpreter->id, id) == 0)
    {
      return interpreter->value;
    }

    interpreter = interpreter->tail;
  }
}

void traverse_stm(A_stm stm, Table_ *interpreter)
{
  switch (stm->kind)
  {
  case A_compoundStm:
    traverse_stm(stm->u.compound.stm1, interpreter);
    traverse_stm(stm->u.compound.stm2, interpreter);
    break;
  case A_assignStm:
    (*interpreter) = Table(
        stm->u.assign.id,
        eval_expr(stm->u.assign.exp, *interpreter),
        *interpreter);
    break;
  case A_printStm:
    traverse_expList(stm->u.print.exps, interpreter);
    break;
  }
}

int eval_expr(A_exp exp, Table_ interpreter)
{
  switch (exp->kind)
  {
  case A_idExp:
    return lookup(interpreter, exp->u.id);
    break;
  case A_numExp:
    return exp->u.num;
  case A_opExp:
  {
    int left = eval_expr(exp->u.op.left, interpreter);
    int right = eval_expr(exp->u.op.right, interpreter);

    switch (exp->u.op.oper)
    {
    case A_plus:
      return left + right;
    case A_minus:
      return left - right;
    case A_times:
      return left * right;
    case A_div:
      if (right == 0)
      {
        printf("Error division by 0\n");
        exit(1);
      }
      return left / right;
    }
  }
  case A_eseqExp:
    traverse_stm(exp->u.eseq.stm, &interpreter);
    return eval_expr(exp->u.eseq.exp, interpreter);
    break;
  }
}

void traverse_expList(A_expList expList, Table_ *interpreter) {
  switch (expList->kind)
  {
  case A_pairExpList:
    printf("%d\n", eval_expr(expList->u.pair.head, *interpreter));
    traverse_expList(expList->u.pair.tail, interpreter);
    break;
  case A_lastExpList:
    printf("%d\n", eval_expr(expList->u.last, *interpreter));
    break;
  default:
    break;
  }
}

int main(int argc, char const *argv[])
{
  const A_stm program = prog();
  Table_ interpreter = NULL;
  traverse_stm(program, &interpreter);
  print_table(interpreter);
  return 0;
}
