#ifndef VARIABLE_H
#define VARIABLE_H


extern void
chapt_1_1(void);
extern void
chapt_1_4(void);
extern void
chapt_2_7(void);

struct timeval timePoint_start;
struct timeval timePoint_end;
FILE *hwork_rept;
const char *blank = 
"                                               ";

static HOMEWORK homework[] = {
  &chapt_1_1,
  &chapt_1_4,
  &chapt_2_7,
};


#endif
