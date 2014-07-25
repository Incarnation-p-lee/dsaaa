/*----------------------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                                             */
/*-DATE:        07102014                                                      */
/*-WHAT:        Homework chapter 3-10                                         */
/*-REVISION:                                                                  */
/*- DATE ------------------------ DESCRIPTION --------------------------------*/
/*- 07102014    CHAPTER 3-10                                                 -*/
/*----------------------------------------------------------------------------*/
void
chapt_3_10(void)
{
  ENTER("chapt_3_10");

  print_report_header(stdout, "Josephus Game in Linked List", 3, 10);
  print_report_header(dsaaa_report, "Josephus Game in Linked List", 3, 10);
  print_josephus_game_title();

  dochapt_3_10();

  LEAVE;
  return;
}

static void
dochapt_3_10(void)
{
  struct josephus_game_serial *head;
  struct josephus_game_report report;
  unsigned *sl, *sc;
  unsigned serial_len[] = {
    1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000,
  };
  unsigned serial_count[] = {
    10, 200, 900, 1000, 5000, 11000, 29000,
  };
  ENTER("dochapt_3_10");

  sc = serial_count;
  while(sc < serial_count + sizeof(serial_count) / sizeof(serial_count[0]))
  {
    sl = serial_len;
    while(sl < serial_len + sizeof(serial_len) / sizeof(serial_len[0]))
    {
      report.count = *sc;
      report.len = *sl;
      report.astringend = report.count * report.len;
      create_serial_loop_link_list(&head, *sl);
      TIME_START;
      start_josephus_game(&head, *sc);
      destroy_josephus_game_serial_node(&head, head);
      TIME_END(&report.usec);
      print_josephus_game_report(&report);
      sl++;
    }
    sc++;
  }

  LEAVE;
  return;
}

static void
start_josephus_game(struct josephus_game_serial **node, unsigned count)
{
  register struct josephus_game_serial *stop;
  ENTER("start_josephus_game");

  while((*node)->sll.next != &(*node)->sll)
  {
    stop = deliver_josephus_game_hot_potato(*node, count);
    destroy_josephus_game_serial_node(node, stop);
  }

  LEAVE;
  return;
}

static void
create_serial_loop_link_list(struct josephus_game_serial **head, int len)
{
  int num;
  struct josephus_game_serial *cur;
  struct josephus_game_serial *pre;
  ENTER("create_serial_loop_link_list");

  if(NULL == head)
    error_handle(ADD_TRACE(error_digest[0]));

  if(0 >= len)
    error_handle(ADD_TRACE(error_digest[1]));

  num = 0;
  malloc_initial((void**)head, sizeof(**head));
  (*head)->serial_num = ++num;
  pre = *head;
  while(num < len)
  {
    malloc_initial((void**)&cur, sizeof(*cur));
    cur->serial_num = ++num;
    pre->sll.next = &cur->sll;
    pre = cur;
  }

  cur->sll.next = &(*head)->sll;

  LEAVE;
  return;
}

static void
print_josephus_game_title(void)
{
  ENTER("print_josephus_game_title");

  fprintf(stdout, "INDEX      MCOUNT     NLEN     TIME(usec)     ASTRINGEND\n");
  fprintf(dsaaa_report,
    "INDEX      MCOUNT     NLEN     TIME(usec)     ASTRINGEND\n");

  LEAVE;
  return;
}

static void
print_josephus_game_report(struct josephus_game_report *report)
{
  static unsigned index = 0;
  ENTER("print_josephus_game_report");

  fprintf(stdout, "%5d      %6d   %6d      %8d      %10.5f\n",
    index++ >> 1, report->count, report->len, report->usec,
    (double)report->usec / report->astringend);
  fprintf(dsaaa_report, "%5d      %6d   %6d      %8d      %10.5f\n",
    index++ >> 1, report->count, report->len, report->usec,
    (double)report->usec / report->astringend);

  LEAVE;
  return;
}

static struct josephus_game_serial *
next_josephus_game_serial(struct josephus_game_serial *cur)
{
  struct josephus_game_serial *next;
  ENTER("next_josephus_game_serial");

  next = CONSTRAINT_OF(cur->sll.next, struct josephus_game_serial, sll);

  LEAVE;
  return next;
}

static void
destroy_josephus_game_serial_node(struct josephus_game_serial **start,
                                  struct josephus_game_serial *node)
{
  register struct josephus_game_serial *next;
  ENTER("destroy_josephus_game_serial_node");

  if(NULL == node || NULL == start)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_DESTROY;
  }

  next = next_josephus_game_serial(*start);
  while(node != next)
  {
    *start = next;
    next = next_josephus_game_serial(*start);
  }

  (*start)->sll.next = node->sll.next;
  saft_free((void**)&node);
  *start = next_josephus_game_serial(*start);

END_OF_DESTROY:
  LEAVE;
  return;
}

static struct josephus_game_serial *
deliver_josephus_game_hot_potato(struct josephus_game_serial *node, int count)
{
  ENTER("deliver_josephus_game_hot_potato");

  if(0 > count)
    error_handle(ADD_TRACE(error_digest[1]));

  if(NULL == node)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_DELIVER;
  }

  while(count)
  {
    node = next_josephus_game_serial(node);
    count--;
  }

END_OF_DELIVER:
  LEAVE;
  return node;
}
