#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

extern char strinfo_buf[STRINFO_BUF_SIZE];

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
#define PRINT_WIDTH            20


struct single_linked_list *
generate_slinked_list(int *, int);
struct single_linked_list *
append_slinked_list_node(struct single_linked_list *, int);
void
destroy_slinked_list(struct single_linked_list **);
int
lengthof_slinked_list(struct single_linked_list *head);
struct single_linked_list *
accessby_index_slinked_list(struct single_linked_list *, int);
void
print_slinked_list(FILE *, char *, struct single_linked_list *);
void
exchange_slinked_list(struct single_linked_list **,
                      struct single_linked_list *);
void
serialize_slinked_list(struct single_linked_list *);
struct single_linked_list *
initial_slinked_list(void);
void
delete_slinked_list_node(struct single_linked_list **,
                         struct single_linked_list *);

#endif
