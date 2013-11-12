/*--------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                               */
/*-DATE:        11102013                                        */
/*-WHAT:        Homework chapter 2.7                            */
/*-REVISION:                                                    */
/*- DATE ------------------------ DESCRIPTION ------------------*/
/*- 11102013    CHAPTER 1-1                                    -*/
/*--------------------------------------------------------------*/
void
chapt_2_7(void)
{
  enter("chapter_2_7");

  print_report_header(stdout, "Random Generation", 2, 7);
  print_report_header(hwork_rept, "Random Generation", 2, 7);
  dochapter2_7();

  leave();
  return;
}


static void
dochapter2_7(void)
{
  int ranges[] = {
    1,    10,
    10,   20,
    1,   100,
    10, 1000,
    20, 3000,
  };
  int *iterator;
  enter("dochapter2_7");

  print_random_title(stdout);
  print_random_title(hwork_rept);

  iterator = ranges;
  while(iterator < ranges + sizeof(ranges) / sizeof(ranges[0]))
  {
    random_sequence(*iterator, *(iterator + 1));
    iterator += 2;
  }

  leave();
  return;
}


static int *
random_sequence(int start, int end)
{
  int *seq_array;
  int seq_size;
  int (**iterator)(const int *, int, int);
  struct gen_random_report data;
  char **title;
  enter("random_replacement");

  srand((unsigned)time(NULL));
  if(start > end)
    error_handle("Index out of range");

  seq_size = end - start + 1;
  data.dimension = seq_size;
  data.start = start;
  data.end = end;

  iterator = repeats;
  title = vehicle_name;
  while(iterator < repeats + sizeof(repeats) / sizeof(repeats[0]))
  {
    malloc_initial((void **)&seq_array,
      seq_size * sizeof(*seq_array));
    data.outline = *title++;

    TIME_START;
    generate_random(seq_array, start, end, *iterator++);
    TIME_END(&data.usec);

    print_random_report(stdout, seq_array, &data);
    print_random_report(hwork_rept, seq_array, &data);
    saft_free((void **)&seq_array);
  }

  leave();
  return seq_array;
}

static void
print_random_title(FILE *fd)
{
  enter("print_random_title");

  fprintf(fd, "\nNUM_START      END  DIMENSION  "
    "TIME(usec)  DESCRIPTION\n");

  leave();
  return;
}

static void
print_random_report(FILE *fd, int *data,
  struct gen_random_report *rreport)
{
  enter("print_random_report");


  fprintf(fd, " %8d %8d   %8d    %8d  %s\n",
    rreport->start, rreport->end,
    rreport->dimension, rreport->usec,
    rreport->outline);

  leave();
  return;
}

static void
generate_random(int *seq, int start, int end,
  int (*isrepeated)(const int *, int, int))
{
  int seq_size;
  int raw_value;
  register int *iterator;
  enter("generate_random");

  seq_size = end - start + 1;
  iterator = seq;
  while(iterator < seq + seq_size)
  {
    while(1)
    {
      raw_value = rand() % (end + 1);
      raw_value = (raw_value + start) % (end + 1);
      if(!isrepeated(seq, iterator - seq + 1, raw_value))
      {
        *iterator++ = raw_value;
        break;
      }
    }
  }

  leave();
  return;
}

static int
isrepeated_util(const int *seq, int size, int raw)
{
  int repeated;
  int *iterator;
  enter("isrepeated_util");

  if(0 > size)
    error_handle("Invalid data dimension");

  repeated = 0;
  iterator = (int *)seq;
  while(iterator < seq + size)
  {
    if(*iterator++ == raw)
      repeated = 1;
  }

  leave();
  return repeated;
}
