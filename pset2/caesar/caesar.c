//Commented lines will be added and tested wheni have access to cs50 dev environment

//#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//int main(int argc, string argv[])
int main(int argc, char *argv[])
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
    char p[] = "be sure to drink your Ovaltine";   //will remove this
    //string name = get_string();
    printf("\nciphertext: ");

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
