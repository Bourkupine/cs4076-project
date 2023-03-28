#include "recipe.h"

Recipe::Recipe(QString name,int diff, bool fav, int makes, int time, QString instructions, vector<IngredientAmount> ingredientAmount, map<QString, bool> allergies, DietaryUnion dietary) {
    this->name = name;
    this->difficulty = diff;
    this->fav = fav;
    this->makes = makes;
    this->time = time;
    this->instructions = instructions;
    this->ingredientAmount = ingredientAmount;
    this->allergies = allergies;
    this->dietaryUnion = dietary;

    calcAllergies();
}

void Recipe::calcAllergies(){
    //loop through all ingredients
    //get allergies and add to map

    //might need to change ia to pointer
    for(IngredientAmount ia : ingredientAmount) {
        for(auto const &iaMap : ia.getIngredient()->getAllergies()) {
            if(iaMap.second == true && allergies[iaMap.first] == false) {
                allergies[iaMap.first] = true;
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
vector<IngredientAmount> Recipe::getIngredientAmount() {
    return ingredientAmount;
}

map<QString, bool> Recipe::getAllergies() {
    return allergies;
}
int Recipe::getDifficulty() {
    return difficulty;
}

