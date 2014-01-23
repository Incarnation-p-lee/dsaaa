/*--------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                               */
/*-DATE:        11142013                                        */
/*-WHAT:        Homework chapter 2.12                           */
/*-REVISION:                                                    */
/*- DATE ------------------------ DESCRIPTION ------------------*/
/*- 11182013    CHAPTER 2-12                                   -*/
/*--------------------------------------------------------------*/
void
chapt_2_12(void)
{
  ENTER("chapt_2_12");

  print_report_header(stdout, "Sub Sequences", 2, 12);
  print_report_header(dsaaa_report, "Sub Sequences", 2, 12);
  dochapt_2_12();

  LEAVE;
  return;
}

static void
dochapt_2_12(void)
{
  double (**iterator)(double *, int, int *, int *);
  enum minsub_sequence *min_type;
  int data_size;
  int data_cnt;
  static double cases[][MAX_SUB_DATA_SIZE] = {
    { 0.1,  0.2, 0.0,  0.3, 0.4, 0.5,  0.6,  0.9,  0.8, 0.7,},
    {-0.1, -2.1, 3.8, -0.9, 1.3, 9.0, -2.1, -6.0, -0.4,-1.1,},
    {-0.1, -0.1,-2.8, -1.9,-0.3,-1.3, -7.1, -2.0, -0.3,-2.7,},
    { 0.0,  0.0, 0.0,  0.0, 0.0, 0.0,  0.0,  0.0,  0.0, 0.0,},
    { 1.1,  1.1, 1.1,  1.1, 1.1, 1.1,  1.1,  1.1,  1.1, 1.1,},
    {-0.1,  0.2,-0.3,  0.4,-0.5, 0.6, -0.7,  0.8, -0.8, 0.9,},
    {-0.2, -0.8, 1.3, -1.9, 0.7,-2.1, -3.2,  2.3,  3.4,-1.1,},
    {-2.1, -8.3,-0.8, -0.4, 7.3, 2.3, -8.2, -2.7, -1.5,-0.1,},
    {-3.3, -2.2, 1.3, -4.7, 2.1, 0.7, -3.4, -2.8, -1.4,-8.1,},
    {-0.1, -2.9, 4.2, -1.9, 2.9, 7.3, -1.4, -6.2, -1.4,-0.1,},
  };
  ENTER("dochapt_2_12");

  print_data_in(stdout, cases, sizeof(cases) / sizeof(cases[0]));
  print_data_in(dsaaa_report, cases,
    sizeof(cases) / sizeof(cases[0]));

  data_size = sizeof(cases[0]) / sizeof(cases[0][0]);
  data_cnt = sizeof(cases) / sizeof(cases[0]);

  iterator = func_name;
  min_type = minsub_type;
  while(iterator < func_name + 
    sizeof(func_name) / sizeof(func_name[0]))
  {
    print_submin_title(stdout, data_size, *min_type);
    print_submin_title(dsaaa_report, data_size, *min_type);
    find_minsub_seq(cases, data_cnt, data_size,
      *iterator++, *min_type++);
  }

  LEAVE;
  return;
}

static void
find_minsub_seq(double (*cases)[MAX_SUB_DATA_SIZE], int data_cnt,
  int data_size, double (*entry)(double *, int, int *, int *),
  enum minsub_sequence type)
{
  register double (*iterator)[MAX_SUB_DATA_SIZE];
  struct sub_sequence su_rpt;
  int counts;
  ENTER("find_minsub_seq");

  iterator = cases;
  su_rpt.astringent = data_size;
  astringent_init(&su_rpt, data_size, type);
  while(iterator < cases + data_cnt)
  {
    counts = SUB_CASES_COUNT;

    TIME_START;
    su_rpt.min = SUB_PERFORMANCE(counts, entry,
      *iterator, data_size, &su_rpt.st, &su_rpt.ed);
    TIME_END(&su_rpt.usec);

    print_submin_report(stdout, &su_rpt);
    print_submin_report(dsaaa_report, &su_rpt);
    iterator++;
  }

  LEAVE;
  return;
}

static void
astringent_init(struct sub_sequence *su_rpt, int dimension,
  enum minsub_sequence type)
{
  ENTER("astringent_init");

  switch(type)
  {
    case MIN_SUB:
    case MAX_MULTI_SUB:
      su_rpt->astringent = dimension;
      break;
    case MIN_POSITIVE_SUB:
      su_rpt->astringent = dimension * dimension;
      break;
    default:
      error_handle("Unresolved enum value detected.");
      break;
  }

  LEAVE;
  return;
}

static void
print_submin_report(FILE *fd, struct sub_sequence *rpt)
{
  static int index = 0;
  ENTER("print_submin_report");

  fprintf(fd, "%4d. %10.4f  %7d  %7d  %11.6f  %11.6f\n",
    index++ >> 1, rpt->min, rpt->st, rpt->ed,
    (double)rpt->usec / SUB_CASES_COUNT,
    rpt->usec / rpt->astringent);

  LEAVE;
  return;
}

static void
print_submin_title(FILE *fd, int size_s,
  enum minsub_sequence type)
{
  ENTER("print_submin_title");

  switch(type)
  {
    case MIN_SUB:
      fprintf(fd, "MINIMUN SUB SEQUENCE *ASTRINGENT => O[N]\n");
      break;
    case MIN_POSITIVE_SUB:
      fprintf(fd, "MINIMUN POSITIVE SUB SEQUENCE"
        " *ASTRINGENT => O[N^2]\n");
      break;
    case MAX_MULTI_SUB:
      fprintf(fd, "MAXIMUN MULTIPLE SUB SEQUENCE"
        " *ASTRINGENT => O[N]\n");
      break;
    default:
      error_handle("Unresolved enum value detected.");
      break;
  }

