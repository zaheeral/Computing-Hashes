#include <stdio.h>
#include <stdlib.h>


// Hash manipulation functions in hash_functions.c
void hash(char *hash_val, long block_size);
int check_hash(const char *hash1, const char *hash2, long block_size);

#ifndef MAX_BLOCK_SIZE
    #define MAX_BLOCK_SIZE 1024
#endif

/* Converts hexstr, a string of hexadecimal digits, into hash_val, an an array of char.
 * Each pair of digits in hexstr is converted to its numeric 8-bit value and stored in
 * an element of hash_val.
 * Preconditions: 
 *    - hash_val must have enough space to store block_size elements
 *    - hexstr must be block_size * 2 characters in length
 */

void xstr_to_hash(char *hash_val, char *hexstr, int block_size) {
    for(int i = 0; i < block_size*2; i += 2) {
        char str[3];
        str[0] = hexstr[i];
        str[1] = hexstr[i + 1];
        str[2] = '\0';
        hash_val[i/2] = strtol(str, NULL, 16);
    }
}

/* Print the values of the char array hash_val in hex
 * Note that each char (8 bits) corresponds to two digits in hex (4 bits per digit)
 * In case you are wondering about the %.2hhx in printf:
 * -- The 2 makes sure that for each char always two digits are printed in hex notation, so that for example
 * for a '\0' (all bits in the byte are zero) two zeros are printed in hex notation, rather than one.
 * -- The hh makes sure that printf treats the char properly, since %x by default expects an int.
 */

void show_hash(char *hash_val, long block_size) {
    for(int i = 0; i < block_size; i++) {
        printf("%.2hhx ", hash_val[i]);
    }
    printf("\n");
}


int main(int argc, char **argv) {
    char hash_val[MAX_BLOCK_SIZE] = {'\0'};
    long block_size;

    char *ptr;
    char *COMPARISON_HASH;

    //array null characters max size 1024
    char array[1024] = {'\0'};


    if (argc <= 1 || argc > 3)
    {
        /* code */
        printf("Usage: compute_hash BLOCK_SIZE [ COMPARISON_HASH ]\n");
        return 0;
    }else{
        block_size = strtol(argv[1], &ptr, 10);
    }
    

    if (block_size <= 0 || block_size > MAX_BLOCK_SIZE)
    {
        /* code */

        printf("The block size should be a positive integer less than %d.\n", MAX_BLOCK_SIZE);
        return 0;
    }

    if (argc == 3)
    {
        COMPARISON_HASH = &(argv[2][0]);

        xstr_to_hash(array, COMPARISON_HASH, block_size);
        check_hash(array, hash_val, block_size);
    }

    hash(hash_val, block_size);
    show_hash(hash_val, block_size);

    return 0;
}