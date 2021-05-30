// Sameh Shahin ew20b001
// V2



#include <stdio.h>
#include <math.h>
#include <libc.h>

double excute_operation(double result, char op[]);

int main()
{
    //  variables
    double final_result;
    double temp_input;
    char operation[10];

    // read an initial input number once
    scanf("%lf", &final_result);

    // read an initial operation
    scanf("%s", &operation);

    while (strcmp(operation, "=") != 0)
    {
        // excute the operation based on its type
        final_result = excute_operation(final_result, operation);

        // read the next operation
        scanf("%s", &operation);
    }

    printf("Result: %.3f\n", final_result);
    return 0;
}

// excute the operation based on its type and read second input if neded
double excute_operation(double result, char op[])
{
    double temp_input;

    // operations with no need to second input
    if (strcmp(op, "sqrt") == 0)
    {
        result = sqrt(result);
    }
    else if (strcmp(op, "neg") == 0)
    {
        result = result * -1;
    }
    else
    {
        // operations with need to second input
        scanf("%lf", &temp_input);

        if (strcmp(op, "+") == 0)
        {
            result += temp_input;
        }
        else if (strcmp(op, "-") == 0)
        {

            result -= temp_input;
        }
        else if (strcmp(op, "*") == 0)
        {

            result = result * temp_input;
        }
        else if (strcmp(op, "/") == 0)
        {

            result = result / temp_input;
        }
    }

    return result;
}