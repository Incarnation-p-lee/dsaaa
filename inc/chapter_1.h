#ifndef CHAPTER11_H
#define CHAPTER11_H


extern FILE *hwork_rept;
extern const char *blank;

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

extern void
error_handle(const char *);
extern void
timing_start(void);
extern void
timing_end(unsigned *);
extern void
exchange(int *, int *);
extern void
leave(void);
extern void
enter(const char *);
extern void
print_report_header(FILE *, const char *, int, int);


void
chapt_1_1(void);
void
chapt_1_4(void);


static int *
selection_data_prepare(int);
static int
selection_problem(int *, int, int);
static int
selection_split(int *, int, int);
static int
selection_validate(int *, int, int);
static void
selection_data(struct rept_entry *);
static void
dochapt_1_1(int);
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
expand_report(char *fmt, ...);
static void
print_algo_info(FILE *);


#endif
