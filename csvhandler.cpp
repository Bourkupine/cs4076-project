#include "csvhandler.h"
#include <iostream>

using namespace std;

namespace csv {
CSVhandler::CSVhandler() {
    rootPath =  "..//cs4076_21332142//";
}
void CSVhandler::writeRToCSV(QString name, int diff, bool fav, int makes, int time, QString instructions, vector<IngredientAmount> ingredientAmount, int dietary) {

        string path = rootPath + "recipes.csv";

        fstream writer(path);

        string favString = diff ? "fav" : "notFav";

        string ingAm;
        //loop through ingredient amounts
        for(IngredientAmount ia : ingredientAmount) {
            ingAm = ingAm + ia.getIngredient()->getName().toStdString() + "|";
            ingAm = ingAm + std::to_string(ia.getAmount()) + "%";
        }


        writer << name.toStdString() << std::to_string(diff) << favString << std::to_string(makes) << std::to_string(time) << instructions.toStdString()<< ingAm << std::to_string(dietary);
        writer.close();

}
void CSVhandler::writeIToCSV(QString name, map<QString, bool> m, QString type) {

    string path = rootPath + "ingredients.csv";

    fstream writer(path);

    //format map to be a string
    string mString;
    for (const auto &p : m) {
        string b = p.second ? "true" : "false";
        mString.append(p.first.toStdString() + "|" + b + "%");
    }

    writer << name.toStdString() << "," << type.toStdString() << "," << mString;
    writer.close();

}
vector<string> CSVhandler::readIFromCSV() {

}
vector<string> CSVhandler::readRFromCSV() {

}
}
