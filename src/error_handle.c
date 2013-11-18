/*--------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                               */
/*-DATE:        08122013                                        */
/*-WHAT:        Error handling                                  */
/*-REVISION:                                                    */
/*- DATE ------------------------ DESCRIPTION ------------------*/
/*- 08122013    Generate error handle module                   -*/
/*--------------------------------------------------------------*/
void
error_handle(const char *message)
{
  char *unknown = "Unknown location.";
  ENTER("error_handle");

  if(NULL == message)
    message = unknown;

  fprintf(stdout, "break at %s. ", message);
  fprintf(stdout, "%02d =>%s\n", errno, strerror(errno));
  print_stack_traces();

  LEAVE();
  exit(1);
}
