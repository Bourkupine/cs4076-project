#include "solid.h"

Solid::Solid(QString type)
{
    this->type = type;
}

Solid::Solid(QString type, QString name, map<QString, bool> allergies)
    :   type{type}
    ,   Ingredient(name, allergies)
{}

//Solid::Solid(QString type, QString name, map<QString, bool> allergies) {
//    this->type = type;
//    this->name = name;
//    this->allergies = allergies;
//}

QString Solid::getType() {
    return type;
}

