#ifndef UTILISZE_H
#define UTILISZE_H


extern FILE *hwork_rept;


void
error_handle(const char *);
void
exchange(int *, int *);
void
filepointer_init(void);
void
entering_frame(const char *);
void
leaving_frame(void);
void
print_stack_traces(void);

static const char *stack_traces[TRACE_DEPTH];
static int top_index = 0;

#endif
