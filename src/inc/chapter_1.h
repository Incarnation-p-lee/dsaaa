#ifndef CHAPTER11_H
#define CHAPTER11_H


extern FILE *dsaaa_report;
extern const char *blank;
extern const char *warning_digest[];
extern const char *error_digest[];
extern char strinfo_buf[];

extern void
error_handle(const char *);
extern void
warning_prompt(char *);
extern void
timing_start(void);
extern void
timing_end(unsigned *);
extern void
leave(void);
extern void
enter(const char *);
extern void
print_report_header(FILE *, const char *, int, int);
extern void
malloc_initial(void **, unsigned int);
extern void
saft_free(void **);
extern void
exchange(int *, int *);




/*                  chapter 1-1                                               */
#define MAX_SELECT_VALUE       1024000
#define SELECT_REPEAT_CNT      2
#define SELECT_PERFORMANCE(times, func, data_in, size, key) \
(*(func))((data_in), (size), (key));                        \
while(--(times) > 0)                                        \
{                                                           \
  (*(func))((data_in), (size), (key));                      \
}

struct select_report{
  int      kvalue;
  int      data_size;
  int      validate;
  unsigned usec_cost;
  int      count;
  double   astringent;
};

void
chapt_1_1(void);
static void
dochapt_1_1(int);
static int *
selection_data_prepare(int);
static int
selection_problem(int *, int, int);
static int
selection_split(int *, int, int);
static int
selection_validate(int *, int, int);
static void
selection_data(FILE *, struct select_report *);
static void
print_select_title(FILE *);


/*                  chapter 1-4                                               */
#if 1
  #define STD_HEAD_FILE
#else
  #define NO_STD_HEAD_FILE
#endif
#ifdef NO_STD_HEAD_FILE
  #define EXPAND_DEPTH         128
  #define FILENAME_LENGTH      32
#endif
#define MAX_WIDTH_OF_LINE      120
#define FULL_NAME_LENGTH       256
#define FILENAME_SPLITER       "\"< >"

void
chapt_1_4(void);
static void
dochapt_1_4(void);
static void
expand_file(char *);
static char *
include_line(char*);
static void
include_filename(char *, char *);
static FILE *
open_included_file(const char *);
static int
isvalid_include(char *);
static int
expand_file_filter(const char *);
static void
print_expand_report(char *fmt, ...);

static char *include_path[] = {
  "./",
  "./inc/",
  "./src/",
  "/usr/include/",
  "/usr/include/x86_64-linux-gnu/",
};
static int depth = -1;

#ifdef STD_HEAD_FILE
static char *std_head[] = {
  "assert.h",
  "stdio.h",
  "stdlib.h",
  "string.h",
  "stddef.h",
  "stdarg.h",
  "errno.h",
  "limits.h",
  "time.h",
  "ctype.h",
  "math.h",
  "float.h",

  #ifdef __linux__
  "sys/types.h",
  "sys/stat.h",
  "sys/wait.h",
  "sys/time.h",
  "sys/mman.h",
  "unistd.h",
  "fcntl.h",
  "netinet/in.h",
  "sys/socket.h",
  "arpa/inet.h",
  "pthread.h",
  #endif
};
#endif

#ifdef NO_STD_HEAD_FILE
  static int exstack_top = 0;
  static char expand_stack[EXPAND_DEPTH][FILENAME_LENGTH];
  static void
  pop_expand_stack(void);
#endif

#endif
