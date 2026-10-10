#include "inverted.h"

// Validate command line arguments and store valid files
void validation(int argc, char *argv[])
{ 
    // Traverse all command line files
    for(int i=1; i < argc; i++)
    {
        if(check_extension(argv[i]) == SUCCESS) // Check file extension
        { 
            FILE *fptr = fopen(argv[i],"r"); // Open file in read mode

            if(fptr != NULL)
            { 
                fseek(fptr,0,SEEK_END); // Move file pointer to end of file

                if(ftell(fptr) != 0) // Check whether file is empty
                {
                    fclose(fptr);

                    // Check for duplicate files
                    if(check_list(argv[i],file_list) == SUCCESS)
                    { 

                        // Insert file into linked list
                        if(insert_at_last(argv[i],&file_list) == SUCCESS)
                        {
                            printf("%s Stored Successfully\n",argv[i]);
 
                            count++;
                        }
                        else
                        {
                            printf("Failed to Store File\n");
                        }
                    }
                    else
                    { 
                        printf("%s Is Duplicate file, Skipping...\n",argv[i]);
                    }
                }
                else
                {
                    fclose(fptr);
 
                    printf("%s File is Empty\n",argv[i]);
                }
            }
            else
            {
                printf("%s File not Found\n",argv[i]);
            }
        }
        else
        { 
            printf("%s Does not have .txt Extension\n",argv[i]);
        }
    }
}

// Check whether file has .txt extension
int check_extension(char *str)
{
    char *extension = strrchr(str,'.');

    if(extension != NULL && strcmp(extension,".txt") == 0)
    {
        return SUCCESS;
    }
    return FAILURE;
}

// Check whether file already exists in list
int check_list(char *str,Slist *file_list)
{
    Slist *temp = file_list;

    while(temp != NULL)
    {
        // Compare file names
        if(strcmp(temp->file,str) == 0)
        {
            return FAILURE;
        }

        temp = temp->link;
    }
    return SUCCESS;
}

// Insert file name at end of linked list
int insert_at_last(char *str,Slist **file_list)
{
    Slist *newnode = malloc(sizeof(Slist)); // Create new node

    if(newnode == NULL)
    {
        return FAILURE;
    }

    strcpy(newnode->file,str); // Store file name

    newnode->link = NULL;

    if(*file_list == NULL) // Insert as first node
    {
        *file_list = newnode;

        return SUCCESS;
    }

    Slist *temp = *file_list; // Traverse till last node

    while(temp->link != NULL)
    {
        temp = temp->link;
    }
    temp->link = newnode; // Attach new node

    return SUCCESS;
}

// Display all files in linked list
void print_list(Slist *head)
{
    if(head == NULL) // Check for empty list
    {
        printf("List Empty\n");
        return;
    }

    // Traverse and print file names
    while(head)
    {
        printf("%s\n",head->file);

        head = head->link;
    }
}