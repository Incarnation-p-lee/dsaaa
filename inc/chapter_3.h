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
leave(void);
extern void
enter(const char *);
extern void
print_report_header(FILE *, const char *, int, int);
extern void
malloc_initial(void **, unsigned int);
extern void
saft_free(void **);
extern void
clear_slinked_list(struct single_linked_list **);
extern void
serialize_slinked_list(struct single_linked_list *);
extern int *
gen_random_int_array(int);
extern void
free_random_int_array(int *);


/*-     REFERENCE OF SINGLE LINKED LIST MODULE                               -*/
/*-     Single Linked List                                                   -*/
extern struct single_linked_list *
generate_slinked_list(int *, int);
extern void
destroy_slinked_list(struct single_linked_list **);
extern int
lengthof_slinked_list(struct single_linked_list *head);
extern struct single_linked_list *
accessby_index_slinked_list(struct single_linked_list *, int);
extern void
print_slinked_list(FILE *, char *, struct single_linked_list *);

/*-     Doubly Linked List                                                   -*/
extern struct doubly_linked_list *
generate_dlinked_list(int *, int);
extern void
destroy_dlinked_list(struct doubly_linked_list **);
extern void
print_dlinked_list(FILE *fd, char *msg, struct doubly_linked_list *head);
extern void
initial_dlinked_list_node(struct doubly_linked_list *);
extern void
insert_after_dlinked_list(struct doubly_linked_list *,
                          struct doubly_linked_list *);
extern struct doubly_linked_list *
remove_node_dlinked_list(struct doubly_linked_list *);




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
  float  coefficient;
  int    pow;
  struct single_linked_list sll;
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


/*-     CHAPTER 03-09                                                        -*/
#define POSITIVE               0xA5B2
#define NEGATIVE               0x5A2B
#define MAX_NUMBER             10
#define BIG                    0x28D
#define SMALL                  0xA73
#define EQUAL                  0xFE7
typedef int                    SIGN_AINT;

enum CBFLAG{
  DEFAULT,
  CARRY,
  BORROW,
};

enum ARITHMETIC{
  ADD,
  SUBTRACT,
  MULTIPLY,
};

struct any_integer{
  int    value;
  struct single_linked_list sll;
};

struct any_integer_catalog{
  void (*arithmetic)(struct any_integer *, struct any_integer *);
  enum ARITHMETIC type;
};

struct any_integer_arithmetic_report{
  unsigned        usec;
  int             msize;
  int             nsize;
  int             astringend;
};

static enum CBFLAG cb_flag;

void
chapt_3_9(void);
static void
dochapt_3_9(void);
static void
do_any_integer_performance(int *, int, int *, int,
  struct any_integer_arithmetic_report *,
  void (*)(struct any_integer *, struct any_integer *));
static void
set_astringend(struct any_integer_arithmetic_report *,
  enum ARITHMETIC);
static int *
generate_random_seat_array(int, SIGN_AINT);
static struct any_integer *
init_any_integer(int *, int);
static void
assign_numeric(struct any_integer *, int);
static void
clear_any_integer(struct any_integer **);
void
add_any_integer(struct any_integer *, struct any_integer *);
void
subtract_any_integer(struct any_integer *, struct any_integer *);
void
multiply_any_integer(struct any_integer *, struct any_integer *);
void
set_zero_any_integer(struct any_integer *);
static void
multiply_single_any_integer(struct any_integer *, int);
struct any_integer *
copyof_any_integer(struct any_integer *);
struct any_integer *
getzero_node_any_integer(void);
void
shift_right_any_integer(struct any_integer *, int);
void
shift_left_any_integer(struct any_integer *, int);
int
iszero_any_integer(struct any_integer *);
int
abscompare_any_integer(struct any_integer *, struct any_integer *);
static void
eliminate_leading_zero(struct any_integer *);
void
insert_any_integer(struct any_integer *, struct any_integer *);
void
delete_any_integer(struct any_integer *, struct any_integer *);
static void
deal_left_cb(struct any_integer *);
static void
set_sign(SIGN_AINT, struct any_integer *);
static void
iscarry(struct any_integer *);
static void
isborrow(struct any_integer *);
struct any_integer *
previous_any_integer(struct any_integer *, struct any_integer *);
struct any_integer *
next_any_integer(struct any_integer *);
struct any_integer *
last_any_integer(struct any_integer *);
void
print_any_integer(struct any_integer *);
static void
print_any_integer_title(void);
static void
print_any_integer_report(struct any_integer_arithmetic_report *);
static void
set_arithmetic_catalog(enum ARITHMETIC);


/*-     CHAPTER 03-10                                                        -*/
struct josephus_game_serial{
  int    serial_num;
  struct single_linked_list sll;
};

struct josephus_game_report{
  unsigned count;
  unsigned len;
  unsigned usec;
  unsigned astringend;
};

void
chapt_3_10(void);
static void
dochapt_3_10(void);
static void
start_josephus_game(struct josephus_game_serial **, unsigned);
static void
create_serial_loop_link_list(struct josephus_game_serial **, int);
static void
print_josephus_game_title(void);
static void
print_josephus_game_report(struct josephus_game_report *);
static inline struct josephus_game_serial *
next_josephus_game_serial(struct josephus_game_serial *);
static void
destroy_josephus_game_serial_node(struct josephus_game_serial **,
                                  struct josephus_game_serial *);
static struct josephus_game_serial *
deliver_josephus_game_hot_potato(struct josephus_game_serial *, int);

/*-     CHAPTER 03-16                                                        -*/
#define REDUNDANT_RAW_DATA_MAX 128u
struct redundant_list {
  unsigned num;
  struct doubly_linked_list dll;
};

struct redundant_list_report {
  float redundant_rate;
  unsigned size;
  unsigned usec;
  unsigned astringend;
};

void
chapt_3_16(void);
static void
dochapt_3_16(void);
static unsigned *
create_raw_random_data(int);
static inline void
destroy_raw_random_data(unsigned **);
static struct redundant_list *
create_redundant_linked_list(unsigned *, int);
static void
destroy_redundant_linked_list(struct redundant_list **);
static struct redundant_list *
next_redundant_linked_list(struct redundant_list *);
static void
remove_redundant_linked_list(struct redundant_list *);
static struct redundant_list *
remove_node_redundant_linked_list(struct redundant_list *);
static inline void
init_redundant_list_report(struct redundant_list_report *, int);
static void
print_redundant_list_report(struct redundant_list_report *);
static void
print_title_redundant_list_report(void);

#endif
