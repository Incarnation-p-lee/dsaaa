#ifndef VARIABLE_H
#define VARIABLE_H

#include "externals.h"

struct timeval ts_begin;
struct timeval ts_end;

FILE *hwork_rept;
const char *blank = 
"                                               ";

static HOMEWORK homework[] = {
#if 1
  &chapt_1_1,
  &chapt_1_4,
  &chapt_2_7,
  &chapt_2_11,
  &chapt_2_12,
  &chapt_2_13,
  &chapt_2_16,
  &chapt_2_19,
#else
  &chapt_2_19,
#endif
};


#endif
