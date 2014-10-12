#ifndef CHAPTER2_H
#define CHAPTER2_H


extern FILE *dsaaa_report;
extern const char *warning_digest[];
extern const char *error_digest[];
extern char strinfo_buf[];


/*-     EXTERNAL SYMBOLS                                                     -*/
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
extern int
get_bit_length(unsigned int);



/*-     CHAPTER 02-07                                                        -*/
#define RANDOM_REPEAT_CNT      100
#define REPEATED               0xA0A0
#define NOT_REPEATED           0x0A0A
#define REPEAT_USED            0x1010
#define REPEAT_UNUSED          0x0101
#define SEQ_PERFORMANCE(times, func, start, end, type) \
while((times)-- > 0)                                   \
{                                                      \
  (*(func))((start), (end), (type));                   \
}

struct gen_random_report{
  unsigned usec;
  int      dimension;
  char     *outline;
  int      start;
  int      end;
  double   expected;
};

enum repeat_vehicle{
  UTIL,
  USED,
  SWAP,
};

void
chapt_2_7(void);
static void
dochapt_2_7(enum repeat_vehicle);
static void
random_sequence(int, int, enum repeat_vehicle);
static void
generate_random(int, int, enum repeat_vehicle);
static int
isrepeated_util(int, int);
static int
isrepeated_used(int, int);
static void
print_random_title(FILE *);
static void
print_random_report(FILE *, struct gen_random_report *);
static void
repeat_assist_init(int, int, enum repeat_vehicle);
static void
repeat_assist_clear(enum repeat_vehicle);
static void
random_swap(int);
static void
expected_init(struct gen_random_report *, int,
  enum repeat_vehicle);

static enum repeat_vehicle repeats[] = {
  UTIL,
  USED,
  SWAP,
};
static char *repeat_description[] = {
  "UNTIL Diffence",
  "USED Buffering",
  "SWAP Randomly ",
};
static int *sequence_data;
static int *used_number;


/*-     CHAPTER 02-11                                                        -*/
#define MIN_STEP_WIDTH         1
#define CONTAINED              0x1234
#define NOT_CONTAINED          0x4321
#define SPECIFIED_REPEAT_CNT   10000
#define CON_PERFORMANCE(times, func, specified, raw_data, size_c) \
(*(func))((specified), (raw_data), (size_c)); \
while(--(times) > 0) \
{  \
  (*(func))((specified), (raw_data), (size_c)); \
}

struct iscontains_report{
  unsigned usec;
  int      min;
  int      size_c;
  double   astringent;
  int      result;
};

void
chapt_2_11(void);
static void
dochapt_2_11(void);
static void
specified_contains(int, int, int, int);
static int *
prepare_raw_data(int, int, int);
static void
clear_raw_data(int *);
static int
iscontains(int, int *, int);
static void
print_contains_title(FILE *);
static void
print_contains_report(FILE *, struct iscontains_report *);


/*-     CHAPTER 02-12                                                        -*/
#define MIN_DOUBLE             0.000001f
#define MAX_SUB_DATA_SIZE      10
#define SUB_CASES_COUNT        1024
#define SUB_PERFORMANCE(times, func, data_in, size_s, st, ed) \
(*(func))((data_in), (size_s), (st), (ed));                   \
while(--(times) > 0)                                          \
{                                                             \
  (*(func))((data_in), (size_s), (st), (ed));                 \
}

enum minsub_sequence{
  MIN_SUB,
  MIN_POSITIVE_SUB,
  MAX_MULTI_SUB,
};
struct sub_sequence{
  double   min;
  unsigned usec;
  int      st;
  int      ed;
  double   astringent;
};

void
chapt_2_12(void);
static void
dochapt_2_12(void);
static void
find_minsub_seq(double (*)[MAX_SUB_DATA_SIZE], int, int,
  double (*)(double *, int, int *, int *), enum minsub_sequence);
static void
astringent_init(struct sub_sequence *, int, enum minsub_sequence);
static double
min_subsequence(double *, int, int *, int*);
static double
min_posi_subsequence(double *, int, int *, int *);
static double
max_multi_subsequence(double *, int, int *, int *);
static void
print_submin_report(FILE *, struct sub_sequence *);
static void
print_submin_title(FILE *, int, enum minsub_sequence);
static void
print_data_in(FILE *, double (*)[MAX_SUB_DATA_SIZE], int);
static void
min_posi_assist(double *, double *, int);

static double (*func_name[])(double *, int, int *, int *) = {
  &min_subsequence,
  &min_posi_subsequence,
  &max_multi_subsequence,
};
static enum minsub_sequence minsub_type[] = {
  MIN_SUB,
  MIN_POSITIVE_SUB,
  MAX_MULTI_SUB,
};


/*-     CHAPTER 02-13                                                        -*/
#define PRIME_REPEAT_COUNT     10000
#define PRIMED                 0xA349
#define INTEGRATE_ODD          0x2321
#define NOT_PRIMED             0x3B21
#define PRIME_PERFORMANCE(times, func, raw_data) \
(*(func))((raw_data));                           \
while(--(times) > 0)                             \
{                                                \
  (*(func))((raw_data));                         \
}

struct prime_num_report{
  int      raw_data;
  int      isprimed;
  unsigned usec;
  double   astringent;
};

void
chapt_2_13(void);
static void
dochapt_2_13(void);
static int
isprime_number(int);
static void
print_prime_title(FILE *);
static void
print_prime_report(FILE *, struct prime_num_report *);
static int
isodd_number(int);


/*-     CHAPTER 02-16                                                        -*/
#define DEFAULT_BASE           2
#define FPOWER_REPEATS         1000
#define MAX_EXP_COUNT          10
#define FPOWER_PERFORMANCE(times, func, base, exp) \
(*(func))((base), (exp));                          \
while(--(times) > 0)                               \
{                                                  \
  (*(func))((base), (exp));                        \
}

struct buffered_power{
  int dimension;
  int value;
};

struct fast_power_report{
  unsigned result;
  unsigned usec;
  int      mult_counts;
  double   astringent;
};

void
chapt_2_16(void);
static void
dochapt_2_16(void);
static int
cal_mult_counts(int);
static int
cal_fast_power(unsigned, int);
static void
update_power_buffer(unsigned, int);
static void
initial_power_buffer(unsigned);
static void
filling_power_buffer(unsigned, int);
static void
print_power_title(FILE *);
static void
print_power_report(FILE *, unsigned, int, struct fast_power_report *);

static struct buffered_power *pbuf;


/*-     CHAPTER 02-19                                                        -*/
#define PRIN_DATA_SIZE         128
#define PRIN_VALUE_SIZE        3
#define PRINT_LINE_MAX         16
#define PRINCIPLE_ELE          0x1253
#define NOT_PRINCIPLE          0x3748
#define PRIN_REPEATS           10000
#define PRINCIPLE_PERFORMANCE(times, func, data_in, size) \
(*(func))((data_in), size); \
while(--(times) > 0) \
{ \
  (*(func))((data_in), size); \
}

struct principle_ele_report{
  unsigned usec;
  unsigned dimension;
  int      result;
  double   astringent;
};

void
chapt_2_19(void);
static void
dochapt_2_19(void);
static void
print_prin_title(FILE *);
static void
print_prin_report(FILE *, int, struct principle_ele_report *);
static void
data_init(int *, int);
static void
print_raw_data(FILE *, int *, int);
static int
principle_element(int *, int);
static int
principle_element_iter(int *, int *, int);
static int
isprinciple(int *, int, int);

#endif
