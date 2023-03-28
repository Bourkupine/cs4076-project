#ifndef RECIPE_H
#define RECIPE_H

#include <QMainWindow>

#include "ingredientamount.h"

using namespace std;

class Recipe {
private:

    //0 = none
    //1 = vegetarian
    //2 = vegan
    //3 = vegan
    union DietaryUnion {
        struct DietaryBitField{
            unsigned int vegetarian : 1;
            unsigned int vegan : 1;
        };
        int dietary;
    };

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
