#include "inverted.h"

// Function to display database contents
void display_database(main_nd **hash)
{
    printf("\n");

    // Print table heading
    printf("%-10s %-15s %-12s %-20s %-10s\n",
            "Index","Word","Filecount","Filename","Wordcount");

    printf("--------------------------------------------------------------------------\n");

    for(int i=0; i < 27; i++) // Traverse all hash table indices
    {
        if(hash[i] == NULL) // Skip empty indices
        {
            continue;
        }

        main_nd *temp = hash[i]; // Traverse main node list

        while(temp != NULL)
        {  
            // Point to first sub node
            sub_nd *temp1 = temp->sublink;

            // Flag to print main node details only once
            int first = 1;
 
            while(temp1 != NULL) // Traverse sub node list
            {
                // Print main node details for first sub node
                if(first)
                {    
                    printf("%-10d %-15s %-12d",i,temp->word,temp->file_count);

                    first = 0;
                }
                else
                { 
                    // Leave main node columns blank for remaining sub nodes
                    printf("%-10s %-15s %-12s","","","");
                }

                  // Print file name and word count
                printf("%-20s %-10d\n",temp1->file_name,temp1->word_count);

                // Move to next sub node
                temp1 = temp1->sublink;
            }
            // Move to next main node
            temp = temp->mainlink;
        }
    }
}