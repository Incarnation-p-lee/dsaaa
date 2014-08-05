#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

/*-     EXTERNALS                                                            -*/
extern void
error_handle(const char *);
extern void
warning_prompt(char *);
extern void
exchange(int *, int *);
extern void
leave(void);
extern void
enter(const char *);
extern void
malloc_initial(void **, unsigned int);
extern void
realloc_initial(void **, unsigned int);
extern void
saft_free(void **);


/*-     TYPE, MARCO AND VARIABLE                                             -*/
#define DEFAULT_QUEUE_SIZE     32

struct array_queue *
create_array_queue_instance(void);
void
destroy_array_queue_instance(struct array_queue **);
void
expand_array_queue(struct array_queue *, unsigned);
void
enter_array_queue(struct array_queue *, void *);
void *
leave_array_queue(struct array_queue *);
void
clear_array_queue(struct array_queue *);
void
traverse_array_queue(struct array_queue *, void (*)(void *));
int
is_empty_array_queue(struct array_queue *);
int
is_full_array_queue(struct array_queue *);

#endif
