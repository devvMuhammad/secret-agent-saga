#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
void battleWithGuard();
void bossFight();
void gameState(int);
void gameEndingMessage(int);
using namespace std;
//! these are all the stats of my player throughout the game
struct Player
{
  int lives;        //*3
  int health;       //*100
  int kills;        // the  number of kills per stage
  int ammo;         //*3
  int smokes;       //*3
  int points;       //* the number of kills + number of lives gives the points for the game stats and the game summary at the end
  int bandages;     //*3
  int currentStage; //*starts from 1 to 3
} myPlayer;

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
//! This struct has been used to create an underlined option in the function getOptions(Option[],int)
struct Option
{
  // bool isRight;
  char code;
  string optionText;
};
//! function prototype for the option animation
Option getOptions(Option[], int);

int main(void)
{
  srand(time(NULL));
  //*setting values for my player
  myPlayer.health = 100;
  myPlayer.lives = 3;
  myPlayer.bandages = 2;
  myPlayer.kills = 0;
  myPlayer.ammo = 3;
  myPlayer.smokes = 3;
  myPlayer.points = 0; //*will be calculated at the end of every stage using the formula kills+lives and awarded accordingly
  myPlayer.currentStage = 1;
  battleWithGuard(); //* function used for fighting with guards
  bossFight();       //*function used for fighting with the boss
  return 0;
}

