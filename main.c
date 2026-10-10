#include "inverted.h"

// Global linked lists
Slist *file_list = NULL;       // Stores input files
Slist *updated_list = NULL;    // Stores updated files
Slist *unique_list = NULL;     // Stores unique files

//Global countters
int count = 0;
int updated_count = 0;


main_nd *hash[27] = {NULL};  //Hash table initialization

int main(int argc, char *argv[])
{
    char word[50];
    char file[30];
    char backupfile[30];

    // Flags to track database status
    int create_flag = 0;
    int update_flag = 0;

    // Validate command-line arguments and store files
    validation(argc, argv);

    // Display stored files
    printf("Files Stored are:\n");
    print_list(file_list);

     // Display total number of valid files
    printf("Number of Files Stored Successfully : %d\n",count);

    int choice;

    while(1)
    {
        // Display menu
        printf("\n");
        printf("1.Create Database\n");
        printf("2.Display Database\n");
        printf("3.Search Database\n");
        printf("4.Save Database\n");
        printf("5.Update Database\n");
        printf("6.Exit\n");

        printf("Enter your choice : ");  //Read from user
        scanf("%d",&choice);

        switch(choice)
        {
            
            case 1: 
                if(create_flag) // Check if database is already created
                {
                    printf("Database Already Created\n");
                    break;
                }

                
                if(update_flag == 0) // Create database from original files
                {
                    if(create_database(count,file_list) == SUCCESS)
                    {
                        create_flag = 1;
                        printf("Database Created Successfully\n");
                    }
                    else
                    {
                        printf("Database Creation Failed\n");
                    }
                }
                else // Create database using updated files
                { 
                    updated_count=updatedd_list(&file_list,&updated_list,&unique_list);

                    if(create_database(updated_count,unique_list) == SUCCESS)
                    {
                        create_flag=1;
                        printf("Database Created Successfully\n");
                    }
                }

                break;

            case 2:
                // Display database contents
                display_database(hash);
                break;

            
            case 3:
                // Search for a word in database
                printf("Enter word : ");
                scanf("%s",word);

                search_word(hash,word);
                break;

            case 4:
                // Get backup file name
                printf("Enter backup filename : ");
                scanf("%s",file);

                 // Check file extension
                char *extension = strrchr(file,'.');

                if(extension && strcmp(extension,".txt")==0)
                {
                    // Save database to backup file
                    save_database(hash,file);

                    printf("Database saved successfully\n");
                }
                else
                {
                    printf("File extension should be .txt\n");
                }
                 break;

            case 5:
               // Update not allowed after database creation
                if(create_flag)
                {
                    printf("Update not possible after create\n");
                    break;
                }
  
                if(update_flag) // Prevent multiple updates
                {
                    printf("Database already updated\n");
                    break;
                }
                 // Get backup file name
                printf("Enter backup filename : ");
                scanf("%s",backupfile);

                // Check file extension
                char *ext = strrchr(backupfile,'.');
 
                if(ext && strcmp(ext,".txt") == 0)
                {
                     // Update database from backup file
                    if(update_database(hash,backupfile)== SUCCESS)
                    {
                        printf("Updated files:\n");

                        // Display updated file list
                        print_list(updated_list);

                        update_flag = 1;

                        printf("Database updated successfully\n");
                    }
                    else
                    {
                        printf("Update failed\n");
                    }
                }
                else
                {
                    printf("File extension should be .txt\n");
                }

                break;
            
            case 6:

                printf("Exiting...\n");
                exit(0);

            default:
            // Handle invalid menu choice
            printf("Invalid choice\n");
        }
    }

    return 0;
}