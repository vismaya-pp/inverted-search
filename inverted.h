#ifndef INVERTED_H
#define INVERTED_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define SUCCESS 1
#define FAILURE 0

// Sub node structure to store file information
typedef struct sub_node
{
    int word_count;             // Number of occurrences of word in file
    char file_name[30];         // File name
    struct sub_node *sublink;   // Pointer to next sub node

}sub_nd;

// Main node structure to store word information
typedef struct main_node
{
    char word[50];               // Word stored in database
    int file_count;              // Number of files containing the word
    sub_nd *sublink;             // Pointer to sub node list
    struct main_node *mainlink;  // Pointer to next main node

}main_nd;

// Singly linked list to store file names
typedef struct single
{
    char file[30];               // File name
    struct single *link;         // Pointer to next node

}Slist;

// Global linked list declarations
extern Slist *file_list;         // Original input file list
extern Slist *updated_list;      // Files restored from backup
extern Slist *unique_list;       // Unique files for database creation

// Global counters
extern int count;           // Total valid files
extern int updated_count;   // Total unique files after update

// Hash table declaration
extern main_nd *hash[27];

/* validation */

void validation(int,char *[]);  // Validate input files
int check_extension(char *);  // Check file extension
int check_list(char *,Slist *); // Check duplicate files
int insert_at_last(char *,Slist **); // Insert file into linked list
void print_list(Slist *); // Display file list

/* database */

int create_database(int,Slist *);// Create inverted search database
void display_database(main_nd **); // Display database contents

void search_word(main_nd **,char *);// Search word in database
void save_database(main_nd **,char *); // Save database into backup file
int update_database(main_nd **,char *); //Restore database from backup file

/* utility */

int my_to_lower(char); // Convert uppercase character to lowercase
int myatoi(char *); // Convert string to integer

main_nd *create_mainnode(char *);// Create main node
sub_nd *create_subnode(char *);// Create sub node

void add_to_list(Slist **,const char *); // Add file to updated list

// Generate unique file list
int updatedd_list
(
Slist **,
Slist **,
Slist **
);

int exists_in_list(Slist *,const char *); // Check file existence in list
void add_node(Slist **,const char *); // Add node at end of list
Slist *create_node(const char *); // Create linked list node

#endif