#ifndef DEFINES_H
#define DEFINES_H

/* DEFINE CONSTANT                                                            */
#define STRINFO_BUF_SIZE           256
#define RIGHT_MOST_BIT_MASK        1
#define ENTER(fname)               enter(#fname)
#define LEAVE                      leave()
#define TIME_START                 timing_start()
#define TIME_END(usec)             timing_end(usec)
#define SYMBOL_TO_STRING(symbol)   #symbol
#define PI                         3.14159265
#define FLT_ITER                   PI
#define RANDOM_DATA_SIZE           1024


/* DEFINE EXPANDING                                                           */
#define ADD_TRACE(msg)             (sprintf(strinfo_buf, "[%d] ", __LINE__), \
          strcat(                                       \
            strcat(                                     \
              strcat(strinfo_buf, __FILE__),            \
                ":"),                                   \
                  (msg)))

#define CONSTRAINT_OF(ptr, type, ele)                   \
          (type*)((char*)(ptr) - (char*)(&((type*)0)->ele))


typedef void (*HOMEWORK)(void);


#endif
