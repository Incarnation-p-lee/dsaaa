/*----------------------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                                             */
/*-DATE:        12162013                                                      */
/*-WHAT:        Homework chapter 2.11                                         */
/*-REVISION:                                                                  */
/*- DATE ------------------------ DESCRIPTION --------------------------------*/
/*- 11162013    CHAPTER 2-16                                                 -*/
/*----------------------------------------------------------------------------*/
void
chapt_2_16(void)
{
  ENTER("chapt_2_16");

  print_report_header(stdout, "Fast Power", 2, 16);
  print_report_header(dsaaa_report, "Fast Power", 2, 16);

  print_power_title(stdout);
  print_power_title(dsaaa_report);

  dochapt_2_16();

  LEAVE;
  return;
}


static void
dochapt_2_16(void)
{
  int counts;
  register unsigned *base_iterator;
  register int *exp_iterator;
  struct fast_power_report fp_report;
  unsigned bases[] = {
    2, 3, 4,
  };
  int exponents[] = {
    2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
  };
  ENTER("dochapt_2_16");

  srand((unsigned)time(NULL));
  initial_power_buffer(DEFAULT_BASE);

  base_iterator = bases;
  while(base_iterator < bases + sizeof(bases) / sizeof(*bases))
  {
    exp_iterator = exponents;
    while(exp_iterator < exponents +
      sizeof(exponents) / sizeof(*exponents))
    {
      counts = FPOWER_REPEATS;
      fp_report.mult_counts = cal_mult_counts(*exp_iterator);

      TIME_START;
      fp_report.result = FPOWER_PERFORMANCE(counts, cal_fast_power,
        *base_iterator, *exp_iterator);
      TIME_END(&fp_report.usec);

      print_power_report(stdout, *base_iterator, *exp_iterator, &fp_report);
      print_power_report(dsaaa_report, *base_iterator, *exp_iterator,
        &fp_report);
      exp_iterator++;
    }
    base_iterator++;
  }

  saft_free((void**)&pbuf);

  LEAVE;
  return;
}


static int
cal_mult_counts(int exp)
{
  int result;
  int loc;
  ENTER("cal_mult_counts");

  result = loc = 0;
  if(exp % 2)
  {
    /*- If exp equal 1 or 0, there is no multiples.                          -*/
    if(exp == exp % 2)
      goto CAL_END;
    /*- If right most bit is 1, it multiples at least 1 times.               -*/
    result = 1;
  }

  while(exp)
  {
    if(exp & RIGHT_MOST_BIT_MASK)
      result += loc;
    exp >>= 1;
    loc++;
  }

CAL_END:
  LEAVE;
  return result;
}


static int
cal_fast_power(unsigned base, int exp)
{
  register struct buffered_power *iterator;
  unsigned result;
  ENTER("cal_fast_power");

  if(0 > exp)
    error_handle(ADD_TRACE(error_digest[1]));

  update_power_buffer(base, get_bit_length(exp));

  result = 1;
  iterator = pbuf;
  while(exp)
  {
    if(exp & RIGHT_MOST_BIT_MASK)
      result *= iterator->value;
    exp >>= 1;
    iterator++;
  }

  LEAVE;
  return result;
}


static void
update_power_buffer(unsigned base, int buf_size)
{
  ENTER("update_power_buffer");

  if(NULL == pbuf)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    initial_power_buffer(base);
  }

  if(buf_size > MAX_EXP_COUNT || base != pbuf->value)
  {
    buf_size = buf_size > MAX_EXP_COUNT? buf_size: MAX_EXP_COUNT;
    realloc_initial((void**)&pbuf, buf_size * sizeof(*pbuf));
    filling_power_buffer(base, buf_size);
  }

  LEAVE;
  return;
}


static void
initial_power_buffer(unsigned base)
{
  ENTER("initial_power_buffer");

  malloc_initial((void**)&pbuf, MAX_EXP_COUNT * sizeof(*pbuf));
  filling_power_buffer(base, MAX_EXP_COUNT);

  LEAVE;
  return;
}


static void
filling_power_buffer(unsigned base, int buf_size)
{
  register struct buffered_power *iterator;
  register struct buffered_power *last;
  ENTER("filling_power_buffer");

  /*- Initialize the first entry of struct buffered_power.                   -*/
  iterator = pbuf;
  iterator->dimension = 1;
  iterator->value = base;

  last = iterator++;;
  while(iterator < pbuf + buf_size)
  {
    iterator->dimension = last->dimension << 1;
    iterator->value = last->value * last->value;
    last = iterator++;;
  }

  LEAVE;
  return;
}


static void
print_power_title(FILE *fd)
{
  ENTER("print_power_title");

  fprintf(fd, "FAST POWER CALULATION: O[log(N)]\n");
  fprintf(fd, "INDEX   BASE   EXPONENT       RESULT  MULT(cnt)"
    " TIME(usec)  ASTRINGEND\n");

  LEAVE;
  return;
}


static void
print_power_report(FILE *fd, unsigned base, int exponent,
  struct fast_power_report *report)
{
  static int index = 0;
  ENTER("print_power_report");

  report->astringent = (double)report->usec / (log(exponent) * FPOWER_REPEATS);
  fprintf(fd, " %4d %6u %10d %12u   %8d  %9d   %9.4f\n",
    (index++) >> 1, base, exponent, report->result,
    report->mult_counts, report->usec, report->astringent);

  LEAVE;
  return;
}
