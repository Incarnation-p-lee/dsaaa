#ifndef EVALUATION_H
#define EVALUATION_H

extern struct timeval timePoint_start;
extern struct timeval timePoint_end;


void
timing_start(void);
void
timing_end(unsigned *);


static unsigned
timing_cost(void);

#endif
