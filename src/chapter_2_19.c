/*--------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                               */
/*-DATE:        01102014                                        */
/*-WHAT:        Homework chapter 2.19                           */
/*-REVISION:                                                    */
/*- DATE ------------------------ DESCRIPTION ------------------*/
/*- 01102014    CHAPTER 2-19                                   -*/
/*--------------------------------------------------------------*/
void
chapt_2_19(void)
{
  ENTER("chapt_2_19");

  print_report_header(stdout, "Principle Element", 2, 19);
  print_report_header(dsaaa_report, "Principle Element", 2, 19);

  dochapt_2_19();

  LEAVE;
  return;
}


static void
dochapt_2_19(void)
{
  int *raw_data;
  int repeats;
  register int *iter;
  struct principle_ele_report prin_rpt;
  int cases[] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    20, 30, 40, 50, 60, 70, 80, 90, 100,
  };
  ENTER("dochapt_2_19");

  srand((unsigned)time(NULL));
  malloc_initial((void**)&raw_data,
    sizeof(*raw_data) * PRIN_DATA_SIZE);
  data_init(raw_data, PRIN_DATA_SIZE);

  print_raw_data(stdout, raw_data, PRIN_DATA_SIZE);
  print_raw_data(dsaaa_report, raw_data, PRIN_DATA_SIZE);
  print_prin_title(stdout);
  print_prin_title(dsaaa_report);

  iter = cases;
  repeats = PRIN_REPEATS;
  while(iter < cases + sizeof(cases) / sizeof(*cases))
  {
    repeats = PRIN_REPEATS;
    prin_rpt.dimension = *iter;
    TIME_START;
    prin_rpt.result = PRINCIPLE_PERFORMANCE(repeats, principle_element,
      raw_data, *iter);
    TIME_END(&prin_rpt.usec);
    print_prin_report(stdout, *iter, &prin_rpt);
    print_prin_report(dsaaa_report, *iter++, &prin_rpt);
  }

  saft_free((void**)&raw_data);
  LEAVE;
  return;
}

static void
print_prin_title(FILE *fd)
{
  ENTER("print_prin_title");

  fprintf(fd, "Find Principle element: O[2N]\n");
  fprintf(fd, "INDEX  DIMENSION          RESULT"
    "  TIME(usec)  ASTRINGEND\n");

  LEAVE;
  return;
}

static void
print_prin_report(FILE *fd, int size,
  struct principle_ele_report *report)
{
  static int index = 0;
  const char *result;
  ENTER("print_prin_title");

  switch(report->result)
  {
    case PRINCIPLE_ELE:
      result = MACRO_TO_STRING(PRINCIPLE_ELE);
      break;
    case NOT_PRINCIPLE:
      result = MACRO_TO_STRING(NOT_PRINCIPLE);
      break;
    default:
      result = "N/A";
      warn_prompt("Unknown macro name detected.");
      break;
  }
  fprintf(fd, "%5d     %6d   %13s    %8d  %10.4f\n",
    (index++) >> 1, report->dimension, result,
    report->usec, (double)report->usec / (size << 1));

  LEAVE;
  return;
}

static void
data_init(int *dt_in, int size)
{
  register int *iterator = dt_in;
  ENTER("data_init");

  while(iterator < dt_in + size)
    *iterator++ = rand() % PRIN_VALUE_SIZE + 1;

  LEAVE;
  return;
}

static void
print_raw_data(FILE *fd, int *dt_in, int size)
{
  register int *iterator;
  int ind;
  ENTER("print_raw_data");

  fprintf(fd, "Raw Data[%d]:\n", size);

  ind = 0;
  while(ind < PRINT_LINE_MAX)
    fprintf(fd, "%03d ", ind++);
  fprintf(fd, "\n");

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

static int
principle_element(int *raw_data, int size)
{
  int *data_in;
  int *data_out;
  int candidate;
  int result;
  ENTER("principle_element_setup");

  if(size > PRIN_DATA_SIZE)
    warn_prompt("A risk of memory leak detected.");

  malloc_initial((void**)&data_in, sizeof(*data_in) * size);
  malloc_initial((void**)&data_out, sizeof(*data_out) * size);
  memcpy(data_in, raw_data, sizeof(*data_in) * size);

  candidate = principle_element_iter(data_out, data_in, size);
  result = -1 == candidate?
    NOT_PRINCIPLE: isprinciple(raw_data, size, candidate);

  saft_free((void**)&data_out);
  saft_free((void**)&data_in);
  LEAVE;
  return result;
}

static int
principle_element_iter(int *data_out, int *data_in, int size)
{
  register int *iter_in;
  register int *iter_out;
  int iseven;
  int candidate;
  ENTER("principle_element");

  if(0 == size)
  {
    candidate = -1;
    goto ITER_END;
  }
  else if(1 == size)
  {
    candidate = *data_in;
    goto ITER_END;
  }

  memset(data_out, 0, sizeof(*data_out) * size);
  iseven = size % 2;
  iter_in = data_in;
  iter_out = data_out;
  while(iter_in < data_in + size - iseven)
  {
    if(*iter_in == *(iter_in + 1))
      *iter_out++ = *iter_in;
    iter_in += 2;
  }

  if(iseven)
    /*- If size is even, compare the last element with both    -*/
    /*- the second last one and the first one for 2 cases.     -*/
    /*- Case1: 1,0,1,0,1.                                      -*/
    /*- Case2: 0,1,0,1,1.                                      -*/
    if(*data_in == *iter_in || *iter_in == *(iter_in - 1))
      *iter_out++ = *iter_in;

  candidate = principle_element_iter(data_in, data_out,
    iter_out - data_out);

ITER_END:
  LEAVE;
  return candidate;
}

static int
isprinciple(int *raw_data, int size, int cand)
{
  register int *iter;
  int cnt;
  ENTER("isprinciple");

  iter = raw_data;
  cnt = 0;
  while(iter < raw_data + size)
  {
    if(cand == *iter++)
      cnt++;
  }

  LEAVE;
  return cnt > (size >> 1)? PRINCIPLE_ELE: NOT_PRINCIPLE;
}
