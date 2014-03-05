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
generate_slinked_list(int *, int);
void
append_slinked_list_node(struct single_linked_list *, int);
void
clear_slinked_list(struct single_linked_list **);
int
lengthof_slinked_list(struct single_linked_list *head);
struct single_linked_list *
accessby_index_slinked_list(struct single_linked_list *, int);
void
print_slinked_list(FILE *, char *, struct single_linked_list *);

#endif
