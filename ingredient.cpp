#include "ingredient.h"



Ingredient::Ingredient(int cal, string name, vector<string> allergies) {
    this->cal = cal;
    this->name = name;
    this->allergies = allergies;
}

int Ingredient::getCal() { //maybe make this const
    return cal;
}

string Ingredient::getName() {
    return name;
}

vector<string> Ingredient::getAllergies() {
    return allergies;
}
