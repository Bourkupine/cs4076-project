#ifndef RECIPE_H
#define RECIPE_H

#include <QMainWindow>
#include "ingredient.h"

using namespace std;



class Recipe {
private:
    struct IngAndAm {
        Ingredient ingredient;
        int amount;
    };
    vector<IngAndAm> ingredientsAndAmount;
    QString name;
    map<QString, bool> allergies;

public:
    Recipe(QString name);
    QString getName();
    QString getIngredientAndAmount(int index);
    map<QString, bool> getAllergies();
};

#endif // RECIPE_H
