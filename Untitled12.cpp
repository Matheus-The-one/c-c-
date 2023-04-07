#include <iostream>
#include <string>
#include <map>

int main() {
  std::map<std::string, int> stats;
  std::string name;
  int strength, intelligence, agility;

  std::cout << "Enter your character's name: ";
  std::cin >> name;
  std::cout << "Enter your character's strength (1-10): ";
  std::cin >> strength;
  std::cout << "Enter your character's intelligence (1-10): ";
  std::cin >> intelligence;
  std::cout << "Enter your character's agility (1-10): ";
  std::cin >> agility;

  stats["strength"] = strength;
  stats["intelligence"] = intelligence;
  stats["agility"] = agility;

  std::cout << "Welcome to your quest, " << name << "!" << std::endl;
  std::cout << "Your strength is " << stats["strength"] << ", intelligence is " << stats["intelligence"] << ", and agility is " << stats["agility"]

<< "." << std::endl;

std::cout << "You find yourself in a dark dungeon. You can either (1) fight the monsters or (2) try to sneak past them." << std::endl;
std::cout << "Enter your choice (1/2): ";
int choice;
std::cin >> choice;

if (choice == 1) {
if (stats["strength"] >= 8) {
std::cout << "You successfully defeat the monsters and find the treasure! Congratulations, you win the game!" << std::endl;
} else {
std::cout << "You try to fight the monsters, but your strength is not high enough. You die. Game over." << std::endl;
}
} else if (choice == 2) {
if (stats["agility"] >= 8) {
std::cout << "You successfully sneak past the monsters and find the treasure! Congratulations, you win the game!" << std::endl;
} else {
std::cout << "You try to sneak past the monsters, but your agility is not high enough. You die. Game over." << std::endl;
}
} else {
std::cout << "Invalid choice. Game over." << std::endl;
}
return 0;
}
