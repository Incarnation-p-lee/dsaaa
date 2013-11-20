/*--------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                               */
/*-DATE:        10312013                                        */
/*-WHAT:        Add call stack tracing module.                  */
/*-REVISION:                                                    */
/*- DATE ------------------------ DESCRIPTION ------------------*/
/*- 10312013    Tracing and print stack path.                  -*/
/*--------------------------------------------------------------*/
void
enter(const char *fuc_name)
{
  stack_traces[top_index++] = fuc_name;
  return;
}

void
leave(void)
{
  stack_traces[top_index--] = NULL;
  return;
}

void
print_stack_traces(void)
{
  const char **start_stack = stack_traces;
  const char *indent = 
    "                                               ";
  int count = 0;

  while(start_stack <= stack_traces + top_index)
  {
    if(NULL != *start_stack)
    {
      fprintf(stdout, "%.*s => [%d]%s\n", count, indent,
        count, *start_stack);
    }
    start_stack++;
    count++;
  }
  return;
}
