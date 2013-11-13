#ifndef DEFINES_H
#define DEFINES_H


#if 1
#define STD_HEAD_FILE
#else
#define NO_STD_HEAD_FILE
#endif


#define DATA_MAX                   1024000
#define TRACE_DEPTH                4098
#define MAX_WIDTH_OF_LINE          120
#define FULL_NAME_LENGTH           256
#define REPEAT_COUNT               100
#define FILENAME_SPLITER           "\"< >"
#define REPEAT_USED                0x1010
#define REPEAT_UNUSED              0x0101
#define REPEATED                   0xA0A0
#define NOT_REPEATED               0x0A0A

#define TIME_START       timing_start()
#define TIME_END(usec)   timing_end(usec)


#ifdef NO_STD_HEAD_FILE
#define EXPAND_DEPTH               128
#define FILENAME_LENGTH            32
#endif


typedef void (*HOMEWORK)(void);
typedef enum repeat_vehicle{
  UTIL,
  USED,
  SWAP,
}Rept_v;

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


#endif
