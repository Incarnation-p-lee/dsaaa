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
    error_handle("malloc");

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
