#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, string argv[])
{
  if (argc != 2)
  {
    printf("Error: caesar should be called with 1 command line argument\n");
    return 1;
  }
  else
  {
    //convert key to int and wrap it around
    int k = atoi(argv[1]) % 26;
    //get plaintext from user
    printf("plaintext: ");
    string p = get_string();
    
    printf("ciphertext: ");

    for (int i = 0, n = strlen(p); i < n; i++){
      //encipher
      if (isupper(p[i]))
      {
        printf("%c",(((p[i] - 'A') + k) % 26) + 'A');
      }
      else if (islower(p[i]))
      {
        printf("%c",(((p[i] - 'a') + k) % 26) + 'a');
      }

      // deal with non alphabetical symbols
      else
      {
        printf("%c",p[i]);
      }
    }
    printf("\n");
    return 0;
  }
}
