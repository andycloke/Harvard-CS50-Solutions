#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, string argv[])
{
  if (argc != 2)
  {
    printf("Error: vigenere should be called with 1 command line argument\n");
    return 1;
  }
  else
  {
    // length of keyword
    int l = strlen(argv[1]);

    // check that command line keyword only contains letters
    for (int i = 0; i < l; i++)
    {
        if (isalpha( argv[1][i]) == false)
        {
            printf("Error: keyword must contain only alphabetical characters\n");
            return 1;
        }
    }

    // get plaintext from user
    printf("plaintext: ");
    string p = get_string();

    // go to newline and ready output for ciphertext
    printf("ciphertext: ");

    for (int i = 0, j = 0, n = strlen(p); i < n; i++){

      // get character from keyword, and wrap around if plaintext is longer than keyword
      // j is used to avoid incrementing the keyword character used when enciphering non-alphabetical characters
      char k = argv[1][j % l];

      // shift k so that 'A' or 'a' is 0. we know k is an alphabetical character
      if (isupper(k))
      {
        k = k - 'A';
      }
      else
      {
        k = k - 'a';
      }
      //encipher
      if (isupper(p[i]))
      {
        printf("%c",(((p[i] - 'A') + k) % 26) + 'A');
        j++;
      }
      else if (islower(p[i]))
      {
        printf("%c",(((p[i] - 'a') + k) % 26) + 'a');
        j++;
      }
      else
      {
        printf("%c",p[i]);
      }
    }
    printf("\n");
    return 0;

  }
}
