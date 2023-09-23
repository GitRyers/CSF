#include <stdio.h>
#include <stdint.h>
#include "wcfuncs.h"

// Suggested number of buckets for the hash table
#define HASHTABLE_SIZE 13249

void process_input_word(struct WordEntry *buckets[], unsigned char *word, uint32_t *unique_words, const unsigned char **best_word, uint32_t *best_word_count);

int main(int argc, char **argv) {
  // stats (to be printed at end)
  uint32_t total_words = 0;
  uint32_t unique_words = 0;
  const unsigned char *best_word = (const unsigned char *) "";
  uint32_t best_word_count = 0;

    FILE *file;
    file = stdin;

    // Initializing the hash table
    // Will have arrays, each entry is a bucket
    // Bucket points to list of words (hashed same value)
    // All buckets will start empty

    struct WordEntry *buckets[HASHTABLE_SIZE];
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        buckets[i] = NULL;
    }

    // Opens file for reading, can't use "read"

    if (argc == 2) {
        file = fopen(argv[1], "r");

        if (file == NULL) {
            perror("Error opening provided file");
            return 1;
        }
    }

    // Hold word that is being processed
    unsigned char word[MAX_WORDLEN + 1];

    // If word read from file, keep iterating
    while (wc_readnext(file, word)) {
        // Increase total word count
        total_words++;

        // Converts words to lower case and non alpha
        // We want words to be case insensitive??
        // non alpha means Cat & Cat! are same word
        wc_tolower(word);
        wc_trim_non_alpha(word);

        // Adds the word to our hash table
        // Updates unique word count & most frequent word stats
        process_input_word(buckets, word, &unique_words, &best_word, &best_word_count);
    }

  printf("Total words read: %u\n", (unsigned int) total_words);
  printf("Unique words read: %u\n", (unsigned int) unique_words);
  printf("Most frequent word: %s (%u)\n", (const char *) best_word, best_word_count);

  // TODO: make sure file is closed (if one was opened)
  // TODO: make sure memory is freed

  return 0;
}

// TODO: definitions of helper functions
