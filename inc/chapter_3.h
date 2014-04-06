#ifndef CHAPTER3_H
#define CHAPTER3_H

/*-     EXTERNALS                                                            -*/
extern FILE *dsaaa_report;
extern int int_random[];
extern const char *warning_digest[];
extern const char *error_digest[];
extern char strinfo_buf[];

/*-     REFERENCE OF GENERATE FUNCTION MODULE                                -*/
extern void
error_handle(const char *);
extern void
warning_prompt(char *);
extern void
timing_start(void);
extern void
timing_end(unsigned *);
extern void
exchange(int *, int *);
extern void
leave(void);
extern void
enter(const char *);
extern void
print_report_header(FILE *, const char *, int, int);
extern void
malloc_initial(void **, unsigned int);
extern void
realloc_initial(void **, unsigned int);
extern void
saft_free(void **);
extern void
clear_slinked_list(struct single_linked_list **);
extern struct single_linked_list *
initial_slinked_list(void);
extern void
serialize_slinked_list(struct single_linked_list *);


/*-     REFERENCE OF SINGLE LINKED LIST MODULE                               -*/
/*-     Single Linked List                                                   -*/
extern struct single_linked_list *
generate_slinked_list(int *, int);
extern void
append_slinked_list_node(struct single_linked_list *, int);
extern void
clear_slinked_list(struct single_linked_list **);
extern int
lengthof_slinked_list(struct single_linked_list *head);
extern struct single_linked_list *
accessby_index_slinked_list(struct single_linked_list *, int);
extern void
print_slinked_list(FILE *, char *, struct single_linked_list *);
extern void
exchange_slinked_list(struct single_linked_list **,
  struct single_linked_list *);

/*-     Doubly Linked List                                                   -*/
extern struct doubly_linked_list *
generate_dlinked_list(int *, int);
extern void
append_dlinked_list_node(struct doubly_linked_list *, int);
extern void
clear_dlinked_list(struct doubly_linked_list **);
extern int
lengthof_dlinked_list(struct doubly_linked_list *head);
extern struct doubly_linked_list *
accessby_index_dlinked_list(struct doubly_linked_list *, int);
extern void
print_dlinked_list(FILE *, char *, struct doubly_linked_list *);
extern void
print_reverse_dlinked_list(FILE *, char *, struct doubly_linked_list *);
extern void
exchange_dlinked_list(struct doubly_linked_list **,
                      struct doubly_linked_list *);



/*-     CHAPTER 03-01                                                        -*/
#define NODE_SIZE              1000
#define TRAVERSAL_CNT          10000
#define TRAVERSAL_PERFORMANCE(times, func, head) \
(*(func))((head));                               \
while(--(times) > 0)                             \
{                                                \
  (*(func))((head));                             \
}

struct traversal_report{
  int      sum;
  int      dimension;
  unsigned usec;
};

void
chapt_3_1(void);
static void
dochapt_3_1(void);
static void
init_node_value(int *, int);
static void
print_traversal_title(FILE *);
static void
print_traversal_report(FILE *, struct traversal_report *);
static int
traversal_single_linked_list(struct single_linked_list *);
static void
print_lots_title(FILE *);


/*-     CHAPTER 03-02                                                        -*/
#define LOTS_RANDOM_SEED       9876
#define LOTS_RANDOM_MAX        10000
#define LOTS_LIST_LEN          128
#define TEST_LOTS_CNT          1
#define PRINT_LOTS_PERFORMANCE(times, func, val, ind) \
while((times)-- > 0)                                  \
{                                                     \
  (*(func))((val), (ind));                            \
}

struct lots_report{
  int      val_len;
  int      ind_len;
  unsigned usec;
};

void
chapt_3_2(void);
static void
dochapt_3_2(void);
static void
init_maxed_array(int *, int, int);
static void
print_lots(struct single_linked_list *, struct single_linked_list *);
static void
print_lots_title(FILE *);
static void
print_lots_report(FILE *, struct lots_report *);


/*-     CHAPTER 03-06                                                        -*/
#define POLY_ADD_COUNT         1000
struct poly_linked{
  float    coefficient;
  int      pow;
  struct   single_linked_list sll;
};
struct poly_add_report{
  unsigned usec;
  int      msize;
  int      nsize;
};


void
chapt_3_6(void);
static void
dochapt_3_6(void);
static float *
prepare_flt_random(void);
static void
clear_flt_random(void **);
static struct poly_linked *
generate_polynomial(float *, int *, int);
static struct poly_linked *
polynomial_add(struct poly_linked *, struct poly_linked *);
static void
clear_polynomial(struct poly_linked **);
static struct poly_linked *
get_next_poly(struct single_linked_list *);
static void
print_polynomial_layout(struct poly_linked *);
static void
print_polynomial_title(void);
static void
print_polynomial_report(struct poly_add_report *);



#endif

