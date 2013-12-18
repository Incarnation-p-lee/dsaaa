/*---------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                                */
/*-DATE:        08132013                                         */
/*-WHAT:        Homework chapter 1.1                             */
/*-REVISION:                                                     */
/*- DATE -------------------- DESCRIPTION -----------------------*/
/*- 08132013    Generate Function for external invoke           -*/
/*---------------------------------------------------------------*/
void
exchange(int *a, int *b)
{
  assert(NULL != a && NULL != b);

  if(*a == *b)
    return;

  *a = *a^*b;
  *b = *a^*b;
  *a = *b^*a;
  return;
}

void
filepointer_init()
{
  char *rept_fname = "./archive/homework.rept";
  hwork_rept = fopen(rept_fname, "w+");
  if(NULL == hwork_rept)
    error_handle("fopen");

  return;
}

void
filepointer_close()
{
  fclose(hwork_rept);

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
