#include <iostream>
#include <fstream>
using namespace std;

struct Player
{
  int lives;
  int health;
  int kills;
  int ammo;
  int smokes;
  int points;
  int currentSecretsCompleted;
  int bandages;
  int currentStage;
} Player;

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

// Function to save obfuscated game data to a file
void saveObfuscatedGameData(const string &filename)
{
  ofstream outFile(filename);

  if (outFile.is_open())
  {
    // Serialize the struct to a string
    // !REMEMBER THE ORDER STRICTLY
    // Player.lives = 2;
    // Player.health = 100;
    // Player.kills = 0;
    // Player.ammo = 3;
    // Player.smokes = 3;
    // Player.points = 0;
    // Player.currentSecretsCompleted = 0;
    // Player.bandages = 2;
    // Player.currentStage = 3;
    string serializedData =
        to_string(Player.lives) + "," +
        to_string(Player.health) + "," +
        to_string(Player.kills) + "," +
        to_string(Player.ammo) + "," +
        to_string(Player.points) + "," +
        to_string(Player.currentSecretsCompleted) + "," +
        to_string(Player.bandages) + "," +
        to_string(Player.currentStage);

    // Obfuscate the serialized data
    string obfuscatedData = obfuscateData(serializedData);

    // Save the obfuscated data to the file
    outFile << obfuscatedData;
    outFile.close();

    cout << "Obfuscated game data saved successfully.\n";
  }
  else
  {
    cerr << "Unable to open the file for writing.\n";
  }
}

// Function to load obfuscated game data from a file
void loadObfuscatedGameData(const string &filename)
{
  ifstream inFile(filename);

  if (inFile.is_open())
  {
    // Read obfuscated data from the file
    string obfuscatedData;
    inFile >> obfuscatedData;

    // Deobfuscate the data
    string decodedData = deobfuscateData(obfuscatedData);

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
    sscanf(decodedData.c_str(), "%d,%d,%d,%d,%d,%d,%d,%d,%d,", &Player.lives, &Player.health, &Player.kills, &Player.ammo, &Player.smokes, &Player.points, &Player.currentSecretsCompleted, &Player.bandages, &Player.currentStage);
    // sscanf(obfuscatedData.c_str(), "%d,%d,%d,%d", &Player.lives, &Player.health, &Player.kills, &Player.ammo, &Player.smokes, &Player.points, &Player.currentSecretsCompleted, &Player.bandages, &Player.currentStage);

    inFile.close();

    cout << "Obfuscated game data loaded successfully.\n";
  }
  else
  {
    cerr << "Unable to open the file for reading.\n";
  }
}

int main()
{

  // Save obfuscated game data to a file
  saveObfuscatedGameData("obfuscated_game_data.txt");

  // Load obfuscated game data from the file
  loadObfuscatedGameData("obfuscated_game_data.txt");

  cout << "Loaded game data:\n";
  cout << "Lives: " << Player.lives << endl;
  cout << "Health: " << Player.health << endl;
  cout << "Points: " << Player.kills << endl;
  cout << "Kills: " << Player.ammo << endl;
  cout << "Smokes: " << Player.smokes << endl;
  cout << "Ppints: " << Player.points << endl;
  cout << "Current Secrets Completed: " << Player.currentSecretsCompleted << endl;
  cout << "Bandages: " << Player.bandages << endl;
  cout << "Current Stage: " << Player.currentStage << endl;

  return 0;
}
