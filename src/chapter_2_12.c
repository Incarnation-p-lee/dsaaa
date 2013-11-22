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
    {11,  2, 8,  2,  3, 7, 22, 6,  1, 12,  9,  8,  3,  8, 21, 19},
    { 1,  1, 1,  1,  1, 1,  1, 1,  1,  1,  1,  1,  1,  1,  1,  1},
    {-1,  1,-1,  1, -1, 1, -1, 1, -1,  1, -1,  1, -1,  1, -1,  1},
    {-1, -7,-8,-72,-28,-7,-27,-6,-31,-32,-89, -8, -5, -2,-41,-39},
    {21, 17,-3,-43,-83, 8, -7,-9,-33,-18, 89, 38, -1, -8, 51,-48},
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
    print_submin_title(hwork_rept, data_size, *min_type++);
    find_minsub_seq(cases, data_cnt, data_size, *iterator++);
  }

  LEAVE;
  return;
}

static void
find_minsub_seq(signed (*cases)[MAX_SUB_DATA_SIZE], int data_cnt,
  int data_size, signed (*entry)(signed *, int, int *, int *))
{
  register signed (*iterator)[MAX_SUB_DATA_SIZE];
  struct sub_sequence su_rpt;
  int counts;
  ENTER("find_minsub_seq");

  iterator = cases;
  su_rpt.astringent = data_size;
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
      fprintf(fd, "MINIMUN-SUB SEQUENCE *ASTRINGENT => O[N]\n");
      break;
    case MIN_POSITIVE_SUB:
      fprintf(fd, "MINIMUN POSITIVE SUB SEQUENCE"
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

#if 1
static signed
min_posi_subsequence(signed *data, signed size_s, int *st, int *ed)
{
  signed min_posi;
  signed min_composed;
  signed sum;
  signed *iterator;
  struct navi_entry nav_vi[size_s];
  int nav_top;
  ENTER("min_posi_subsequence");

  memset(nav_vi, 0, sizeof(nav_vi));
  iterator = data;
  nav_top = sum = min_composed = 0;
  min_posi = INT_MAX;
  while(iterator < data + size_s)
  {
    sum += *iterator;
    if(sum < 0)
    {
      nav_vi[nav_top].navi_value = sum;
      nav_vi[nav_top++].ed_index = iterator - data;
      sum = 0;
    }

    if(sum > 0)
    {
      *st  = minimun_composed(&min_composed, sum, nav_vi, nav_top);
      if(min_composed < min_posi)
      {
        min_posi = min_composed;
        *ed = iterator - data;
      }
      if(*iterator > 0 && min_posi > *iterator)
      {
        min_posi = *iterator;
        *st = iterator - data;
      }
    }
    iterator++;
  }

  /*- if all negative numbers, reset the min, st and ed to 0.  -*/
  if(INT_MAX == min_posi)
  {
    min_posi = 0;
    *st = *ed = 0;
  }

  LEAVE;
  return min_posi;
}
#else

static signed
min_posi_subsequence(signed *data, signed size_s, int *st, int *ed)
{
  signed min_posi;
  signed sum;
  signed *iterator;
  signed nav_sum[size_s];
  int nav_top;
  int st_index;
  ENTER("min_posi_subsequence");

  memset(nav_sum, 0, sizeof(nav_sum));
  iterator = data;
  nav_top = sum = st_index = 0;
  min_posi = INT_MAX;
  while(iterator < data + size_s)
  {
    sum += *iterator;
    if(sum < 0)
    {
      sum = 0;
    }

    if(sum > 0 && min_posi > sum)
    {
      min_posi = sum;
    }
    iterator++;
  }

  /*- if all negative numbers, reset the min, st and ed to 0.  -*/
  if(INT_MAX == min_posi)
  {
    min_posi = 0;
  }
  *st = *ed = 0;

  LEAVE;
  return min_posi;
}

#endif

static int
minimun_composed(signed *min_composed, signed sum,
  struct navi_entry *nav_sum, int size)
{
  signed result;
  int st_index;
  register struct navi_entry *iterator;
  ENTER("minimun_composed");

  result = sum;
  st_index = 0;
  iterator = nav_sum + size - 1;
  while(iterator >= nav_sum)
  {
    result += iterator->navi_value;
    if(0 >= result)
    {
      result -= iterator->navi_value;
      st_index = iterator->ed_index + 1;
      break;
    }
    iterator--;
  }

  *min_composed = result;
  LEAVE;
  return st_index;
}
