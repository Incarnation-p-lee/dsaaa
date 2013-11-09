/*-------------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                                    */
/*-DATE:        08122013                                             */
/*-WHAT:        Time cost collection                                 */
/*-REVISION:                                                         */
/*- DATE ------------------------ DESCRIPTION -----------------------*/
/*- 08122013    TIMING MODE                                         -*/
/*-------------------------------------------------------------------*/
void
timing_start()
{
  gettimeofday(&timePoint_start,NULL);

  return;
}

void
timing_end(unsigned *usec)
{
  gettimeofday(&timePoint_end,NULL);
  *usec = timing_cost();

  return;
}

static unsigned
timing_cost()
{
  unsigned usec;

  usec = (timePoint_end.tv_sec - timePoint_start.tv_sec) * 1000000;
  usec += (unsigned)(timePoint_end.tv_usec - timePoint_start.tv_usec);

  return usec;
}
