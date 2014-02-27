#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H


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
#define PRINT_WIDTH            10


struct single_linked_list *
generate_linked_list(int *, int);
void
append_linked_list_node(struct single_linked_list *, int);
void
clear_linked_list(struct single_linked_list **);
int
lengthof_linked_list(struct single_linked_list *head);
struct single_linked_list *
accessby_index_linked_list(struct single_linked_list *, int);
void
print_single_linked_list(FILE *, char *, struct single_linked_list *);

#endif
