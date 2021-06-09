
// stack
struct stack_node
{
    int value;
    struct stack_node *next;
};

stack_node *stack_push(int value, stack_node *old_head)
{
    stack_node *new_head =
        (stack_node *)malloc(sizeof(stack_node));
    new_head->value = value;
    new_head->next = old_head;
    return new_head;
}

stack_node *stack_pop(stack_node *old_head)
{
    stack_node *new_head = old_head->next;
    free(old_head);
    return new_head;
}

// other Procedures

bool is_int(char s[])
{
    for (int i = 0; (unsigned)i < strlen(s); i++)
        if (isdigit(s[i]) == false)
            return false;

    return true;
}

int get_int_value(char s[])
{
    int result = 0;
    for (int i = 0; (unsigned)i < strlen(s); i++)
    {
        int char_int_val = s[i] - '0';
        // get the decimal value
        int char_position = strlen(s) - i - 1;
        result += char_int_val * pow(10, char_position);
    }
    return result;
}