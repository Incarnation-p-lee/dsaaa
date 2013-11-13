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
  int cases[] = {
    1,      10,
    11,     20,
    1,     100,
    201,   400,
    101,   600,
    11,   1000,
    1001, 2000,
  };
  int *iterator;
  enter("dochapter2_7");

  print_random_title(stdout);
  print_random_title(hwork_rept);
  srand((unsigned)time(NULL));

  iterator = cases;
  while(iterator < cases + sizeof(cases) / sizeof(cases[0]))
  {
    random_sequence(*iterator, *(iterator + 1));
    iterator += 2;
  }

  leave();
  return;
}


static void
random_sequence(int start, int end)
{
  int size_r;
  enum repeat_vehicle *iterator;
  struct gen_random_report data;
  char **title;
  int counts;
  enter("random_replacement");

  if(start > end)
    error_handle("Index out of range");

  size_r = end - start + 1;
  data.dimension = size_r;
  data.start = start;
  data.end = end;

  iterator = repeats;
  title = repeat_description;
  while(iterator < repeats + sizeof(repeats) / sizeof(repeats[0]))
  {
    data.outline = *title++;
    expected_init(&data, size_r, *iterator);
    malloc_initial((void **)&sequence_data,
      size_r * sizeof(*sequence_data));

    counts = REPEAT_COUNT;
    TIME_START;
    SEQ_PERFORMANCE(counts, generate_random, start, end, *iterator);
    TIME_END(&data.usec);

    print_random_report(stdout, &data);
    print_random_report(hwork_rept, &data);
    saft_free((void **)&sequence_data);
    iterator++;
  }

  leave();
  return;
}

static void
expected_init(struct gen_random_report *data_r, int size_r,
  enum repeat_vehicle type)
{
  double exp;
  enter("expected_init");

  switch(type)
  {
    case UTIL:
      exp = 3.0;
      break;
    case USED:
      exp = 2.0;
      break;
    case SWAP:
      exp = 1.0;
      break;
    default:
      error_handle("Unresolved enum value detected.");
      break;
  }
  data_r->expected = pow((double)size_r, exp);

  leave();
  return;
}

static void
print_random_title(FILE *fd)
{
  enter("print_random_title");

  fprintf(fd, "\nNUM_START      END  DIMENSION  "
    "  TIME(usec)  DESCRIPTION     ASTRINGENT\n");

  leave();
  return;
}

static void
print_random_report(FILE *fd, struct gen_random_report *rrpt)
{
  enter("print_random_report");

  fprintf(fd, " %8d %8d   %8d    %10.4f  %.16s  %10.7f\n",
    rrpt->start, rrpt->end, rrpt->dimension,
    (double)rrpt->usec / REPEAT_COUNT, rrpt->outline,
    (double)rrpt->usec / rrpt->expected);

  leave();
  return;
}

static void
generate_random(int start, int end, enum repeat_vehicle type)
{
  int size_r;
  int raw_value;
  int repeated;
  register int *iterator;
  enter("generate_random");

  size_r = end - start + 1;
  repeat_assist_init(start, size_r, type);

  switch(type)
  {
    case UTIL:
    case USED:
      iterator = sequence_data;
      while(iterator < sequence_data + size_r)
      {
        while(1)
        {
          raw_value = rand() % (end - start + 1) + start;
          switch(type)
          {
            case UTIL:
              repeated = isrepeated_util(
                  iterator - sequence_data, raw_value);
              break;
            case USED:
              repeated = isrepeated_used(start, raw_value);
              break;
            case SWAP:
              break;
          }
          if(NOT_REPEATED == repeated)
            break;
        }
        *iterator++ = raw_value;
      }
      break;
    case SWAP:
      random_swap(size_r);
      break;
    default:
      error_handle("Unresolved enum value detected.");
      break;
  }

  repeat_assist_clear(type);

  leave();
  return;
}

static void
repeat_assist_init(int start, int size_r,
  enum repeat_vehicle type)
{
  int ittr;
  enter("repeat_assist_init");

  ittr = 0;
  switch(type)
  {
    case UTIL:
      break;
    case USED:
      malloc_initial((void **)&used_number,
        sizeof(*used_number) * size_r);
      while(ittr < size_r)
        used_number[ittr++] = REPEAT_UNUSED;
      break;
    case SWAP:
      while(ittr < size_r)
        sequence_data[ittr++] = start++;
      break;
    default:
      error_handle("Unresolved enum value detected.");
      break;
  }

  leave();
  return;
}

static void
repeat_assist_clear(enum repeat_vehicle type)
{
  enter("repeat_assist_clear");

  switch(type)
  {
    case UTIL:
      break;
    case USED:
      saft_free((void **)&used_number);
      break;
    case SWAP:
      break;
    default:
      error_handle("Unresolved enum value detected.");
      break;
  }

  leave();
  return;
}

static int
isrepeated_util(int size_r, int raw)
{
  int repeated;
  int *iterator;
  enter("isrepeated_util");

  if(0 > size_r)
    error_handle("Invalid data dimension");

  repeated = NOT_REPEATED;
  iterator = (int *)sequence_data;
  while(iterator < sequence_data + size_r)
  {
    if(*iterator++ == raw)
    {
      repeated = REPEATED;
      break;
    }
  }

  leave();
  return repeated;
}

static int
isrepeated_used(int start, int raw)
{
  int repeated;
  enter("isrepeated_used");

  switch(used_number[raw - start])
  {
    case REPEAT_UNUSED:
      used_number[raw - start] = REPEAT_USED;
      repeated = NOT_REPEATED;
      break;
    case REPEAT_USED:
      repeated = REPEATED;
      break;
    default:
      error_handle("Invalid definition value detected");
      break;
  }

  leave();
  return repeated;
}

static void
random_swap(int size_r)
{
  int *data_r;
  int ittr;
  enter("isrepeated_swap");

  data_r = sequence_data;
  ittr = 1;
  while(ittr < size_r)
  {
    exchange(data_r + ittr, data_r + rand() % ittr);
    ittr++;
  }

  leave();
  return;
}
