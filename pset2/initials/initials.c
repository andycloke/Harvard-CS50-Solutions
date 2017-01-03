#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string name = get_string();
    for (int i = 0, n = strlen(name); i < n; i++)
    {
      // if either first character or a character after a space, which isn't a space itself and is not first character, then print
      if ((i == 0 && isalpha(name[i])) || ((i > 0 && name[i-1] == ' ') && name[i] != ' ' )){
        printf("%c",toupper(name[i]));
      }
    }
    printf("\n");
}
