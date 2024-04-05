
#include <stdio.h>
#include <stdio.h>
#include <util.c>
#include <slp.h>

typedef struct table *Table_;
struct table { string id; int value; Table_ tail };

Table_ Table(string id, int value, struct table *tail) {
  Table_ t = malloc(sizeof(*t));
  t->id = id; t->value = value; t->tail=tail;
  return t;
}

Table_ interpStm(A_stm s, Table_ t) {
  return;
}

int main(int argc, char const *argv[])
{
  const A_stm program = prog();
  interpStm(program, NULL);

  return 0;
}
