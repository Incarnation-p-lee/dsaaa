/*-------------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                                    */
/*-DATE:        08132013                                             */
/*-WHAT:        Homework chapter 1.1                                 */
/*-REVISION:                                                         */
/*- DATE ------------------------ DESCRIPTION -----------------------*/
/*- 08132013    Generate Function for external invoke               -*/
/*-------------------------------------------------------------------*/
void
exchange(int *a, int *b)
{
  assert(NULL != a && NULL != b);

  if(*a == *b)
    return;

  *a = *a^*b;
  *b = *a^*b;
  *a = *b^*a;
  return;
}

void
filepointer_init()
{
  char *rept_fname = "./homework.rept";
  hwork_rept = fopen(rept_fname, "w+");
  if(NULL == hwork_rept)
    error_handle("fopen");

  return;
}

void
filepointer_close()
{
  fclose(hwork_rept);

  return;
}

