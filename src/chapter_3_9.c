/*----------------------------------------------------------------------------*/
/*-AUTHOR:      Incarnation.P Lee                                             */
/*-DATE:        04032014                                                      */
/*-WHAT:        Homework chapter 3-9                                          */
/*-REVISION:                                                                  */
/*- DATE ------------------------ DESCRIPTION --------------------------------*/
/*- 04032014    CHAPTER 3-9                                                  -*/
/*----------------------------------------------------------------------------*/
void
chapt_3_9(void)
{
  ENTER("chapt_3_9");

  print_report_header(stdout, "Any Integer in Linked List", 3, 9);
  print_report_header(dsaaa_report, "Any Integer in Linked List", 3, 9);

  dochapt_3_9();

  LEAVE;
  return;
}


static void
dochapt_3_9(void)
{
  int *nlen;
  int *mlen;
  int *nai;
  int *mai;
  int nai_lens[] = {
    100, 200,
  };
  int mai_lens[] = {
    10, 20, 30, 40, 50, 60, 70, 80, 90, 100,
  };
  struct any_integer_arithmetic_report report;
  struct any_integer_catalog *iter;
  struct any_integer_catalog arith[] = {
    {add_any_integer, ADD,},
    {subtract_any_integer, SUBTRACT,},
    {multiply_any_integer, MULTIPLY,},
  };
  ENTER("dochapt_3_9");

  iter = arith;
  print_any_integer_title();
  report.astringend = 1;

  while(iter < arith + sizeof(arith) / sizeof(arith[0]))
  {
    nlen = nai_lens;
    set_arithmetic_catalog(iter->type);
    while(nlen < nai_lens + sizeof(nai_lens) / sizeof(nai_lens[0]))
    {
      nai = generate_random_seat_array(*nlen, POSITIVE);
      mlen = mai_lens;
      while(mlen < mai_lens + sizeof(mai_lens) / sizeof(mai_lens[0]))
      {
        mai = generate_random_seat_array(*mlen, POSITIVE);
        do_any_integer_performance(mai, *mlen, nai, *nlen,
          &report, iter->arithmetic);
        free_random_int_array(mai);
        set_astringend(&report, iter->type);
        print_any_integer_report(&report);
        mlen++;
      }
      free_random_int_array(nai);
      nlen++;
    }
    iter++;
  }

  LEAVE;
  return;
}


static void
do_any_integer_performance(int *m, int msize, int *n, int nsize,
  struct any_integer_arithmetic_report *report,
  void (*arithmetic)(struct any_integer *, struct any_integer *))
{
  int count;
  unsigned usec;
  struct any_integer *a;
  struct any_integer *b;
  ENTER("do_any_integer_performance");
  /* performance test function need not parameter checking.                  */

  count = 50;
  usec = 0;
  report->usec = 0;
  b = init_any_integer(n, nsize);

  while(count-- > 0)
  {
    a = init_any_integer(m, msize);

    TIME_START;
    arithmetic(a, b);
    TIME_END(&usec);
    report->usec += usec;

    clear_any_integer(&a);
  }

  clear_any_integer(&b);
  report->msize = msize;
  report->nsize = nsize;

  LEAVE;
  return;
}


static int *
generate_random_seat_array(int size, SIGN_AINT sign)
{
  int *raw;
  register int *iter;
  ENTER("generate_random_seat_array");

  if(0 >= size)
    error_handle(ADD_TRACE(error_digest[1]));

  if(POSITIVE != sign && NEGATIVE != sign)
  {
    warning_prompt(ADD_TRACE(warning_digest[9]));
    goto GEN_RAD_SEAT_ARY_END;
  }

  raw = gen_random_int_array(size);
  iter = raw;
  while(iter < raw + size)
  {
    *iter = *iter % 10;
    iter++;
  }

  *raw = sign;

GEN_RAD_SEAT_ARY_END:
  LEAVE;
  return raw;
}


