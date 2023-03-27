#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <QMainWindow>
#include <string>
#include <vector>

using namespace std;

class Ingredient
{

private:
    int cal;
    QString name;
    map<QString, bool> allergies;

public:
    Ingredient();
    Ingredient(int cal, QString name, map<QString, bool> allergies);
    Ingredient(const Ingredient &ingredient);

    int getCal();
    QString getName();
    map<QString, bool>& getAllergies();
};

#endif // INGREDIENT_H
