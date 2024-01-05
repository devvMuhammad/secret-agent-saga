#include <iostream>
#include <fstream>
using namespace std;
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
bool loadGameData(const string &filename)
{
  ifstream inFile(filename);

  if (inFile.is_open())
  {
    // Read obfuscated data from the file
    string obfuscatedData;
    inFile >> obfuscatedData;

    // Deobfuscate the data
    // string decodedData = deobfuscateData(obfuscatedData);

    // !Deserialize the data back to the struct in this order
    //   int lives = 5;
    // int health = 100;
    // int kills = 0;
    // int ammo = 3;
    // int smokes = 3;
    // int points = 0;
    // int currentSecretsCompleted = 0;
    // int bandages = 2;
    // int currentStage = 3;
    // sscanf(decodedData.c_str(), "%d,%d,%d,%d,%d,%d,%d,%d,%d,", &Player.lives, &Player.health, &Player.kills, &Player.ammo, &Player.smokes, &Player.points, &Player.currentSecretsCompleted, &Player.bandages, &Player.currentStage);
    sscanf(obfuscatedData.c_str(), "%d,%d,%d,%d,%d,%d,%d,%d,%d,", &Player.lives, &Player.health, &Player.kills, &Player.ammo, &Player.smokes, &Player.points, &Player.currentSecretsCompleted, &Player.bandages, &Player.currentStage);
    // sscanf(obfuscatedData.c_str(), "%d,%d,%d,%d", &Player.lives, &Player.health, &Player.kills, &Player.ammo, &Player.smokes, &Player.points, &Player.currentSecretsCompleted, &Player.bandages, &Player.currentStage);
    if (Player.lives == 0 && Player.health == 0)
    {
      cout << "No previous game to load :(\n";
      return false;
    }
    else
    {
      cout << "Data loaded successfully.\n";
      return true;
    }
    inFile.close();
  }
  else
  {
    // cerr << "Unable to open the file for reading.\n";
    cout << "No previous game to load :(";
    return false;
  }
}
int main()
{
  cout << loadGameData("game-data.txt");
  return 0;
}