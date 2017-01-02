//Commented lines will be added and tested wheni have access to cs50 dev environment

//#include <cs50.h>
#include <stdio.h>
#include <string.h>


int main(void)
{
    char name[] = "Zamyla Chan";   //remove this
    //string name = get_string();
    for (int i = 0, n = strlen(name); i < n; i++)
    {
      // if either first character or a character after a space, which isn't a space itself and is not first character, then print
      if ( i == 0 || ((i > 0 && name[i-1] == ' ') && name[i] != ' ')){
        printf("%c",name[i]);
      }
    }
    printf("\n");
}
