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

  if(*a != *b)
  {
    *a = *a^*b;
    *b = *a^*b;
    *a = *b^*a;
  }

  LEAVE;
  return;
}

void
filepointer_init()
{
  char *rept_fname = "./homework.rept";
  ENTER("filepointer_init");

  dsaaa_report = fopen(rept_fname, "w+");
  if(NULL == dsaaa_report)
    error_handle(ADD_TRACE(error_digest[6]));

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
    error_handle(ADD_TRACE(error_digest[7]));

  memset(*pointer, 0, length);

  LEAVE;
  return;
}

void
realloc_initial(void **pointer, unsigned int length)
{
  ENTER("realloc_initial");

  realloc_noinitial(pointer, length);
  memset(*pointer, 0, length);

  LEAVE;
  return;
}

void
realloc_noinitial(void **pointer, unsigned int length)
{
  ENTER("realloc_noinitial");

  *pointer = realloc(*pointer, length);
  if(NULL == *pointer)
    error_handle(ADD_TRACE(error_digest[8]));

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

void
free_random_int_array(int *raw)
{
  ENTER("free_random_int_array");

  if(NULL == raw)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto FREE_END;
  }

  saft_free((void**)&raw);

FREE_END:
  LEAVE;
  return;
}
