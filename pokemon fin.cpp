#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

struct Pokemon {
  int Pokemon_Number;
  string Name;
  string Type;
  string Region;
  int Catch;
  string Dex_Entry;
  int Number_caught;
  int Number_seen;
};

void printmenu();
string lower(string choice);
string upper(string choice);
void hunt(Pokemon *dex, string &choice, int &pokeball, int &greatball, int &ultraball, int &Number_caught, int &Number_seen, int PokemonSize);
void pokedex(string name, Pokemon* dex, int PokemonSize);
void pokemon(string userName, Pokemon* dex, int PokemonSize);
void pokemoncaught(int Number_caught, int Number_seen);
void inventory(int pokeball, int greatball, int ultraball);

int main() {
  srand(time(NULL));
  string choice, userName;
  ifstream IN;
  int PokemonSize;
  Pokemon *dex;
  int pokeball = 10, greatball = 10, ultraball = 10;
  int Number_caught = 0, Number_seen = 0;
  cout << "What's your name, trainer? > ";
  getline(cin, userName);
  cout << "Welcome, " << userName << " , to the Programming I Safari Zone!\nYou'll have 30 chances to catch Pokemon, make them count!\nThe hunt will end when you choose or when you run out of Pokeballs." << endl;

  IN.open("poke.txt");

  if (!IN) {
    cout << "POKE.TXT FILE FAILED TO OPEN, ENDING PROGRAM." << endl;
    return 1;
  }

  IN >> PokemonSize;
  IN.ignore(); 
  dex = new Pokemon[PokemonSize];

  for (int i = 0; i < PokemonSize; i++) {
    IN >> dex[i].Pokemon_Number;
    IN.ignore();
    getline(IN, dex[i].Name, ',');
    getline(IN, dex[i].Type, ',');
    getline(IN, dex[i].Region, ',');
    IN >> dex[i].Catch;
    IN.ignore();
    getline(IN, dex[i].Dex_Entry);
    dex[i].Number_caught = 0;
    dex[i].Number_seen = 0;
  }

  IN.close();

  printmenu();

  while (true) {
    cout << "\nSelection > ";
    getline(cin, choice);
    choice = lower(choice);

    if (choice == "hunt") {
      hunt(dex, choice, pokeball, greatball, ultraball, Number_caught, Number_seen, PokemonSize);
    } else if (choice == "pokemon") {
      pokemon(userName, dex, PokemonSize);
    } else if (choice == "statistics") {
      pokemoncaught(Number_caught, Number_seen);
    } else if (choice == "inventory") {
      inventory(pokeball, greatball, ultraball);
    } else if (choice.find("dex") != string::npos) {
      string pokemonName = choice.substr(4); // Get the Pokémon name after "dex "
      pokedex(pokemonName, dex, PokemonSize);
    } else if (choice == "menu") {
      printmenu();
    } else if (choice == "exit") {
      pokemoncaught(Number_caught, Number_seen);
      break;
    } else {
      cout << "Invalid option. Please try again." << endl;
    }
  }

  delete[] dex;
  return 0;
}

string lower(string choice) {
  int i = 0;
  while (choice[i]) {
    choice[i] = tolower(choice[i]);
    i++;
  }
  return choice;
}

string upper(string choice) {
  int i = 0;
  while (choice[i]) {
    choice[i] = toupper(choice[i]);
    i++;
  }
  return choice;
}

void pokedex(string name, Pokemon* dex, int PokemonSize) {
  bool found = false;
  for (int i = 0; i < PokemonSize; i++) {
    if (lower(dex[i].Name) == lower(name)) {
      found = true;
      cout << "NAME: " << dex[i].Name << endl;
      cout << "Type: " << dex[i].Type << endl;
      cout << "\"" << dex[i].Dex_Entry << "\"" << endl;
    }
  }
  if (!found) cout << "No Pokedex entry for " << upper(name) << endl;
}

void pokemon(string userName, Pokemon* dex, int PokemonSize) {
  bool invfound = false;
  cout << userName << "'s POKEMON:" << endl;
  for (int i = 0; i < PokemonSize; i++) {
    if (dex[i].Number_caught > 0) {
      invfound = true;
      cout << "no " << dex[i].Pokemon_Number << "   " << dex[i].Name << endl;
    }
  }
  if (!invfound) cout << "No Pokedex entry for " << endl;
  cout << endl;
}

