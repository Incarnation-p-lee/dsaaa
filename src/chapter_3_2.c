/*----------------------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                                             */
/*-DATE:        02252014                                                      */
/*-WHAT:        Homework chapter 3-2                                          */
/*-REVISION:                                                                  */
/*- DATE ------------------------ DESCRIPTION --------------------------------*/
/*- 02252014    CHAPTER 3-2                                                  -*/
/*----------------------------------------------------------------------------*/
void
chapt_3_2(void)
{
  ENTER("chapt_3_2");

  print_report_header(stdout, "Print Lots of Linked List", 3, 2);
  print_report_header(dsaaa_report, "Print Lots of Linked List", 3, 2);

  dochapt_3_2();

  LEAVE;
  return;
}


static void
dochapt_3_2(void)
{
  int cnt;
  int *index;
  int *iterator;
  int value[LOTS_LIST_LEN];
  struct lots_report report;
  struct single_linked_list *ind_list;
  struct single_linked_list *val_list;
  /*--------------------------------------------------------------------------*/
  /*- This cases array specific the length of different index single linked  -*/
  /*- list, for evaluating the time cost of print lots.                      -*/
  /*--------------------------------------------------------------------------*/
  int cases[] = {
    1, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600,
    700, 800, 900, 1000,
  };
  ENTER("dochapt_3_2");

  report.val_len = LOTS_LIST_LEN;

  srand(LOTS_RANDOM_SEED);
  init_maxed_array(value, LOTS_LIST_LEN, LOTS_RANDOM_MAX);
  val_list = generate_linked_list(value, LOTS_LIST_LEN);

  print_single_linked_list(stdout, "Val_List", val_list);
  print_single_linked_list(dsaaa_report, "Val_List", val_list);
  print_lots_title(stdout);
  print_lots_title(dsaaa_report);

  iterator = cases;
  index = NULL;
  while(iterator < cases + sizeof(cases) / sizeof(cases[0]))
  {
    cnt = TEST_LOTS_CNT;
    report.ind_len = *iterator;
    malloc_initial((void**)&index, sizeof(*index) * (*iterator));
    init_maxed_array(index, *iterator, lengthof_linked_list(val_list));
    ind_list = generate_linked_list(index, *iterator++);

    TIME_START;
    PRINT_LOTS_PERFORMANCE(cnt, print_lots, val_list, ind_list);
    TIME_END(&report.usec);

    print_lots_report(stdout, &report);
    print_lots_report(dsaaa_report, &report);
    clear_linked_list(&ind_list);
    saft_free((void**)&index);
  }

  clear_linked_list(&val_list);
  LEAVE;
  return;
}


static void
init_maxed_array(int *value, int size, int max)
{
  register int *iterator;
  ENTER("init_lots_value");

  if(NULL == value)
    error_handle("Null pointer detected when initilizing");

  srand(LOTS_RANDOM_SEED);
  iterator = value;
  while(iterator < value + size)
    *iterator++ = rand() % max;

  LEAVE;
  return;
}


static void
print_lots(struct single_linked_list *data, struct single_linked_list *index)
{
  register struct single_linked_list *node;
  ENTER("print_lots");

  if(NULL == data || NULL == index)
  {
    warn_prompt("Null linked list head pointer detected");
    goto END_OF_PRINT_LOTS;
  }

  node = index;
  while(NULL != node)
  {
    accessby_index_linked_list(data, node->value);
    /*- fprintf(stdout, "%d->", rt_node->value);                            -*/
    node = node->next;
  }

END_OF_PRINT_LOTS:
  LEAVE;
  return;
}


static void
print_lots_title(FILE *fd)
{
  ENTER("print_lots_title");

  fprintf(fd, "Print Lots of Linked List: O[N + M]\n");
  fprintf(fd, "INDEX  VAL(LENGTH)  IND(LENGTH)   TIME(usec)  ASTRINGEND\n");

  LEAVE;
  return;
}


static void
print_lots_report(FILE *fd, struct lots_report *report)
{
  static int index = 0;
  ENTER("print_lots_report");

  fprintf(fd, "%5d    %8d     %8d     %8d    %9.4f\n", index++ >> 1,
     report->val_len, report->ind_len, report->usec,
    (double)report->usec / (report->val_len + report->ind_len));

  LEAVE;
  return;
}
