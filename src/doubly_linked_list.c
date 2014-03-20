/*----------------------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                                            -*/
/*-DATE:        02262014                                                     -*/
/*-WHAT:        Doubly linked list API for other modules.                    -*/
/*-REVISION:                                                                 -*/
/*- DATE -------------------- DESCRIPTION ------------------------------------*/
/*- 03052014    Doubly linked list API for others.                           -*/
/*----------------------------------------------------------------------------*/
struct doubly_linked_list *
generate_dlinked_list(int *val, int size)
{
  struct doubly_linked_list *head;
  struct doubly_linked_list *node;
  register int *iterator;
  ENTER("generate_dlinked_list");

  if(NULL == val)
    error_handle(ADD_TRACE(error_digest[0]));

  if(size <= 0)
    error_handle(ADD_TRACE(error_digest[1]));

  iterator = val;
  malloc_initial((void**)&node, sizeof(*node));
  node->index = *iterator++;
  node->previous = node->next = NULL;
  head = node;

  while(iterator < val + size)
  {
    append_dlinked_list_node(node, *iterator++);
    node = node->next;
  }

  LEAVE;
  return head;
}


void
append_dlinked_list_node(struct doubly_linked_list *node, int value)
{
  struct doubly_linked_list *next;
  ENTER("append_dlinked_list_node");

  if(NULL == node)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_APPEND;
  }

  malloc_initial((void**)&next, sizeof(*next));
  next->index = value;
  next->previous = NULL;
  next->next = NULL;

  if(NULL != node->next)
  {
    next->next = node->next;
    node->next->previous = next;
  }
  node->next = next;
  next->previous = node;

END_OF_APPEND:
  LEAVE;
  return;
}


void
clear_dlinked_list(struct doubly_linked_list **head)
{
  struct doubly_linked_list *cur;
  struct doubly_linked_list **iter;
  ENTER("clear_dlinked_list");

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
lengthof_dlinked_list(struct doubly_linked_list *head)
{
  int length;
  ENTER("lengthof_dlinked_list");

  if(NULL == head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    length = -1;
    goto END_OF_LENGTHOF;
  }

  length = 0;
  while(NULL != head)
  {
    length++;
    head = head->next;
  }

END_OF_LENGTHOF:
  LEAVE;
  return length;
}


struct doubly_linked_list *
accessby_index_dlinked_list(struct doubly_linked_list *head, int index)
{
  struct doubly_linked_list *node;
  ENTER("accessby_index_slinked_list");

  node = head;
  if(NULL == head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_ACCESS;
  }
  if(0 > index)
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
print_dlinked_list(FILE *fd, char *msg, struct doubly_linked_list *head)
{
  int align;
  register struct doubly_linked_list *iterator;
  char *default_msg = "Default doubly linked list";
  ENTER("print_dlinked_list");

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
print_reverse_dlinked_list(FILE *fd, char *msg, struct doubly_linked_list *tail)
{
  int align;
  register struct doubly_linked_list *iterator;
  char *default_msg = "Default doubly linked list";
  ENTER("print_dlinked_list");

  if(NULL == msg)
    msg = default_msg;

  align = 0;
  iterator = tail;
  fprintf(fd, "[%s]:\n", msg);
  while(NULL != iterator)
  {
    fprintf(fd, "%d-> ", iterator->index);
    if(!(++align % PRINT_WIDTH))
      fprintf(fd, "\n");
    iterator = iterator->previous;
  }
  fprintf(fd, "NULL\n");

  LEAVE;
  return;
}


void
exchange_dlinked_list(struct doubly_linked_list **head,
  struct doubly_linked_list *node)
{
  struct doubly_linked_list *cur;
  ENTER("exchange_dlinked_list");

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

  while((cur = *head))
  {
    if(cur->next == node)
      break;
    head = &cur->next;
  }

  if(cur)
  {
    /* If cur == *head                                                        */
    if(cur->previous)
    {
      cur->previous->next = node;
      /* If the last element is node                                          */
      if(node->next)
        node->next->previous = cur;
    }
    node->previous = cur->previous;
    cur->previous = node;
    cur->next = node->next;
    node->next = cur;
  }
  else
    warning_prompt(ADD_TRACE(warning_digest[3]));

END_OF_EXCHANGE:
  LEAVE;
  return;
}

