/*-------------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                                    */
/*-DATE:        08042013                                             */
/*-WHAT:        Homework of DSAAA                                    */
/*-REVISION:                                                         */
/*- DATE ------------------------ DESCRIPTION -----------------------*/
/*- 08042013    CHAPTER 1. Initilize the program.                   -*/
/*-------------------------------------------------------------------*/
#include "include.h"
#include "defs.h"
#include "vars.h"
#include "externals.h"

int
main(int argc, char **argv)
{
  filepointer_init();
  chapt_1_1();
  filepointer_close();

  return EXIT_SUCCESS;
}
