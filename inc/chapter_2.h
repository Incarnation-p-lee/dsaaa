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


void
chapt_2_7(void);


static void
dochapter2_7(void);
static void
random_sequence(int, int);
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

static char *vehicle_name[] = {
  "UNTIL Diffence",
  "USED Buffering",
  "SWAP Randomly ",
};

static int *sequence_data;
static int *used_number;

#endif
