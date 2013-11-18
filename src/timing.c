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
  ENTER("timing_start");
  gettimeofday(&ts_begin,NULL);

  LEAVE();
  return;
}

void
timing_end(unsigned *usec)
{
  ENTER("timing_end");
  gettimeofday(&ts_end,NULL);
  *usec = timing_cost();

  LEAVE();
  return;
}

static unsigned
timing_cost()
{
  unsigned usec;
  ENTER("timing_cost");

  usec = (ts_end.tv_sec - ts_begin.tv_sec) * 1000000;
  usec += (unsigned)(ts_end.tv_usec - ts_begin.tv_usec);

  LEAVE();
  return usec;
}
