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


static int
isrepeated_util(const int *, int, int);
static void
dochapter2_7(void);
static int *
random_sequence(int, int);
static void
generate_random(int *, int, int,
  int (*)(const int *, int, int));
static void
print_random_title(FILE *);
static void
print_random_report(FILE *, int *, struct gen_random_report *);


static int (*repeats[])(const int *, int, int) = {
  &isrepeated_util,
};

static char *vehicle_name[] = {
  "Until Diffence",
};

#endif
