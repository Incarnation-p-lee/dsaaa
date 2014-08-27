/*----------------------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                                            -*/
/*-DATE:        02262014                                                     -*/
/*-WHAT:        Homework chapter 1.1                                         -*/
/*-REVISION:                                                                 -*/
/*- DATE -------------------- DESCRIPTION ------------------------------------*/
/*- 02262014    Single linked list API for others.                           -*/
/*----------------------------------------------------------------------------*/
struct single_linked_list *
generate_slinked_list(int *values, int size)
{
  struct single_linked_list *head;
  struct single_linked_list *node;
  register int *iterator;
  ENTER("generate_slinked_list");

  if(NULL == values)
    error_handle(ADD_TRACE(error_digest[0]));

  if(size <= 0)
    error_handle(ADD_TRACE(error_digest[1]));

  iterator = values;
  malloc_initial((void**)&node, sizeof(*node));
  node->index = *iterator++;
  node->next = NULL;
  head = node;

  while(iterator < values + size)
  {
    append_slinked_list_node(node, *iterator++);
    node = node->next;
  }

  LEAVE;
  return head;
}


struct single_linked_list *
initial_slinked_list(void)
{
  struct single_linked_list *head;
  ENTER("initial_slinked_list");

  malloc_initial((void**)&head, sizeof(*head));
  head->index = 0;
  head->next = NULL;

  LEAVE;
  return head;
}


struct single_linked_list *
append_slinked_list_node(struct single_linked_list *node, int value)
{
  struct single_linked_list *next;
  ENTER("append_slinked_list_node");

  if(NULL == node)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_APPEND;
  }

  malloc_initial((void**)&next, sizeof(*next));
  next->index = value;
  next->next = NULL;

  if(NULL != node->next)
    next->next = node->next;
  node->next = next;

END_OF_APPEND:
  LEAVE;
  return next;
}


void
delete_slinked_list_node(struct single_linked_list **head,
                         struct single_linked_list *node)
{
  struct single_linked_list *cur;
  ENTER("delete_slinked_list_node");

  if(NULL == node || NULL == head || NULL == *head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_DELETE;
  }

  cur = *head;
  if(cur == node)
  {
    *head = node->next;
  }
  else
  {
    while(node != cur->next)
      cur = cur->next;
  }

  saft_free((void**)&node);

END_OF_DELETE:
  LEAVE;
  return;
}


struct single_linked_list *
next_slinked_list(struct single_linked_list *cur)
{
  struct single_linked_list *result;
  ENTER("next_slinked_list");

  result = NULL;
  if(cur)
    result = cur->next;

  LEAVE;
  return result;
}


void
destroy_slinked_list(struct single_linked_list **head)
{
  struct single_linked_list *cur;
  struct single_linked_list **iter;
  ENTER("destroy_slinked_list");

  if(NULL == head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_CLEAR;
  }

  iter = head;
  while(NULL != (cur = *iter))
  {
    iter = &cur->next;
    saft_free((void**)&cur);
  }

  *head = NULL;

END_OF_CLEAR:
  LEAVE;
  return;
}


int
lengthof_slinked_list(struct single_linked_list *head)
{
  int length;
  ENTER("lengthof_slinked_list");

  length = 0;
  if(NULL == head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_LENGTHOF;
  }

  while(NULL != head)
  {
    length++;
    head = head->next;
  }

END_OF_LENGTHOF:
  LEAVE;
  return length;
}


struct single_linked_list *
accessby_index_slinked_list(struct single_linked_list *head, int index)
{
  struct single_linked_list *node;
  ENTER("accessby_index_slinked_list");

  node = head;
  if(NULL == head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_ACCESS;
  }
  if(0 > index || index > lengthof_slinked_list(head))
  {
    warning_prompt(ADD_TRACE(warning_digest[1]));
    goto END_OF_ACCESS;
  }

  while(index > 0)
  {
    node = node->next;
    index--;
  }

END_OF_ACCESS:
  LEAVE;
  return node;
}


void
serialize_slinked_list(struct single_linked_list *head)
{
  struct single_linked_list *node;
  int index;
  ENTER("serialize_slinked_list");

  if(NULL == head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_SERIAL;
  }

  index = 0;
  node = head;
  while(node)
  {
    node->index = index++;
    node = node->next;
  }

END_OF_SERIAL:
  LEAVE;
  return;
}

void
print_slinked_list(FILE *fd, char *msg, struct single_linked_list *head)
{
  int align;
  register struct single_linked_list *iterator;
  char *default_msg = "Default single linked list";
  ENTER("print_slinked_list");

  if(NULL == msg)
    msg = default_msg;

  align = 0;
  iterator = head;
  fprintf(fd, "[%s]:\n", msg);
  while(NULL != iterator)
  {
    fprintf(fd, "%d-> ", iterator->index);
    if(!(++align % PRINT_WIDTH))
      fprintf(fd, "\n");
    iterator = iterator->next;
  }
  fprintf(fd, "NULL\n");

  LEAVE;
  return;
}


void
exchange_slinked_list(struct single_linked_list **head,
  struct single_linked_list *node)
{
  struct single_linked_list *cur;
  struct single_linked_list *pre;
  ENTER("exchange_slinked_list");

  if(NULL == head || NULL == *head || NULL == node)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_EXCHANGE;
  }
  if(*head == node)
  {
    warning_prompt(ADD_TRACE(warning_digest[2]));
    goto END_OF_EXCHANGE;
  }

  pre = *head;
  while((cur = *head))
  {
    if(cur->next == node)
      break;
    pre = cur;
    head = &cur->next;
  }

  if(cur)
  {
    pre->next = node;
    cur->next = node->next;
    node->next = cur;
  }
  else
    warning_prompt(ADD_TRACE(warning_digest[3]));

END_OF_EXCHANGE:
  LEAVE;
  return;
}
