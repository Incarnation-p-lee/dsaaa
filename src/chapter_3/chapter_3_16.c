void
chapt_3_16(void)
{
  ENTER("chapt_3_16");

  print_report_header(stdout, "Remove Redundant Linked List", 3, 16);
  print_report_header(dsaaa_report, "Remove Redundant Linked List", 3, 16);

  print_title_redundant_list_report();

  dochapt_3_16();

  LEAVE;
  return;
}

static inline void
init_redundant_list_report(struct redundant_list_report *report, int size)
{
  ENTER("init_redundant_list_report");

  if(report && size > 0)
  {
    report->size = size;
    report->astringend = size * size;
    report->redundant_rate = (float)size / REDUNDANT_RAW_DATA_MAX;
  }

  LEAVE;
  return;
}

static void
print_title_redundant_list_report(void)
{
  ENTER("print_title_redundant_list_report");

  fprintf(stdout, "INDEX   SIZE   RATE   TIME(usec)   ASTRINGEND\n");
  fprintf(dsaaa_report, "INDEX   SIZE   RATE   TIME(usec)   ASTRINGEND\n");

  LEAVE;
  return;
}

static void
print_redundant_list_report(struct redundant_list_report *report)
{
  static unsigned index = 0;
  ENTER("print_redundant_list_report");

  fprintf(stdout, "%5d %6d  %5.1f     %8d   %10.5f\n", index++ >> 1,
    report->size, report->redundant_rate, report->usec,
    (double)report->usec / report->astringend);
  fprintf(dsaaa_report, "%5d %6d  %5.1f     %8d   %10.5f\n",
    index++ >> 1, report->size, report->redundant_rate, report->usec,
    (double)report->usec / report->astringend);

  LEAVE;
  return;
}

static void
dochapt_3_16(void)
{
  int entries[] = {
    100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000,
    4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000, 40000,
    50000, 60000, 70000, 80000, 90000,
  };
  unsigned *data;
  int *item;
  struct redundant_list *head;
  struct redundant_list_report report;
  ENTER("dochapt_3_16");

  item = entries;
  while(item < entries + sizeof(entries) / sizeof(entries[0]))
  {
    init_redundant_list_report(&report, *item);

    data = create_raw_random_data(*item);
    head = create_redundant_linked_list(data, *item++);

    TIME_START;
    remove_redundant_linked_list(head);
    TIME_END(&report.usec);
    print_redundant_list_report(&report);

    destroy_raw_random_data(&data);
    destroy_redundant_linked_list(&head);
  }

  LEAVE;
  return;
}

static void
remove_redundant_linked_list(struct redundant_list *head)
{
  register struct redundant_list *item;
  struct redundant_list *start;
  ENTER("remove_redundant_linked_list");

  if(head)
  {
    start = head;
    while(next_redundant_linked_list(start) != head)
    {
      item = next_redundant_linked_list(start);
      while(item != head)
      {
        if(start->num == item->num)
        {
          item = remove_node_redundant_linked_list(item);
        }
        else
          item = next_redundant_linked_list(item);
      }
      start = next_redundant_linked_list(start);
    }
  }

  LEAVE;
  return;
}

static unsigned *
create_raw_random_data(int size)
{
  unsigned *item;
  unsigned *data;
  ENTER("create_raw_random_data");

  if(size > 0)
  {
    malloc_initial((void**)&data, sizeof(*data) * size);
    item = data;
    while(item < data + size)
      *item++ = (unsigned)rand() % REDUNDANT_RAW_DATA_MAX;
  }

  LEAVE;
  return data;
}

static inline void
destroy_raw_random_data(unsigned **raw)
{
  ENTER("destroy_raw_random_data");

  if(raw && *raw)
  {
    saft_free((void**)raw);
  }

  LEAVE;
  return;
}

static struct redundant_list *
create_redundant_linked_list(unsigned *rdm, int size)
{
  struct redundant_list *head;
  struct redundant_list *node;
  struct redundant_list *cur;
  unsigned *item;
  ENTER("create_redundant_linked_list");

  if(rdm && size > 0)
  {
    node = NULL;
    item = rdm;
    malloc_initial((void**)&head, sizeof(*head));
    initial_dlinked_list_node(&head->dll);

    head->num = *item++;
    cur = head;
    while(item < rdm + size)
    {
      malloc_initial((void**)&node, sizeof(*head));
      node->num = *item++;
      insert_after_dlinked_list(&cur->dll, &node->dll);
      cur = next_redundant_linked_list(node);
    }
  }

  LEAVE;
  return head;
}

static void
destroy_redundant_linked_list(struct redundant_list **head)
{
  struct redundant_list *item;
  struct redundant_list *node;
  struct redundant_list **next;

  ENTER("destroy_redundant_linked_list");

  if(*head && head)
  {
    node = item = *head;
    next = head;
    while(NULL != (item = *next))
    {
      node = remove_node_redundant_linked_list(item);
      next = &node;
    }
  }

  LEAVE;
  return;
}

static struct redundant_list *
next_redundant_linked_list(struct redundant_list *node)
{
  struct redundant_list *next;
  ENTER("next_redundant_linked_list");

  next = NULL;
  if(node)
    next = CONSTRAINT_OF(node->dll.next, struct redundant_list, dll);

  LEAVE;
  return next;
}

/*
* As doubly linked list, remove operation will return next node by default.
*/
static struct redundant_list *
remove_node_redundant_linked_list(struct redundant_list *node)
{
  struct redundant_list *next;
  ENTER("remove_node_redundant_linked_list");

  next = NULL;
  if(node)
  {
    if(node != next_redundant_linked_list(node))
      next = next_redundant_linked_list(node);
    remove_node_dlinked_list(&node->dll);
    saft_free((void**)&node);
  }

  LEAVE;
  return next;
}