//! BATTLESYSTEM CODE Only For Guard
void battleWithGuard()
{
  system("cls");
  string message = "Oh!You got caught by a guard,the battle with the guard begins";
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
  while (guard.health != 0 && myPlayer.health > 0)
  {
    //! using the animation function I have done this so that I can get a struct
    myOption = getOptions(options, 2);
    //! myOption.code gives me the selected options' corresponding char
    switch (myOption.code)
    {
    //*This is the case in which i shoot the guard directly
    case 's':
      myPlayer.ammo -= 2;
      guard.health = 0;
      //*The case in which we just use two bullets and kill the guard directly
      cout << "You have killed the guard using the silenced pistol.You used 2 bullets in the process" << endl;
      cout << "You received ";
      //! This is the reward that we get on killing each guard
      int battleReward;
      battleReward = rand() % 3 + 1;
      if (battleReward == 1)
      {
        myPlayer.ammo++;
        cout << "1 bullet" << endl;
      }
      else if (battleReward == 2)
      {
        myPlayer.smokes++;
        cout << "1 smoke" << endl;
      }
      else
      {
        myPlayer.bandages++;
        cout << "1 bandage" << endl;
      }
      system("pause");
      break;
    //*The case in which i have to fight the guard
    case 'f':
      //! either i die or the guard dies
      while (guard.health != 0 && myPlayer.health > 0)
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
          myPlayer.health -= rand() % (myPlayer.currentStage * 10);
          cout << "Your health has become " << myPlayer.health << endl;
          //! The rewarding system
          if (guard.health == 0)
          {
            int battleReward;
            battleReward = rand() % 3 + 1;
            if (battleReward == 1)
            {
              myPlayer.ammo++;
              cout << "Your ammo has been increased by 1" << endl;
            }
            else if (battleReward == 2)
            {
              myPlayer.smokes++;
              cout << "Your smokes have been increased by 1" << endl;
            }
            else
            {
              myPlayer.bandages++;
              cout << "Your bandages have been increased by 1" << endl;
            }
          }
          system("pause");
          break;
        case 'p':
          //! I use my pistol so he gets a damage of 50
          if (myPlayer.ammo > 0)
          {
            myPlayer.ammo -= 1;
            guard.health -= 50;
            if (guard.health < 0)
            {
              guard.health = 0;
            }
            cout << "The health of the guard has become " << guard.health << endl;
            myPlayer.health -= rand() % (myPlayer.currentStage * 10);
            if (myPlayer.health < 0)
            {
              myPlayer.health = 0;
            }
            if (myPlayer.health == 0 && myPlayer.bandages > 0)
            {
              myPlayer.health += 40;
              myPlayer.bandages -= 1;
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
                myPlayer.ammo++;
                cout << "Your ammo has been increased by 1" << endl;
              }
              else if (battleReward == 2)
              {
                myPlayer.smokes++;
                cout << "Your smokes have been increased by 1" << endl;
              }
              else
              {
                myPlayer.bandages++;
                cout << "Your bandages have been increased by 1" << endl;
              }
            }
            cout << "Your health has become " << myPlayer.health << endl;
          }
          else
          {
            cout << "You do not have sufficient ammo" << endl;
          }
          system("pause");
          break;
          //! The case in which i use my bandage and my health increases
        case 'u':
          if (myPlayer.bandages > 0)
          {
            myPlayer.bandages -= 1;
            myPlayer.health += 40;
            cout << "You have used a bandage" << endl
                 << "Your new health is " << myPlayer.health << endl;
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
//! written for the final boss
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
    cout << messages[0][i];
    Sleep(20);
  }
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
  while (boss.health != 0 && myPlayer.health > 0)
  {
    myOption = getOptions(options, 2);
    //*The returned char according to my selected option
    switch (myOption.code)
    {
    case 's':
      system("cls");
      if (myPlayer.ammo > 1)
      {
        myPlayer.ammo -= 2;
        cout << "Oh what!The boss has an armor he does not get as damaged as other guards do!" << endl;
        boss.health -= 70;
        cout << "You have damaged the boss using the silenced pistol.You used 2 bullets in the process" << endl;
        cout << "The boss's helath is now " << boss.health << endl;
        myPlayer.health -= rand() % (40);
        if (myPlayer.health < 0)
        {
          myPlayer.health = 0;
        }
        cout << "Your health has become " << myPlayer.health << endl;
      }
      else
      {
        cout << "You do not have sufficient ammo" << endl;
      }
      system("pause");
      break;
    case 'f':
      while (boss.health != 0 && myPlayer.health > 0)
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
          myPlayer.health -= rand() % (40);
          if (myPlayer.health < 0)
          {
            myPlayer.health = 0;
          }
          //! incase my health goes to zero but i still have bandages then the player will automatically use the bandage to keep the game running
          if (myPlayer.health == 0 && myPlayer.bandages > 0)
          {
            myPlayer.bandages -= 1;
            myPlayer.health += 40;
            cout << "You have used a bandage " << endl;
          }
          cout << "Your health has become " << myPlayer.health << endl;
          system("pause");
          break;
          //*The use of pistol
        case 'p':
          if (myPlayer.ammo > 0)
          {
            myPlayer.ammo -= 1;
            boss.health -= 35;
          }
          else
          {
            cout << "You do not have sufficient ammo" << endl;
            system("pause");
            break;
          }
          if (boss.health < 0)
          {
            boss.health = 0;
            break;
          }
          cout << "The health of the boss has become " << boss.health << endl;
          myPlayer.health -= rand() % (myPlayer.currentStage * 10);
          if (myPlayer.health < 0)
          {
            myPlayer.health = 0;
          }
          //! just incase my health goes to zero but i still have bandages
          if (myPlayer.health == 0 && myPlayer.bandages > 0)
          {
            myPlayer.health += 40;
            myPlayer.bandages -= 1;
            cout << "You have used your remaining bandages." << endl;
          }
          cout << "Your health has become " << myPlayer.health << endl;
          system("pause");
          break;
          //! case for the use of bandages
        case 'u':
          if (myPlayer.bandages > 0)
          {
            myPlayer.bandages -= 1;
            myPlayer.health += 40;
            cout << "You have used a bandage" << endl;
            cout << "Your health is " << myPlayer.health << endl;
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
  gameState(boss.health);
  gameEndingMessage(boss.health);
}

//! This is the function that has been used for the animated options
Option getOptions(Option options[], int numOptions)
{
  //*the current option
  int activeOption = 0;
  while (true)
  {
    system("cls");
    //! this loop displays the options in the form that the current option is underlined
    for (int i = 0; i < numOptions; i++)
    {
      cout << (i == activeOption ? "\033[1;4m" : "") << options[i].optionText << "\033[0m" << endl;
    }
    system("pause>null");
    //*when enter is pressed the loop is broken
    if (GetAsyncKeyState(VK_RETURN) & 0x8000)
    {
      break;
    }
    //*when upward key is pressed
    if (GetAsyncKeyState(VK_UP))
    {
      activeOption = activeOption == 0 ? 0 : activeOption - 1;
    }
    //*when downward key is pressed
    if (GetAsyncKeyState(VK_DOWN))
    {
      activeOption = activeOption == numOptions - 1 ? (numOptions - 1) : activeOption + 1;
    }
    //! Escape key
    if (GetAsyncKeyState(VK_ESCAPE))
    {
      break;
    }
  }
  return options[activeOption];
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
    myPlayer.lives--;
  }
  system("pause");
}
//! just a special message in case you win the game
void gameEndingMessage(int health)
{
  system("cls");
  string gameEndMessage = "Agent 47 you have won the game and finally the notorius organization has been destroyed once and for all!";
  for (size_t i = 0; i < gameEndMessage.length(); i++)
  {
    cout << gameEndMessage[i];
    Sleep(20);
  }
  cout << endl;
}