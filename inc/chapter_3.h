#ifndef CHAPTER3_H
#define CHAPTER3_H

/*-     EXTERNALS                                              -*/
extern FILE *dsaaa_report;

extern void
error_handle(const char *);
extern void
warn_prompt(const char *);
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


/*-     CHAPTER 03-01                                          -*/
#define NODE_SIZE              1000
#define TRAVERSAL_CNT          10000
#define TRAVERSAL_PERFORMANCE(times, func, head) \
(*(func))((head));                               \
while(--(times) > 0)                             \
{                                                \
  (*(func))((head));                             \
}

struct single_linked_list{
  int value;
  struct single_linked_list *next;
};
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
static struct single_linked_list *
generate_linked_list(int *, int);
static void
append_linked_list_node(struct single_linked_list *, int);
static void
clear_linked_list(struct single_linked_list **);
static int
traversal_single_linked_list(struct single_linked_list *);
#endif
