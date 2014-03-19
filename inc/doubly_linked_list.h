#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H


/*-     EXTERNALS                                                            -*/
extern void
error_handle(const char *);
extern void
warn_prompt(const char *);
extern void
exchange(int *, int *);
extern void
leave(void);
extern void
enter(const char *);
extern void
malloc_initial(void **, unsigned int);
extern void
realloc_initial(void **, unsigned int);
extern void
saft_free(void **);



/*-     TYPE, MARCO AND VARIABLE                                             -*/

struct doubly_linked_list *
generate_dlinked_list(int *, int);
void
append_dlinked_list_node(struct doubly_linked_list *, int);
void
clear_dlinked_list(struct doubly_linked_list **);
int
lengthof_dlinked_list(struct doubly_linked_list *head);
struct doubly_linked_list *
accessby_index_dlinked_list(struct doubly_linked_list *, int);
void
print_dlinked_list(FILE *, char *, struct doubly_linked_list *);
void
exchange_dlinked_list(struct doubly_linked_list **,
  struct doubly_linked_list *);

#endif

