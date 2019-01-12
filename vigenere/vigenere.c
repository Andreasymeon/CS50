#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, string argv[])
{
    // get key from user in commmand line argument or return error
    if (argc !=2)
    {
        printf("Usage: ~/cs50/pset2/vigenere <keyword>\n");
        return 1;
    }
    // iterate over each characters in string to check if argv is alpha or return error
    else
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (!isalpha (argv[1][i]))
            {
                printf("error <keyword> must be a word\n");
                return 1;
            }
        }
    }
    //get user's text to encrypt
    printf("plaintext:");
    string text = get_string();

    //store argv keyword
    string kword = argv[1];

    printf("ciphertext:");

    for (int i = 0, k_index = 0, n = strlen(text); i < n; i++)
    {
        //define length of keyword
        //keep track of position in keyword and wrap around keyword until text is finish
        //formula to get the numerical key (btween 0 and 25) for each letter in kword and lower char that would be upper case
        int k_length = strlen(kword);
        int wrap = k_index % k_length;
        int key_letter = tolower (kword[wrap]) - 'a';

        // encipher text only if case is alpha
        if (isalpha(text[i]))
        {
            //each letter in text is shifted by appropriate key in kword to get the enciphered letter
            if (isupper(text[i]))
            {
                int encipher = (text[i] + key_letter - 'A') % 26 + 'A';
                k_index++;
                printf("%c", encipher);
            }
            if (islower(text[i]))
            {
                int encipher = (text[i] + key_letter - 'a') % 26 + 'a';
                k_index++;
                printf("%c", encipher);
            }
        }
        // print non alpha case in text as it is
        else
        {
           printf("%c", text[i]);
        }
    }
    //print a new-line
    printf("\n");

    return 0;
}
