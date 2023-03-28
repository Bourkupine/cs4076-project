#include "liquid.h"

Liquid::Liquid(QString type)
{
    this->type = type;
    this->name = name;
    this->allergies = allergies;
}

Liquid::Liquid(QString type, QString name, map<QString, bool> allergies)
    :   type{type}
    ,   Ingredient(name, allergies)
{}

//Liquid::Liquid(QString type, QString name, map<QString, bool> allergies) {
//    this->type = type;
//    this->name = name;
//    this->allergies = allergies;
//}

QString Liquid::getType() {
    return type;
}
