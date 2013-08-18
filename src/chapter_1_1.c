/*-------------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                                    */
/*-DATE:        08122013                                             */
/*-WHAT:        Homework chapter 1.1                                 */
/*-REVISION:                                                         */
/*- DATE ------------------------ DESCRIPTION -----------------------*/
/*- 08122013    CHAPTER 1-1                                         -*/
/*-------------------------------------------------------------------*/
void
chapt_1_1(void)
{
  register int *pos;
  int dsize[] = {10, 100, 1000, 10000, 100000};
  
  report_header();
  pos = dsize;
  while(pos < dsize + sizeof(dsize) / sizeof(dsize[0]))
    chaptdo_1_1(*pos++);
  
  return;
}


static void
chaptdo_1_1(int data_size)
{
  int *dinput;
  struct rept_entry entry;

  entry.data_size = data_size;
  dinput = data_prepare(data_size);
  TIME_START;
  entry.kvalue = selection_problem(dinput, data_size, data_size >> 1);
  TIME_END(&entry.usec_cost);
  entry.validate = result_validate(dinput, data_size, entry.kvalue);
  report_data(&entry);
   
  free(dinput);
  dinput = NULL;
  return;
}


static int
selection_problem(int *data, int size, int key)
{
  register int big_cnt;
  int data_size;
  int start;
  int index;
 
  assert(NULL != data);
  start = 0;
  data_size = size;
  while(1)
  {
    big_cnt = split_data(data, start, data_size);
    /*---------------------------------------------------------------*/
    /* if the count of big part is less than key, reset the data size*/
    /* and update rest key.                                          */
    /*---------------------------------------------------------------*/
    if(big_cnt < key)
    {
      data_size -= big_cnt;
      key -= big_cnt;
    }
    /*---------------------------------------------------------------*/
    /* if the count of big part is more than key, reset the start    */
    /* index and update data size.                                   */
    /*---------------------------------------------------------------*/
    else if(big_cnt > key)
    {
      start += (data_size - big_cnt + 1);
      data_size = big_cnt - 1;
    }
    else
      break;
  }
  index = start + data_size - big_cnt;
  
  return data[index];
}

/*-------------------------------------------------------------------*/
/* Return the count of big part include the key value.               */
/*-------------------------------------------------------------------*/
static int
split_data(int *data, int start, int len)
{
  int key;
  int i;
  int j;

  if(len < 0)
    return -1;

  key = data[start];
  i = start + 1;
  j = start + len - 1;
  while(1)
  {
    while(key < data[j])
      j--;
    while(key > data[i] && i < j)
      i++;
    if(i >= j)
      break;
    exchange(data + i, data + j);
  }
  exchange(data + start, data + j);
  
  return len - (j - start);
}


static int*
data_prepare(int data_size)
{
  register int *pos;
  int *random_data;

  if(0 >= data_size)
    error_handle("data_prepare");

  random_data = calloc(sizeof(int), data_size);
  if(NULL == random_data)
    error_handle("calloc");
  
  pos = random_data;
  srand((unsigned)time(NULL));
  while(pos < random_data + data_size)
    *pos++ = (DATA_MAX >> 1) - (rand() % DATA_MAX);
 
  return random_data;
}


static void
report_header()
{
  time_t date;
  date = time(NULL);
  fprintf(stdout, "          Chapter 1-1\n\n\n");
  fprintf(stdout, 
    "                        Selection problem\n");
  fprintf(stdout, "TIME: %s", ctime((const time_t *)&date));
  fprintf(stdout, 
    "No.       DATA_SIZE     KVALUE[ VALD ]    TIME_COST(usec)\n");



  fprintf(hwork_rept, "          Chapter 1-1\n\n\n");
  fprintf(hwork_rept,
    "                        Selection problem\n");
  fprintf(hwork_rept, "TIME: %s", ctime((const time_t *)&date));
  fprintf(hwork_rept,
    "No.       DATA_SIZE     KVALUE[ VALD ]    TIME_COST(usec)\n");
  return;
}


static void
report_data(struct rept_entry *rept)
{
  static int number = 1;

  fprintf(stdout, 
    "%2d       %10d     %6d[%6d]    %10u\n",
    number, rept->data_size, rept->kvalue,
    rept->validate, rept->usec_cost);

  fprintf(hwork_rept, 
    "%2d       %10d     %6d[%6d]    %10u\n",
    number, rept->data_size, rept->kvalue,
    rept->validate, rept->usec_cost);

  number++;
  return;
}


static int
result_validate(int *data, int len, int key)
{
  register int *pos;
  int cnt;

  assert(NULL != data);
  pos = data;
  
  cnt = 0;
  while(pos < data + len)
  {
    if(*pos++ >= key)
      cnt++;
  }
  
  return cnt;
}


