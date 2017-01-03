/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n <= 0)
    {
      return false;
    }

    int start = 0, end = n-1, middle;
    
    while (start <= end)
    {
      middle = (start + end)/2;
      if (values[middle] ==  value)
      {
        return true;
      }
      else if (values[middle] > value)
      {
        end = middle - 1;
      }
      else
      {
        start = middle + 1;
      }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
    {
      
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
      //use count as location of starting indice for each value in values (+1)
      int output[n];
      for (int i = 0; i < n; i++)
      {
        output[count[values[i]]-1] = values[i];
        count[values[i]]--;
      }
      for (int i = 0; i < n; i++)
      {
        values[i] = output[i];
      }
}
