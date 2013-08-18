#ifndef CHAPTER11_H
#define CHAPTER11_H


extern void
error_handle(const char *);
extern void
timing_start(void);
extern void
timing_end(unsigned *);
extern void
exchange(int *, int *);

extern FILE *hwork_rept;

void
chapt_1_1(void);


static int*
data_prepare(int);
static int
selection_problem(int *, int, int);
static int
split_data(int *, int, int);
static void
report_header(void);
static int 
result_validate(int *, int, int);
static void
report_data(struct rept_entry *);
static void
chaptdo_1_1(int);



#endif

