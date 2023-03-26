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
    bool fav;
    int makes;
    int time;
    QString instructions;
    vector<IngAndAm> ingredientsAndAmount;
    QString name;
    map<QString, bool> allergies;

public:
    Recipe(QString name, bool fav, int makes, int time, QString instructions, vector<IngAndAm> ingredientsAndAmount, map<QString, bool> allergies);

    void calcAllergies();

    QString getName();
    QString getIngredientAndAmount(int index);
    map<QString, bool> getAllergies();

    friend class MainWindow;

};

#endif // RECIPE_H
