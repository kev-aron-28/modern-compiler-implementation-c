
#include <stdio.h>
#include <stdlib.h>
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

void traverse_stm(A_stm stm, Table_ *interpreter);
void traverse_exp(A_exp exp, string id, Table_ *interpreter);
void traverse_expList(A_expList expList, string id, Table_ *interpreter);

void traverse_stm(A_stm stm, Table_ *interpreter)
{
  switch (stm->kind)
  {
  case A_compoundStm:
    traverse_stm(stm->u.compound.stm1, interpreter);
    traverse_stm(stm->u.compound.stm2, interpreter);
    break;
  case A_assignStm:
    traverse_exp(stm->u.assign.exp, stm->u.assign.id, interpreter);
    // Additional processing for assign statement
    break;
  case A_printStm:
    traverse_expList(stm->u.print.exps, "", interpreter);
    // Additional processing for print statement
    break;
  }
}

void traverse_exp(A_exp exp, string id, Table_ *interpreter)
{
  switch (exp->kind)
  {
  case A_idExp:
    break;
  case A_numExp:
    break;
  case A_opExp:
    traverse_exp(exp->u.op.left, id, interpreter);
    traverse_exp(exp->u.op.right, id, interpreter);
    // Additional processing for operation expression
    break;
  case A_eseqExp:
    traverse_stm(exp->u.eseq.stm, interpreter);
    traverse_exp(exp->u.eseq.exp, id, interpreter);
    // Additional processing for eseq expression
    break;
  }
}

void traverse_expList(A_expList expList, string id, Table_ *interpreter)
{
  switch (expList->kind)
  {
  case A_pairExpList:
    traverse_exp(expList->u.pair.head, id, interpreter);
    traverse_expList(expList->u.pair.tail, id, interpreter);
    // Additional processing for pair expression list
    break;
  case A_lastExpList:
    traverse_exp(expList->u.last, id, interpreter);
    // Additional processing for last expression list
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
