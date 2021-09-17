// Sameh Shahin ew20b001
// Final exam (basically a combination of the previous exercises)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>

#define MAX_INPUT_LENGTH 63

typedef struct
{
    char *pointer;
    int length
} word;

bool is_int(char s[]);

int get_int_value(char s[]);

word store_word(int max_word_length, char input_word[max_word_length]);

int check_word(int max_word_length, char input_word[], int words_counter, int initial_size, word words_dyn_array[initial_size]);

void store_word_in_dyn_array(word input_word_info, int word_nr, int *initial_size_pointer, word **words_dyn_array);

void store_num_in_dyn_array(int input_num, int num_nr, int *initial_size_pointer, int **numTable);

void sortNum(int num_counter, int *numTable);
int main()
{
    // variables
    char input[MAX_INPUT_LENGTH];
    int initial_w_taple_size = 10;
    int initial_n_taple_size = 10;
    int words_counter, num_counter = 0;

    //** dynamic array for words
    word *wordTable = (word *)malloc(initial_w_taple_size * sizeof(word));
    //** dynamic array for numbers
    int *numTable = (char *)malloc(initial_n_taple_size * sizeof(char));

    //** read an initial input allocAndReadInput()
    scanf("%s", input);

    while (strcmp(input, ".") != 0)
    {
        // check type
        if (is_int(input))
        {
            //** is num

            // get int value and store it in the stack
            int int_val = get_int_value(input);
            store_num_in_dyn_array(int_val, num_counter, &initial_n_taple_size, &numTable);
            // keep track of how many words are added
            num_counter++;
        }
        else
        {
            //** is word
            if (check_word(MAX_INPUT_LENGTH, input, words_counter, initial_w_taple_size, wordTable) != 0)
            {
                // store the word and get it's info
                word input_word_info = store_word(MAX_INPUT_LENGTH, input);

                // store the word information in the words dynamic array
                store_word_in_dyn_array(input_word_info, words_counter, &initial_w_taple_size, &wordTable);

                // keep track of how many words are added
                words_counter++;
            }
        }

        // read the next input
        scanf("%s", input);
    };

    //** print words
    for (int ic = 0; ic < words_counter; ic++)
    {
        char array_word[MAX_INPUT_LENGTH];
        for (int l = 0; l < wordTable[ic].length; l++)
        {
            array_word[l] = *(wordTable[ic].pointer + l);
        }
        array_word[wordTable[ic].length] = '\0';

        printf("%s ", array_word);
    }
    printf("\n");

    //** sort numbers
    sortNum(num_counter, numTable);

    //** print numbers
    for (int i = 0; i < num_counter; i++)
    {
        printf("%d ", numTable[i]);
    }
    

    return 0;
}

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

word store_word(int max_word_length, char input_word[max_word_length])
{
    char *stored_word = strdup(input_word);
    word stored_word_info = {stored_word, strlen(stored_word)};
    return stored_word_info;
}

int check_word(int max_word_length, char input_word[], int words_counter, int initial_size, word words_dyn_array[initial_size])
{
    int add_this_word = 0;

    // validate the word
    if (strlen(input_word) != 0 && input_word[0] != '.' && input_word[0] != ' ' && input_word[0] != '\n' && input_word[0] != '\0')
    {
        //compare to the existing words
        for (int i = 0; i < words_counter; i++)
        {

            // skip if sizes are different
            if (words_dyn_array[i].length == strlen(input_word))
            {
                char array_word[max_word_length];
                for (int l = 0; l < words_dyn_array[i].length; l++)
                {
                    array_word[l] = *(words_dyn_array[i].pointer + l);
                }
                array_word[words_dyn_array[i].length] = '\0';

                if (strcmp(array_word, input_word) == 0)
                {
                    // match is found
                    add_this_word = 0;
                    return add_this_word;
                    break;
                }
            }
        }
        // no match is found
        add_this_word = 1;
    }

    return add_this_word;
};

void store_word_in_dyn_array(word input_word_info, int word_nr, int *initial_size_pointer, word **words_dyn_array)
{
    //* printf("current size %d , word nr %d \n", *initial_size_pointer, word_nr);

    //check for if there is enogh memory before adding new words
    if (word_nr >= *initial_size_pointer)
    {
        *initial_size_pointer = *initial_size_pointer * 2;
        *words_dyn_array = (word *)realloc(*words_dyn_array, (*initial_size_pointer) * sizeof(word));

        if (words_dyn_array == NULL)
        {
            printf("reallocation error %d \n", words_dyn_array);
        }
        else
        {
            //* printf("reallocated new size %d \n", *initial_size_pointer);
        }
    }

    // add the word info to the dynamic array
    (*words_dyn_array)[word_nr] = input_word_info;
}

void store_num_in_dyn_array(int input_num, int num_nr, int *initial_size_pointer, int **numTable)
{
    //printf("current size %d , word nr %d \n", *initial_size_pointer, num_nr);

    //check for if there is enogh memory before adding new words
    if (num_nr >= *initial_size_pointer)
    {
        *initial_size_pointer = *initial_size_pointer * 2;
        *numTable = (int *)realloc(*numTable, (*initial_size_pointer) * sizeof(int));

        if (numTable == NULL)
        {
            printf("reallocation error %d \n", numTable);
        }
        else
        {
            //* printf("reallocated new size %d \n", *initial_size_pointer);
        }
    }

    // add the number to the dynamic array
    (*numTable)[num_nr] = input_num;
}

void sortNum(int num_counter, int *numTable)
{
    int sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (int counter = 0; counter < num_counter - 1; counter++)
        {
            int num_1 = numTable[counter];
            int num_2 = numTable[counter + 1];
            if (num_1 > num_2)
            {
                numTable[counter] = num_2;
                numTable[counter + 1] = num_1;

                sorted = false;
            }
        }
    }
}