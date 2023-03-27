#include "recipe.h"

Recipe::Recipe(QString name, bool fav, int makes, int time, QString instructions, vector<IngredientAmount> ingredientAmount, map<QString, bool> allergies) {
    this->name = name;
    this->fav = fav;
    this->makes = makes;
    this->time = time;
    this->instructions = instructions;
    this->ingredientAmount = ingredientAmount;
    this->allergies = allergies;

    calcAllergies();
}

void Recipe::calcAllergies(){
    //loop through all ingredients
    //get allergies and add to map

    //    for(IngAndAm &ing : ingredientsAndAmount) {
    //        for(auto const &ingMap : ing.ingredient->getAllergies()) {
    //            if(ingMap.second == true && allergies[ingMap.first] == false) {
    //                allergies[ingMap.first] = true;
    //            }
    //        }
    //    }
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

