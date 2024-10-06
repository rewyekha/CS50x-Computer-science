// Implements a dictionary's functionality
#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1000; // Increased number of buckets for better distribution

// Hash table
node *table[N];

// Global variable to keep track of the number of words
unsigned int word_count = 0;

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int hash = 0;
    while (*word)
    {
        hash = (hash << 2) ^ *word; // Bit shifting and XORing
        word++;
    }
    return hash % N; // Ensure the index is within the bounds of the table size
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false; // File could not be opend
    }

    // Initialize the hash table to NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Read each word from the file
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create a new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(file);
            unload(); // Free any memory already allocated

            return false;
        }

        // Copy the word into the new node
        strcpy(new_node->word, word);
        new_node->next = NULL;

        // Hash the word to determine the index
        unsigned int index = hash(word);

        // Insert the new node into the hash table
        new_node->next = table[index];
        table[index] = new_node;

        // Increment the word count
        word_count++;
    }
    fclose(file);

    return true; // Dic successfully loaded
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count; // return the number of words
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO: Create a copy of the word to work with (in case it's altered)
    char lowercase_word[LENGTH + 1];
    int i = 0;
    // Convert word to lowercase
    while (word[i] != '\0')
    {
        lowercase_word[i] = tolower(word[i]);
        i++;
    }
    lowercase_word[i] = '\0'; // NULL - terminate the string

    // Hash the lowercase word to find the appropriate bucket]
    unsigned int index = hash(lowercase_word);

    // Traverse the linked list at that index
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcmp(cursor->word, lowercase_word) == 0)
        {
            return true; // Word found
        }
        cursor = cursor->next; // Move to the next node
    }

    return false;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO : Iterate over each bucket
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp); // Free the current node
        }
    }

    return true;
}
