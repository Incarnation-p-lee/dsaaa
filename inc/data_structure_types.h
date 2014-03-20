#ifndef DATA_STRUCTURE_TYPES_H
#define DATA_STRUCTURE_TYPES_H


struct single_linked_list{
  int index;
  struct single_linked_list *next;
};
struct doubly_linked_list{
  int index;
  struct doubly_linked_list *next;
  struct doubly_linked_list *previous;
};

#endif
