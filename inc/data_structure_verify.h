#ifndef DATA_STRUCTURE_VERIFY_H
#define DATA_STRUCTURE_VERIFY_H


/*-     EXTERNALS                                                            -*/
extern const int raw_data[];
extern FILE *dsaaa_report;
extern const char *blank;
extern const char *error_digest[];
extern const char *warning_digest[];

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
realloc_initial(void **, unsigned int);
extern void
saft_free(void **);


/*-     DATA STRUCTURE TYPE DEFINITION                                       -*/
#define RAW_DATA_SIZE          sizeof(raw_data) / sizeof(raw_data[0])
#define STRUCTSET_DIM          sizeof(structure_set) / sizeof(structure_set[0])


void
data_structure_verify(void);
static void
single_linked_list_verify(void);
static void
doubly_linked_list_verify(void);
static void
print_operation(const char *);
static void
print_done(const char *);
static void
print_slist_result(struct single_linked_list *);
static void
print_slist_node(struct single_linked_list *);
static void
print_dlist_result(struct doubly_linked_list *);
static void
print_dlist_node(struct doubly_linked_list *);


/*-     GLOBAL or STATIC AVAILABLES                                          -*/
static const char *ds_info[] = {
  "Single Linked List",
  "Doubly Linked List",
};
static void (*structure_set[])(void) = {
  &single_linked_list_verify,
  &doubly_linked_list_verify,
};


#endif
