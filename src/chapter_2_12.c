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
  print_report_header(hwork_rept, "Sub Sequences", 2, 12);
  dochapt_2_12();

  LEAVE;
  return;
}

static void
dochapt_2_12(void)
{
  signed (**iterator)(signed *, int, int *, int *);
  enum minsub_sequence *min_type;
  int data_size;
  int data_cnt;
  static signed int cases[][MAX_SUB_DATA_SIZE] = {
    {-1, -2, 3, -9, 13, 9, -2,-6, -4,-11, 18,  1,  2,  7, -1, -3},
    {21, 17,-3, 43, 83, 8,  7, 9, 33,-18, 89, 38, -1,  5, 51, 48},
    {11,  2, 8,  2,  3, 7, 22, 6,  1, 12,  9,  8,  3,  8, 21, 19},
    { 1,  1, 1,  1,  1, 1,  1, 1,  1,  1,  1,  1,  1,  1,  1,  1},
    {-1,  1,-1,  1, -1, 1, -1, 1, -1,  1, -1,  1, -1,  1, -1,  1},
    {-1, -7,-8,-72,-28,-7,-27,-6,-31,-32,-89, -8, -5, -2,-41,-39},
    { 8,  0,-1,-13,  0, 7,  0,19,  0, -8,  0,  4,  0, 68,  0,-42},
    { 0,  0, 0,  0,  0, 0,  0, 0,  0,  0,  0,  0,  0,  0,  0,  0},
    { 1,  0, 2,  0,  3, 0,  4, 0,  5,  0,  6,  0,  7,  0,  8,  0},
    { 1, -2, 3, -4,  5,-6,  7,-8,  9,-10, 11,-12, 13,-14, 15,-16},
  };
  ENTER("dochapt_2_12");

  print_data_in(stdout, cases, sizeof(cases) / sizeof(cases[0]));
  print_data_in(hwork_rept, cases, sizeof(cases) / sizeof(cases[0]));

  data_size = sizeof(cases[0]) / sizeof(cases[0][0]);
  data_cnt = sizeof(cases) / sizeof(cases[0]);

  iterator = func_name;
  min_type = minsub_type;
  while(iterator < func_name + 
    sizeof(func_name) / sizeof(func_name[0]))
  {
    print_submin_title(stdout, data_size, *min_type);
    print_submin_title(hwork_rept, data_size, *min_type);
    find_minsub_seq(cases, data_cnt, data_size,
      *iterator++, *min_type++);
  }

  LEAVE;
  return;
}

static void
find_minsub_seq(signed (*cases)[MAX_SUB_DATA_SIZE], int data_cnt,
  int data_size, signed (*entry)(signed *, int, int *, int *),
  enum minsub_sequence type)
{
  register signed (*iterator)[MAX_SUB_DATA_SIZE];
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
    print_submin_report(hwork_rept, &su_rpt);
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

  fprintf(fd, "%4d. %7d  %7d  %7d  %11.6f  %11.6f\n",
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
    default:
      error_handle("Unresolved enum value detected.");
      break;
  }

  LEAVE;
  return;
}


static void
print_data_in(FILE *fd,
  signed (*data)[MAX_SUB_DATA_SIZE], int size_s)
{
  register signed *itt_i;
  register signed (*itt_o)[MAX_SUB_DATA_SIZE];
  int index;
  ENTER("print_data_in");

  fprintf(fd, "\nInput Data:\n");

  index = 0;
  fprintf(fd, "INDEX ");
  while(index < MAX_SUB_DATA_SIZE)
    fprintf(fd, " [%02d]", index++);
  fprintf(fd, "\n");

  itt_o = data;
  while(itt_o < data + size_s)
  {
    itt_i = *itt_o;
    fprintf(fd, "%4d. ", (int)(itt_o - data));
    while(itt_i < *itt_o + MAX_SUB_DATA_SIZE)
      fprintf(fd, "%4d ", *itt_i++);

    fprintf(fd, "\n");
    itt_o++;
  }

  fprintf(fd, "Report:\nINDEX MINIMUN    START      END   "
    "TIME(usec)   ASTRINGENT\n");

  LEAVE;
  return;
}


static signed
min_subsequence(signed *data, signed size_s, int *st, int *ed)
{
  signed min;
  signed sum;
  signed single;
  int single_index;
  int st_index;
  register signed *iterator;
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

/*- Assume Y[i] i = (0 ... N) [size == N -1], raw input X[i].  -*/
/*- POSTULATION:                                               -*/
/*- Y[0] = 0.                                                  -*/
/*- Y[1] = X[0].                                               -*/
/*- Y[2] = X[0] + X[1].                                        -*/
/*- Y[N] = X[0] + X[1] + ... + X[N - 1].                       -*/
/*- Then the minimum sub positive sequence has two conditions: -*/
/*-   1. Y[i] - Y[j] > 0 && i > j                              -*/
/*-   2. (Y[i] - Y[j]) is the smallest positive                -*/
static signed
min_posi_subsequence(signed *data, signed size_s, int *st, int *ed)
{
  signed min_posi;
  signed sum_cad;
  signed *iterator_1;
  signed *iterator_2;
  signed *data_ass;
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
min_posi_assist(signed *assist, signed *raw, int size)
{
  int sum;
  register signed *iterator;
  ENTER("min_posi_assist");

  iterator = raw;
  sum = 0;
  *assist++ = 0;
  while(iterator < raw + size)
  {
    sum += *iterator++;
    *assist++ = sum;
  }

  LEAVE;
  return;
}
