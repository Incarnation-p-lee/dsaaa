#ifndef EVALUATION_H
#define EVALUATION_H

extern struct timeval ts_begin;
extern struct timeval ts_end;
extern void ENTER(const char *);
extern void LEAVE(void);


void
timing_start(void);
void
timing_end(unsigned *);


static unsigned
timing_cost(void);

#endif
