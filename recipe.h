#ifndef RECIPE_H
#define RECIPE_H

#include <QMainWindow>

#include "ingredientamount.h"

using namespace std;

class Recipe {
private:

    struct DietaryBitField {
        unsigned int vegetarian : 1;
        unsigned int vegan : 1;
    };
    //0 = none
    //1 = vegetarian
    //2 = vegan
    //3 = vegan
    union DietaryUnion {
        DietaryBitField bits;
        unsigned int dietary : 2;
    };

    bool fav;
    int makes;
    int time;
    vector<IngredientAmount*> ingredientAmount;
    QString instructions;
    QString name;
    map<QString, bool> allergies;
    int difficulty;
    DietaryUnion dietaryUnion;

public:
    Recipe(QString name,int diff, bool fav, int makes, int time, QString instructions, vector<IngredientAmount*> IngredientAmount, DietaryUnion dietary);
    Recipe(QString name,int diff, bool fav, int makes, int time, QString instructions, vector<IngredientAmount*> ingredientAmount, int dietary);
    void calcAllergies();

    QString getName();
    bool getFav();
    int getMakes();
    int getTime();
    QString getInstructions();
    vector<IngredientAmount*> getIngredientAmount();
    map<QString, bool> getAllergies();
    int getDifficulty();
    QString operator=(const Recipe &r);


    friend class MainWindow;
    friend class CSVhandler;
};

#endif // RECIPE_H
