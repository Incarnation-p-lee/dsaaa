/*----------------------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                                             */
/*-DATE:        11142013                                                      */
/*-WHAT:        Homework chapter 2.11                                         */
/*-REVISION:                                                                  */
/*- DATE ------------------------ DESCRIPTION --------------------------------*/
/*- 11142013    CHAPTER 2-11                                                 -*/
/*----------------------------------------------------------------------------*/
void
chapt_2_11(void)
{
  ENTER("chapt_2_11");

  print_report_header(stdout, "Specified Contains", 2, 11);
  print_report_header(dsaaa_report, "Specified Contains", 2, 11);

  print_contains_title(stdout);
  print_contains_title(dsaaa_report);

  dochapt_2_11();

  LEAVE;
  return;
}


static void
dochapt_2_11(void)
{
  int cases[] = {
  /*- cases format: [specified, min, size, step width]         -*/
       123,    1,      10,  2,
        98,   11,      20,  4,
         9,    1,     100,  6,
       234,  201,     400,  8,
       101,  101,     600, 10,
      1002,   11,    1000, 12,
      2345, 1001,   12000, 14,
     22345,    1,   42000, 16,
     52345,  101,   82000, 10,
     42345, 2001,   62000,  8,
    342345,  121,  122000,  6,
    652345,   11, 3452000,  4,
    722345, 9001, 8622000,  2,
  };
  int *iterator;
  ENTER("dochapt_2_11");

  srand((unsigned)time(NULL));

  iterator = cases;
  while(iterator < cases + sizeof(cases) / sizeof(cases[0]))
  {
    specified_contains(*iterator, *(iterator + 1),
      *(iterator + 2), *(iterator + 3));
    iterator += 4;
  }

  LEAVE;
  return;
}


static void
specified_contains(int specified, int min, int size_c, int width)
{
  int *raw_data;
  int counts;
  struct iscontains_report data_r;
  ENTER("specified_contains");

  counts = SPECIFIED_REPEAT_CNT;
  data_r.size_c = size_c;
  data_r.min = min;
  data_r.astringent = (double)log(data_r.size_c);
  raw_data = prepare_raw_data(min, size_c, width);

  TIME_START;
  data_r.result = CON_PERFORMANCE(counts, iscontains,
    specified, raw_data, size_c);
  TIME_END(&data_r.usec);

  print_contains_report(stdout, &data_r);
  print_contains_report(dsaaa_report, &data_r);
  clear_raw_data(raw_data);

  LEAVE;
  return;
}

static int *
prepare_raw_data(int min, int size_c, int step_width)
{
  int *raw_data;
  int last;
  register int *iterator;
  ENTER("prepare_raw_data");

  malloc_initial((void **)&raw_data, sizeof(*raw_data) * size_c);
  raw_data[0] = min;
  iterator = raw_data;
  while(iterator < raw_data + size_c - 1)
  {
    last = *iterator;
    *(++iterator) = last + MIN_STEP_WIDTH +
      rand() % (step_width - MIN_STEP_WIDTH + 1);
  }

  LEAVE;
  return raw_data;
}

static void
clear_raw_data(int *raw_data)
{
  ENTER("clear_raw_data");

  saft_free((void **)&raw_data);

  LEAVE;
  return;
}

static int
iscontains(int specified, int *raw_data, int size_c)
{
  int result;
  int begin_i;
  int end_i;
  int mid_i;
  ENTER("iscontains");

  result = NOT_CONTAINED;
  begin_i = 0;
  end_i = size_c - 1;
  while(1)
  {
    mid_i = (begin_i + end_i) / 2;
    if(specified > raw_data[mid_i])
      begin_i = mid_i + 1;
    else if(specified < raw_data[mid_i])
      end_i = mid_i - 1;
    else
    {
      result = CONTAINED;
      break;
    }

    if(begin_i > end_i)
      break;
  }

  LEAVE;
  return result;
}

static void
print_contains_title(FILE *fd)
{
  ENTER("print_contains_title");

  fprintf(fd, "\nNUMBER(MIN)  DIMENSION   TIME(usec)"
    "    RESULT      ASTRINGENT\n");
  fprintf(fd, "EXPECTED: O[log(N)]\n");

  LEAVE;
  return;
}

static void
print_contains_report(FILE *fd, struct iscontains_report *data_r)
{
  char *result[] = {
    "NO_CONTAINS",
    "CONTAINS   ",
  };
  char *descript;
  ENTER("print_contains_report");

  switch(data_r->result)
  {
    case NOT_CONTAINED:
      descript = result[0];
      break;
    case CONTAINED:
      descript = result[1];
      break;
    default:
      error_handle("Unresolved contains macro value detected");
      break;
  }

  fprintf(fd, "  %8d    %8d    %8d     %.12s %10.6f\n", data_r->min,
    data_r->size_c, data_r->usec, descript, data_r->usec / data_r->astringent);

  LEAVE;
  return;
}