static struct any_integer *
init_any_integer(int *data, int size)
{
  register int *iter;
  struct any_integer *head;
  struct any_integer *node;
  struct single_linked_list *lnode;
  ENTER("init_any_integer");

  if(NULL == data)
    error_handle(ADD_TRACE(error_digest[0]));

  if(size <= 0)
    error_handle(ADD_TRACE(error_digest[1]));

  iter = data;
  malloc_initial((void**)&head, sizeof(*head));
  head->value = *iter++;

  lnode = &head->sll;
  while(iter < data + size)
  {
    malloc_initial((void**)&node, sizeof(*node));
    assign_numeric(node, *iter++);
    lnode->next = &node->sll;
    lnode = lnode->next;
  }

  LEAVE;
  return head;
}


static void
assign_numeric(struct any_integer *node, int value)
{
  ENTER("assign_numeric");

  if(NULL == node)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto ASSIGN_NUM_END;
  }

  if(value > 9 || value < 0)
    error_handle(ADD_TRACE(error_digest[4]));

  node->value = value;

ASSIGN_NUM_END:
  LEAVE;
  return;
}


static void
clear_any_integer(struct any_integer **head)
{
  struct any_integer *node;
  ENTER("clear_any_integer");

  if(NULL == *head || NULL == head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto CLEAR_AI_END;
  }

  while(node = *head, node)
  {
    *head = next_any_integer(node);
    saft_free((void**)&node);
  }

CLEAR_AI_END:
  LEAVE;
  return;
}


void
add_any_integer(struct any_integer *dhead, struct any_integer *shead)
{
  struct any_integer *node_a;
  struct any_integer *node_b;
  SIGN_AINT op_sign;
  ENTER("add_any_integer");

  if(NULL == dhead || NULL == shead)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_ADD_AI;
  }

  op_sign = dhead->value;
  if(dhead->value != shead->value)
  {
    set_sign(op_sign, shead);
    subtract_any_integer(dhead, shead);
    op_sign = POSITIVE == op_sign ? NEGATIVE : POSITIVE;
    set_sign(op_sign, shead);
    goto END_OF_ADD_AI;
  }

  node_a = last_any_integer(dhead);
  node_b = last_any_integer(shead);

  while(node_a && node_b)
  {
    node_a->value += node_b->value;
    iscarry(node_a);

    node_a = previous_any_integer(dhead, node_a);
    node_b = previous_any_integer(shead, node_b);
  }

  /*- If node_b is NULL, update node_a with cb_flag.                         -*/
  while(node_a && CARRY == cb_flag)
  {
    iscarry(node_a);
    node_a = previous_any_integer(dhead, node_a);
  }

  /*- If node_a is NULL, copy node_a in front if node_a.                     -*/
  while(node_b)
  {
    malloc_initial((void**)&node_a, sizeof(*node_a));
    node_a->value = node_b->value;
    iscarry(node_a);

    insert_any_integer(dhead, node_a);
    node_b = previous_any_integer(shead, node_b);
  }

  deal_left_cb(dhead);
  set_sign(op_sign, dhead);

END_OF_ADD_AI:
  LEAVE;
  return;
}


void
subtract_any_integer(struct any_integer *dhead, struct any_integer *shead)
{
  struct any_integer *node_a;
  struct any_integer *node_b;
  SIGN_AINT op_sign;
  int abscmp;
  ENTER("subtract_any_integer");

  if(NULL == dhead || NULL == shead)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_SUB_AI;
  }

  op_sign = dhead->value;
  if(dhead->value != shead->value)
  {
    set_sign(op_sign, shead);
    add_any_integer(dhead, shead);
    op_sign = POSITIVE == op_sign ? NEGATIVE : POSITIVE;
    set_sign(op_sign, shead);
    goto END_OF_SUB_AI;
  }

  node_a = last_any_integer(dhead);
  node_b = last_any_integer(shead);
  abscmp = abscompare_any_integer(dhead, shead);

  while(node_a && node_b)
  {
    if(SMALL == abscmp)
      node_a->value = node_b->value - node_a->value;
    else
      node_a->value -= node_b->value;
    isborrow(node_a);

    node_a = previous_any_integer(dhead, node_a);
    node_b = previous_any_integer(shead, node_b);
  }

  if(SMALL == abscmp)
    op_sign = POSITIVE == op_sign ? NEGATIVE : POSITIVE;

  /*- If node_b is NULL, update node_a with cb_flag.                         -*/
  while(node_a && BORROW == cb_flag)
  {
    isborrow(node_a);
    node_a = previous_any_integer(dhead, node_a);
  }

  /*- If node_a is NULL, copy node_a in front if node_a.                     -*/
  while(node_b)
  {
    malloc_initial((void**)&node_a, sizeof(*node_a));
    node_a->value = node_b->value;
    isborrow(node_a);

    insert_any_integer(dhead, node_a);
    node_b = previous_any_integer(shead, node_b);
  }

  deal_left_cb(dhead);
  set_sign(op_sign, dhead);
  eliminate_leading_zero(dhead);

