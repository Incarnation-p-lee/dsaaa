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

  print_report_header(stdout, "Polynomial Add in Linked List", 3, 6);
  print_report_header(dsaaa_report, "Polynomial Add in Linked List", 3, 6);

  dochapt_3_6();

  LEAVE;
  return;
}


static void
dochapt_3_6(void)
{
  register int *miter;
  register int *niter;
  struct poly_linked *mpoly;
  struct poly_linked *npoly;
  struct poly_linked *spoly;
  struct poly_add_report pa_report;
  int count;
  float *coeff;
  int *pow;
  int mpoly_len[] = {
    100, 500, 1000,
  };
  int npoly_len[] = {
    100, 200, 300, 400, 500, 600, 700, 800, 900, 1000,
  };
  ENTER("dochapt_3_6");

  print_polynomial_title();

  coeff = prepare_flt_random();
  count = 0;
  pow = int_random;
  miter = mpoly_len;
  niter = npoly_len;
  while(miter < mpoly_len + sizeof(mpoly_len) / sizeof(*mpoly_len))
  {
    mpoly = generate_polynomial(coeff, pow, *miter);
    niter = npoly_len;
    while(niter < npoly_len + sizeof(npoly_len) / sizeof(*npoly_len))
    {
      count = POLY_ADD_COUNT;
      npoly = generate_polynomial(coeff, pow, *niter);
      print_polynomial_layout(mpoly);
      print_polynomial_layout(npoly);

      TIME_START;
      while(count--)
      {
        spoly = polynomial_add(mpoly, npoly);
        clear_polynomial(&spoly);
      }
      TIME_END(&pa_report.usec);
      pa_report.msize = *miter;
      pa_report.nsize = *niter++;

      clear_polynomial(&npoly);
      print_polynomial_report(&pa_report);
    }
    clear_polynomial(&mpoly);
    miter++;
  }
  clear_flt_random((void**)&coeff);

  LEAVE;
  return;
}


static float *
prepare_flt_random(void)
{
  float *flt_random;
  register float *fiter;
  register int *iiter;
  ENTER("prepare_flt_random");

  malloc_initial((void**)&flt_random, sizeof(*flt_random) * RANDOM_DATA_SIZE);
  fiter = flt_random;
  iiter = int_random;
  while(iiter < int_random + RANDOM_DATA_SIZE)
    *fiter++ = (float)(*iiter++) / FLT_ITER;

  LEAVE;
  return flt_random;
}


static void
clear_flt_random(void **mem)
{
  ENTER("clear_flt_random");

  if(NULL == mem || NULL == *mem)
    error_handle(ADD_TRACE(error_digest[0]));

  saft_free(mem);
  *mem = NULL;

  LEAVE;
  return;
}


static struct poly_linked *
generate_polynomial(float *coeff, int *pow, int size)
{
  struct poly_linked *poly_head;
  struct poly_linked *pnode;
  struct single_linked_list *lnode;
  register float *flt_iter;
  register int *int_iter;
  int index;
  ENTER("generate_polynomial");

  if(NULL == coeff || NULL == pow)
    error_handle(ADD_TRACE(warning_digest[0]));

  if(size <= 0)
    error_handle(ADD_TRACE(error_digest[1]));

  malloc_initial((void**)&poly_head, sizeof(*poly_head));

  flt_iter = coeff;
  int_iter = pow;
  index = 0;
  poly_head->coefficient = *flt_iter++;
  poly_head->pow = *int_iter++;
  poly_head->sll.index = index++;

  lnode = &poly_head->sll;
  while(flt_iter < coeff + size)
  {
    malloc_initial((void**)&pnode, sizeof(*pnode));
    pnode->coefficient = *flt_iter++;
    pnode->pow = *int_iter++;
    pnode->sll.index = index++;
    lnode->next = &pnode->sll;
    lnode = lnode->next;
  }

  LEAVE;
  return poly_head;
}


