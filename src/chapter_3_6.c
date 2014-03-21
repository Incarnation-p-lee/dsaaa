/*----------------------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                                             */
/*-DATE:        03192014                                                      */
/*-WHAT:        Homework chapter 3-6                                          */
/*-REVISION:                                                                  */
/*- DATE ------------------------ DESCRIPTION --------------------------------*/
/*- 03192014    CHAPTER 3-6                                                  -*/
/*----------------------------------------------------------------------------*/
void
chapt_3_6(void)
{
  ENTER("chapt_3_6");

  print_report_header(stdout, "Polynomial Add in Linked List", 3, 3);
  print_report_header(dsaaa_report, "Polynomial Add in Linked List", 3, 3);

  dochapt_3_2();

  LEAVE;
  return;
}


static void
dochapt_3_3(void)
{
  int mpoly_len[] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    100, 200, 300, 400, 500, 600, 700, 800, 900, 1000,
  };
  int npoly_len[] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    100, 200, 300, 400, 500, 600, 700, 800, 900, 1000,
  };
  ENTER("dochapt_3_3");

  
  LEAVE;
  return;
}

static struct poly_linked*
polynomial_add(struct poly_linked *mpol, struct poly_linked *npol)
{
  struct poly_linked *sum_head;
  struct single_linked_list *link_head;
  ENTER("polynomial_add");

  sum_head = NULL;
  if(NULL == mpol || NULL == npol)
  {
    sum_head = NULL == mpol? npol: mpol;
    warn_prompt("Null linked list head pointer detected");
    goto POLY_ADD_END;
  }

  link_head = initial_slinked_list();
  malloc_initial((void**)&sum_head, sizeof(*sum_head));

POLY_ADD_END:
  LEAVE;
  return sum_head;
}
