/*----------------------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                                            -*/
/*-DATE:        03192014                                                     -*/
/*-WHAT:        Ensure data structure works as expected.                     -*/
/*-REVISION:                                                                 -*/
/*- DATE -------------------- DESCRIPTION ------------------------------------*/
/*- 03192014    Ensure data structure works as expected.                     -*/
/*----------------------------------------------------------------------------*/
void
data_structure_verify(void)
{
  void (**iter)(void);
  const char **info;
  ENTER("data_structure_verify");

  fprintf(stdout, "\n         BUILD-IN DATA STRUCTURE SELF CHECKING\n\n");
  fprintf(dsaaa_report, "\n         BUILD-IN DATA STRUCTURE SELF CHECKING\n\n");

  iter = structure_set;
  info = ds_info;
  while(iter < structure_set + STRUCTSET_DIM)
  {
    fprintf(stdout, ">>>>>> %s\n\n", *info);
    fprintf(dsaaa_report, ">>>>>> %s\n\n", *info++);
    (*(*iter++))();
  }

  LEAVE;
  return;
}


static void
single_linked_list_verify(void)
{
  struct single_linked_list *head;
  struct single_linked_list *node;
  int length;
  int iter;
  ENTER("single_linked_list_verify");

  print_operation(SYMBOL_TO_STRING(generate_slinked_list));
  /* head = generate_slinked_list(NULL, RAW_DATA_SIZE);                       */
  /* head = generate_slinked_list((int*)raw_data, 0);                         */
  head = generate_slinked_list((int*)raw_data, RAW_DATA_SIZE);
  print_slist_result(head);
  print_done(SYMBOL_TO_STRING(generate_slinked_list));

  print_operation(SYMBOL_TO_STRING(lengthof_slinked_list));
  length = lengthof_slinked_list(NULL);
  length = lengthof_slinked_list(head);
  fprintf(stdout, "Length of linked list = %d.\n", length);
  fprintf(dsaaa_report, "Length of linked list = %d.\n", length);
  print_done(SYMBOL_TO_STRING(lengthof_slinked_list));

  print_operation(SYMBOL_TO_STRING(append_slinked_list_node));
  append_slinked_list_node(NULL, length);
  append_slinked_list_node(head, length);
  print_slist_result(head);
  print_done(SYMBOL_TO_STRING(append_slinked_list_node));

  node = head;
  while(node->next)
    node = node->next;

  print_operation(SYMBOL_TO_STRING(append_slinked_list_node));
  append_slinked_list_node(NULL, length);
  append_slinked_list_node(node, length);
  print_slist_result(head);
  print_done(SYMBOL_TO_STRING(append_slinked_list_node));

  length = lengthof_slinked_list(head);
  print_operation(SYMBOL_TO_STRING(accessby_index_slinked_list));
  iter = 0;
  while(iter < length)
  {
    if(0 == iter)
    {
      node = accessby_index_slinked_list(NULL, iter++);
      node = accessby_index_slinked_list(head, -1);
    }
    node = accessby_index_slinked_list(head, iter++);
    print_slist_node(node);
  }
  print_done(SYMBOL_TO_STRING(accessby_index_slinked_list));

  node = head;
  print_operation(SYMBOL_TO_STRING(exchange_slinked_list));
  exchange_slinked_list(NULL, node);
  exchange_slinked_list(&head, NULL);
  exchange_slinked_list(&head, node);
  while(node->next)
    node = node->next;
  exchange_slinked_list(&head, node);
  print_slist_result(head);
  print_done(SYMBOL_TO_STRING(exchange_slinked_list));

  print_operation(SYMBOL_TO_STRING(serialize_slinked_list));
  serialize_slinked_list(head);
  print_slist_result(head);
  print_done(SYMBOL_TO_STRING(serialize_slinked_list));

  print_operation(SYMBOL_TO_STRING(clear_slinked_list));
  clear_slinked_list(&head);
  if(NULL != head)
  {
    printf("AAA = %p", head);
    getchar();
  }
  print_slist_result(head);
  print_done(SYMBOL_TO_STRING(clear_slinked_list));

  LEAVE;
  return;
}


