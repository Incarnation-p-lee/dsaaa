/*----------------------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                                            -*/
/*-DATE:        08132013                                                     -*/
/*-WHAT:        Homework chapter 1.1                                         -*/
/*-REVISION:                                                                 -*/
/*- DATE -------------------- DESCRIPTION ------------------------------------*/
/*- 08132013    Generate Function for external invoke                        -*/
/*- 02262014    Add trace function to util, adjusted comments width          -*/
/*----------------------------------------------------------------------------*/
void
exchange(int *a, int *b)
{
  ENTER("exchange");
  assert(NULL != a && NULL != b);

  if(*a == *b)
    return;

  *a = *a^*b;
  *b = *a^*b;
  *a = *b^*a;

  LEAVE;
  return;
}

void
filepointer_init()
{
  char *rept_fname = "./archive/homework.rept";
  ENTER("filepointer_init");

  dsaaa_report = fopen(rept_fname, "w+");
  if(NULL == dsaaa_report)
    error_handle("fopen");

  LEAVE;
  return;
}

void
filepointer_close()
{
  ENTER("filepointer_close");
  fclose(dsaaa_report);

  LEAVE;
  return;
}

void
print_report_header(FILE *fd, const char *title,
  int chapter, int item)
{
  time_t date;
  ENTER("print_report_header");

  time(&date);
  fprintf(fd, "\n-----------------------------");
  fprintf(fd, "Chapter %02d-%02d", chapter, item);
  fprintf(fd, "-------------------------------\n\n");
  fprintf(fd,
    "                               %.30s\n\n", title);
  fprintf(fd, "TIME: %s", ctime((const time_t *)&date));

  LEAVE;
  return;
}

void
malloc_initial(void **pointer, unsigned int length)
{
  ENTER("malloc_initial");

  *pointer = malloc(length);
  if(NULL == *pointer)
    error_handle("malloc failed to get suffient memory");

  memset(*pointer, 0, length);

  LEAVE;
  return;
}


void
realloc_initial(void **pointer, unsigned int length)
{
  ENTER("realloc_initial");

  *pointer = realloc(*pointer, length);
  if(NULL == *pointer)
    error_handle("realloc failed to update memory");

  memset(*pointer, 0, length);

  LEAVE;
  return;
}

void
saft_free(void **pointer)
{
  ENTER("saft_free");

  free(*pointer);
  *pointer = NULL;

  LEAVE;
  return;
}

int
get_bit_length(unsigned int n)
{
  int result;
  ENTER("get_bit_length");

  if(!n)
    result = 0;
  else
    result = 1;

  while((n >>= 1))
    result++;

  LEAVE;
  return result;
}

int *
gen_random_int_array(int size)
{
  int *raw;
  int scnt;
  int base;
  ENTER("gen_random_int_array");

  if(0 >= size)
    error_handle(ADD_TRACE(error_digest[1]));

  scnt = sizeof(int_random) / sizeof(int_random[0]);
  malloc_initial((void**)&raw, sizeof(*raw) * size);

  base = size % scnt;
  memcpy(raw, int_random, base);

  while(base < size)
  {
    memcpy(raw + base, int_random, scnt);
    base += scnt;
  }

  LEAVE;
  return raw;
}
