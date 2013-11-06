#ifndef DEFINES_H
#define DEFINES_H


//#define STD_INCLUDED
#define DATA_MAX                   1024000
#define TRACE_DEPTH                4098
#define MAX_WIDTH_OF_LINE          120
#define FULL_NAME_LENGTH           256
#define FILENAME_SPLITER           "\"< >"

#define TIME_START       timing_start()
#define TIME_END(usec)   timing_end(usec)


#ifndef STD_INCLUDED
#define EXPAND_DEPTH               128
#define FILENAME_LENGTH            32
#endif

typedef void (*HOMEWORK)(void);

typedef struct rept_entry{
  int      kvalue;
  int      data_size;
  int      validate;
  unsigned usec_cost;
	double   astringent;
}REPT_entry;

#endif
