/*--------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                               */
/*-DATE:        12052013                                        */
/*-WHAT:        Homework chapter 2.13                           */
/*-REVISION:                                                    */
/*- DATE ------------------------ DESCRIPTION ------------------*/
/*- 12052013    CHAPTER 2-13                                   -*/
/*--------------------------------------------------------------*/
void
chapt_2_13(void)
{
  ENTER("chapt_2_13");

  print_report_header(stdout, "IS Prime Number", 2, 13);
  print_report_header(dsaaa_report, "IS Prime Number", 2, 13);
  dochapt_2_13();

  LEAVE;
  return;
}

static void
dochapt_2_13(void)
{
  int rcount;
  struct prime_num_report pn_rpt;
  register int *iterator;
  int raw_data[] = {
    2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
    101, 201, 301, 601, 901, 1021, 7341, 12371, 19127, 23761,
    86117, 86269, 86477, 86579, 86587, 84461,
  };
  ENTER("dochapt_2_13");

  print_prime_title(stdout);
  print_prime_title(dsaaa_report);

  iterator = raw_data;
  while(iterator < raw_data +
    sizeof(raw_data) / sizeof(*raw_data))
  {
    rcount = PRIME_REPEAT_COUNT;
    pn_rpt.raw_data = *iterator++;
    pn_rpt.astringent = sqrt((double)pn_rpt.raw_data);

    TIME_START;
    pn_rpt.isprimed = PRIME_PERFORMANCE(rcount, isprime_number,
      pn_rpt.raw_data);
    TIME_END(&pn_rpt.usec);

    print_prime_report(stdout, &pn_rpt);
    print_prime_report(dsaaa_report, &pn_rpt);
  }

  LEAVE;
  return;
}

static int
isprime_number(int num)
{
  int result;
  int num_limit;
  int iterator;
  ENTER("isprime_number");

  if(num < 2)
    error_handle("Expected Positive Integrate More Than 1.");

  result = isodd_number(num);
  if(INTEGRATE_ODD == result)
  {
    iterator = 3;
    result = PRIMED;
    num_limit = (int)sqrt((double)num);
    while(iterator <= num_limit)
    {
      if(!(num % iterator))
      {
        result = NOT_PRIMED;
        break;
      }
      iterator += 2;
    }
  }

  LEAVE;
  return result;
}

static int
isodd_number(int num)
{
  int result;
  ENTER("iseven_number");

  if(num < 0)
    error_handle("Expected Positive Integrate.");

  if(0 == (num & RIGHT_MOST_BIT_MASK))
  {
    if(2 == num)
      result = PRIMED;
    else
      result = NOT_PRIMED;
  }
  else
    result = INTEGRATE_ODD;

  LEAVE;
  return result;
}

static void
print_prime_title(FILE *fd)
{
  ENTER("print_prime_title");

  fprintf(fd, "PRIME NUMBER VALIDATION: O[sqrt(N)]\n");
  fprintf(fd, "INDEX   DATA_IN   IS_PRIMED"
    "  TIME(usec)  ASTRINGEND\n");

  LEAVE;
  return;
}

static void
print_prime_report(FILE *fd, struct prime_num_report *rpt)
{
  static int index_r = 0;
  char *msg_r;
  ENTER("print_prime_report");

  switch(rpt->isprimed)
  {
    case PRIMED:
      msg_r = MACRO_TO_STRING(PRIMED);
      break;
    case NOT_PRIMED:
      msg_r = MACRO_TO_STRING(NOT_PRIMED);
      break;
    default:
      error_handle("Unresolved Prime type detected");
      break;
  }
  fprintf(fd, "%4d. %9d  %10s %10.5f  %11.5f\n",
    (index_r++ >> 1), rpt->raw_data, msg_r,
    (double)rpt->usec / PRIME_REPEAT_COUNT,
    rpt->usec / rpt->astringent);

  LEAVE;
  return;
}
