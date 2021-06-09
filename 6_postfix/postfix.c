// Sameh Shahin ew20b001

#include "stack.h"
#include "stack.c"

int main()
{

    // variables
    char input[MAX_INPUT_LENGTH];
    stack_node *stack_head = (stack_node *)malloc(sizeof(stack_node));

    // read an initial input
    scanf("%s", &input[0]); // Apparently this way of reading strings is beeter than using (&input) .. and it removes the warnings so I used it
    while (strcmp(input, "=") != 0)
    {
        // check type
        if (is_int(input))
        {
            // get int value and store it in the stack
            int int_val = get_int_value(input);
            stack_head = stack_push(int_val, stack_head);
        }
        else
        {
            // pop 2 values to excute the operations (order matters!)

            int n2 = stack_head->value;
            stack_head = stack_pop(stack_head);
            int n1 = stack_head->value;
            stack_head = stack_pop(stack_head);

            if (strcmp(input, "+") == 0)
            {
                stack_head = stack_push((n1 + n2), stack_head);
            }
            else if (strcmp(input, "-") == 0)
            {
                stack_head = stack_push((n1 - n2), stack_head);
            }
            else if (strcmp(input, "*") == 0)
            {
                stack_head = stack_push((n1 * n2), stack_head);
            }
            else if (strcmp(input, "/") == 0)
            {
                stack_head = stack_push((n1 / n2), stack_head);
            }
            else if (strcmp(input, "%") == 0)
            {
                stack_head = stack_push((n1 % n2), stack_head);
            }
        }

        // read the next input
        scanf("%s", &input[0]);
    };
    printf("%d\n", stack_head->value);

    return 0;
}