#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
//* initial position
const int initialX = 3;
const int initialY = 7;
const int initialAX = 6;
const int initialAY = 8;
const int initialBX = 30;
const int initialBY = 8;

const int initialX2 = 4;
// const int initialY = 8;
const int initialY2 = 22;
const int initialAX2 = 6;
// const int initialAY = 9;
const int initialAY2 = 22;
const int initialBX2 = 30;
// const int initialBY = 9;
const int initialBY2 = 22;

const int initialX3 = 4;
const int initialY3 = 22;
const int initialAX3 = 6;
const int initialAY3 = 22;
const int initialBX3 = 30;
const int initialBY3 = 22;
const int initialCX3 = 50;
const int initialCY3 = 22;

void level2();
//*The selected option for any case
struct Option
{
  // bool isRight;
  char code;
  string optionText;
};
//*stats of my player
struct Player
{
  int lives = 3;
  int health = 100;
  int kills = 0;
  int ammo = 3;
  int smokes = 3;
  int points = 0;
  int bandages = 3;
  int currentStage = 1;
  int currentSecretsCompleted = 0;
} Player;
//! stats for the guard
struct guardStats
{
  int health;
} guard;
//! stats for the boss
struct bossStats
{
  int health;
} boss;
//* intelroom code along with its answer
struct Code
{
  string code;
  string answer;
} code;
//! vector used
vector<int> used2;
vector<int> used3;
//! This is the map for stage 1
string map1[] = {
    "   --------------------------------------------------------- \n",
    "   |                   |                    |               |\n",
    "---                    |                    |               |\n",
    "                       #                    C               |\n",
    "---                    |                    |               |\n",
    "   |                   |                    |               |\n",
    "   ------------------------------------------------XXX-------\n",
    "                                            |               |\n",
    "                                            |               |\n",
    "                                            |   INTEL ROOM  |\n",
    "                                            |               |\n",
    "                                            -----------------\n",
};

string map2[] = {
    "                                            ----------------- \n",
    "                                            |               |\n",
    "                                            |               |\n",
    "                                            |  INTEL ROOM 2 |\n",
    "                                            |               |\n",
    "                                            -------   -------\n",
    "                                                   |  |      \n",
    "                                                   |  |      \n",
    "                                            ---------X-------\n",
    "                                            |               |\n",
    "                                            |               |\n",
    "                                            |               |\n",
    "                                            |               |\n",
    "                                            |               |\n",
    "    ------------------------------------------------C--------\n",
    "   |                   |                    |               |\n",
    "---                    |                    |               |\n",
    "                       #                    #               |\n",
    "---                    |                    |               |\n",
    "   |                   |                    |               |\n",
    "   -------------------------------------------------C--------\n",
    "                                            |               |\n",
    "                                            |               |\n",
    "                                            |               |\n",
    "                                            |               |\n",
    "                                            ---------X-------\n",
    "                                                   |  |      \n",
    "                                                   |  |      \n",
    "                                            --------  -------\n",
    "                                            |               |\n",
    "                                            |               |\n",
    "                                            |  INTEL ROOM 1 |\n",
    "                                            |               |\n",
    "                                            -----------------\n"};

string map3[] = {
    "                                            ----------------- \n",
    "                                            |               |\n",
    "                                            |               |\n",
    "                                            |  INTEL ROOM 2 |\n",
    "                                            |               |\n",
    "                                            -------   -------\n",
    "                                                   |  |      \n",
    "                                                   |  |      \n",
    "                                            ---------X-------\n",
    "                                            |               |\n",
    "                                            |               |\n",
    "                                            |               |\n",
    "                                            |               |\n",
    "                                            |               |\n",
    "    ------------------------------------------------C--------     -------------------\n",
    "   |                   |                    |               |     |                 |\n",
    "---                    |                    |               |-----                  |\n",
    "                       #                    C               X         INTEL ROOM 3  |\n",
    "---                    |                    |               |-----                  |\n",
    "   |                   |                    |               |     |                 |\n",
    "   -------------------------------------------------C--------     -------------------\n",
    "                                            |               |\n",
    "                                            |               |\n",
    "                                            |               |\n",
    "                                            |               |\n",
    "                                            ---------X-------\n",
    "                                                   |  |      \n",
    "                                                   |  |      \n",
    "                                            --------  -------\n",
    "                                            |               |\n",
    "                                            |               |\n",
    "                                            |  INTEL ROOM 1 |\n",
    "                                            |               |\n",
    "                                            -----------------\n"};
