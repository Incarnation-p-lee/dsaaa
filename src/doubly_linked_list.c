/*----------------------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                                            -*/
/*-DATE:        02262014                                                     -*/
/*-WHAT:        Doubly linked list API for other modules.                     -*/
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
    error_handle("Attempted to access NULL pointer detected");

  if(size <= 0)
    error_handle("No positive dimension detected");

  iterator = val;
  malloc_initial((void**)&node, sizeof(*node));
  node->value = *iterator++;
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
    warn_prompt("Null pointer of current node detected");
    goto END_OF_APPEND;
  }

  malloc_initial((void**)&next, sizeof(*next));
  next->value = value;
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
  ENTER("clear_dlinked_list");

  if(NULL == head)
  {
    warn_prompt("Null pointer of head node detected");
    goto END_OF_CLEAR;
  }

  while(NULL != (cur = *head))
  {
    head = &cur->next;
    saft_free((void**)&cur);
  }

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
    warn_prompt("Null linked list head detected");
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
    warn_prompt("Null linked list head pointer detected");
    goto END_OF_ACCESS;
  }
  if(0 > index)
  {
    warn_prompt("Invalid index of linked list detected");
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
    fprintf(fd, "%d-> ", iterator->value);
    if(!(++align % PRINT_WIDTH))
      fprintf(fd, "\n");
    iterator = iterator->next;
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

  if(NULL == head || NULL == *head)
  {
    warn_prompt("Null linked list head pointer detected");
    goto END_OF_DL_EXCHANGE;
  }
  if(NULL == node)
  {
    warn_prompt("Null pointer of current node detected");
    goto END_OF_DL_EXCHANGE;
  }
  if(*head == node)
  {
    warn_prompt("Can not exchange node before head");
    goto END_OF_DL_EXCHANGE;
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
    warn_prompt("Do not find target node in linked list");

END_OF_DL_EXCHANGE:
  LEAVE;
  return;
}

