#include <cs50.h>
#include <stdio.h>

int main(void)
{
  int height;
  do
  {
    printf("Height: ");
    height = get_int();
  }
  while (height < 0 || height > 23);
  if (height == 0)
  {
    printf("");
  }
  else
  {
    for (int i = 1; i <= height; i++)   //row number
    {
      for(int j = 1; j <= height-i; j++)   //leading spaces
      {
        printf(" ");
      }
      for(int h = 1; h <= i; h++)
      {
        printf("#");    //left hand pyramid
      }
      printf("  ");      //middle space
      for(int h = 1; h <= i; h++)
      {
        printf("#");   // right hand pyramid
      }
      printf("\n");
    }
}
}
