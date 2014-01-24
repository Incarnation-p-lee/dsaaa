#ifndef DEFINES_H
#define DEFINES_H

#define RIGHT_MOST_BIT_MASK    1
#define ENTER(fname)               enter(#fname)
#define LEAVE                      leave()
#define TIME_START                 timing_start()
#define TIME_END(usec)             timing_end(usec)
#define MACRO_TO_STRING(symbol)    #symbol

typedef void (*HOMEWORK)(void);

#endif