  LEAVE;
  return;
}

static void
print_data_in(FILE *fd,
  double (*data)[MAX_SUB_DATA_SIZE], int size_s)
{
  register double *itt_i;
  register double (*itt_o)[MAX_SUB_DATA_SIZE];
  int index;
  ENTER("print_data_in");

  fprintf(fd, "Input Data:\n");

  index = 0;
  fprintf(fd, "INDEX ");
  while(index < MAX_SUB_DATA_SIZE)
    fprintf(fd, " [%02d]", index++);
  fprintf(fd, "\n");

  itt_o = data;
  while(itt_o < data + size_s)
  {
    itt_i = *itt_o;
    fprintf(fd, "%4d.  ", (int)(itt_o - data));
    while(itt_i < *itt_o + MAX_SUB_DATA_SIZE)
      fprintf(fd, "%4.1f ", *itt_i++);

    fprintf(fd, "\n");
    itt_o++;
  }

  fprintf(fd, "Report:\nINDEX    MINIMUN    START      END   "
    "TIME(usec)   ASTRINGENT\n");

  LEAVE;
  return;
}

static double
min_subsequence(double *data, int size_s, int *st, int *ed)
{
  double min;
  double sum;
  double single;
  int single_index;
  int st_index;
  register double *iterator;
  ENTER("min_subsequence");

  iterator = data;
  min = sum = *st = *ed = st_index = 0;
  single = INT_MAX;
  while(iterator < data + size_s)
  {
    sum += *iterator++;
    /*- if all zero items of input data, only > may not update -*/
    /*- start index and single related variable.               -*/
    if(sum >= 0)
    {
      /*- if all positive number, keep the smallest and its    -*/
      /*- index value.                                         -*/
      st_index = (int)(iterator - data);
      if(single > sum)
      {
        single = sum;
        single_index = st_index - 1;
      }
      sum = 0;
    }
    if(sum < min)
    {
      min = sum;
      *st = st_index;
      *ed = (int)(iterator - data) - 1;
    }
  }

  /*- if all positive numbers, use the smallest one as min.    -*/
  if(0 == min)
  {
    min = single;
    *ed = *st = single_index;
  }

  LEAVE;
  return min;
}

/*- Assume Y[i] i = (0 ... N) [size == N + 1], raw input X[i]. -*/
/*- POSTULATION:                                               -*/
/*- Y[0] = 0.                                                  -*/
/*- Y[1] = X[0].                                               -*/
/*- Y[2] = X[0] + X[1].                                        -*/
/*- Y[N] = X[0] + X[1] + ... + X[N - 1].                       -*/
/*- Then the minimum sub positive sequence has two conditions: -*/
/*-   1. Y[i] - Y[j] > 0 && i > j                              -*/
/*-   2. (Y[i] - Y[j]) is the smallest positive                -*/
static double
min_posi_subsequence(double *data, int size_s, int *st, int *ed)
{
  double min_posi;
  double sum_cad;
  double *iterator_1;
  double *iterator_2;
  double *data_ass;
  ENTER("min_posi_subsequence");

  malloc_initial((void **)&data_ass,
    sizeof(*data_ass) * (size_s + 1));
  min_posi_assist(data_ass, data, size_s);

  min_posi = INT_MAX;
  sum_cad = 0;
  iterator_1 = iterator_2 = data_ass;

  /* size of Y[N] == size of X[N] + 1                          -*/
  while(iterator_1 < data_ass + size_s + 1)
  {
    iterator_2 = iterator_1 + 1;
    while(iterator_2 < data_ass + size_s + 1)
    {
      sum_cad = *iterator_2 - *iterator_1;
      if(sum_cad > 0 && sum_cad < min_posi)
      {
        min_posi = sum_cad;
        *st = iterator_1 - data_ass;
        *ed = iterator_2 - data_ass - 1;
      }
      iterator_2++;
    }
    iterator_1++;
  }

  /* For there is no positive number in raw input data.        -*/
  if(INT_MAX == min_posi)
  {
    min_posi = 0;
    *st = *ed = 0;
  }
  saft_free((void **)&data_ass);

  LEAVE;
  return min_posi;
}

static void
min_posi_assist(double *assist, double *raw, int size)
{
  double sum;
  register double *iterator;
  ENTER("min_posi_assist");

  iterator = raw;
  sum = 0.0;
  *assist++ = 0.0;
  while(iterator < raw + size)
  {
    sum += *iterator++;
    *assist++ = sum;
  }

  LEAVE;
  return;
}

static double
max_multi_subsequence(double *data, int size_s, int *st, int *ed)
{
  double single;
  double multi_max;
  double multi_sub;
  double abs_multi;
  int st_index;
  int single_index;
  register double *iterator;
  ENTER("max_muli_subsequence");

  multi_max = multi_sub = 1.0;
  single = 0.0;
  iterator = data;
  st_index = single_index = 0;
  while(iterator < data + size_s)
  {
    multi_sub *= *iterator++;
    abs_multi = fabs(multi_sub);
    if(abs_multi < 1)
    {
      /*- For all positive number who's value less than 1.0.   -*/
      if(multi_sub > single)
      {
        single = multi_sub;
        single_index = iterator - data - 1;
      }
      st_index = iterator - data;
      multi_sub = 1.0;
    }
    if(multi_sub > multi_max)
    {
      multi_max = multi_sub;
      *st = st_index;
      *ed = iterator - data - 1;
    }
  }

  /*- If all values less than 1.0.(including all zeros)        -*/
  if(multi_max - 1.0 < MIN_DOUBLE)
  {
    multi_max = single;
    *st = *ed = single_index;
  }

  LEAVE;
  return multi_max;
}

