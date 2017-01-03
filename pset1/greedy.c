#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
  float change, rounded;
  // get user input
  do
  {
    printf("Change required: ");
    change = get_float();
  }
  while (change < 0.00);
  
  //round user input
  rounded =  roundf(change * 100); 
  
  //counter
  int coinsRequired = 0;
  
  
    while (rounded >= 25)
    {
      rounded = rounded - 25;
      coinsRequired = coinsRequired + 1;
    }
    while (rounded >= 10)
    {
      rounded = rounded - 10;
      coinsRequired = coinsRequired + 1;
    }
    while (rounded >= 5)
    {
      rounded = rounded - 5;
      coinsRequired = coinsRequired + 1;
    }
    while (rounded > 0)
    {
      rounded = rounded - 1;
      coinsRequired = coinsRequired + 1;
    }
  printf("%i\n",coinsRequired);
}
