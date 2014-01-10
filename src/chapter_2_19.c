/*--------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                               */
/*-DATE:        01102014                                        */
/*-WHAT:        Homework chapter 2.19                           */
/*-REVISION:                                                    */
/*- DATE ------------------------ DESCRIPTION ------------------*/
/*- 01102014    CHAPTER 2-19                                   -*/
/*--------------------------------------------------------------*/
void
chapt_2_16(void)
{
  ENTER("chapt_2_19");

  print_report_header(stdout, "Principle Element", 2, 19);
  print_report_header(hwork_rept, "Principle Element", 2, 19);

  dochapt_2_19();

  LEAVE;
  return;
}


static void
dochapt_2_19(void)
{
  int *raw_data;
  ENTER("dochapt_2_19");

  srand((unsigned)time(NULL));
  malloc_initial(&raw_data, sizeof(*raw_data) * PRIN_DATA_SIZE);

  LEAVE;
  return;
}

static void
data_init(int *dt_in, int size)
{
  register int *iterator = dt_in;
  ENTER("data_init");

  while(iterator < dt_in + size)
    *iterator++ = rand() % PRIN_VALUE_SIZE;

  LEAVE;
  return;
}

static void
print_raw_data(FILE *fd, int *dt_in, int size)
{
  register int *iterator;
  ENTER("print_raw_data");

  iterator = dt_in;
  while(iterator < dt_in + size)
  {
    fprintf(fd, "%3d,", *iterator++);
    if(!((iterator - dt_in) % PRINT_LINE_MAX))
      fprintf(fd, "\n");
  }

  LEAVE;
  return;
}

static void
principle_element_setup(int *raw_data, int size)
{
  int *iter_in;
  int *iter_out;
  ENTER("principle_element_setup");

  if(size > PRIN_DATA_SIZE)
    warn_prompt("A risk of memory leak detected.");

  malloc_initial(&iter_in, sizeof(*iter_in) * size);
  malloc_initial(&iter_out, sizeof(*iter_out) * size);
  memcpy(iter_in, raw_data, sizeof(*iter_in) * size);

  LEAVE;
  return;
}

static void
principle_element(int *data_out, int *data_in, int size)
{
  register int *iter_in;
  register int *iter_out;
  ENTER("principle_element");

  memset(data_out, 0, sizeof(*data_out) * size);

  iter_in = data_in;
  iter_out = data_out;
  if(size % 2)

  while(iter_in < data_in + size)
  {

  }

  LEAVE;
  return;
}

