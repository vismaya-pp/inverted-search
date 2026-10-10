#include "inverted.h"

// Convert uppercase character to lowercase
int my_to_lower(char ch)
{
    if(ch >= 'A' && ch <= 'Z')
    {
        return ch + 32;
    }
    return ch;
}

// Create and initialize a main node
main_nd *create_mainnode(char *str)
{
    main_nd *mainnode = malloc(sizeof(main_nd));

     // Check memory allocation
    if(mainnode == NULL)
    {
        return NULL;
    }

    // Store word in main node
    strcpy(mainnode->word,str);

    // Initialize main node fields
    mainnode->file_count = 1;
    mainnode->sublink = NULL;
    mainnode->mainlink = NULL;

    return mainnode;
}

// Create and initialize a sub node
sub_nd *create_subnode(char *str)
{
    sub_nd *subnode = malloc(sizeof(sub_nd));

    // Check memory allocation
    if(subnode == NULL)
    {
        return NULL;
    }
    
    // Store file name
    strcpy(subnode->file_name,str);

     // Initialize sub node fields
    subnode->word_count = 1;
    subnode->sublink = NULL;

    return subnode;
}

// Convert string to integer
int myatoi(char *str)
{
    int i=0;
    int sum=0;

     // Traverse string
    while(str[i]!='\0')
    {  
         // Convert digit characters to integer
        if(str[i] >= '0' && str[i] <= '9')
        {
            sum = sum*10+(str[i]-'0');
        }
        i++;
    }
    return sum;
}

// Add file to updated list if not already present
void add_to_list(Slist **updated_list,const char *file_name)
{
    Slist *temp = *updated_list;

    // Check for duplicate file
    while(temp != NULL)
    {
        if(strcmp(temp->file, file_name)==0)
        {
            return;
        }
        temp = temp->link;
    }

    // Create new node
    Slist *newnode = malloc(sizeof(Slist));

    if(newnode == NULL)
    {
        return;
    }
    strcpy(newnode->file,file_name);

    newnode->link = NULL;

    // Insert as first node
    if(*updated_list == NULL)
    {
        *updated_list = newnode;
    }
    else
    {
        // Traverse to last node
        temp = *updated_list;

        while(temp->link != NULL)
        {
            temp = temp->link;
        }

        // Attach new node
        temp->link = newnode;
    }
}

// Create a new linked list node
Slist *create_node(const char *file)
{
    Slist *newnode = malloc(sizeof(Slist));

    // Check memory allocation
    if(newnode == NULL)
    {
        return NULL;
    }

    strcpy(newnode->file,file); // Store file name

    newnode->link = NULL;

    return newnode;
}

// Add node at end of linked list
void add_node(Slist **head,const char *file)
{
    // Create new node
    Slist *newnode = create_node(file);

    if(newnode == NULL)
    {
        return;
    }

    if(*head == NULL) // Insert as first node
    {
        *head = newnode;

        return;
    }

    Slist *temp = *head;  // Traverse to last node

    while(temp->link)
    {
        temp = temp->link;
    }
    temp->link = newnode; // Attach new node
}

// Check whether file exists in linked list
int exists_in_list(Slist *head,const char *file)
{
    while(head)
    {
        // Compare file names
        if(strcmp(head->file,file) == 0)
        {
            return 1;
        }
        head = head->link;
    }

    return 0;
}

// Create list of files not present in updated list
int updatedd_list(Slist **list1,Slist **list2,Slist **unique_list)
{
    int count = 0;

    Slist *temp = *list1;

    // Traverse original file list
    while(temp)
    {
       
        // Check whether file is unique
        if(!exists_in_list(*list2, temp->file) && !exists_in_list(*unique_list,temp->file))
        {
            // Add unique file to list
            add_node(unique_list,temp->file);

            count++;
        }

        temp = temp->link;
    }

    return count;
}