#include "ingredient.h"

Ingredient::Ingredient(){}

Ingredient::Ingredient(int cal, QString name, map<QString, bool> allergies) {
    this->cal = cal;
    this->name = name;
    this->allergies = allergies;
}
Ingredient::Ingredient(const Ingredient &ingredient) {
    cal = ingredient.cal;
    name = ingredient.name;
    allergies = ingredient.allergies;
}


int Ingredient::getCal() { //maybe make this const
    return cal;
}

QString Ingredient::getName() {
    return name;
}

map<QString, bool>& Ingredient::getAllergies() {
    return allergies;
}