static struct poly_linked *
polynomial_add(struct poly_linked *mpol, struct poly_linked *npol)
{
  struct poly_linked *sum_head;
  struct poly_linked *pnode;
  struct poly_linked *inode;
  struct single_linked_list *lnode;
  ENTER("polynomial_add");

  sum_head = NULL;
  if(NULL == mpol || NULL == npol)
  {
    sum_head = NULL == mpol ? npol : mpol;
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto POLY_ADD_END;
  }

  /*--------------------------------------------------------------------------*/
  /*- The initial head node is not use for store sume result. It just hold a -*/
  /*- node for iteratating start. This node will be delete after poly add.   -*/
  /*--------------------------------------------------------------------------*/
  malloc_initial((void**)&sum_head, sizeof(*sum_head));
  sum_head->coefficient = 0.0f;
  sum_head->pow = 0;

  lnode = &sum_head->sll;
  while(mpol && npol)
  {
    malloc_initial((void**)&pnode, sizeof(*pnode));
    lnode->next = &pnode->sll;
    lnode = lnode->next;
    if(npol->pow > mpol->pow)
    {
      pnode->coefficient = npol->coefficient;
      pnode->pow = npol->pow;
      npol = get_next_poly(&npol->sll);
    }
    else if(npol->pow < mpol->pow)
    {
      pnode->coefficient = mpol->coefficient;
      pnode->pow = mpol->pow;
      mpol = get_next_poly(&mpol->sll);
    }
    else
    {
      pnode->coefficient = npol->coefficient + mpol->coefficient;
      pnode->pow = npol->pow;
      mpol = get_next_poly(&mpol->sll);
      npol = get_next_poly(&npol->sll);
    }
  }

  inode = mpol == NULL ? npol : mpol;
  while(inode)
  {
    malloc_initial((void**)&pnode, sizeof(*pnode));
    lnode = &pnode->sll;
    lnode = lnode->next;
    pnode->pow = inode->pow;
    pnode->coefficient = inode->coefficient;
    inode = get_next_poly(&pnode->sll);
  }

  /*--------------------------------------------------------------------------*/
  /*- Delete the initial node, and reset the sum head pointer.               -*/
  /*--------------------------------------------------------------------------*/
  pnode = sum_head;
  sum_head = get_next_poly(&sum_head->sll);
  serialize_slinked_list(&sum_head->sll);
  saft_free((void**)&pnode);

POLY_ADD_END:
  LEAVE;
  return sum_head;
}


static void
clear_polynomial(struct poly_linked **head)
{
  struct poly_linked *pnode;
  struct single_linked_list *lnode;
  ENTER("clear_polynomial");

  if(NULL == head || NULL == *head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto CLEAR_POLY;
  }

  pnode = *head;
  while(pnode)
  {
    lnode = &pnode->sll;
    saft_free((void**)&pnode);
    pnode = get_next_poly(lnode);
  }

  *head = NULL;

CLEAR_POLY:
  LEAVE;
  return;
}


static struct poly_linked *
get_next_poly(struct single_linked_list *lnode)
{
  struct poly_linked *pnode;
  ENTER("get_next_poly");

  pnode = NULL;
  if(NULL == lnode)
  {
    warning_prompt(ADD_TRACE(warning_digest[4]));
    goto END_OF_GETNPY;
  }

  if(NULL != lnode->next)
    pnode = CONSTRAINT_OF(lnode->next, struct poly_linked, sll);

END_OF_GETNPY:
  LEAVE;
  return pnode;
}


static void
print_polynomial_layout(struct poly_linked *head)
{
  struct poly_linked *pnode;
  ENTER("print_polynomial_layout");
  if(NULL == head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto LAYOUT_POLY;
  }

  pnode = head;
  while(pnode)
  {
    /*- fprintf(stdout, "%+fx^%+d", pnode->coefficient,                      -*/
    /*-         pnode->pow);                                                 -*/
    /*- fprintf(dsaaa_report, "%+fx^%+d", pnode->coefficient,                -*/
    /*-         pnode->pow);                                                 -*/
    pnode = get_next_poly(&pnode->sll);
  }
  /*- fprintf(stdout, "\n");                                                 -*/
  /*- fprintf(dsaaa_report, "\n");                                           -*/

LAYOUT_POLY:
  LEAVE;
  return;
}


static void
print_polynomial_title(void)
{
  ENTER("print_polynomial_title");

  fprintf(stdout, "Polynomial Add in Linked List: O[M + N]\n");
  fprintf(stdout, "INDEX  DIMENSION[M]  DIMENSION[N]"
                  "  TIME(usec)  ASTRINGEND\n");
  fprintf(dsaaa_report, "Polynomial Add in Linked List: O[N]\n");
  fprintf(dsaaa_report, "INDEX  DIMENSION[M]  DIMENSION[N]"
                        "  TIME(usec)  ASTRINGEND\n");

  LEAVE;
  return;
}


static void
print_polynomial_report(struct poly_add_report *report)
{
  static int index = 0;
  ENTER("print_polynomial_report");

  fprintf(stdout, "%5d      %8d      %8d    %8d   %9.4f\n",
          index, report->msize, report->nsize, report->usec,
          (float)report->usec / (report->msize + report->nsize));
  fprintf(dsaaa_report, "%5d      %8d      %8d    %8d   %9.4f\n",
          index, report->msize, report->nsize, report->usec,
          (float)report->usec / (report->msize + report->nsize));
  index++;

  LEAVE;
  return;
}
