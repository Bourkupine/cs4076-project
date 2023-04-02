#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <QMainWindow>
#include <string>
#include <vector>

using namespace std;

class Ingredient
{

protected:
    QString name;
    map<QString, bool> allergies;

public:
    virtual QString getType() = 0;
    Ingredient();
    Ingredient(QString name, map<QString, bool> allergies);
    Ingredient(const Ingredient &ingredient);
    virtual ~Ingredient();

    void setName(QString s);
    void setAllergies(map<QString, bool> m);
    QString getName();
    map<QString, bool>& getAllergies();
    QString& operator=(Ingredient* i);

    friend class MainWindwow;
    friend class CSVhandler;

};

#endif // INGREDIENT_H
