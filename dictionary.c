// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 143091;

// Hash table
node *table[N];

// Word Count
unsigned int wordCount = 0;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *sourse = fopen(dictionary, "r");
    if (sourse == NULL)
    {
        return false;
    }

    char buffer[LENGTH + 1];

    while (fscanf(sourse, "%s", buffer) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, buffer);
        unsigned int index = hash(n->word);

        n->next = table[index];
        table[index] = n;
        wordCount++;
    }

    fclose(sourse);
    return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int length = strlen(word);
    int hash = 3;

    for (int i = 0; i < length; i++)
    {
        hash = (hash << 3) + (int) toupper(word[i]);
        hash %= 143091;
    }

    return hash;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordCount;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    node *cursor;

    cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor;
        node *tmp;
        cursor = table[i];

        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
