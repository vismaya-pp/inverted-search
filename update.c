#include "inverted.h"

int update_database(main_nd **hash,char *backupfile)
{
    // Open backup file in read mode
    FILE *fptr = fopen(backupfile,"r");
    
    // Check whether file opened successfully
    if(fptr == NULL)
    {
        printf("File cannot be opened\n");
        return FAILURE;
    }

    char str[200];

    // Read each record from backup file
    while(fscanf(fptr,"%s",str) != EOF)
    { 
        if(str[0] != '#') // Validate backup file format
        {
            printf("Invalid backup file\n");

            fclose(fptr);

            return FAILURE;
        }
        char *token;

        // Extract hash index
        token = strtok(str,"#;");
        int index = myatoi(token);

        // Extract word
        token = strtok(NULL,"#;");
        char word[50];
        strcpy(word,token);

        // Extract file count
        token = strtok(NULL,"#;");
        int file_count = myatoi(token);

        // Create main node for word
        main_nd *mainnode = create_mainnode(word);

        if(mainnode == NULL)
        {
            fclose(fptr);
            return FAILURE;
        }

          // Restore file count
        mainnode->file_count = file_count;

        sub_nd *head = NULL;
        sub_nd *tail = NULL;

        // Create sub nodes for each file
        for(int i=0; i < file_count; i++)
        {  
            // Extract file name
            token = strtok(NULL,"#;");

            char filename[30];
            strcpy(filename,token);

             // Extract word count
            token=strtok(NULL,"#;");

            int wordcount = myatoi(token);

            // Create sub node
            sub_nd *subnode = create_subnode(filename);

            if(subnode == NULL)
            {
                fclose(fptr);
                return FAILURE;
            }

            // Restore word count
            subnode->word_count = wordcount;

            // Store updated file names
            add_to_list(&updated_list,filename);

            // Connect sub nodes
            if(head == NULL)
            {
                head = subnode;
                tail = subnode;
            }
            else
            {
                tail->sublink = subnode;

                tail = subnode;
            }
        }

        // Attach sub list to main node
        mainnode->sublink = head;

        // Insert main node into hash table
        if(hash[index] == NULL)
        {
            hash[index] = mainnode;
        }
        else
        {
            main_nd *temp = hash[index];

            // Move to last main node
            while(temp->mainlink != NULL)
            {
                temp = temp->mainlink;
            }
             // Attach new main node
            temp->mainlink = mainnode;
        }
    }

    // Close backup file
    fclose(fptr);

   // Database updated successfully
    return SUCCESS;
}