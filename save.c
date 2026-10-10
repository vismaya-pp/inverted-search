#include "inverted.h"

void save_database(main_nd **hash,char *file)
{
    // Open backup file in write mode
    FILE *fptr = fopen(file,"w");

    // Check whether file opened successfully
    if(fptr == NULL)
    {
        printf("Unable to Open File\n");
        return;
    }
    for(int i=0; i < 27; i++) // Traverse all hash table indices
    { 
        if(hash[i] == NULL) // Skip empty indices
        {
            continue;
        }

        // Traverse main node list
        main_nd *temp = hash[i];

        while(temp != NULL)
        { 
            // Write index, word, and file count
            fprintf(fptr,"#%d;%s;%d",i,temp->word,temp->file_count);
 
            sub_nd *temp2 = temp->sublink; // Traverse sub node list

            while(temp2 != NULL)
            {   
                // Write file name and word count
                fprintf(fptr,";%s;%d",temp2->file_name,temp2->word_count);

                temp2 = temp2->sublink;
            }

            fprintf(fptr,"#\n"); // Mark end of record

            temp = temp->mainlink;  // Move to next main node
        }
    }

    fclose(fptr);  // Close backup file

    printf("Database Saved Successfully\n");
}