/*--------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                               */
/*-DATE:        08122013                                        */
/*-WHAT:        Homework chapter 1.1                            */
/*-REVISION:                                                    */
/*- DATE ------------------------ DESCRIPTION ------------------*/
/*- 08122013    CHAPTER 1-1                                    -*/
/*--------------------------------------------------------------*/
void
chapt_1_1(void)
{
  register int *pos;
  int dsize[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 500,
   1000, 5000, 10000, 50000, 100000, 500000, 1000000, 5000000,
   10000000, };
  enter("chapt_1_1");

  print_report_header(stdout, "Selection Problem", 1, 1);
  print_report_header(hwork_rept, "Selection Problem", 1, 1);
  print_algo_info(stdout);
  print_algo_info(hwork_rept);

  pos = dsize;
  while(pos < dsize + sizeof(dsize) / sizeof(dsize[0]))
    dochapter1_1(*pos++);

  leave();
  return;
}


static void
print_algo_info(FILE *fd)
{
  enter("print_algo_info");

  fprintf(fd, "\nASTRINGENT: O(N*logN)\n");
  fprintf(fd,
    "No.     DATA_SIZE         KVALUE:VALIDATION     "
    "TIME(usec)=>ASTRINGENT\n");

  leave();
  return;
}


static void
dochapter1_1(int data_size)
{
  int *dinput;
  struct rept_entry entry;

  enter("do_chapter");
  entry.data_size = data_size;
  dinput = data_prepare(data_size);

  TIME_START;
  entry.kvalue = selection_problem(
    dinput, data_size, data_size >> 1);
  TIME_END(&entry.usec_cost);

  entry.astringent = (double)entry.usec_cost / 
    (log(data_size) * data_size);
  entry.validate = result_validate(
    dinput, data_size, entry.kvalue);

  report_data(&entry);

  free(dinput);
  dinput = NULL;

  leave();
  return;
}


static int
selection_problem(int *data, int size, int key)
{
  register int big_cnt;
  int data_size;
  int start;
  int index;

  enter("selection_problem");
  assert(NULL != data);
  start = 0;
  data_size = size;
  while(1)
  {
    big_cnt = split_data(data, start, data_size);
    /*----------------------------------------------------------*/
    /* if the count of big part is less than key, reset the data*/
    /* and update rest key.                                     */
    /*----------------------------------------------------------*/
    if(big_cnt < key)
    {
      data_size -= big_cnt;
      key -= big_cnt;
    }
    /*----------------------------------------------------------*/
    /* if the count of big part is more than key, reset start   */
    /* index and update data size.                              */
    /*----------------------------------------------------------*/
    else if(big_cnt > key)
    {
      start += (data_size - big_cnt + 1);
      data_size = big_cnt - 1;
    }
    else
      break;
  }
  index = start + data_size - big_cnt;

  leave();
  return data[index];
}


/*--------------------------------------------------------------*/
/* Return the count of big part include the key value.          */
/*--------------------------------------------------------------*/
static int
split_data(int *data, int start, int len)
{
  int key;
  int i;
  int j;

  enter("split_data");
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

  leave();
  return len - (j - start);
}


static int*
data_prepare(int data_size)
{
  register int *pos;
  int *random_data;

  enter("data_prepare");
  if(0 >= data_size)
    error_handle("data_prepare");

  random_data = calloc(sizeof(int), data_size);
  if(NULL == random_data)
    error_handle("calloc");

  pos = random_data;
  srand((unsigned)time(NULL));
  while(pos < random_data + data_size)
    *pos++ = ((unsigned)DATA_MAX >> 1) - (rand() % DATA_MAX);

  leave();
  return random_data;
}


static void
report_data(struct rept_entry *rept)
{
  static int number = 1;

  enter("report_data");
  fprintf(stdout,
    "%2d     %10d     %10d:%10d     %10u=>%10.6f\n",
    number, rept->data_size, rept->kvalue,
    rept->validate, rept->usec_cost, rept->astringent);

  fprintf(hwork_rept,
    "%2d     %10d     %10d:%10d     %10u=>%10.6f\n",
    number, rept->data_size, rept->kvalue,
    rept->validate, rept->usec_cost, rept->astringent);

  number++;

  leave();
  return;
}


static int
result_validate(int *data, int len, int key)
{
  register int *pos;
  int cnt;

  enter("result_validate");
  assert(NULL != data);
  pos = data;

  cnt = 0;
  while(pos < data + len)
  {
    if(*pos++ >= key)
      cnt++;
  }

  leave();
  return cnt;
}
