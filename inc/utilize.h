#ifndef UTILISZE_H
#define UTILISZE_H


extern FILE *dsaaa_report;
extern char strinfo_buf[STRINFO_BUF_SIZE];

extern void
enter(const char *);
extern void
leave(void);

#define TRACE_DEPTH            4098

void
error_handle(const char *);
void
warning_prompt(char *);
void
exchange(int *, int *);
void
filepointer_init(void);
void
enter(const char *);
void
leave(void);
void
print_stack_traces(void);
void
print_report_header(FILE *, const char *, int, int);
void
malloc_initial(void **, unsigned int);
void
realloc_initial(void **, unsigned int);
void
saft_free(void **);
int
get_bit_length(unsigned int);

static const char *stack_traces[TRACE_DEPTH];
static int top_index = 0;

#endif
