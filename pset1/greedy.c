#include <cs50.h>
#include <stdio.h>

int main(void)
{
  float change;
  do
  {
    printf("Change required: ");
    change = get_float();
  }
  while (change < 0.00);

  int coinsRequired = 0;

  while (change >= 0.25)
  {
    change = change - 0.25;
    coinsRequired = coinsRequired + 1;
  }
  while (change >= 0.10)
  {
    change = change - 0.10;
    coinsRequired = coinsRequired + 1;
  }
  while (change >= 0.05)
  {
    change = change - 0.05;
    coinsRequired = coinsRequired + 1;
  }
  while (change > 0.00)
  {
    change = change - 0.01;
    coinsRequired = coinsRequired + 1;
  }
  printf("%i\n",coinsRequired);
}
