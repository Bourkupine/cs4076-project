#include "recipe.h"

Recipe::Recipe(QString name, bool fav, int makes, int time, QString instructions, vector<IngAndAm> ingredientsAndAmount, map<QString, bool> allergies) {
    this->name = name;
    this->fav = fav;
    this->makes = makes;
    this->time = time;
    this->instructions = instructions;
    this->ingredientsAndAmount = ingredientsAndAmount;
    this->allergies = allergies;

    calcAllergies();
}

void Recipe::calcAllergies(){
    //loop through all ingredients
    //get allergies and add to map

    for(IngAndAm &ing : ingredientsAndAmount) {
        for(auto const &ingMap : ing.ingredient->getAllergies()) {
            if(ingMap.second == true && allergies[ingMap.first] == false) {
                allergies[ingMap.first] = true;
            }
        }
    }
}


//getters
QString Recipe::getName() {
    return name;
}
bool Recipe::getFav() {
    return fav;
}
int Recipe::getMakes() {
    return makes;
}
int Recipe::getTime() {
    return time;
}
QString Recipe::getInstructions() {
    return instructions;
}
vector<Recipe::IngAndAm> Recipe::getIngAndAm() {
    return ingredientsAndAmount;
}

map<QString, bool> Recipe::getAllergies() {
    return allergies;
}
int Recipe::getDifficulty() {
    return difficulty;
}

