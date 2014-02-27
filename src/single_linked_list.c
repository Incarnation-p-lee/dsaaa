/*----------------------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                                            -*/
/*-DATE:        02262014                                                     -*/
/*-WHAT:        Homework chapter 1.1                                         -*/
/*-REVISION:                                                                 -*/
/*- DATE -------------------- DESCRIPTION ------------------------------------*/
/*- 02262014    Single linked list API for others.                           -*/
/*----------------------------------------------------------------------------*/
struct single_linked_list *
generate_linked_list(int *values, int size)
{
  struct single_linked_list *head;
  struct single_linked_list *node;
  register int *iterator;
  ENTER("generate_linked_list");

  if(NULL == values)
    error_handle("Attempted to access NULL pointer detected");

  if(size <= 0)
    error_handle("No positive dimension detected");

  iterator = values;
  malloc_initial((void**)&node, sizeof(*node));
  node->value = *iterator++;
  node->next = NULL;
  head = node;

  while(iterator < values + size)
  {
    append_linked_list_node(node, *iterator++);
    node = node->next;
  }

  LEAVE;
  return head;
}


void
append_linked_list_node(struct single_linked_list *node, int value)
{
  struct single_linked_list *next;
  ENTER("append_linked_list_node");

  if(NULL == node)
  {
    warn_prompt("Null pointer of current node detected");
    goto END_OF_APPEND;
  }

  malloc_initial((void**)&next, sizeof(*next));
  next->value = value;
  next->next = NULL;

  if(NULL != node->next)
    next->next = node->next;
  node->next = next;

END_OF_APPEND:
  LEAVE;
  return;
}


void
clear_linked_list(struct single_linked_list **head)
{
  struct single_linked_list *cur;
  ENTER("clear_linked_list");

  if(NULL == head)
  {
    warn_prompt("Null pointer of head node detected");
    goto END_OF_CLEAR;
  }

  while(NULL != (cur = *head))
  {
    head = &(*head)->next;
    saft_free((void**)&cur);
  }

END_OF_CLEAR:
  LEAVE;
  return;
}


int
lengthof_linked_list(struct single_linked_list *head)
{
  int length;
  ENTER("lengthof_linked_list");

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


struct single_linked_list *
accessby_index_linked_list(struct single_linked_list *head, int index)
{
  struct single_linked_list *node;
  ENTER("accessby_index_linked_list");

  node = NULL;
  if(NULL == head)
  {
    warn_prompt("Null linked list head pointer detected");
    goto END_OF_ACCESS;
  }
  if(0 > index)
  {
    warn_prompt("Null linked list head pointer detected");
    goto END_OF_ACCESS;
  }

  node = head;
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
print_single_linked_list(FILE *fd, char *msg, struct single_linked_list *head)
{
  int align;
  register struct single_linked_list *iterator;
  char *default_msg = "Default single linked list";
  ENTER("print_single_linked_list");

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
