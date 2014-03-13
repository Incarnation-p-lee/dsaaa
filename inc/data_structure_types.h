#ifndef DATA_STRUCTURE_TYPES_H
#define DATA_STRUCTURE_TYPES_H

/*-     DATA STRUCTURE TYPE DEFINITION                                       -*/
struct single_linked_list{
  int value;
  struct single_linked_list *next;
};
struct doubly_linked_list{
  int value;
  struct doubly_linked_list *next;
  struct doubly_linked_list *previous;
};

#endif
