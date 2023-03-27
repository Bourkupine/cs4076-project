#ifndef LIQUID_H
#define LIQUID_H

#include "ingredient.h"

class Liquid : public Ingredient
{
private:
    QString type;
public:
    Liquid(QString type);
    Liquid(QString type, QString name, map<QString, bool> allergies);
    QString getType();
};

#endif // LIQUID_H
