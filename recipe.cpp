#include "recipe.h"

Recipe::Recipe(QString name) {
    this->name = name;
}

QString Recipe::getName() {
    return name;
}

QString Recipe::getIngredientAndAmount(int index) {
    //make this return Ingredient | Amount
    //return ingredientsAndAmount.at(index);
}

map<QString, bool> Recipe::getAllergies() {
    return allergies;
}
