#include "inverted.h"

int create_database(int size, Slist *files)
{
    if(files == NULL)// Check if file list is empty
    {
        return FAILURE;
    }

    Slist *temp = files;
    char word[50];

    // Process each file in the file list
    for(int i=0; i < size; i++)
    { 
        FILE *fptr = fopen(temp->file,"r"); // Open current file

        if(fptr == NULL)
        {
            return FAILURE;
        }

        while(fscanf(fptr,"%s",word) != EOF) // Read words one by one from file
        { 
            // Calculate hash index using first character
            int index = my_to_lower(word[0])-97;
 
            if(index < 0 || index > 25)  // Store non-alphabetic words in index 26
            {
                index=26;
            }

            if(hash[index] == NULL) // If no main node exists at hash index
            {  
                // Create main node for word
                main_nd *mainnode = create_mainnode(word);

                if(mainnode == NULL)
                {
                    fclose(fptr);
                    return FAILURE;
                }

                // Create sub node for file
                sub_nd *subnode = create_subnode(temp->file);

                if(subnode == NULL)
                {
                    fclose(fptr);
                    return FAILURE;
                }

                mainnode->sublink = subnode; // Link sub node to main node

                hash[index] = mainnode; // Insert main node into hash table
            }

            else
            {
               // Traverse main node list
                main_nd *temp1 = hash[index];
                main_nd *prev1 = NULL;

                int found = 0;

                while(temp1 != NULL)
                { 
                    if(strcmp(temp1->word, word) == 0)  // Check whether word already exists
                    {
                        found = 1 ;
                        break;
                    }
                    prev1 = temp1;
                    temp1 = temp1->mainlink;
                }

                if(found == 0) // Word not found, create new main node
                {  
                    main_nd *mainnode = create_mainnode(word);

                    if(mainnode == NULL)
                    {
                        fclose(fptr);
                        return FAILURE;
                    }
                    // Create sub node for current file
                    sub_nd *subnode = create_subnode(temp->file);

                    if(subnode == NULL)
                    {
                        fclose(fptr);
                        return FAILURE;
                    }
 
                    mainnode->sublink = subnode; // Link sub node to main node

                    prev1->mainlink = mainnode; // Append main node to list
                }

                else
                {
                    // Traverse sub node list
                     sub_nd *temp2 = temp1->sublink;
                     sub_nd *prev2 = NULL;

                    int sub_found = 0;

                    while(temp2 != NULL)
                    {
                        // Check if file already exists
                        if(strcmp(temp2->file_name,temp->file) == 0)
                        {   
                            temp2->word_count++; // Increment word count

                            sub_found = 1;
                            break;
                        }

                        prev2 = temp2;
                        temp2 = temp2->sublink;
                    }

                    // File not found in sub list
                    if(sub_found == 0)
                    {   
                        // Create new sub node                     
                        sub_nd *subnode = create_subnode(temp->file);

                        if(subnode==NULL)
                        {
                            fclose(fptr);
                            return FAILURE;
                        }
                       
                        prev2->sublink = subnode; // Append sub node
                        
                        temp1->file_count++; // Increment file count
                    }
                }
            }
        }

        // Close file
        fclose(fptr);

        temp = temp->link;  // Move to next file
    }
     // Database creation successful
    return SUCCESS;
}