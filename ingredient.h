#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>
#include <vector>

using namespace std;

class Ingredient
{

private:
    int cal;
    string name;
    vector<string> allergies; //maybe use array since allergies wont be changing

public:
    Ingredient(int cal, string name, vector<string> allergies);

    int getCal();
    string getName();
    vector<string> getAllergies();
};

#endif // INGREDIENT_H
