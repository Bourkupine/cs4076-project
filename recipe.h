#ifndef RECIPE_H
#define RECIPE_H

#include <QMainWindow>

#include "ingredientamount.h"

using namespace std;

class Recipe {
private:

    bool fav;
    int makes;
    int time;
    vector<IngredientAmount> ingredientAmount;
    QString instructions;
    QString name;
    map<QString, bool> allergies;
    int difficulty;

public:
    Recipe(QString name, bool fav, int makes, int time, QString instructions, vector<IngredientAmount> IngredientAmount, map<QString, bool> allergies);
    void calcAllergies();

    QString getName();
    bool getFav();
    int getMakes();
    int getTime();
    QString getInstructions();
    vector<IngredientAmount> getIngredientAmount();
    map<QString, bool> getAllergies();
    int getDifficulty();


    friend class MainWindow;

};

#endif // RECIPE_H
