#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;
void compute(int *arr, int size, float *avg, float *pdt);
int main()
{
  int n;
  float average, product = 1;
  cout << "Please enter the size of array: ";
  cin >> n;                      // Taking the size of the array from the user
  int *numIntegers = new int[n]; // Declared a dynamic array using new keyword
  srand(time(0));
  cout << "\nThe randomly generated array is: " << endl;
  for (int i = 0; i < n; i++)
  { // Storing the elements in the array randomoly from 1 to 100
    numIntegers[i] = (rand() % 100 + 1);
  }
  for (int j = 0; j < n; j++)
  { // Printing the array
    cout << numIntegers[j] << " ";
  }
  cout << endl
       << endl;
  compute(numIntegers, n, &average, &product);                              // Passing the array to the function along with the size of the array and the references of average and product whose values will be updated inside the function
  cout << "The average of elements of the array is: " << average << endl;   // Printing average
  cout << "\nThe product of elements of the array is: " << product << endl; // Printing Product
  delete[] numIntegers;                                                     // Deleting the dynamic array to free the block of memory

  return 0;
}
void compute(int *arr, int size, float *avg, float *pdt)
{
  int sum = 0;
  for (int i = 0; i < size; i++)
  {
    sum += arr[i]; // Computing the sum
  }
  *avg = float(sum) / size; // Computing the average and storing it in the value pointed by avg
  for (int i = 0; i < size; i++)
  {
    if (arr[i] > *avg)
    {
      *pdt *= arr[i];
    }
  }
}