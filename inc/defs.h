#ifndef DEFINES_H
#define DEFINES_H





#define DATA_MAX         1024000

#define TIME_START       timing_start()
#define TIME_END(usec)   timing_end(usec)


typedef void HOMEWORK(void);

typedef struct rept_entry{
  int      kvalue;
  int      data_size;
  int      validate;
  unsigned usec_cost;
}REPT_entry;

#endif
