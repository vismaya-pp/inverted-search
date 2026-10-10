#include "inverted.h"

void search_word(main_nd **hash,char *word)
{
    int index;
    // Calculate hash index using first character
    index = my_to_lower(word[0]) - 97;

    if(index < 0 || index > 25) // Use index 26 for non-alphabetic characters
    {
        index = 26;
    }

    // Check whether hash index is empty
    if(hash[index] == NULL)
    {
        printf("Word not found\n");
        return;
    }

    // Traverse main node list
    main_nd *temp = hash[index];

    while(temp != NULL)
    { 
        if(strcmp(temp->word,word) == 0) // Check whether word matches
        {
            printf("\nWord found successfully\n");

            printf("--------------------------------------\n"); 

            // Display word information
            printf("Word : %s\n",temp->word);

            printf("File count : %d\n",temp->file_count);

            sub_nd *temp1 = temp->sublink; // Traverse sub node list

            while(temp1 != NULL)
            {
                // Display file name and word count
                printf("File Name : %s\n",temp1->file_name);

                printf("Word Count : %d\n",temp1->word_count);

                printf("\n");

                temp1 = temp1->sublink;
            }
            // Word found, exit function 
            return;
        } 
        temp = temp->mainlink;
    }
    // Word not present in database
    printf("Word not found\n");
}