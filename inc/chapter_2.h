#ifndef CHAPTER2_H
#define CHAPTER2_H

extern FILE *hwork_rept;

extern void
error_handle(const char *);
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
saft_free(void **);

/*-     CHAPTER 02-07                                          -*/
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


/*-     CHAPTER 02-11                                          -*/
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


/*-     CHAPTER 02-12                                          -*/
void
chapt_2_12(void);

static void
dochapt_2_12(void);
static void
find_minsub_seq(double (*)[MAX_SUB_DATA_SIZE], int, int,
  double (*)(double *, int, int *, int *),
  enum minsub_sequence);
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


/*-     CHAPTER 02-13                                          -*/
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

#endif