END_OF_SUB_AI:
  LEAVE;
  return;
}


void
multiply_any_integer(struct any_integer *dhead, struct any_integer *shead)
{
  struct any_integer *node;
  struct any_integer *imd;
  struct any_integer *base;
  SIGN_AINT sg;
  int len;
  ENTER("multiply_any_integer");

  if(NULL == dhead || NULL == shead)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_MUL_AI;
  }

  base = copyof_any_integer(dhead);
  set_zero_any_integer(dhead);
  sg = dhead->value == shead->value ? POSITIVE : NEGATIVE;

  len = 0;
  node = last_any_integer(shead);
  while(node)
  {
    imd = copyof_any_integer(base);

    multiply_single_any_integer(imd, node->value);
    shift_left_any_integer(imd, len++);
    add_any_integer(dhead, imd);
    clear_any_integer(&imd);

    node = previous_any_integer(shead, node);
  }

  clear_any_integer(&base);
  set_sign(sg, dhead);

END_OF_MUL_AI:
  LEAVE;
  return;
}


void
set_zero_any_integer(struct any_integer *head)
{
  struct any_integer *fir;
  struct any_integer *sec;
  ENTER("set_zero_any_integer");

  if(NULL == head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_SET_ZERO_AI;
  }

  fir = next_any_integer(head);
  sec = next_any_integer(fir);
  fir->value = 0;
  fir->sll.next = NULL;
  if(sec)
    clear_any_integer(&sec);

END_OF_SET_ZERO_AI:
  LEAVE;
  return;
}


static void
multiply_single_any_integer(struct any_integer *head, int seat)
{
  struct any_integer *node;
  struct any_integer *node2;
  struct any_integer *node4;
  ENTER("multiply_single_any_integer");

  if(NULL == head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_MUL_SINGLE_AI;
  }

  if(seat < 0 || seat >= MAX_NUMBER)
    error_handle(ADD_TRACE(error_digest[4]));

  if(0 == seat)
  {
    node = next_any_integer(head);
    set_zero_any_integer(head);
    goto END_OF_MUL_SINGLE_AI;
  }

  node = copyof_any_integer(head);
  node2 = copyof_any_integer(head);
  add_any_integer(node2, node);
  node4 = copyof_any_integer(node2);
  add_any_integer(node4, node2);

  seat--;
  while(seat)
  {
    switch(seat)
    {
      case 8:
      case 7:
      case 6:
      case 5:
      case 4:
        seat -= 4;
        add_any_integer(head, node4);
        break;
      case 3:
      case 2:
        seat -= 2;
        add_any_integer(head, node2);
        break;
      case 1:
        seat--;
        add_any_integer(head, node);
      default:
        break;
    }
  }

  clear_any_integer(&node);
  clear_any_integer(&node2);
  clear_any_integer(&node4);

END_OF_MUL_SINGLE_AI:
  LEAVE;
  return;
}


struct any_integer *
copyof_any_integer(struct any_integer *head)
{
  struct any_integer *node;
  struct any_integer *pre;
  struct any_integer *nhead;
  ENTER("copyof_any_integer");

  node = NULL;
  if(NULL == head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto COPYOF_AI_END;
  }

  malloc_initial((void**)&nhead, sizeof(*node));
  nhead->value = head->value;

  pre = nhead;
  head = next_any_integer(head);
  while(head)
  {
    malloc_initial((void**)&node, sizeof(*node));
    node->value = head->value;
    pre->sll.next = &node->sll;
    pre = node;
    head = next_any_integer(head);
  }

COPYOF_AI_END:
  LEAVE;
  return nhead;
}


