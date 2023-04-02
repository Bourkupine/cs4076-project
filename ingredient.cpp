#include "ingredient.h"

Ingredient::Ingredient(){}

Ingredient::Ingredient(QString name, map<QString, bool> allergies)
    :   name{name}
    ,   allergies{allergies}
{}
Ingredient::Ingredient(const Ingredient &ingredient) {
    name = ingredient.name;
    allergies = ingredient.allergies;
}

QString Ingredient::getName() {
    return name;
}
Ingredient::~Ingredient() {};


void Ingredient::setName(QString s) {
    this->name = s;
}
void Ingredient::setAllergies(map<QString, bool> m) {
    this->allergies = m;
}


map<QString, bool>& Ingredient::getAllergies() {
    return allergies;
}

QString& Ingredient::operator=(Ingredient* i) {
    QString s;
    QString all;
    s.append(i->name + ",");
    for(auto const &a : i->allergies) {
        all.append(a.first + "|");
        all.append(QString::number(a.second) + "%");
    }

    return *new QString(s);
}

