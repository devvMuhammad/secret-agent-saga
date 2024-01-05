#include <iostream>
#include <windows.h>
// #include <iomanip>
// #include <stdlib.h>
// #include <time.h>
using namespace std;
void loadingTheMap1();
void loadMap2();
struct gameVariables
{
  string Name = "Agent47";
  int Health = 100;
  int ammo = 4;
  int smokes = 2;
} myPlayer;
int main()
{
  system("cls");
  cout << "\t\t\t\tSECRET AGENT SAGA" << endl;
  cout << "You are a spy and your goal is to kill the mafia boss of an extremely notorious organization." << endl
       << endl;
  cout << "\t\t";
  for (int i = 0; i < 30; i++)
  {
    printf("%c", 177);
  }
  cout << "\r";
  cout << "\t\t";

  for (size_t i = 0; i < 30; i++)
  {
    printf("%c", 219);
    Sleep(20);
  }

  cout << endl;
  cout << "\t\t";
  system("pause");
  system("cls");

  cout << "\t\t\t\tMenu" << endl;
  cout << "1.Start a new game" << endl;
  cout << "2.Continue an already existing game" << endl;

  int userChoice;
  cin >> userChoice;

  switch (userChoice)
  {
  case 1:
    cout << "\t\t";
    for (int i = 0; i < 30; i++)
    {
      printf("%c", 177);
    }
    cout << "\r";
    cout << "\t\t";

    for (size_t i = 0; i < 30; i++)
    {
      printf("%c", 219);
      Sleep(20);
    }

    cout << endl;
    cout << "\t\t";
    system("pause");
    system("cls");
    loadingTheMap1();
    cout << endl;
    loadMap2();
    break;
  case 2:
    cout << "Load the already existing game" << endl;
    break;
  default:

    break;
  }
}

void loadingTheMap1()
{

  // string map2 =
  //  { {"    -------------------------------------------------------- \n"},

  //   {"   |                   |                    |               |\n"},
  //   {"---                    |                    |               |\n"},
  //   {"                       #                    #               |\n"},
  //   {"---                    |                    |               |\n"},
  //   {"   |                   |                    |               |\n"},
  //   "    ------------------------------------------------###----- \n"
  //   "                                            |               |\n"
  //   "                                            |               |\n"
  //   "                                            |               |\n"
  //   "                                            |               |\n"
  //   "                                            |_______________|\n"};

  // cout << map;
}

void loadMap2()
{
  string map[] = {
      {"                                             _______________ \n"},
      {"                                            |               |\n"},
      {"                                            |               |\n"},
      {"                                            |  INTEL ROOM   |\n"},
      {"                                            |               |\n"},
      {"                                            |______    _____|\n"},
      {"                                                   |  |      \n"},
      {"                                                   |  |      \n"},
      {"                                             ______####_____\n"},
      {"                                            |               |\n"},
      {"                                            |               |\n"},
      {"                                            |               |\n"},
      {"                                            |               |\n"},
      {"                                            |               |\n"},
      {"    ________________________________________|______####_____|\n"},
      {"   |                   |                    |               |\n"},
      {"___|                   |                    |               |\n"},
      {"                       #                    #               #\n"},
      {"___                    |                    |               |\n"},
      {"   |                   |                    |               |\n"},
      {"   |___________________|____________________|______####_____|\n"},
      {"                                            |               |\n"},
      {"                                            |               |\n"},
      {"                                            |               |\n"},
      {"                                            |               |\n"},
      {"                                            |______####_____|\n"},
      {"                                                   |  |      \n"},
      {"                                             ______|  |_____\n"},
      {"                                            |               |\n"},
      {"                                            |               |\n"},
      {"                                            |  INTEL ROOM   |\n"},
      {"                                            |               |\n"},
      {"                                            |_______________|\n"}};
  cout << map;
}
