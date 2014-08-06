#ifndef DATA_STRUCTURE_TYPES_H
#define DATA_STRUCTURE_TYPES_H


struct single_linked_list{
  int    index;
  struct single_linked_list *next;
};

struct doubly_linked_list{
  int    index;
  struct doubly_linked_list *next;
  struct doubly_linked_list *previous;
};

/*
 * sp point to top of stack
 * bp point to the first element of a array in void * type
 */
struct stack_loc{
  void **sp;
  void *bp;
};

struct array_stack{
  struct stack_loc loc;
  unsigned         rest;
  unsigned         size;
};

#endif
