/*----------------------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                                             */
/*-DATE:        08122013                                                      */
/*-WHAT:        Homework chapter 1.1                                          */
/*-REVISION:                                                                  */
/*- DATE ------------------------ DESCRIPTION --------------------------------*/
/*- 08122013    CHAPTER 1-1                                                  -*/
/*----------------------------------------------------------------------------*/
void
chapt_1_1(void)
{
  register int *pos;
  int dsize[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 500,
   1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000,
   10000000, };
  ENTER("chapt_1_1");

  print_report_header(stdout, "Selection Problem", 1, 1);
  print_report_header(dsaaa_report, "Selection Problem", 1, 1);
  print_select_title(stdout);
  print_select_title(dsaaa_report);

  pos = dsize;
  while(pos < dsize + sizeof(dsize) / sizeof(dsize[0]))
    dochapt_1_1(*pos++);

  LEAVE;
  return;
}

static void
print_select_title(FILE *fd)
{
  ENTER("print_select_title");

  fprintf(fd, "\nASTRINGENT: O(N*logN)\n");
  fprintf(fd, "No.     DATA_SIZE         KVALUE:VALIDATION     "
    "TIME(usec)  ASTRINGENT\n");

  LEAVE;
  return;
}

static void
dochapt_1_1(int data_size)
{
  int *dinput;
  int count;
  struct select_report entry;
  ENTER("dochapt_1_1");

  entry.data_size = data_size;
  dinput = selection_data_prepare(data_size);
  count = SELECT_REPEAT_CNT;

  TIME_START;
  entry.kvalue = SELECT_PERFORMANCE(count, selection_problem,
    dinput, data_size, data_size >> 1);
  TIME_END(&entry.usec_cost);

  entry.astringent = (double)entry.usec_cost / (log(data_size) * data_size);
  entry.validate = selection_validate(dinput, data_size, entry.kvalue);

  selection_data(stdout, &entry);
  selection_data(dsaaa_report, &entry);
  saft_free((void**)&dinput);

  LEAVE;
  return;
}

static int
selection_problem(int *data, int size, int key)
{
  register int big_cnt;
  int data_size;
  int start;
  int index;

  ENTER("selection_problem");
  assert(NULL != data);
  start = 0;
  data_size = size;
  while(1)
  {
    big_cnt = selection_split(data, start, data_size);
    /*------------------------------------------------------------------------*/
    /* if the count of big part is less than key, reset the data and update   */
    /* rest key.                                                              */
    /*------------------------------------------------------------------------*/
    if(big_cnt < key)
    {
      data_size -= big_cnt;
      key -= big_cnt;
    }
    /*------------------------------------------------------------------------*/
    /* if the count of big part is more than key, reset start index and       */
    /* update data size.                                                      */
    /*------------------------------------------------------------------------*/
    else if(big_cnt > key)
    {
      start += (data_size - big_cnt + 1);
      data_size = big_cnt - 1;
    }
    else
      break;
  }
  index = start + data_size - big_cnt;

  LEAVE;
  return data[index];
}

/*----------------------------------------------------------------------------*/
/* Return the count of big part include the key value.                        */
/*----------------------------------------------------------------------------*/
static int
selection_split(int *data, int start, int len)
{
  int key;
  int i;
  int j;

  ENTER("selection_split");
  if(len < 0)
    return -1;

  key = data[start];
  i = start + 1;
  j = start + len - 1;
  while(1)
  {
    while(key <= data[j] && start < j)
      j--;
    while(key >= data[i] && i < j)
      i++;
    if(i >= j)
      break;
    exchange(data + i, data + j);
  }
  exchange(data + start, data + j);

  LEAVE;
  return len - (j - start);
}

static int *
selection_data_prepare(int data_size)
{
  register int *pos;
  int *random_data;

  ENTER("selection_data_prepare");
  if(0 >= data_size)
    error_handle(ADD_TRACE(error_digest[1]));

  malloc_initial((void**)&random_data, sizeof(int) * data_size);

  pos = random_data;
  srand((unsigned)time(NULL));
  while(pos < random_data + data_size)
    *pos++ = ((unsigned)MAX_SELECT_VALUE >> 1) - (rand() % MAX_SELECT_VALUE);

  LEAVE;
  return random_data;
}

static void
selection_data(FILE *fd, struct select_report *rept)
{
  static int number = 0;

  ENTER("selection_data");
  fprintf(fd, "%2d     %10d     %10d:%10d     %10u  %10.6f\n",
    number++ >> 1, rept->data_size, rept->kvalue,
    rept->validate, rept->usec_cost, rept->astringent);

  LEAVE;
  return;
}

static int
selection_validate(int *data, int len, int key)
{
  register int *pos;
  int cnt;

  ENTER("selection_validate");
  assert(NULL != data);
  pos = data;

  cnt = 0;
  while(pos < data + len)
  {
    if(*pos++ >= key)
      cnt++;
  }

  LEAVE;
  return cnt;
}