struct any_integer *
getzero_node_any_integer(void)
{
  struct any_integer *node;
  ENTER("getzero_node_any_integer");

  malloc_initial((void**)&node, sizeof(*node));
  node->sll.next = NULL;
  node->value = 0;

  LEAVE;
  return node;
}


void
shift_right_any_integer(struct any_integer *head, int size)
{
  struct any_integer *node;
  struct any_integer *pre;
  ENTER("shift_right_any_integer");

  if(0 > size)
    error_handle(ADD_TRACE(error_digest[1]));

  if(NULL == head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto SHIFT_RIGHT_AI_END;
  }

  if(iszero_any_integer(head))
    goto SHIFT_RIGHT_AI_END;

  node = last_any_integer(head);
  pre = previous_any_integer(head, node);

  while(size--)
  {
    if(pre)
    {
      saft_free((void**)&node);
      pre->sll.next = NULL;
    }
    else
      node->value = 0;
    node = pre;
    pre = previous_any_integer(head, node);
  }

SHIFT_RIGHT_AI_END:
  eliminate_leading_zero(head);
  LEAVE;
  return;
}


void
shift_left_any_integer(struct any_integer *head, int size)
{
  struct any_integer *cur;
  struct any_integer *next;
  ENTER("shift_left_any_integer");

  if(0 > size)
    error_handle(ADD_TRACE(error_digest[1]));

  if(NULL == head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto SHIFT_LEFT_AI_END;
  }

  if(iszero_any_integer(head))
    goto SHIFT_LEFT_AI_END;

  cur = last_any_integer(head);
  while(size--)
  {
    malloc_initial((void**)&next, sizeof(*next));
    next->sll.next = NULL;
    next->value = 0;
    insert_any_integer(cur, next);
    cur = next;
  }

SHIFT_LEFT_AI_END:
  eliminate_leading_zero(head);
  LEAVE;
  return;
}


int
iszero_any_integer(struct any_integer *head)
{
  int iszero;
  ENTER("iszero_any_integer");

  iszero = 0;
  if(NULL == head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto ISZERO_AI_END;
  }

  eliminate_leading_zero(head);
  head = next_any_integer(head);
  if(0 == head->value && NULL == head->sll.next)
    iszero = 1;

ISZERO_AI_END:
  LEAVE;
  return iszero;
}


int
abscompare_any_integer(struct any_integer *ahead, struct any_integer *bhead)
{
  int result;
  int len_a;
  int len_b;
  struct any_integer *node_a;
  struct any_integer *node_b;
  ENTER("abscompare_any_integer");

  len_a = lengthof_slinked_list(&ahead->sll);
  len_b = lengthof_slinked_list(&bhead->sll);

  if(len_a > len_b)
    result = BIG;

  if(len_a < len_b)
    result = SMALL;

  if(len_a == len_b)
  {
    result = EQUAL;
    node_a = next_any_integer(ahead);
    node_b = next_any_integer(bhead);
    while(node_a)
    {
      if(node_a->value > node_b->value)
      {
        result = BIG;
        break;
      }

      if(node_a->value < node_b->value)
      {
        result = SMALL;
        break;
      }
      node_a = next_any_integer(node_a);
      node_b = next_any_integer(node_b);
    }
  }

  LEAVE;
  return result;
}


static void
eliminate_leading_zero(struct any_integer *head)
{
  struct any_integer *node;
  struct any_integer *next;
  SIGN_AINT op_sign;
  ENTER("eliminate_leading_zero");

  if(NULL == head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto ELIMINATE_LZ_END;
  }

  op_sign = head->value;
  node = next_any_integer(head);
  while(!node->value && NULL != node->sll.next)
  {
    next = next_any_integer(node);
    delete_any_integer(head, node);
    node = next;
  }

  set_sign(op_sign, head);

ELIMINATE_LZ_END:
  LEAVE;
  return;
}


