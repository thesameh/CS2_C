// Sameh Shahin ew20b001
// V1 revised (without feedback just self correcting)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    char *pointer;
    int length
} word;

word store_word(int max_word_length, char input_word[max_word_length]);
int check_word(int max_word_length, char input_word[], int words_counter, int initial_size, word words_dyn_array[initial_size]);
void store_word_in_dyn_array(word input_word_info, int word_nr, int *initial_size_pointer, word **words_dyn_array);
int count_words_array(word words_array[]);

int main()
{

    int max_word_length = 63;
    char input_word[max_word_length];

    int initial_size = 6; // initial amount of words expected .. realloate if exceded (last test case)
    int words_counter = 0;

    word *words_dyn_array = (word *)malloc(initial_size * sizeof(word));

    scanf("%s", &input_word);

    while (strcmp(input_word, ".") != 0)
    {
        if (check_word(max_word_length, input_word, words_counter, initial_size, words_dyn_array) != 0)
        {
            // store the word and get it's info
            word input_word_info = store_word(max_word_length, input_word);

            // store the word information in the words dynamic array
            store_word_in_dyn_array(input_word_info, words_counter, &initial_size, &words_dyn_array);

            // keep track of how many words are added
            words_counter++;
        }
        scanf("%s", &input_word);
    }

    // the variable words_counter can be used but just to make sure i'm getting the right data
    printf("%d\n", count_words_array(words_dyn_array));
    free(words_dyn_array);
    return 0;
}

//****** Procedures ******//

word store_word(int max_word_length, char input_word[max_word_length])
{
    char *stored_word = (char *)malloc((strlen(input_word) + 1) * sizeof(char));

    //stored_word = input_word; // BIG stupid mistake

    for (int s = 0; s < strlen(input_word); s++)
    {
        stored_word[s] = input_word[s];
    }
    stored_word[strlen(input_word) + 1] = '\0';

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

// comments with (//*) are usefull to see the reallocation happening
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
int count_words_array(word words_array[])
{
    int l = 0;
    while ((words_array[l].length) != 0)
    {
        l++;
    }
    return l;
}

//****** end Procedures ******//