void pokemoncaught(int Number_caught, int Number_seen) {
  if (Number_seen == 0) Number_seen = 1;
  cout << "\n\nSTATISTICS:\n";
  cout << "------------------------\n";
  cout << "Caught: " << Number_caught << "\tSeen: " << Number_seen << "\n";
  cout << "Total Catch Percent: " << (static_cast<double>(Number_caught) / Number_seen) * 100 << "%\n";
  cout << endl;
}

void printmenu() {
  cout << "\nHUNT\t(Go hunting for Pokemon!)" << endl;
  cout << "POKEMON\t(See the Pokemon you've caught.)" << endl;
  cout << "STATISTICS\t(See your catch statistics.)" << endl;
  cout << "INVENTORY\t(See your current inventory.)" << endl;
  cout << "DEX NAME\t(ex: DEX BULBASAUR would view Bulbasaur's Pokedex entry.)" << endl;
  cout << "MENU\t(Reprint this menu.)" << endl;
  cout << "EXIT" << endl;
}

void inventory(int pokeball, int greatball, int ultraball) {
  cout << "You have:\n";
  cout << pokeball << " PokeBalls\n";
  cout << greatball << " Great Balls\n";
  cout << ultraball << " Ultra Balls\n";
}

void hunt(Pokemon *dex, string &choice, int &pokeball, int &greatball, int &ultraball, int &Number_caught, int &Number_seen, int PokemonSize) {
  int regionMin, regionMax;
  cout << "Enter the region you want to hunt in (Kanto, Johto, Hoenn, Sinnoh): ";
  getline(cin, choice);
  choice = lower(choice);

  if (choice == "kanto") {
    regionMin = 1;
    regionMax = 151;
  } else if (choice == "johto") {
    regionMin = 152;
    regionMax = 251;
  } else if (choice == "hoenn") {
    regionMin = 252;
    regionMax = 386;
  } else if (choice == "sinnoh") {
    regionMin = 387;
    regionMax = 493;
  } else {
    cout << "Invalid region. Returning to menu." << endl;
    return;
  }

  int randomIndex = rand() % (regionMax - regionMin + 1) + regionMin - 1;

  cout << "A wild " << dex[randomIndex].Name << " has appeared!" << endl;

  if (dex[randomIndex].Catch == 0) {
    cout << "Oh! That's a baby Pokemon! We'll take them to the daycare." << endl;
    dex[randomIndex].Number_seen++;
    dex[randomIndex].Number_caught++;
    Number_seen++;
    Number_caught++;
    return;
  }

  int ballChoice;
  cout << "Choose a ball to throw:\n1 - Poke Ball (" << pokeball << " left)\n2 - Great Ball (" << greatball << " left)\n3 - Ultra Ball (" << ultraball << " left)\nSelection > ";
  cin >> ballChoice;
  cin.ignore();

  int catchRate = dex[randomIndex].Catch;

  if (ballChoice == 1) {
    if (pokeball <= 0) {
      cout << "You have no Poke Balls left!" << endl;
      return;
    }
    pokeball--;
  } else if (ballChoice == 2) {
    if (greatball <= 0) {
      cout << "You have no Great Balls left!" << endl;
      return;
    }
    catchRate += 20;
    greatball--;
  } else if (ballChoice == 3) {
    if (ultraball <= 0) {
      cout << "You have no Ultra Balls left!" << endl;
      return;
    }
    catchRate += 40;
    ultraball--;
  } else {
    cout << "Invalid choice. The Pokemon ran away!" << endl;
    return;
  }

  int randomCatch = rand() % 100 + 1;

  if (randomCatch <= catchRate) {
    cout << "Congratulations! You caught " << dex[randomIndex].Name << "!" << endl;
    dex[randomIndex].Number_caught++;
    Number_caught++;
  } else {
    cout << "Oh no! The " << dex[randomIndex].Name << " ran away!" << endl;
  }

  dex[randomIndex].Number_seen++;
  Number_seen++;
}
