#include "ingredientamount.h"

IngredientAmount::IngredientAmount(Ingredient* ingredient, int amount)
{
    this->ingredient = ingredient;
    this->amount = amount;
}

Ingredient* IngredientAmount::getIngredient() {
    return ingredient;
}
int IngredientAmount::getAmount() {
    return amount;
}
void IngredientAmount::setAmount(int amount) {
    this->amount = amount;
}
