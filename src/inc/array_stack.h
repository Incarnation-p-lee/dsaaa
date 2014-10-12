#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#define STACK_SIZE_DEFAULT     16
#define STACK_SIZE_MIN         32

extern void
malloc_initial(void **, unsigned int);
extern void
realloc_noinitial(void **, unsigned int);
extern void
saft_free(void **);

struct array_stack *
create_array_stack_space(void);
void
destroy_array_stack_space(struct array_stack **);
void
expand_array_stack_space(struct array_stack *, unsigned);
int
is_array_stack_full(struct array_stack *);
unsigned
rest_space_of_array_stack(struct array_stack *);
void
push_array_stack(struct array_stack *, void *);
void *
pop_array_stack(struct array_stack *);
int
is_empty_array_stack(struct array_stack *);
void
cleanup_array_stack(struct array_stack *);
void
traverse_array_stack(struct array_stack *, void (*)(void *));

#endif
