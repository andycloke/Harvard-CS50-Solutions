#include <cs50.h>
#include <stdio.h>

int main(void)
{
  printf("Minutes: ");
  int minutes = get_int();
  printf("Bottles: %i", minutes*12);
}
