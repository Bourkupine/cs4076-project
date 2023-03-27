#ifndef INGREDIENTAMOUNT_H
#define INGREDIENTAMOUNT_H

#include "ingredient.h"

class IngredientAmount
{
public:
    IngredientAmount(Ingredient* ingredient, int amount);

    Ingredient* getIngredient();
    int getAmount();
    void setAmount(int amount);
private:
    Ingredient* ingredient;
    int amount;
};

#endif // INGREDIENTAMOUNT_H
