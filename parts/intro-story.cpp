#include <iostream>
#include <windows.h>
using namespace std;

// function protoypes
void introScreen();
void displayStory();
void animateText(string);
string getOptions(string[], int);

// main function
int main()
{
  introScreen();
  displayStory();
  string loadOptions[2] = {"Start a New Game", "Load an Existing Game"};
  getOptions(loadOptions, 2);
}

// function definitions
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
void animateText(string sentence)
{
  for (int j = 0; j < sentence.length(); j++)
  {
    // skip the text if enter is pressed during the animation, put changes here
    Sleep(20);
    if ((GetAsyncKeyState(VK_RETURN) & 0x8000) && j > 2)
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
string getOptions(string options[], int numOptions)
{
  int activeOption = 0;
  while (true)
  {
    system("cls");
    // cout << GetAsyncKeyState(VK_RETURN);
    cout << "\t\tSelect an option to start a game\n";
    for (int i = 0; i < numOptions; i++)
    {
      cout << "- " << (i == activeOption ? "\033[1;4m" : "") << options[i] << "\033[0m" << endl;
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