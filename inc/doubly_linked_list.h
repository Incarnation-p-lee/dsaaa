#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H


/*-     EXTERNALS                                                            -*/
extern void
error_handle(const char *);
extern void
warning_prompt(char *);
extern void
exchange(int *, int *);
extern void
leave(void);
extern void
enter(const char *);
extern void
malloc_initial(void **, unsigned int);
extern void
saft_free(void **);



/*-     TYPE, MARCO AND VARIABLE                                             -*/



struct doubly_linked_list *
generate_dlinked_list(int *, int);
void
append_dlinked_list_node(struct doubly_linked_list *, int);
void
destroy_dlinked_list(struct doubly_linked_list **);
int
lengthof_dlinked_list(struct doubly_linked_list *head);
struct doubly_linked_list *
accessby_index_dlinked_list(struct doubly_linked_list *, int);
void
print_dlinked_list(FILE *, char *, struct doubly_linked_list *);
void
exchange_dlinked_list(struct doubly_linked_list **,
                      struct doubly_linked_list *);
void
print_reverse_dlinked_list(FILE *, char *, struct doubly_linked_list *);
void
serialize_dlinked_list(struct doubly_linked_list *);
void
initial_dlinked_list_node(struct doubly_linked_list *);
void
insert_after_dlinked_list(struct doubly_linked_list *,
                          struct doubly_linked_list *);
struct doubly_linked_list *
remove_node_dlinked_list(struct doubly_linked_list *);

#endif