static void
doubly_linked_list_verify(void)
{
  struct doubly_linked_list *head;
  struct doubly_linked_list *node;
  int length;
  int iter;
  ENTER("doubly_linked_list_verify");

  /* head = generate_dlinked_list(NULL, RAW_DATA_SIZE);                       */
  /* head = generate_dlinked_list((int*)raw_data, 0);                         */
  print_operation(SYMBOL_TO_STRING(generate_dlinked_list));
  head = generate_dlinked_list((int*)raw_data, RAW_DATA_SIZE);
  print_dlist_result(head);

  node = head;
  while(node->next)
    node = node->next;
  print_dlist_result(node);
  print_done(SYMBOL_TO_STRING(generate_slinked_list));

  print_operation(SYMBOL_TO_STRING(lengthof_dlinked_list));
  length = lengthof_dlinked_list(NULL);
  length = lengthof_dlinked_list(head);
  fprintf(stdout, "Length of linked list = %d.\n", length);
  fprintf(dsaaa_report, "Length of linked list = %d.\n", length);
  print_done(SYMBOL_TO_STRING(lengthof_dlinked_list));

  print_operation(SYMBOL_TO_STRING(append_dlinked_list_node));
  append_dlinked_list_node(NULL, length);
  append_dlinked_list_node(head, length);
  print_dlist_result(head);
  print_done(SYMBOL_TO_STRING(append_dlinked_list_node));


  print_operation(SYMBOL_TO_STRING(append_slinked_list_node));
  append_dlinked_list_node(NULL, length);
  append_dlinked_list_node(node, length);
  print_dlist_result(head);
  print_done(SYMBOL_TO_STRING(append_slinked_list_node));

  length = lengthof_dlinked_list(head);
  print_operation(SYMBOL_TO_STRING(accessby_index_dlinked_list));
  iter = 0;
  while(iter < length)
  {
    if(0 == iter)
    {
      node = accessby_index_dlinked_list(NULL, iter++);
      node = accessby_index_dlinked_list(head, -1);
    }
    node = accessby_index_dlinked_list(head, iter++);
    print_dlist_node(node);
  }
  print_done(SYMBOL_TO_STRING(accessby_index_dlinked_list));

  node = head;
  print_operation(SYMBOL_TO_STRING(exchange_dlinked_list));
  exchange_dlinked_list(NULL, node);
  exchange_dlinked_list(&head, NULL);
  exchange_dlinked_list(&head, node);
  while(node->next)
    node = node->next;
  exchange_dlinked_list(&head, node);
  print_dlist_result(head);
  print_done(SYMBOL_TO_STRING(exchange_dlinked_list));

  print_operation(SYMBOL_TO_STRING(serialize_slinked_list));
  serialize_dlinked_list(head);
  print_dlist_result(head);
  print_done(SYMBOL_TO_STRING(serialize_slinked_list));

  print_operation(SYMBOL_TO_STRING(clear_dlinked_list));
  clear_dlinked_list(&head);
  print_dlist_result(head);
  print_done(SYMBOL_TO_STRING(clear_dlinked_list));

  LEAVE;
  return;
}


static void
print_operation(const char *msg)
{
  const char *op_msg = "Default Message, Operation Unknown";
  ENTER("print_operation");

  if(NULL != msg)
    op_msg = msg;

  fprintf(stdout,"Operating on %30s ...\n", op_msg);
  fprintf(dsaaa_report,"Operating on %30s ...\n", op_msg);

  LEAVE;
  return;
}


static void
print_done(const char *msg)
{
  const char *op_msg = "Default Message, Operation Unknown";
  ENTER("print_done");

  if(NULL != msg)
    op_msg = msg;

  fprintf(stdout,"[DONE] <== %s\n\n", op_msg);
  fprintf(dsaaa_report,"[DONE] <== %s\n\n", op_msg);

  LEAVE;
  return;
}


static void
print_slist_result(struct single_linked_list *head)
{
  ENTER("print_slist_result");

  print_slinked_list(stdout, NULL, head);
  print_slinked_list(dsaaa_report, NULL, head);

  LEAVE;
  return;
}


static void
print_dlist_result(struct doubly_linked_list *head)
{
  ENTER("print_dlist_result");

  if(NULL != head)
  {
    if(NULL == head->next)
    {
      print_reverse_dlinked_list(stdout, NULL, head);
      print_reverse_dlinked_list(dsaaa_report, NULL, head);
    }
  }

  print_dlinked_list(stdout, NULL, head);
  print_dlinked_list(dsaaa_report, NULL, head);

  LEAVE;
  return;
}


static void
print_slist_node(struct single_linked_list *node)
{
  ENTER("print_slist_node");

  fprintf(stdout,"%08d\n", node->index);
  fprintf(dsaaa_report,"%08d\n", node->index);

  LEAVE;
  return;
}


static void
print_dlist_node(struct doubly_linked_list *node)
{
  ENTER("print_dlist_node");

  fprintf(stdout,"%08d\n", node->index);
  fprintf(dsaaa_report,"%08d\n", node->index);

  LEAVE;
  return;
}
