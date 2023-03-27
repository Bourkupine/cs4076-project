#ifndef RECIPE_H
#define RECIPE_H

#include <QMainWindow>
#include "ingredient.h"

using namespace std;

class Recipe {
private:
    struct IngAndAm {
        Ingredient *ingredient;
        int amount;

        //constructor
        IngAndAm(Ingredient ingredient, int amount)
            : amount(amount)
        {
            this->ingredient = new Ingredient;
            *this->ingredient = ingredient;
        }

        //destructor
        ~IngAndAm() {
            delete this->ingredient;
        }

    };


    bool fav;
    int makes;
    int time;
    QString instructions;
    vector<IngAndAm> ingredientsAndAmount;
    QString name;
    map<QString, bool> allergies;
    int difficulty;

public:
    Recipe(QString name, bool fav, int makes, int time, QString instructions, vector<IngAndAm> ingredientsAndAmount, map<QString, bool> allergies);
    void calcAllergies();

    QString getName();
    bool getFav();
    int getMakes();
    int getTime();
    QString getInstructions();
    vector<IngAndAm> getIngAndAm();
    map<QString, bool> getAllergies();
    int getDifficulty();
    friend class MainWindow;

};

#endif // RECIPE_H
