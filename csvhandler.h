#ifndef CSVHANDLER_H
#define CSVHANDLER_H

#include <vector>
#include <QString>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include "ingredientamount.h"

using namespace std;

namespace csv {
    class CSVhandler
    {
    public:
        CSVhandler();
        void writeRToCSV(QString name, int diff, bool fav, int makes, int time, QString instructions, vector<IngredientAmount> IngredientAmount, int dietary);
        void writeIToCSV(QString name, map<QString, bool>, QString type);
        vector<string> readFromCSV();

    private:
        string rootPath;

    };

}

#endif // CSVHANDLER_H