void
insert_any_integer(struct any_integer *cnode, struct any_integer *node)
{
  ENTER("insert_any_integer");

  if(NULL == cnode || NULL == node)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto INSERT_END;
  }

  /*- insert node after head.                                                -*/
  node->sll.next = cnode->sll.next;
  cnode->sll.next = &node->sll;

INSERT_END:
  LEAVE;
  return;
}


void
delete_any_integer(struct any_integer *head, struct any_integer *node)
{
  ENTER("insert_any_integer");

  if(NULL == head || NULL == node)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto INSERT_END;
  }

  /*- insert node after head.                                                -*/
  while(head)
  {
    if(node == next_any_integer(head))
    {
      head->sll.next = node->sll.next;
      saft_free((void**)&node);
      break;
    }
    /*Warning: Muliplex Sematic of Variable head.                            -*/
    head = next_any_integer(head);
  }

  if(!head)
    warning_prompt(ADD_TRACE(warning_digest[3]));

INSERT_END:
  LEAVE;
  return;
}


static void
deal_left_cb(struct any_integer *head)
{
  struct any_integer *node;
  ENTER("deal_left_cb");

  switch(cb_flag)
  {
    case CARRY:
      malloc_initial((void**)&node, sizeof(*node));
      node->value = 1;
      insert_any_integer(head, node);
      break;
    case BORROW:
      node = next_any_integer(head);
      if(1 == node->value)
        delete_any_integer(head, node);
      break;
    case DEFAULT:
      break;
    default:
      warning_prompt(ADD_TRACE(warning_digest[6]));
      goto END_OF_DEAL_LEFT;
      break;
  }
  cb_flag = DEFAULT;

END_OF_DEAL_LEFT:
  LEAVE;
  return;
}


static void
set_sign(SIGN_AINT sign, struct any_integer *head)
{
  ENTER("set_sign");

  if(NULL == head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_SET_SIGN;
  }

  head->value = sign;

END_OF_SET_SIGN:
  LEAVE;
  return;
}


static void
iscarry(struct any_integer *node)
{
  ENTER("iscarry");

  switch(cb_flag)
  {
    case CARRY:
      node->value += 1;
      cb_flag = DEFAULT;
      break;
    case DEFAULT:
      break;
    default:
      warning_prompt(ADD_TRACE(warning_digest[6]));
      cb_flag = DEFAULT;
      goto END_OF_CARRY;
      break;
  }

  if(node->value >= MAX_NUMBER)
  {
    node->value %= MAX_NUMBER;
    cb_flag = CARRY;
  }

END_OF_CARRY:
  LEAVE;
  return;
}


static void
isborrow(struct any_integer *node)
{
  ENTER("isborrow");

  switch(cb_flag)
  {
    case BORROW:
      node->value -= 1;
      cb_flag = DEFAULT;
      break;
    case DEFAULT:
      break;
    default:
      warning_prompt(ADD_TRACE(warning_digest[6]));
      cb_flag = DEFAULT;
      goto END_OF_BORROW;
      break;
  }

  if(node->value < 0)
  {
    node->value += MAX_NUMBER;
    cb_flag = BORROW;
  }

END_OF_BORROW:
  LEAVE;
  return;
}


struct any_integer *
previous_any_integer(struct any_integer *head, struct any_integer *node)
{
  struct any_integer *previous;
  ENTER("previous_any_integer");

  previous = NULL;
  if(NULL == node || NULL == head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_PREVIOUS;
  }

  /*- If specified the sign position(first node), complain and return NULL   -*/
  if(node == head)
  {
    warning_prompt(ADD_TRACE(warning_digest[8]));
    goto END_OF_PREVIOUS;
  }

  /*- If reach the head of list, set previous as NULL.                       -*/
  if(node == next_any_integer(head))
    goto END_OF_PREVIOUS;

  previous = head;
  while(previous)
  {
    if(node == next_any_integer(previous))
      break;
    previous = next_any_integer(previous);
  }

  if(!previous)
    warning_prompt(ADD_TRACE(warning_digest[3]));

END_OF_PREVIOUS:
  LEAVE;
  return previous;
}


