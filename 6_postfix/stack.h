//should I also use include guards for these ?  or does it only make sense for prototypes
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_INPUT_LENGTH 11

// Prototypes
#ifndef STACK_NODE
#define STACK_NODE
typedef struct stack_node stack_node;
#endif

#ifndef PUSH_STACK
#define PUSH_STACK
stack_node *stack_push(int value, stack_node *old_head);
#endif

#ifndef POP_STACK
#define POP_STACK
stack_node *stack_pop(stack_node *old_head);
#endif

#ifndef INT_CHECK
#define INT_CHECK
bool is_int(char s[]);
#endif

#ifndef CHAR_INT_VAL
#define CHAR_INT_VAL
int get_int_value(char s[]);
#endif
