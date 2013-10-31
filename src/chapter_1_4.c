/*--------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                               */
/*-DATE:        10272013                                        */
/*-WHAT:        Homework chapter 1.4                            */
/*-REVISION:                                                    */
/*- DATE ------------------------ DESCRIPTION ------------------*/
/*- 10272013    CHAPTER 1-4                                    -*/
/*--------------------------------------------------------------*/
void
chapt_1_4(void)
{
  report_header(stdout);
  report_header(hwork_rept);
}


static void
report_header(FILE *fd)
{
  fprintf(fd, "\n-----------------------------");
  fprintf(fd, "Chapter 1-4");
  fprintf(fd, "-------------------------------\n\n");
  fprintf(fd, 
    "                               Expanding #include\n\n");

}


static void
do_chapter(char *filename)
{
  FILE *fd = fopen(filename);

  if(NULL == fd)
    error_handle("fopen");
   
}
