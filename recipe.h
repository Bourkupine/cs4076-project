#ifndef RECIPE_H
#define RECIPE_H

#include "ingredient.h"

using namespace std;



class recipe {
private:
    struct IngAndAm {
        Ingredient ingredient;
        int amount;
    };
    vector<IngAndAm> ingredientsAndAmount;
    string name;

public:
    recipe();
    string getName();
    string getIngredientAndAmount(int index); //might change this to be a struct
};

#endif // RECIPE_H
