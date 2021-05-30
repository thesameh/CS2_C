// Sameh Shahin ew20b001

// it is a bit over complicated but I just wanted to practice as much as I can :)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct
{
    char *pointer;
    int length;
    int order
} word;

word store_word(int order, int max_word_length, char input_word[max_word_length]);
void store_word_in_dyn_array(word input_word_info, int word_nr, int *initial_size_pointer, word **words_dyn_array);
int count_words_array(word words_array[]);
char *get_word_by_pointer(bool all_lower, word *word_pointer);
void swap(word *el1, word *el2);
void sort_words_array(int f, int l, int words_count, word **words_dyn_array);
void sort_duplicate_words(int f, int l, int words_count, word **words_dyn_array);

int main()
{

    //** Variables **//
    int max_word_length = 63;
    char input_word[max_word_length];
    int initial_size = 6; // initial amount of words expected .. realloate if exceded (last test case)
    int words_counter = 0;
    word *words_dyn_array = (word *)malloc(initial_size * sizeof(word));

    //** input **//
    scanf("%s", &input_word);
    while (strcmp(input_word, ".") != 0)
    {

        // store the word and get it's info
        word input_word_info = store_word(words_counter, max_word_length, input_word);

        // store the word information in the words dynamic array
        store_word_in_dyn_array(input_word_info, words_counter, &initial_size, &words_dyn_array);

        // keep track of how many words are added
        words_counter++;

        // scan the next input
        scanf("%s", &input_word);
    };

    //** sorting (2 step sorting using 2 different sortings algorithms for practice) **//

    sort_words_array(0, words_counter - 1, words_counter, &words_dyn_array);
    sort_duplicate_words(0, words_counter - 1, words_counter, &words_dyn_array);

    //** Result and end **//
    for (int wrc = 0; wrc < words_counter; wrc++)
    {
        char *sdf = get_word_by_pointer(false, &words_dyn_array[wrc]);
        printf("%s\n", sdf);
    }
    free(words_dyn_array);
    return 0;
}

//****** Procedures ******//

word store_word(int order, int max_word_length, char input_word[max_word_length])
{
    char *stored_word = (char *)malloc((strlen(input_word) + 1) * sizeof(char));

    //stored_word = input_word; // BIG stupid mistake

    for (int s = 0; s < strlen(input_word); s++)
    {
        stored_word[s] = input_word[s];
    }
    stored_word[strlen(input_word) + 1] = '\0';

    word stored_word_info = {stored_word, strlen(stored_word), order};
    return stored_word_info;
}

void store_word_in_dyn_array(word input_word_info, int word_nr, int *initial_size_pointer, word **words_dyn_array)
{
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

// carefull!! this function stores the result in one place at the memory and returns a pointer to it so every time it is called the value will change
char *get_word_by_pointer(bool all_lower, word *word_pointer)
{

    word the_word = *word_pointer;
    char word_string[the_word.length];

    for (int i = 0; i <= the_word.length; i++)
    {

        word_string[i] = all_lower ? tolower(*(the_word.pointer + i)) : *(the_word.pointer + i);
    }

    return word_string;
}

void swap(word *el1, word *el2)
{
    word temp = *el1;
    *el1 = *el2;
    *el2 = temp;
}

// quick sort
void sort_words_array(int f, int l, int words_count, word **words_dyn_array)
{
    if (f < l)
    {

        //** "partition" function
        int i = f - 1;
        int p = l;
        char word_p[(*words_dyn_array)[p].length];
        strcpy(word_p, get_word_by_pointer(true, &(*words_dyn_array)[p]));

        for (int j = f; j < l; j++)
        {
            char word_j[(*words_dyn_array)[j].length];
            strcpy(word_j, get_word_by_pointer(true, &(*words_dyn_array)[j]));

            if (strcmp(word_j, word_p) < 0)
            {
                i++;
                swap(&(*words_dyn_array)[j], &(*words_dyn_array)[i]);
            }
        }
        i++;

        //** end "partition" function

        // place the pivot in its place
        swap(&(*words_dyn_array)[p], &(*words_dyn_array)[i]);

        // devide further
        sort_words_array(f, i - 1, words_count, &(*words_dyn_array));
        sort_words_array(i + 1, l, words_count, &(*words_dyn_array));
    }
}

// bubble sort || resort the duplicate words based on their original order to reach a stable result
void sort_duplicate_words(int f, int l, int words_count, word **words_dyn_array)
{
    int sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (int counter = 0; counter < words_count - 1; counter++)
        {
            char word_1[(*words_dyn_array)[counter].length];
            strcpy(word_1, get_word_by_pointer(true, &(*words_dyn_array)[counter]));
            int word_1_order = (*words_dyn_array)[counter].order;

            char word_2[(*words_dyn_array)[counter + 1].length];
            strcpy(word_2, get_word_by_pointer(true, &(*words_dyn_array)[counter + 1]));
            int word_2_order = (*words_dyn_array)[counter + 1].order;

            if (strcmp(word_1, word_2) == 0)
            {
                if (word_1_order > word_2_order)
                {
                    swap(&(*words_dyn_array)[counter], &(*words_dyn_array)[counter + 1]);
                    sorted = false;
                }
            }
        }
    }
}

//****** end Procedures ******//