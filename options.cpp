#include <iostream>
#include <windows.h>
using namespace std;
struct Option
{
  bool isRight;
  string optionText;
};
Option getOptions(Option options[], int numOptions)
{
  int activeOption = 0;
  while (true)
  {
    system("cls");
    cout << GetAsyncKeyState(VK_RETURN);
    cout << "\t\tOh! You have been caught by a guard. What do you want to do?\n";
    for (int i = 0; i < numOptions; i++)
    {
      cout << (i == activeOption ? "\033[1;4m" : "") << options[i].optionText << "\033[0m" << endl;
    }
    system("pause>null");
    if (GetAsyncKeyState(VK_RETURN))
    {
      break;
    }
    if (GetAsyncKeyState(VK_UP))
    {
      activeOption = activeOption == 0 ? 0 : activeOption - 1;
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
      activeOption = activeOption == numOptions - 1 ? (numOptions - 1) : activeOption + 1;
    }
    if (GetAsyncKeyState(VK_ESCAPE))
    {
      break;
    }
  }
  return options[activeOption];
}
int main()
{
  Option options[3] = {{1, "Shoot the Guard"}, {1, "Fight with the Guard"}, {0, "Run Away and Escape"}};
  Option userOption = getOptions(options, 3);
  cout << userOption.isRight;
  return 0;
}