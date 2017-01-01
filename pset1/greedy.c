#include <cs50.h>
#include <stdio.h>

int main(void)
{
  do
  {
    printf("Change required: ");
    float change = get_loat();
  }
  while (change < 0);

  int coinsRequired = 0;

  while(change > 0.00)
  {
    if (change >= 0.25)
    {
      change = change - 0.25;
      coinsRequired = coinsRequired + 1;
    }
    else if (change >= 0.10)
    {
      change = change - 0.10;
      coinsRequired = coinsRequired + 1;
    }
    else if (change >= 0.05)
    {
      change = change - 0.05;
      coinsRequired = coinsRequired + 1;
    }
    else
    {
      change = change - 0.01;
      coinsRequired = coinsRequired + 1;
    }
  }
  printf("%i\n",coinsRequired);
}
