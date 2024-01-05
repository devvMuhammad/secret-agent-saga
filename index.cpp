#include <iostream>
#include <windows.h>
#include <iomanip>
#include <cstdlib>
using namespace std;

const int initialX = 4;
const int initialY = 8;
const int initialAX = 6;
const int initialAY = 9;
const int initialBX = 30;
const int initialBY = 9;

struct Option
{
  // bool isRight;
  char code;
  string optionText;
};
struct Player
{
  int lives = 5;
  int health = 100;
  int kills = 0;
  int ammo = 3;
  int smokes = 2;
  int points = 0;
  int bandages = 2;
  int currentStage = 1;
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

struct Code
{
  string code;
  string answer;
} code;

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
void gotoxy(short x, short y)
{
  COORD pos = {x, y};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void showCursor(bool show)
{
  HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursorInfo;
  GetConsoleCursorInfo(consoleHandle, &cursorInfo);
  cursorInfo.bVisible = show;
  SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void introScreen()
{
  system("cls");
  cout << "\t\t\t\tSECRET AGENT SAGA" << endl;
  cout << "You are a spy and your goal is to kill the mafia boss of an extremely notorious organization." << endl
       << endl;
  cout << "\t\t\t";
  for (int i = 0; i < 30; i++)
  {
    printf("%c", 177);
  }
  cout << "\r";
  cout << "\t\t\t";

  for (size_t i = 0; i < 30; i++)
  {
    printf("%c", 219);
    Sleep(10);
  }

  cout << endl;
  cout << "\t\t\t";
  cout << endl;
  system("pause");
  system("cls");
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
    animateText(texts[i]);
    cout << endl;
  }
  system("cls");
}

void displayMap(string map[], size_t size)
{
  cout << "\033[1m" << setw(7) << "Stage:"
       << "\033[0m" << setw(2) << Player.currentStage << "\t\033[1mObjectives:\033[0m "
       << "3 Kills and 2 Secret Codes" << endl;
  cout << "\033[1m" << setw(7) << "Points:"
       << "\033[0m" << setw(2) << Player.points << "\t\033[1mLives:\033[0m" << setw(2) << Player.lives << "\t\033[1mHealth: \033[0m" << setw(2) << Player.health << endl;
  cout << "\033[1m" << setw(7) << "Ammo:"
       << "\033[0m" << setw(2) << Player.ammo << "\t\033[1mSmokes:\033[0m" << setw(2) << Player.smokes << endl;

  // return 0;
  for (int i = 0; i < size; i++)
  {
    cout << map[i];
  }
}

char getCharacterAtPosition(short x, short y)
{
  return map1[y - 4][x];
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
  for (int i = 0; i < 3; ++i)
  {
    // check if the next character is the entry to the camera room
    moveCharacter(x, y);

    if ((*x == *ax && *y == *ay) || (*x == *bx && *y == *by))
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
    Sleep(200);
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
    Player.lives--;
  }
  system("pause");
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
        //*The case in which we just use two bullets and kill the guard directly
        cout << "You have killed the guard using the silenced pistol. You used 2 bullets in the process" << endl;
        cout << "You received ";
        //! This is the reward that we get on killing each guard
        int battleReward;
        battleReward = rand() % 3 + 1;
        if (battleReward == 1)
        {
          Player.ammo++;
          cout << "1 bullet" << endl;
        }
        else if (battleReward == 2)
        {
          Player.smokes++;
          cout << "1 smoke" << endl;
        }
        else
        {
          Player.bandages++;
          cout << "1 bandage" << endl;
        }
      }
      else
      {
        cout << "You do not have enough ammo to kill the guard directly" << endl;
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
          }
          cout << "The health of the guard has become " << guard.health << endl;
          Player.health -= rand() % (Player.currentStage * 10);
          cout << "Your health has become " << Player.health << endl;
          //! The rewarding system
          if (guard.health == 0)
          {
            int battleReward;
            battleReward = rand() % 3 + 1;
            if (battleReward == 1)
            {
              Player.ammo++;
              cout << "Your ammo has been increased by 1" << endl;
            }
            else if (battleReward == 2)
            {
              Player.smokes++;
              cout << "Your smokes have been increased by 1" << endl;
            }
            else
            {
              Player.bandages++;
              cout << "Your bandages have been increased by 1" << endl;
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
              //! again the battle reward
              int battleReward;
              battleReward = rand() % 3 + 1;
              if (battleReward == 1)
              {
                Player.ammo++;
                cout << "Your ammo has been increased by 1" << endl;
              }
              else if (battleReward == 2)
              {
                Player.smokes++;
                cout << "Your smokes have been increased by 1" << endl;
              }
              else
              {
                Player.bandages++;
                cout << "Your bandages have been increased by 1" << endl;
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
  gameState(guard.health);
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

  if (level == 1)
  {
    return codesArrayLevel1[rand() % 5];
  }
  else if (level == 2)
  {
    return codesArrayLevel2[rand() % 5];
  }
  else if (level == 3)
  {
    return codesArrayLevel3[rand() % 9];
  }
}

void endScenario(int *x, int *y, bool &scenarioCondition)
{
  system("pause");
  system("cls");
  scenarioCondition = false;
  // render the map1 again
  cout << endl; // !so the map1 is rendered one line below
  displayMap(map1, 12);

  gotoxy(*x, *y);
  cout << "@";
}

void level1()
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
    animation("down", &x, &y, &ax, &ay, &bx, &by, collisionOccurred, caughtByCamera, enteredIntelRoom);

    //! COLLISION SCENARIO
    if (collisionOccurred)
    {
      system("cls");
      //! NEW CODE
      battleWithGuard();
      // check for the battle result using the health
      if (Player.health <= 0)
      {
        restartLevel(x, y, "Oops, Agent! You lost the battle. You will have to restart :(");
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
          cout << "You have successfully decoded the secret. You now move on to level 2";
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
        restartLevel(x, y, "Oops! You are out of tries. You will have to start again. Better luck next time.\n");

        //! BOILERPLATE CODE FOR ENDING THE SCENARIO
        endScenario(&x, &y, enteredIntelRoom);
      }
      else
      {
        // move to level 2
        restartLevel(x, y, "");
      }

      // system("pause");
    }
  }
}

void level2()
{
  showCursor(false);
  // system()
  int ax, ay, bx, by;
  int x = initialX;
  int y = initialY;

  // displayMap(map2, 12);

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
    animation("down", &x, &y, &ax, &ay, &bx, &by, collisionOccurred, caughtByCamera, enteredIntelRoom);

    //! COLLISION SCENARIO
    if (collisionOccurred)
    {
      system("cls");
      //! NEW CODE
      battleWithGuard();
      // check for the battle result using the health
      if (Player.health <= 0)
      {
        restartLevel(x, y, "Oops, Agent! You lost the battle. You will have to restart :(");
      }
      else
      {
        x++; // move one position to the right after a successful fight
        map1[ax - 4][y] = ' ';
        // map[ax-4][y] = ' ';
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
          cout << "You have successfully decoded the secret. You now move on to level 2";
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
        restartLevel(x, y, "Oops! You are out of tries. You will have to start again. Better luck next time.\n");

        //! BOILERPLATE CODE FOR ENDING THE SCENARIO
        endScenario(&x, &y, enteredIntelRoom);
      }
      else
      {
        // move to level 2
        restartLevel(x, y, "");
      }

      // system("pause");
    }
  }
}

void game()
{
  switch (Player.currentStage)
  {
  case 1:
    level1();
    break;
    // case 2:
    // case 2:
    //   map2();
    //   break;
    // case 3:
    //   map3();
    //   break;
  }
}

int main()
{
  system("cls");
  showCursor(false);

  introScreen();
  displayStory();

  Option loadOptions[2] = {{'s', "Start a New Game"}, {'l', "Load an Existing Game"}};
  getOptions(loadOptions, 2, "What do you want to do?");

  system("cls");
  cout << endl;

  // transition to map1 1
  // level1();
  game();

  return 0;
}