/*----------------------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                                            -*/
/*-DATE:        08122013                                                     -*/
/*-WHAT:        Error handling                                               -*/
/*-REVISION:                                                                 -*/
/*- DATE ------------------------ DESCRIPTION --------------------------------*/
/*- 08122013    Generate error handle module                                 -*/
/*----------------------------------------------------------------------------*/
void
error_handle(const char *message)
{
  char *unknown = "Unknown location.";
  ENTER("error_handle");

  if(NULL == message)
    message = unknown;

  fprintf(stdout, "=ERROR=: breaked at line %s. ", message);
  fprintf(stdout, "%02d =>%s\n", errno, strerror(errno));
  print_stack_traces();

  LEAVE;
  exit(1);
}

void
warning_prompt(char *message)
{
  char *unknown = "Unknown location.";
  ENTER("warn_handle");

  if(NULL == message)
    message = unknown;

  fprintf(stdout, "=WARNING=: detected at line %s. ", message);
  fprintf(dsaaa_report, "=WARNING=: detected at line %s. ", message);
  print_stack_traces();

  if(message == strinfo_buf)
    memset(message, 0, strlen(message));

  LEAVE;
  return;
}

