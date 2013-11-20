#ifndef VARIABLE_H
#define VARIABLE_H


extern void
chapt_1_1(void);
extern void
chapt_1_4(void);
extern void
chapt_2_7(void);
extern void
chapt_2_11(void);
extern void
chapt_2_12(void);

struct timeval ts_begin;
struct timeval ts_end;

FILE *hwork_rept;
const char *blank = 
"                                               ";

static HOMEWORK homework[] = {
#if 0
  &chapt_1_1,
  &chapt_1_4,
  &chapt_2_7,
  &chapt_2_11,
#else
  &chapt_2_12,
#endif
};


#endif
