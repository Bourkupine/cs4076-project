#ifndef SOLID_H
#define SOLID_H

#include "ingredient.h"

class Solid : public Ingredient
{
private:
    QString type;
public:
    Solid(QString type);
    Solid(QString type, QString name, map<QString, bool> allergies);
    QString getType();


};

#endif // SOLID_H
