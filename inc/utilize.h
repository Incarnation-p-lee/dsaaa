#ifndef UTILISZE_H
#define UTILISZE_H


extern FILE *hwork_rept;

extern void
enter(const char *);
extern void
leave(void);


void
error_handle(const char *);
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
saft_free(void **);


static const char *stack_traces[TRACE_DEPTH];
static int top_index = 0;

#endif
