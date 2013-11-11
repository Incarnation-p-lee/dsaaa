/*--------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                               */
/*-DATE:        08042013                                        */
/*-WHAT:        Homework of DSAAA                               */
/*-REVISION:                                                    */
/*- DATE ------------------------ DESCRIPTION ------------------*/
/*- 08042013    CHAPTER 1. Initilize the program.              -*/
/*- 10242013    CHAPTER 1. Add function pointer.               -*/
/*-                        Start chapter1.2                    -*/
/*--------------------------------------------------------------*/
#include "include.h"
#include "defs.h"
#include "vars.h"
#include "externals.h"

int
main(int argc, char **argv)
{
  register HOMEWORK *hw_entry = homework;

  enter("main");
  filepointer_init();

  while(hw_entry < homework + sizeof(homework) / sizeof(HOMEWORK))
    (*hw_entry++)();

  filepointer_close();
  leave();

  return EXIT_SUCCESS;
}
