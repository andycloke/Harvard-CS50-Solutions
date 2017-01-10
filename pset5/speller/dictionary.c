/**
 * Implements a dictionary's functionality.
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// hash table size = 2^16
const int HASHTABLE_SIZE = 65536;

// define linked list node
typedef struct node
{
    char word[LENGTH+1];
    struct node *next;
} node;

// initialise hash table
node *hash_table[HASHTABLE_SIZE];

/**
* Returns integer hash value for a given a string
* https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/cf9nlkn/
**/
int hash(const char* needs_hashing)
{
    unsigned int hash = 0;
    for (int i=0, n=strlen(needs_hashing); i<n; i++)
        hash = (hash << 2) ^ needs_hashing[i];
    return hash % HASHTABLE_SIZE;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{

    // initialise lower case word
    char lcword[LENGTH+1];

    // convert to lowercase, as we need this to lookup. TODO: change from length to length of word
    for (int i = 0; i < LENGTH; i++)
    {
        lcword[i] = tolower(word[i]);
    }

    // set cursor to start of appropriate lined list
    node *cursor = hash_table[hash(lcword)];


    // traverse list
    while (cursor != NULL)
    {
        // check node's word to see if it is target word, ignoring case
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // initialise word
    char word[LENGTH+1];

    // open dictionary
    FILE *dicptr = fopen(dictionary, "r");

    // iterate through dictionary words
    while (fscanf(dicptr, "%s", word) != EOF)
    {
        // make a new word.
        node *new_node = malloc(sizeof(node));

        // check for error assigning memory
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        else
        {
            // copy word into node
            strcpy(new_node->word, word);

            // use hash function to determine which bucket (linked list) to insert word into
            int n = hash(new_node->word);

            // insert into list
            new_node->next = hash_table[n];
            hash_table[n] = new_node;
        }
    }
    // close dictionary
    fclose(dicptr);

    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // dictionary size counter
    int counter = 0;

    // iterate through hashtable
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        // set pointer to head of list
        node *cursor = hash_table[i];

        // traverse list
        while (cursor != NULL)
        {
            counter++;
            cursor = cursor->next;
        }
    }
    return counter;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // iterate through hashtable
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        // set pointer to head of list
        node *cursor = hash_table[i];

        // traverse list
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        free(cursor);
    }
    return true;
}
