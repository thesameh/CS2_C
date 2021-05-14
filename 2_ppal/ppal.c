// Sameh Shahin ew20b001

#include <stdio.h>

// prototypes
int strlength(char s[]);
int is_char(char letter);
void get_char_only_string(int line_length, char input_line[], char char_line[]);
void rev_string(char char_line[], char char_line_rev[]);
int compare_strings_same_size(char s1[], char s2[]);

int main()
{
    int is_palindrome = 1;
    int max_char_length = 80;
    char input_line[max_char_length];
    char char_line[max_char_length];
    char char_line_rev[max_char_length];

    // read input line and get it's length
    fgets(input_line, max_char_length, stdin);
    int line_length = strlength(input_line);

    // initial check if palindrome or not based on length (carefull! additional \0 is added)
    if (line_length > 2)
    {
        // parse input to a char only string
        get_char_only_string(line_length, input_line, char_line);

        // get a char only reversed string
        rev_string(char_line, char_line_rev);

        // check if they are the same
        is_palindrome = compare_strings_same_size(char_line, char_line_rev);
    }

    // print output
    if (is_palindrome)
    {
        printf("palindrome\n");
    }
    else
    {
        printf("not a palindrome\n");
    }

    return 0;
}

//****** Procedures ******//

int strlength(char s[])
{
    int i = 0;
    while (s[i] != '\0')
        ++i;
    return i;
}

int is_char(char letter)
{
    if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//** modified to use pointer arithmetics
void get_char_only_string(int line_length, char input_line[], char char_line[])
{

    char *il_pos_1 = input_line;
    char *cl_pos_1 = char_line;

    char *il_pos_last = input_line + line_length;

    for (il_pos_1; il_pos_1 < il_pos_last; il_pos_1++)
    {

        if (is_char(*il_pos_1))
        {
            *cl_pos_1 = *il_pos_1;
            cl_pos_1++;
        }
    }

    *cl_pos_1 = '\0';
}

//** modified to use pointer arithmetics
void rev_string(char char_line[], char char_line_rev[])
{
    int j = 0;
    int line_length = strlength(char_line);

    char *pos1 = char_line;
    char *pos1_rev = char_line_rev;

    char *last_pos = char_line + line_length;
    char *last_pos_rev = char_line_rev + line_length;

    *last_pos_rev = '\0';
    last_pos_rev--;

    for (pos1; pos1 < last_pos; pos1++)
    {
        *last_pos_rev = *pos1;
        last_pos_rev--;
    }
}

//** modified to use pointer arithmetics
int compare_strings_same_size(char s1[], char s2[])
{
    char *size = s1 + strlength(s1);
    int result = 1;
    char compare_char_1, compare_char_2;

    char *l1 = s1;
    char *l2 = s2;

    for (l1; l1 < size; l1++)
    {
        // convert lower case to upper case
        compare_char_1 = *l1 >= 'a' ? *l1 - 32 : *l1;
        compare_char_2 = *l2 >= 'a' ? *l2 - 32 : *l2;
        if (compare_char_1 != compare_char_2)
        {
            result = 0;
        }
        l2++;
    }
    return result;
}

//****** end Procedures ******//