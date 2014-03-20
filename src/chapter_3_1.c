/*----------------------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                                             */
/*-DATE:        01202014                                                      */
/*-WHAT:        Homework chapter 3-1                                          */
/*-REVISION:                                                                  */
/*- DATE ------------------------ DESCRIPTION --------------------------------*/
/*- 01202014    CHAPTER 3-1                                                  -*/
/*----------------------------------------------------------------------------*/
void
chapt_3_1(void)
{
  ENTER("chapt_3_1");

  print_report_header(stdout, "Traversal Single Linked List", 3, 1);
  print_report_header(dsaaa_report, "Traversal Single Linked List", 3, 1);

  print_traversal_title(stdout);
  print_traversal_title(dsaaa_report);

  dochapt_3_1();

  LEAVE;
  return;
}


static void
dochapt_3_1(void)
{
  register int *iterator;
  struct single_linked_list *head;
  struct traversal_report tr_report;
  int count;
  int values[NODE_SIZE];
  int node_size[] = {
    10, 20, 30, 40, 50, 60, 70, 80, 90, 100,
    200, 300, 400, 500, 600, 700, 800, 900, 1000,
  };
  ENTER("dochapt_3_1");

  init_node_value(values, NODE_SIZE);

  iterator = node_size;
  while(iterator < node_size + sizeof(node_size) / sizeof(*node_size))
  {
    count = TRAVERSAL_CNT;
    tr_report.dimension = *iterator;
    head = generate_slinked_list(values, *iterator++);

    TIME_START;
    tr_report.sum = TRAVERSAL_PERFORMANCE(count,
      traversal_single_linked_list, head);
    TIME_END(&tr_report.usec);

    clear_slinked_list(&head);
    print_traversal_report(stdout, &tr_report);
    print_traversal_report(dsaaa_report, &tr_report);
  }

  LEAVE;
  return;
}

static int
traversal_single_linked_list(struct single_linked_list *head)
{
  int sum;
  struct single_linked_list *iter;
  ENTER("traversal_single_linked_list");

  sum = 0;
  iter = head;
  while(NULL != iter)
  {
    sum += iter->index;
    iter = iter->next;
  }

  LEAVE;
  return sum;
}

static void
init_node_value(int *values, int size)
{
  register int i;
  ENTER("init_node_value");

  i = 0;
  while(i < size)
  {
    values[i] = i + 1;
    i++;
  }

  LEAVE;
  return;
}

static void
print_traversal_title(FILE *fd)
{
  ENTER("print_traversal_title");

  fprintf(fd, "Traversal Single Linked List: O[N]\n");
  fprintf(fd, "INDEX  DIMENSION       SUM  TIME(usec)  ASTRINGEND\n");

  LEAVE;
  return;
}

static void
print_traversal_report(FILE *fd, struct traversal_report *report)
{
  static int index = 0;
  ENTER("print_traversal_report");

  fprintf(fd, "%5d   %8d  %8d  %10u  %10.4f\n", index++ >> 1, report->dimension,
    report->sum, report->usec, (double)report->usec / report->dimension);

  LEAVE;
  return;
}

