#ifndef DEFINES_H
#define DEFINES_H


#if 1
#define STD_HEAD_FILE
#else
#define NO_STD_HEAD_FILE
#endif


#define MIN_STEP_WIDTH             1
#define DATA_MAX                   1024000
#define TRACE_DEPTH                4098
#define MAX_WIDTH_OF_LINE          120
#define FULL_NAME_LENGTH           256
#define REPEAT_COUNT               100
#define SUB_CASES_COUNT            1024
#define MAX_SUB_DATA_SIZE          16
#define FILENAME_SPLITER           "\"< >"
#define REPEAT_USED                0x1010
#define REPEAT_UNUSED              0x0101
#define REPEATED                   0xA0A0
#define NOT_REPEATED               0x0A0A
#define CONTAINED                  0x1234
#define NOT_CONTAINED              0x4321
#define CONTAINS_COUNT             10000


#ifdef NO_STD_HEAD_FILE
#define EXPAND_DEPTH               128
#define FILENAME_LENGTH            32
#endif


#define ENTER(fname)     enter(#fname)
#define LEAVE            leave()
#define TIME_START       timing_start()
#define TIME_END(usec)   timing_end(usec)

#define SEQ_PERFORMANCE(times, func, start, end, type) \
while((times)-- > 0) \
{  \
  (*(func))((start), (end), (type)); \
}
#define CON_PERFORMANCE(times, func, specified, raw_data, size_c) \
(*(func))((specified), (raw_data), (size_c)); \
while(--(times) > 0) \
{  \
  (*(func))((specified), (raw_data), (size_c)); \
}
#define SUB_PERFORMANCE(times, func, data_in, size_s, st, ed) \
(*(func))((data_in), (size_s), (st), (ed)); \
while(--(times) > 0) \
{ \
  (*(func))((data_in), (size_s), (st), (ed)); \
}


typedef void (*HOMEWORK)(void);
typedef enum repeat_vehicle{
  UTIL,
  USED,
  SWAP,
}Rept_v;
typedef enum minsub_sequence{
  MIN_SUB,
  MIN_POSITIVE_SUB,
}MinSub_seq;

typedef struct rept_entry{
  int      kvalue;
  int      data_size;
  int      validate;
  unsigned usec_cost;
  int      count;
  double   astringent;
}REPT_entry;

typedef struct gen_random_report{
  unsigned usec;
  int      dimension;
  char     *outline;
  int      start;
  int      end;
  double   expected;
}GR_report;

typedef struct iscontains_report{
  unsigned usec;
  int      min;
  int      size_c;
  double   astringent;
  int      result;
}IC_report;

typedef struct sub_sequence{
  signed   min;
  unsigned usec;
  int      st;
  int      ed;
  double   astringent;
}SU_seq;

typedef struct navi_entry{
  signed navi_value;
  int    ed_index;
}NA_entry;
#endif
