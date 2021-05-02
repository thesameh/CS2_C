// Sameh Shahin ew20b001

#include <stdio.h>
#include <math.h>

double excute_operation(double result, char op);

int main()
{
    //  variables
    double final_result;
    char operation[5];

    // read an initial input number once
    scanf("%lf", &final_result);

    /*
    * loop through the inputs in an (operation/value) pairs
    * check for the operation at the begining of each loop
    * read the operation at the end of the loop
    */

    while (operation[0] != '=')
    {

        // 2 - check operation - read second input if needed - excute operation
        final_result = excute_operation(final_result, operation[0]);

        // 1 - read the operation
        scanf("%s", operation);
    }

    printf("Result: %.3f\n", final_result);
    return 0;
}

// since none of the operations share the first char in the string array we can check for that first char only
// excute the operation based on its type and read second input if neded
double excute_operation(double result, char op)
{

    double input_1;

    // only read a second input if needed else skip and go to the next (operation/value) pair loop
    if (op != 's' && op != 'n')
    {
        scanf("%lf", &input_1);
    }

    switch (op)
    {
    case 's':
        result = sqrt(result);
        break;
    case 'n':
        result = result * -1;
        break;
    case '+':
        result += input_1;
        break;
    case '-':
        result -= input_1;
        break;
    case '*':
        result = result * input_1;
        break;
    case '/':
        result = result / input_1;
        break;
    }
    return result;
}