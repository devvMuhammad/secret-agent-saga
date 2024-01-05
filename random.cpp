#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
// #include <cstdlib>

using namespace std;
struct Code
{
  string a;
  string b;
} Codex;
Code codesArrayLevel3[9] = {
    {"1,1,2,6,24,120..The next term?", "720"}, // factorial
    {"9,10,8,11,7,12,6,13,5,14,4..What would the next term be", "15"},
    {"0,2,6,12,20,30,42..Enter the next term to proceed", "56"},         // n*n - n
    {"0,4,18,48,100..To proceed enter the key to this sequence", "180"}, // n*n*n -n*n
    {"The number of guards on this floor are ?", "3"},
    {"The number of cameras on this floor are?", "3"},
    {"2,3,5,7,11,13,17...What would the next term be", "19"},
    {"99,11,88,22,77,33,66,44..What would the sum of the next two terms be", "110"},
    {"1,0,3,10,21,36..What would the next term be", "55"} //(2n-1)(n-1) start from zero 
};
int main()
{
  vector<int> used2;
  srand(time(NULL));
  for (int i = 0; i < 8; i++)
  {

    int randomizedNumber2 = rand() % 5;
    // keep generating until we find a random number that does not exist in the used list
    while (find(used2.begin(), used2.end(), randomizedNumber2) != used2.end())
    {
      randomizedNumber2 = rand() % 5;
    }
    used2.push_back(randomizedNumber2);
    // return codesArrayLevel3[randomizedNumber2];

    cout << codesArrayLevel3[randomizedNumber2].a << endl;
  }
  return 0;
}