struct any_integer *
next_any_integer(struct any_integer *node)
{
  struct any_integer *next;
  ENTER("next_any_integer");

  next = NULL;
  if(NULL == node)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto END_OF_NEXT;
  }

  next = CONSTRAINT_OF(node->sll.next, struct any_integer, sll);
/*
  asm volatile(
    "movq %1, %%rax\n\t"
    "movq %2, %%rdx\n\t"
    "subq %%rdx, %%rax\n\t"
    "movq %%rax, %0\n\t"
    :"=r"(next)
    :"r"(linker), "r"(offset)
    :"rax", "rdx", "memory"
  );
*/

END_OF_NEXT:
  LEAVE;
  return next;
}


struct any_integer *
last_any_integer(struct any_integer *head)
{
  struct any_integer *last;
  ENTER("last_any_integer");

  last = head;
  while(last->sll.next)
    last = next_any_integer(last);

  LEAVE;
  return last;
}


void
print_any_integer(struct any_integer *head)
{
  struct any_integer *node;
  ENTER("print_any_integer");
  if(NULL == head)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto PRINT_AI_END;
  }

  switch(head->value)
  {
    case POSITIVE:
      fprintf(stdout, " + ");
      break;
    case NEGATIVE:
      fprintf(stdout, " - ");
      break;
    default:
      warning_prompt(ADD_TRACE(warning_digest[6]));
      goto PRINT_AI_END;
      break;
  }

  node = next_any_integer(head);
  while(node)
  {
    fprintf(stdout, "%1d", node->value);
    node = next_any_integer(node);
  }

  fprintf(stdout, "\n");

PRINT_AI_END:
  LEAVE;
  return;
}


static void
print_any_integer_title(void)
{
  ENTER("print_any_integer_title");

  fprintf(stdout, "INDEX  MSIZE  NSIZE  TIME(usec)  ASTRINGEND\n");
  fprintf(dsaaa_report, "INDEX  MSIZE  NSIZE  TIME(usec)  ASTRINGEND\n");

  LEAVE;
  return;
}


static void
print_any_integer_report(struct any_integer_arithmetic_report *report)
{
  static int index = 0;
  ENTER("print_any_integer_report");

  fprintf(stdout, "  %3d %6d %6d    %8d  %10.5f\n", index++ >> 1,
    report->msize, report->nsize, report->usec,
    (double)report->usec / report->astringend);
  fprintf(dsaaa_report, "  %3d %6d %6d    %8d  %10.5f\n", index++ >> 1,
    report->msize, report->nsize, report->usec,
    (double)report->usec / report->astringend);

  LEAVE;
  return;
}


static void
set_astringend(struct any_integer_arithmetic_report *report,
  enum ARITHMETIC type)
{
  ENTER("set_astringend");

  if(NULL == report)
  {
    warning_prompt(ADD_TRACE(warning_digest[0]));
    goto SET_ASTRINGEND_END;
  }

  switch(type)
  {
    case ADD:
    case SUBTRACT:
      report->astringend = report->msize + report->nsize;
      break;
    case MULTIPLY:
      report->astringend = report->msize * report->nsize;
      break;
    default:
      warning_prompt(ADD_TRACE(warning_digest[6]));
      goto SET_ASTRINGEND_END;
      break;
  }

SET_ASTRINGEND_END:
  LEAVE;
  return;
}


static void
set_arithmetic_catalog(enum ARITHMETIC type)
{
  char *msg;
  ENTER("set_arithmetic_catalog");

  switch(type)
  {
    case ADD:
      msg = SYMBOL_TO_STRING(ADD);
      break;
    case SUBTRACT:
      msg = SYMBOL_TO_STRING(SUBTRACT);
      break;
    case MULTIPLY:
      msg = SYMBOL_TO_STRING(MULTIPLY);
      break;
    default:
      warning_prompt(ADD_TRACE(warning_digest[6]));
      goto SET_ARITH_CTLG_END;
      break;
  }

  fprintf(stdout, "[%s]\n", msg);
  fprintf(dsaaa_report, "[%s]\n", msg);

SET_ARITH_CTLG_END:
  LEAVE;
  return;
}