//! This function is used to move in the map
void gotoxy(short x, short y)
{
  COORD pos = {x, y};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void SetConsoleColor(int colorCode)
{
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, colorCode);
}
void showCursor(bool show)
{
  HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursorInfo;
  GetConsoleCursorInfo(consoleHandle, &cursorInfo);
  cursorInfo.bVisible = show;
  SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

//! This is the initial loading screen
void introScreen()
{
  system("cls");
  SetConsoleColor(10);
  cout << "\t\t\t\tSECRET AGENT SAGA" << endl;
  SetConsoleColor(12);
  cout << "You are a spy and your goal is to kill the mafia boss of an extremely notorious organization." << endl
       << endl;
  SetConsoleColor(7);
  cout << "\t";
  for (int i = 0; i < 60; i++)
  {
    printf("%c", 177);
  }
  cout << "\r"; //*Takes the cursor back to the beginning can be used to overwrite two texts
  cout << "\t";

  for (size_t i = 0; i < 60; i++)
  {
    printf("%c", 219);
    Sleep(10);
  }

  cout << endl;
  cout << "\t";
  system("pause");
  system("cls");
}
void loadingScreen(string message = "Loading level ...")
{
  SetConsoleColor(12);
  cout << "\t" << message << endl;
  SetConsoleColor(7);
  cout << "\t";
  for (int i = 0; i < 60; i++)
  {
    printf("%c", 177);
  }
  cout << "\r"; //*Takes the cursor back to the beginning can be used to overwrite two texts
  cout << "\t";

  for (size_t i = 0; i < 60; i++)
  {
    printf("%c", 219);
    Sleep(10);
  }
}
void animateText(string sentence, bool skipEnabled = true)
{
  for (int j = 0; j < sentence.length(); j++)
  {
    // skip the text if enter is pressed during the animation, put changes here
    Sleep(20);
    if ((GetAsyncKeyState(VK_RETURN) & 0x8000) && j > 2 && skipEnabled)
    {
      for (int k = j; k < sentence.length(); k++)
      {
        cout << sentence[k];
      }
      Sleep(300);
      break;
    }
    cout << sentence[j];
  }
}
void displayStory()
{
  // string toRender ="";
  const int textNums = 4;
  // Success depends on overcoming every trial in your path. Your adventure begins now.
  string texts[] = {
      "Welcome, Agent 47. You're on a mission to infiltrate a notorious organization, gather intel, eliminate key targets, face a final boss, and escape undetected.",
      "You must surpass every trial that comes in your way. Each choice will "
      "Facing an enigmatic final boss, he navigates trials and challenges, showcasing strategic mastery.",
      "Success in these covert operations shapes the destiny of a world teetering on the brink of chaos.",
      "Welcome to the game, Agent 47. Your journey into the shadows begins now."};

  for (int i = 0; i < textNums; i++)
  {
    SetConsoleColor(0);
    animateText(texts[i]);
    cout << endl;
  }
  SetConsoleColor(7);
  system("cls");
}

void displayMap(string map[], size_t size)
{
  cout << "\033[1m" << setw(7) << left << "Stage:"
       << "\033[0m" << left << Player.currentStage << "\t\033[1mObjectives:\033[0m "
       << Player.currentStage << " Secret Code(s)" << endl;
  cout << "\033[1mLives:\033[0m" << left << setw(2) << Player.lives << "\t\033[1mHealth: \033[0m" << setw(2) << Player.health << "\t\033[1mSecrets: \033[0m" << setw(2) << Player.currentSecretsCompleted << endl;
  cout << "\033[1m" << setw(7) << "Ammo:"
       << "\033[0m" << setw(2) << Player.ammo << "\t\033[1mSmokes:\033[0m" << setw(2) << Player.smokes << "\t\033[1mBandages:\033[0m" << setw(2) << Player.bandages << endl;
  SetConsoleColor(7);
  // return 0;
  for (int i = 0; i < size; i++)
  {
    SetConsoleColor(14);
    cout << map[i];
  }
  SetConsoleColor(7);
}

char getCharacterAtPosition(short x, short y)
{
  if (Player.currentStage == 1)
  {

    return map1[y - 3][x];
  }
  else if (Player.currentStage == 2)
  {

    return map2[y - 3][x];
  }
  else
  {
    return map3[y - 3][x];
  }
}

// Function to move the character right
void moveRight(int &x, int &y, char c = '@')
{
  gotoxy(x, y);
  cout << " ";
  x += 1;
  gotoxy(x, y);
  cout << c;
}

// Function to move the character left
void moveLeft(int &x, int &y, char c = '@')
{
  gotoxy(x, y);
  cout << " ";
  x -= 1;
  gotoxy(x, y);
  cout << c;
}

// Function to move the character up
void moveUp(int &x, int &y, char c = '@')
{
  gotoxy(x, y);
  cout << " ";
  y -= 1;
  gotoxy(x, y);
  cout << c;
}

// Function to move the character down
void moveDown(int &x, int &y, char c = '@')
{
  gotoxy(x, y);
  cout << " ";
  y += 1;
  gotoxy(x, y);
  cout << c;
}

void moveCharacter(int *x, int *y)
{
  if (GetAsyncKeyState(VK_RIGHT) && getCharacterAtPosition(*x + 1, *y) != '|' && getCharacterAtPosition(*x + 1, *y) != '-')
    moveRight(*x, *y);
  if (GetAsyncKeyState(VK_LEFT) && getCharacterAtPosition(*x - 1, *y) != '|' && getCharacterAtPosition(*x - 1, *y) != '-')
    moveLeft(*x, *y);
  if (GetAsyncKeyState(VK_UP) && getCharacterAtPosition(*x, *y - 1) != '-' && getCharacterAtPosition(*x, *y - 1) != '|' && getCharacterAtPosition(*x, *y - 1) != '_')
    moveUp(*x, *y);
  if (GetAsyncKeyState(VK_DOWN) && getCharacterAtPosition(*x, *y + 1) != '-' && getCharacterAtPosition(*x, *y + 1) != '|' && getCharacterAtPosition(*x, *y + 1) != '_')
    moveDown(*x, *y);
}

void animation(string direction, int *x, int *y, int *ax, int *ay, int *bx, int *by, bool &collisionOcurred, bool &caughtByCamera, bool &enteredIntelRoom)
{
  for (int i = 0; i < 4; ++i)
  {
    // check if the next character is the entry to the camera room
    // moveCharacter(x, y);
    Sleep(200);
    if ((*x == *bx && *y == *by))
    {
      // Collision detected
      collisionOcurred = true;
      break;
    }
    if (getCharacterAtPosition(*x, *y) == 'C')
    {
      caughtByCamera = true;
      break;
    }
    if (getCharacterAtPosition(*x, *y) == 'X')
    {
      enteredIntelRoom = true;
      break;
    }
    if (!caughtByCamera || !enteredIntelRoom || !enteredIntelRoom)
      moveCharacter(x, y);

    if (direction == "up")
    {
      // moveUp(*ax, *ay, '#');
      moveUp(*bx, *by, '#');
    }
    else if (direction == "down")
    {
      // moveDown(*ax, *ay, '#');
      moveDown(*bx, *by, '#');
    }
  }
};

void animation2(string direction, int *x, int *y, int *ax, int *ay, int *bx, int *by, bool &collisionOcurred, bool &caughtByCamera, bool &enteredIntelRoom)
{
  for (int i = 0; i < 4; ++i)
  {
    // check if the next character is the entry to the camera room
    Sleep(100);

    if ((*x == *ax && *y == *ay) || (*x == *bx && *y == *by))
    {
      // Collision detected
      collisionOcurred = true;
      break;
    }
    if (getCharacterAtPosition(*x, *y) == 'C')
    {
      caughtByCamera = true;
      // map2[*y - 4][*x] = ' ';
      break;
    }
    if (getCharacterAtPosition(*x, *y) == 'X')
    {
      enteredIntelRoom = true;
      // map2[*y - 4][*x] = ' ';
      break;
    }
    if (!caughtByCamera || !enteredIntelRoom || !enteredIntelRoom)
      moveCharacter(x, y);

    if (direction == "up")
    {
      moveUp(*ax, *ay, '#');
      moveUp(*bx, *by, '#');
    }
    else if (direction == "down")
    {
      moveDown(*ax, *ay, '#');
      moveDown(*bx, *by, '#');
    }
  }
};

void animation3(string direction, int iterations, int *x, int *y, int *ax, int *ay, int *bx, int *by, int *cx, int *cy, bool &collisionOcurred, bool &caughtByCamera, bool &enteredIntelRoom)
{
  for (int i = 0; i < iterations; ++i)
  {
    // check if the next character is the entry to the camera room
    Sleep(100);

    if ((*x == *ax && *y == *ay) || (*x == *bx && *y == *by) || (*x == *cx && *y == *cy))
    {
      // Collision detected
      collisionOcurred = true;
      break;
    }
    if (getCharacterAtPosition(*x, *y) == 'C')
    {
      caughtByCamera = true;
      // map3[*y - 4][*x] = ' ';
      break;
    }
    if (getCharacterAtPosition(*x, *y) == 'X')
    {
      enteredIntelRoom = true;
      // map3[*y - 4][*x] = ' ';
      break;
    }
    if (!caughtByCamera || !enteredIntelRoom || !enteredIntelRoom)
      moveCharacter(x, y);

    if (direction == "up")
    {
      moveUp(*ax, *ay, '#');
      moveUp(*bx, *by, '#');
      moveUp(*cx, *cy, '#');
    }
    else if (direction == "down")
    {
      moveDown(*ax, *ay, '#');
      moveDown(*bx, *by, '#');
      moveDown(*cx, *cy, '#');
    }
  }
};

Option getOptions(Option options[], int numOptions, string message = "Choose what do you want to do")
{
  int activeOption = 0;
  while (true)
  {
    system("cls");
    // cout << "\t\tOh! You have been caught by a guard. What do you want to do?\n";
    cout << "\t\t" << message << endl;
    for (int i = 0; i < numOptions; i++)
    {
      cout << (i == activeOption ? "\033[1;4m" : "") << options[i].optionText << "\033[0m" << endl;
    }
    system("pause>null");
    if (GetAsyncKeyState(VK_RETURN) & 0x8000)
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

void restartLevel(int &x, int &y, string message)
{
  cout << message;
  Player.lives--;
  x = initialX;
  y = initialY;
  //! RESET RESOURCES
  Player.health = 100;
  // Player.lives = 3;
  Player.currentSecretsCompleted = 0;
  Player.ammo = 3;
  Player.smokes = 3;
  Player.bandages = 3;
}

void restartLevel2(int &x, int &y, string message)
{
  cout << message;
  Player.lives--;
  x = initialX2;
  y = initialY2;
  //! RESET MAP
  map2[8][53] = 'X';
  map2[14][52] = 'C';
  map2[20][52] = 'C';
  map2[25][53] = 'X';
  //! RESET RESOURCES
  Player.health = 100;
  // Player.lives = 3;
  Player.currentSecretsCompleted = 0;
  Player.ammo = 3;
  Player.smokes = 3;
  Player.bandages = 3;
}

void restartLevel3(int &x, int &y, string message)
{
  cout << message;
  Player.lives--;
  x = initialX3;
  y = initialY3;
  //! RESET MAP
  map3[8][53] = 'X';
  map3[14][52] = 'C';
  map3[20][52] = 'C';
  map3[17][44] = 'C';
  map3[25][53] = 'X';
  map3[17][60] = 'X';
  //! RESET RESOURCES
  Player.ammo = 3;
  Player.smokes = 3;
  // Player.lives = 3;
  Player.bandages = 3;
  Player.health = 100;
  Player.currentSecretsCompleted = 0;
  boss.health = 300;
}

void gameState(int health)
{
  string finalMessage[2] = {"You have won the battle", "You have lost the battle"};
  //*incase of the win
  if (health == 0)
  {
    for (size_t i = 0; i < finalMessage[0].length(); i++)
    {
      cout << finalMessage[0][i];
      Sleep(20);
    }
    cout << endl;
  }
  //*incase of losing
  else
  {

    for (size_t i = 0; i < finalMessage[1].length(); i++)
    {
      cout << finalMessage[1][i];
      Sleep(20);
    }
    cout << endl;
    // Player.lives--;
  }
}

void battleWithGuard()
{
  system("cls");
  string message = "Oh! You got caught by a guard, the battle with the guard begins";
  //! for animation
  for (size_t i = 0; i < message.length(); i++)
  {
    cout << message[i];
    Sleep(20);
  }
  cout << endl;
  guard.health = 100; //* since every guard has a health of 100 the health has been declared inside the function body
  system("pause");
  system("cls");
  Option options[2] = {{'s', "Shoot The guard"}, {'f', "Fight the guard"}};
  Option myOption;

  //! either my health goes to zero or the guard's
  while (guard.health != 0 && Player.health > 0)
  {
    //! using the animation function I have done this so that I can get a struct
    myOption = getOptions(options, 2);
    //! myOption.code gives me the selected options' corresponding char
    switch (myOption.code)
    {
      //*This is the case in which i shoot the guard directly
    case 's':
      if ((Player.ammo - 2) > 0)
      {
        Player.ammo -= 2;
        guard.health = 0;
        Player.kills++;
        //*The case in which we just use two bullets and kill the guard directly
        SetConsoleColor(8);
        cout << "You have killed the guard using the silenced pistol. You used 2 bullets in the process" << endl;
        SetConsoleColor(7);
        cout << "You received ";
        //! This is the reward that we get on killing each guard
        int battleReward;
        battleReward = rand() % 3 + 1;
        if (battleReward == 1)
        {
          Player.ammo++;
          SetConsoleColor(10);
          cout << "1 bullet" << endl;
          SetConsoleColor(7);
        }
        else if (battleReward == 2)
        {
          Player.smokes++;
          SetConsoleColor(10);
          cout << "1 smoke" << endl;
          SetConsoleColor(7);
        }
        else
        {
          Player.bandages++;
          SetConsoleColor(10);
          cout << "1 bandage" << endl;
          SetConsoleColor(7);
        }
      }
      else
      {
        SetConsoleColor(12);
        cout << "You do not have enough ammo to kill the guard directly" << endl;
        SetConsoleColor(7);
      }
      system("pause");
      break;
      //*The case in which i have to fight the guard
    case 'f':
      //! either i die or the guard dies
      while (guard.health != 0 && Player.health > 0)
      {

        Option options[3] = {{'l', "Light Attack"}, {'p', "Use Pistol"}, {'u', "Use Bandages"}};
        Option myOption;
        myOption = getOptions(options, 3);
        switch (myOption.code)
        {
        case 'l':
          //! light attack on the guard in which he attacks me and I attack him
          guard.health -= rand() % 40;
          if (guard.health < 0)
          {
            guard.health = 0;
            Player.kills++;
          }
          cout << "The health of the guard has become " << guard.health << endl;
          Player.health -= rand() % (Player.currentStage * 10);
          if (Player.health < 0)
          {
            Player.health = 0;
          }
          cout << "Your health has become " << Player.health << endl;
          //! The rewarding system
          if (guard.health == 0)
          {
            cout << "You have killed the guard" << endl;
            cout << "You received ";
            int battleReward;
            battleReward = rand() % 3 + 1;
            if (battleReward == 1)
            {
              Player.ammo++;
              SetConsoleColor(10);
              cout << "1 ammo" << endl;
              SetConsoleColor(7);
            }
            else if (battleReward == 2)
            {
              Player.smokes++;
              SetConsoleColor(10);
              cout << "1 smoke" << endl;
              SetConsoleColor(7);
            }
            else
            {
              Player.bandages++;
              SetConsoleColor(10);
              cout << "1 bandage" << endl;
              SetConsoleColor(7);
            }
          }
          system("pause");
          break;
        case 'p':
          //! I use my pistol so he gets a damage of 50
          if (Player.ammo > 0)
          {
            Player.ammo -= 1;
            guard.health -= 50;
            if (guard.health < 0)
            {
              guard.health = 0;
              Player.kills++;
            }
            cout << "The health of the guard has become " << guard.health << endl;
            Player.health -= rand() % (Player.currentStage * 10);
            if (Player.health < 0)
            {
              Player.health = 0;
            }
            if (Player.health == 0 && Player.bandages > 0)
            {
              Player.health += 40;
              Player.bandages -= 1;
              cout << "You have used your remaining bandages." << endl;
            }
            if (guard.health == 0)
            {
              cout << "You have killed the guard" << endl;
              cout << "You received ";
              //! again the battle reward
              int battleReward;
              battleReward = rand() % 3 + 1;
              if (battleReward == 1)
              {
                Player.ammo++;
                SetConsoleColor(10);
                cout << "1 ammo" << endl;
                SetConsoleColor(7);
              }
              else if (battleReward == 2)
              {
                Player.smokes++;
                SetConsoleColor(10);
                cout << "1 smoke" << endl;
                SetConsoleColor(7);
              }
              else
              {
                Player.bandages++;
                SetConsoleColor(10);
                cout << "1 smoke" << endl;
                SetConsoleColor(7);
              }
            }
            cout << "Your health has become " << Player.health << endl;
          }
          else
          {
            cout << "You do not have sufficient ammo" << endl;
          }
          system("pause");
          break;
          //! The case in which i use my bandage and my health increases
        case 'u':
          if (Player.bandages > 0)
          {
            Player.bandages -= 1;
            Player.health += 40;
            cout << "You have used a bandage" << endl
                 << "Your new health is " << Player.health << endl;
          }
          else
          {
            cout << "You do not have sufficient bandages" << endl;
          }
          system("pause");
          break;
        default:
          break;
        }
      }
      break;
    default:
      break;
    }
  }
  system("cls");
  //! TO determine the result of the battle
  // gameState(guard.health);
}

void bossFight()
{
  boss.health = 300;
  system("cls");
  string message = "The battle with the boss begins";
  //! text animation
  for (size_t i = 0; i < message.length(); i++)
  {
    cout << message[i];
    Sleep(20);
  }
  cout << endl;
  system("pause");
  //! The initial options for the battle with the boss
  Option options[2] = {{'s', "Shoot the boss"}, {'f', "Fight the boss"}};
  Option myOption;
  system("cls");
  string messages[2] = {
      "You have reached the final stage and you are now fighting the boss!", "Your main target now is to kill the boss so that the objectives of the game get completed"};
  //! text animation
  for (int i = 0; i < messages[0].length(); i++)
  {
    SetConsoleColor(12);
    cout << messages[0][i];
    Sleep(20);
  }
  SetConsoleColor(7);
  cout << endl;
  //! text animation
  for (int i = 0; i < messages[1].length(); i++)
  {
    cout << messages[1][i];
    Sleep(20);
  }
  cout << endl;
  system("pause");
  //! either the boss dies or I die game loop
  while (boss.health != 0 && Player.health > 0)
  {
    myOption = getOptions(options, 2);
    //*The returned char according to my selected option
    switch (myOption.code)
    {
    case 's':
      system("cls");
      if (Player.ammo > 1)
      {
        Player.ammo -= 2;
        cout << "Oh what!The boss has an armor he does not get as damaged as other guards do!" << endl;
        boss.health -= 70;
        cout << "You have damaged the boss using the silenced pistol.You used 2 bullets in the process" << endl;
        cout << "The boss's helath is now " << boss.health << endl;
        Player.health -= rand() % (30);
        if (Player.health < 0)
        {
          Player.health = 0;
        }
        cout << "Your health has become " << Player.health << endl;
      }
      else
      {
        SetConsoleColor(12);
        cout << "You do not have sufficient ammo" << endl;
        SetConsoleColor(7);
      }
      system("pause");
      break;
    case 'f':
      while (boss.health != 0 && Player.health > 0)
      {
        Option options[3] = {{'l', "Light Attack"}, {'p', "Use Pistol"}, {'u', "Use Bandages"}};
        Option myOption;
        myOption = getOptions(options, 3);
        //*Again my option according to the option I select
        switch (myOption.code)
        {
          //*light attack
        case 'l':
          boss.health -= rand() % 40;
          if (boss.health < 0)
          {
            boss.health = 0;
          }
          cout << "The health of the boss has become " << boss.health << endl;
          Player.health -= rand() % (30);
          if (Player.health < 0)
          {
            Player.health = 0;
          }
          //! incase my health goes to zero but i still have bandages then the player will automatically use the bandage to keep the game running
          if (Player.health == 0 && Player.bandages > 0)
          {
            Player.bandages -= 1;
            Player.health += 40;
            SetConsoleColor(10);
            cout << "You have used a bandage " << endl;
            SetConsoleColor(7);
          }
          cout << "Your health has become " << Player.health << endl;
          system("pause");
          break;
          //*The use of pistol
        case 'p':
          if (Player.ammo > 0)
          {
            Player.ammo -= 1;
            boss.health -= 35;
          }
          else
          {
            SetConsoleColor(12);
            cout << "You do not have sufficient ammo" << endl;
            SetConsoleColor(7);
            system("pause");
            break;
          }
          if (boss.health < 0)
          {
            boss.health = 0;
            break;
          }
          cout << "The health of the boss has become " << boss.health << endl;
          Player.health -= rand() % (Player.currentStage * 10);
          if (Player.health < 0)
          {
            Player.health = 0;
          }
          //! just incase my health goes to zero but i still have bandages
          if (Player.health == 0 && Player.bandages > 0)
          {
            Player.health += 40;
            Player.bandages -= 1;
            cout << "You have used your remaining bandages." << endl;
          }
          cout << "Your health has become " << Player.health << endl;
          system("pause");
          break;
          //! case for the use of bandages
        case 'u':
          if (Player.bandages > 0)
          {
            Player.bandages -= 1;
            Player.health += 40;
            cout << "You have used a bandage" << endl;
            cout << "Your health is " << Player.health << endl;
          }
          else
          {
            cout << "You do not have sufficient bandages" << endl;
          }
          system("pause");
          break;
        default:
          break;
        }
      }
      break;
    default:
      break;
    }
  }
  system("cls");
  //! the game ending message
  // gameState(boss.health);
  // gameEndingMessage(boss.health);
}

Code codesArrayLevel1[5] = {
    {"1,1,2,3,5,8.. What would the next term be?", "13"},
    {"SUN is written as WON,then TOM would be written as", "XUM"},
    {"2+2 =5 ,3+3 =10,then 4+4 is", "17"},
    {"1,4,9,16..What would the next term be", "25"},
    {"1,3,6,10,15,21....what would the next term be", "28"}};
Code codesArrayLevel2[5] = {
    {"1,1,2,2,3,3,4,4 what would its 15th term be", "8"},
    {"1,2,2,4,3,6,4,8,5,10..The next term must be", "6"},
    {"1,2,2,4,3,8,4,16,5,32,6.. What would the next term be", "64"},
    {"The number of guards on this floor are", "2"},
    {"The number of cameras on this floor are", "2"}};
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

Code getSecret(int level)
{
  srand(time(NULL));
  int randomizedNumber2;
  int randomizedNumber3;
  Code returnedValue, Null;

  if (level == 1)
  {
    return codesArrayLevel1[rand() % 5];
  }
  else if (level == 2)
  {
    randomizedNumber2 = rand() % 5;
    // keep generating until we find a random number that does not exist in the used list
    while (find(used2.begin(), used2.end(), randomizedNumber2) != used2.end())
    {
      randomizedNumber2 = rand() % 5;
    }
    used2.push_back(randomizedNumber2);
    return codesArrayLevel2[randomizedNumber2];
  }
  else
  {
    randomizedNumber3 = rand() % 9;
    // keep generating until we find a random number that does not exist in the used list
    while (find(used3.begin(), used3.end(), randomizedNumber3) != used3.end())
    {
      randomizedNumber3 = rand() % 9;
    }
    used3.push_back(randomizedNumber3);

    return codesArrayLevel3[randomizedNumber3];
  }
}

void endScenario(int *x, int *y, bool &scenarioCondition)
{
  system("pause");
  system("cls");
  scenarioCondition = false;
  // render the map1 again
  // cout << endl; // !so the map1 is rendered one line below
  displayMap(map1, 12);

  gotoxy(*x, *y);
  cout << "@";
}

void endScenario3(int *x, int *y, bool &scenarioCondition)
{
  system("pause");
  system("cls");
  scenarioCondition = false;
  // render the map1 again
  // cout << endl; // !so the map1 is rendered one line below
  displayMap(map3, 34);

  gotoxy(*x, *y);
  cout << "@";
}

void endScenario2(int *x, int *y, bool &scenarioCondition)
{
  system("pause");
  system("cls");
  scenarioCondition = false;
  // render the map2 again
  // cout << endl; // !so the map2 is rendered one line below
  displayMap(map2, 34);

  gotoxy(*x, *y);
  cout << "@";
}

int level1()
{
  showCursor(false);
  // system()
  int ax, ay, bx, by;
  int x = initialX;
  int y = initialY;

  displayMap(map1, 12);
  bool collisionOccurred = false;
  bool caughtByCamera = false;
  bool enteredIntelRoom = false;

  while (true)
  {
    ax = initialAX;
    ay = initialAY;
    bx = initialBX;
    by = initialBY;

    // guards animation for up and down
    animation("up", &x, &y, &ax, &ay, &bx, &by, collisionOccurred, caughtByCamera, enteredIntelRoom);
    if (!collisionOccurred)
    {
      animation("down", &x, &y, &ax, &ay, &bx, &by, collisionOccurred, caughtByCamera, enteredIntelRoom);
    }

    //! COLLISION SCENARIO
    if (collisionOccurred)
    {
      system("cls");
      //! NEW CODE
      battleWithGuard();

      // check for the battle result using the health
      if (Player.health <= 0)
      {

        if (Player.lives <= 1)
        {
          Player.currentStage = 1;
          Player.lives = 4;
          Player.health = 100;
          restartLevel(x, y, "Out of lives, you wil start again from level 1\n");
          system("pause");
          system("cls");
          loadingScreen();
          system("cls");
          return 0;
        }
        else
        {
          Player.health = 100;
          restartLevel(x, y, "Oops, Agent! You lost the battle. You will have to restart :(");
        }
      }
      else
      {
        x++; // move one position to the right after a successful fight
      }
      endScenario(&x, &y, collisionOccurred);
    }
    //! CAMERA SCENARIO
    else if (caughtByCamera)
    {
      system("cls");

      Option options[3] = {{'d', "Destroy the camera"}, {'s', "Fire a smoke"}, {'e', "Run Away and Escape"}};
      Option userOption = getOptions(options, 3, "Oh! You have been spotted by a camera. Your identity may be revealed. Do something!");

      system("cls");

      if (userOption.code == 'd')
      {
        restartLevel(x, y, "Oops, Agent! You have been spotted destroying the camera. The guards have caught you.\n");
      }
      else if (userOption.code == 'e')
      {
        restartLevel(x, y, "Oops, Agent! Your attempt to escape has failed. Remember you are in a super sensitive area. Be careful next time.\n");
      }
      else if (userOption.code == 's')
      {
        if (Player.smokes > 0)
        {

          cout << "Good job, Agent! You have concealed your identity.\n";
          Player.smokes--;
          map1[y - 3][x] = ' ';
          x++;
        }
        else
        {
          restartLevel(x, y, "Oops, Agent! You ran out of smokes. Be cautious of your resources next time.\n");
        }
      }
      else
      {
        // Default case
      }
      if (Player.lives <= 0)
      {
        Player.currentStage = 1;
        Player.lives = 4;
        restartLevel(x, y, "Out of lives, you wil start again from level 1\n");
        system("pause");
        system("cls");
        loadingScreen();
        system("cls");
        return 0;
      }
      endScenario(&x, &y, caughtByCamera);
    }
    else if (enteredIntelRoom)
    {
      system("cls");
      /**
      - enter Intel room
      - show a code
      - you enter the input
      - display certain number of tries
      - you enter one option
      - if correct then you move to next level (incase of level 1)
      - if wrong, then deduct one try, if at last try then restart level
      */
      int tries = 5;
      Code question = getSecret(1);
      // Code question = {"what is you name?", "Muhammad"};

      string userInput;
      bool isCorrect = false;

      animateText("You have entered an Intel Room. You must decode the secret correctly to progress\n", false);
      system("pause");
      system("cls");

      // Compare user input with the correct answer
      while (tries > 0 && !isCorrect)
      {
        cout << question.code << "\t\t\t Tries: " << tries << endl;
        cout << "Your answer: ";
        getline(cin, userInput);

        userInput.erase(0, userInput.find_first_not_of(" \t\n\r\f\v"));
        userInput.erase(userInput.find_last_not_of(" \t\n\r\f\v") + 1);

        if (userInput == question.answer)
        {
          cout << "You have successfully decoded the secret. You now move on to level 2" << endl;
          isCorrect = true;
          break;
        }
        else
        {
          cout << "Wrong answer. Try again!";
          tries--;
          system("pause>null"); // null or not, decide it later
          system("cls");
        }
      }
      // cout<<"You are out of tries";
      if (!isCorrect)
      {
        if (Player.lives > 1)
        {
          restartLevel(x, y, "Oops! You are out of tries. You will have to start again. Better luck next time.\n");
        }
        else
        {
          Player.currentStage = 1;
          Player.lives = 4;
          restartLevel(x, y, "Out of lives, you wil start again from level 1\n");
          system("pause");
          system("cls");
          loadingScreen();
          system("cls");
          return 0;
        }

        //! BOILERPLATE CODE FOR ENDING THE SCENARIO
        endScenario(&x, &y, enteredIntelRoom);
      }
      else if (isCorrect)
      {

        system("pause");
        system("cls");
        Player.currentStage++;
        // level2();
        return 0;
      }
      // move to level 2
      // restartLevel(x, y, "");

      // system("pause");
    }
  }
}

void level2()
{
  showCursor(false);
  // system()
  int ax, ay, bx, by;
  int x = initialX2;
  int y = initialY2;

  displayMap(map2, 34);

  bool collisionOccurred = false;
  bool caughtByCamera = false;
  bool enteredIntelRoom = false;

  while (true)
  {
    ax = initialAX2;
    ay = initialAY2;
    bx = initialBX2;
    by = initialBY2;

    // guards animation for up and down
    animation2("up", &x, &y, &ax, &ay, &bx, &by, collisionOccurred, caughtByCamera, enteredIntelRoom);
    if (!collisionOccurred)
    {
      animation2("down", &x, &y, &ax, &ay, &bx, &by, collisionOccurred, caughtByCamera, enteredIntelRoom);
    }

    //! COLLISION SCENARIO
    if (collisionOccurred)
    {
      system("cls");
      //! NEW CODE
      battleWithGuard();
      // check for the battle result using the health
      if (Player.health <= 0)
      {

        if (Player.lives <= 1)
        {
          Player.currentStage = 1;
          Player.lives = 4;
          restartLevel(x, y, "Out of lives, you wil start again from level 1\n");
          system("pause");
          system("cls");
          loadingScreen();
          system("cls");
          return;
        }
        else
        {
          restartLevel2(x, y, "Oops, Agent! You lost the battle. You will have to restart :(");
        }
      }
      else
      {
        x++; // move one position to down after a successful fight
      }
      endScenario2(&x, &y, collisionOccurred);
    }
    //! CAMERA SCENARIO
    else if (caughtByCamera)
    {
      system("cls");

      Option options[3] = {{'d', "Destroy the camera"}, {'s', "Fire a smoke"}, {'e', "Run Away and Escape"}};
      Option userOption = getOptions(options, 3, "Oh! You have been spotted by a camera. Your identity may be revealed. Do something!");

      system("cls");

      if (userOption.code == 'd')
      {
        restartLevel2(x, y, "Oops, Agent! You have been spotted destroying the camera. The guards have caught you.\n");
      }
      else if (userOption.code == 'e')
      {
        restartLevel2(x, y, "Oops, Agent! Your attempt to escape has failed. Remember you are in a super sensitive area. Be careful next time.\n");
      }
      else if (userOption.code == 's')
      {
        if (Player.smokes > 0)
        {

          cout << "Good job, Agent! You have concealed your identity.\n";
          Player.smokes--;
          map2[y - 3][x] = ' ';
          // remove the C1 and C2
          y++;
        }
        else
        {
          restartLevel2(x, y, "Oops, Agent! You ran out of smokes. Be cautious of your resources next time.\n");
        }
      }
      else
      {
        // Default case
      }
      if (Player.lives <= 0)
      {
        Player.currentStage = 1;
        Player.lives = 4;
        restartLevel(x, y, "Out of lives, you wil start again from level 1\n");
        system("pause");
        system("cls");
        loadingScreen();
        system("cls");
        return;
      }
      endScenario2(&x, &y, caughtByCamera);
    }
    else if (enteredIntelRoom)
    {
      system("cls");
      /**
      - enter Intel room
      - show a code
      - you enter the input
      - display certain number of tries
      - you enter one option
      - if correct then you move to next level (incase of level 1)
      - if wrong, then deduct one try, if at last try then restart level
      */
      int tries = 5;
      Code question = getSecret(2);
      // Code question = {"what is you name?", "Muhammad"};

      string userInput;
      bool isCorrect = false;

      animateText("You have entered an Intel Room. You must decode the secret correctly to progress\n", false);
      system("pause");
      system("cls");

      // Compare user input with the correct answer
      while (tries > 0 && !isCorrect)
      {
        cout << question.code << "\t\t\t Tries: " << tries << endl;
        cout << "Your answer: ";
        getline(cin, userInput);

        userInput.erase(0, userInput.find_first_not_of(" \t\n\r\f\v"));
        userInput.erase(userInput.find_last_not_of(" \t\n\r\f\v") + 1);

        if (userInput == question.answer)
        {
          cout << "You have successfully decoded the secret." << endl;
          Player.currentSecretsCompleted++;
          isCorrect = true;
        }
        else
        {
          cout << "Wrong answer. Try again!";
          tries--;
          system("pause>null"); // null or not, decide it later
          system("cls");
        }
      }
      // cout<<"You are out of tries";
      if (!isCorrect)
      {
        if (Player.lives > 1)
        {
          restartLevel(x, y, "Oops! You are out of tries. You will have to start again. Better luck next time.\n");
        }
        else
        {
          Player.currentStage = 1;
          Player.lives = 4;
          restartLevel(x, y, "Out of lives, you wil start again from level 1\n");
          system("pause");
          system("cls");
          loadingScreen();
          system("cls");
          return;
        }
        //! BOILERPLATE CODE FOR ENDING THE SCENARIO
        endScenario2(&x, &y, enteredIntelRoom);
      }
      else
      {
        /*
        - in case of level 1, directly move to level 2
        - in case of level 2, if one is completed then progress further and if two completed then move to level3
        */

        if (Player.currentSecretsCompleted == 2)
        {
          //! MOVE TO LEVEL 3
          //! PLACEHOLDER CODE
          animateText("You have completed the tasks for this level and now you will proceed to level 3");
          system("cls");
          //! BOILERPLATE CODE FOR ENDING THE SCENARIO
          Player.currentStage++;
          return;
        }
        else
        {
          map2[y - 3][x] = ' ';
          y++;
          endScenario2(&x, &y, enteredIntelRoom);
        }
        // move to level 2
        // restartLevel(x, y, "");
      }

      // system("pause");
    }
  }
  /**if (Player.lives <= 0)
  {
    x = initialX;
    y = initialY;
    restartLevel(x, y, "You have lost all of your lives now the game must be restarted!");
  }*/
}

void level3()
{
  showCursor(false);
  // system()
  int ax, ay, bx, by, cx, cy;
  int x = initialX3;
  int y = initialY3;

  displayMap(map3, 34);

  bool collisionOccurred = false;
  bool caughtByCamera = false;
  bool enteredIntelRoom = false;

  while (true)
  {
    ax = initialAX3;
    ay = initialAY3;
    bx = initialBX3;
    by = initialBY3;
    cx = initialCX3;
    cy = initialCY3;

    // guards animation for up and down
    animation3("up", 4, &x, &y, &ax, &ay, &bx, &by, &cx, &cy, collisionOccurred, caughtByCamera, enteredIntelRoom);
    if (!collisionOccurred)
    {
      animation3("down", 4, &x, &y, &ax, &ay, &bx, &by, &cx, &cy, collisionOccurred, caughtByCamera, enteredIntelRoom);
    }

    //! COLLISION SCENARIO
    if (collisionOccurred)
    {
      system("cls");
      //! NEW CODE
      battleWithGuard();
      // check for the battle result using the health
      if (Player.health <= 0)
      {
        if (Player.lives <= 1)
        {
          Player.currentStage = 1;
          Player.lives = 4;
          restartLevel(x, y, "Out of lives, you wil start again from level 1\n");
          system("pause");
          system("cls");
          loadingScreen();
          system("cls");
          return;
        }
        else
        {
          restartLevel3(x, y, "Oops, Agent! You lost the battle. You will have to restart :(");
        }
      }
      else if (Player.lives <= 0)
      {

        Player.currentStage = 1;
        restartLevel(x, y, "You are out of lives. The game wil restart.");
        return;
      }
      else
      {
        x++; // move one position to down after a successful fight
      }
      endScenario3(&x, &y, collisionOccurred);
    }
    //! CAMERA SCENARIO
    else if (caughtByCamera)
    {
      system("cls");

      Option options[3] = {{'d', "Destroy the camera"}, {'s', "Fire a smoke"}, {'e', "Run Away and Escape"}};
      Option userOption = getOptions(options, 3, "Oh! You have been spotted by a camera. Your identity may be revealed. Do something!");

      system("cls");

      if (userOption.code == 'd')
      {
        restartLevel3(x, y, "Oops, Agent! You have been spotted destroying the camera. The guards have caught you.\n");
      }
      else if (userOption.code == 'e')
      {
        restartLevel3(x, y, "Oops, Agent! Your attempt to escape has failed. Remember you are in a super sensitive area. Be careful next time.\n");
      }
      else if (userOption.code == 's')
      {
        if (Player.smokes > 0)
        {

          cout << "Good job, Agent! You have concealed your identity.\n";
          Player.smokes--;
          map3[y - 3][x] = ' ';
          // remove the C1 and C2
          if (getCharacterAtPosition(x, y + 1) == '|')
          {
            x++;
          }
          else
          {
            y++;
          }
        }
        else
        {
          restartLevel3(x, y, "Oops, Agent! You ran out of smokes. Be cautious of your resources next time.\n");
        }
      }
      else
      {
        // Default case
      }
      if (Player.lives <= 0)
      {
        Player.currentStage = 1;
        Player.lives = 4;
        restartLevel(x, y, "Out of lives, you wil start again from level 1\n");
        system("pause");
        system("cls");
        loadingScreen();
        system("cls");
        return;
      }
      endScenario3(&x, &y, caughtByCamera);
    }
    else if (enteredIntelRoom)
    {
      system("cls");
      /**
      - enter Intel room
      - show a code
      - you enter the input
      - display certain number of tries
      - you enter one option
      - if correct then you move to next level (incase of level 1)
      - if wrong, then deduct one try, if at last try then restart level
      */
      int tries = 3;
      Code question = getSecret(Player.currentStage);
      // Code question = {"what is you name?", "Muhammad"};

      string userInput;
      bool isCorrect = false;

      animateText("You have entered an Intel Room. You must decode the secret correctly to progress\n", false);
      system("pause");
      system("cls");

      // Compare user input with the correct answer
      while (tries > 0 && !isCorrect)
      {
        cout << question.code << "\t\t\t Tries: " << tries << endl;
        cout << "Your answer: ";
        getline(cin, userInput);

        userInput.erase(0, userInput.find_first_not_of(" \t\n\r\f\v"));
        userInput.erase(userInput.find_last_not_of(" \t\n\r\f\v") + 1);

        if (userInput == question.answer)
        {
          cout << "You have successfully decoded the secret." << endl;
          Player.currentSecretsCompleted++;
          isCorrect = true;
        }
        else
        {
          cout << "Wrong answer. Try again!";
          tries--;
          cout << endl;
          system("pause>null"); // null or not, decide it later
          system("cls");
        }
      }
      // cout<<"You are out of tries";
      if (!isCorrect)
      {
        if (Player.lives > 1)
        {
          restartLevel(x, y, "Oops! You are out of tries. You will have to start again. Better luck next time.\n");
        }
        else
        {
          Player.currentStage = 1;
          Player.lives = 4;
          restartLevel(x, y, "Out of lives, you wil start again from level 1\n");
          system("pause");
          system("cls");
          loadingScreen();
          system("cls");
          return;
        }
        //! BOILERPLATE CODE FOR ENDING THE SCENARIO
        endScenario3(&x, &y, enteredIntelRoom);
      }
      else
      {
        /*
        - in case of level 1, directly move to level 2
        - in case of level 2, if one is completed then progress further and if two completed then move to level3
        */

        if (Player.currentSecretsCompleted == 3)
        {
          animateText("Congratulations! You have decoded all the secrets\n", false);
          bossFight();
          if (Player.health <= 0)
          {
            restartLevel3(x, y, "Oops! You have the lost with the final boss.\n");
            endScenario3(&x, &y, enteredIntelRoom);
          }
          else
          {
            SetConsoleColor(10);
            animateText("Agent, you've done it!\nThe final boss, a shadowy figure orchestrating chaos, has been unmasked and neutralized.\nAs the dust settles, you vanish into the shadows, leaving no trace of your covert operation.\nThe agency applauds your exceptional skills and strategic brilliance.\nThe world remains oblivious to the danger it narrowly escaped, thanks to your silent heroism.\nYour code name echoes in the intelligence community as a symbol of triumph and discretion.\nThe mission is complete, but the enigma of your identity persists.\n", false);
            SetConsoleColor(7);
            remove("game-data.txt");
            system("pause");
            exit(0);
          }
        }
        else
        {
          map3[y - 3][x] = ' ';
          y++;
          endScenario3(&x, &y, enteredIntelRoom);
        }
        // move to level 2
        // restartLevel(x, y, "");
      }

      // system("pause");
    }
  }
  if (Player.lives <= 0)
  {
    Player.currentStage = 1;
    Player.lives = 4;
    restartLevel(x, y, "Out of lives, you wil start again from level 1\n");
    system("pause");
    system("cls");
    loadingScreen();
    system("cls");
    return;
  }
}
// Function to obfuscate data
string obfuscateData(const string &data)
{
  string obfuscatedData = data;
  for (char &c : obfuscatedData)
  {
    // Perform bitwise XOR operation with a key (you can change the key)
    c ^= 0xAA; // Example key, choose a different value for your application
  }
  return obfuscatedData;
}

// Function to deobfuscate data
string deobfuscateData(const string &obfuscatedData)
{
  // Deobfuscation is the same as obfuscation with XOR, so use the same function
  return obfuscateData(obfuscatedData);
}

void saveGameData(const string &filename)
{
  ofstream outFile(filename);

  if (outFile.is_open())
  {
    // Serialize the struct to a string
    // !REMEMBER THE ORDER STRICTLY
    //   int lives = 3;
    // int health = 100;
    // int kills = 0;
    // int ammo = 3;
    // int smokes = 3;
    // int points = 0;
    // int bandages = 3;
    // int currentStage = 1;
    // int currentSecretsCompleted = 0;
    string serializedData =
        to_string(Player.lives) + "," +
        to_string(Player.health) + "," +
        to_string(Player.kills) + "," +
        to_string(Player.ammo) + "," +
        to_string(Player.smokes) + "," +
        to_string(Player.points) + "," +
        to_string(Player.bandages) + "," +
        to_string(Player.currentStage) + "," +
        to_string(Player.currentSecretsCompleted);

    // Obfuscate the serialized data
    string obfuscatedData = obfuscateData(serializedData);

    // Save the obfuscated data to the file
    outFile << obfuscatedData;
    // outFile << obfuscatedData;
    outFile.close();

    // cout << "Obfuscated game data saved successfully.\n";
  }
  else
  {
    cerr << "Unable to open the file for writing.\n";
  }
}

// Function to load obfuscated game data from a file
bool loadGameData(const string &filename)
{
  ifstream inFile(filename);

  if (inFile.is_open())
  {
    // Read obfuscated data from the file
    string obfuscatedData;
    inFile >> obfuscatedData;
    inFile.close();

    // De-obfuscate the data
    string serializedData = deobfuscateData(obfuscatedData);

    // Parse the serialized data to extract individual fields using stringstream
    stringstream ss(serializedData);
    vector<int> playerData;
    string field;

    while (getline(ss, field, ','))
    {
      playerData.push_back(stoi(field));
    }

    // Reconstruct the Player struct

    // Check for invalid data (optional)
    if (playerData[0] == 0 || playerData[1] == 0)
    {
      cerr << "Invalid game data loaded.\n";
      return false;
    }
    Player.lives = playerData[0];
    Player.health = 100;
    Player.kills = 0;
    Player.ammo = 3;
    Player.smokes = 3;
    Player.points = 0;
    Player.bandages = 3;
    Player.bandages = 3;
    Player.currentStage = playerData[7];
    Player.currentSecretsCompleted = 0;

    // Use the reconstructed Player struct as needed
    cout << "Obfuscated game data loaded successfully.\n";

    return true;
  }
  else
  {
    // cerr << "Unable to open the file for reading.\n";
    return false;
  }
}
bool firstAttempt = true;
void game()
{
  // Player.currentStage = 3;
  while (Player.currentStage <= 3)
  {

    switch (Player.currentStage)
    {
    case 1:
      Player.currentSecretsCompleted = 0;
      if (!firstAttempt)
      {
        system("cls");
        animateText("Saving your game data.....\n", false);
        saveGameData("game-data.txt");
        loadingScreen();
        system("cls");
      }
      level1();
      firstAttempt = false;
      break;
    case 2:
      Player.currentSecretsCompleted = 0;
      animateText("Saving your game data.....\n", false);
      saveGameData("game-data.txt");
      loadingScreen();
      system("cls");
      level2();
      break;
    case 3:
      Player.currentSecretsCompleted = 0;
      system("cls");
      animateText("Saving your game data.....\n", false);
      saveGameData("game-data.txt");
      loadingScreen();
      system("cls");
      level3();
      break;
    }
  }
}
void reinitializePlayer()
{
  Player.lives = 3;
  Player.health = 100;
  Player.kills = 0;
  Player.ammo = 3;
  Player.smokes = 3;
  Player.points = 0;
  Player.bandages = 3;
  Player.currentStage = 1;
  Player.currentSecretsCompleted = 0;
}
int main()
{
  // srand(time(NULL));
  system("cls");
  showCursor(false);

  introScreen();
  displayStory();

  while (true)
  {

    Option loadOptions[2] = {{'s', "Start a New Game"}, {'l', "Load an Existing Game"}};
    Option userOption = getOptions(loadOptions, 2, "What do you want to do?");
    // execute based on user input
    if (userOption.code == 'l')
    {
      loadingScreen("Loading the game data ...");
      system("cls");
      /*
      - show loading screen
      - load the user data
      - check if there is any
      - if all not empty, then set it as data and then start the game
      - if empty, then go back to options, and keep in loop unless the user selects "Start a new game"
      */
      if (loadGameData("game-data.txt"))
      {
        animateText("Data loaded successfully!", false);
        system("pause");
        break;
      }
      else
      {
        animateText("No previous data found :(\n", false);
        system("pause");
        reinitializePlayer();
      }
    }
    else
    {
      loadingScreen("Starting a new game ...");
      break;
    };
  }
  system("cls");
  // cout << endl;

  // transition to map1 1
  // level1();
  game();

  return 0;
}
