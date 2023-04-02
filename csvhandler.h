#ifndef CSVHANDLER_H
#define CSVHANDLER_H

#include <vector>
#include <QString>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <QTextStream>
#include "ingredient.h"
#include "recipe.h"
#include "solid.h"
#include "liquid.h"
#include "QFile"

using namespace std;



class CSVhandler
{
public:
    CSVhandler();


    void csvWriteI(Ingredient *i, QTextStream &ts);
    void csvWriteR(Recipe *r, QTextStream &ts);

    Ingredient* csvReadI(QString str);
    Recipe* csvReadR(QString str);


private:

};




#endif // CSVHANDLER_H









