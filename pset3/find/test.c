#include <stdio.h>
//used to test as I don't currently have cs50 ide

int main(void){
  int values[] = {3,6,1,1,3};   //input values to be sorted
  int n = 5;    //length of values
  // get max value in array
  int max = 0;
  for (int i = 0; i < n; i++)
  {
    if (values[i] > max)
    {
      max = values[i];
    }
  }
  //declare a count array to store count of each number. initialise each count to 0
  int count[max+1];
  for (int i = 0; i <= max; i++)
  {
    count[i] = 0;
  }
  //store count of each number in indice equal to that number
  for (int i = 0; i < n; i++)
  {
    count[values[i]]++;
  }
  //replace each count with indices required to store it
  int total = 0;
  for (int i = 0; i <= max; i++)
  {
    if (count[i] != 0)
    {
      total += count[i];
      count[i] = total;
    }
  }
  int output[n];
  for (int i = 0; i < n; i++)
  {
    output[count[values[i]]-1] = values[i];
    count[values[i]]--;
  }
  for (int i = 0; i < n; i++)
  {
    printf("%i,",output[i]);
  }
printf("\n");
}
