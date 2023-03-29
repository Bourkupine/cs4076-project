#include "csvhandler.h"

using namespace std;

namespace csv {
CSVhandler::CSVhandler() {
    rootPath =  "..//cs4076_21332142//";
}
void CSVhandler::writeRToCSV(QString name, int diff, bool fav, int makes, int time, QString instructions, vector<IngredientAmount> IngredientAmount, int dietary) {

}
void CSVhandler::writeIToCSV(QString name, map<QString, bool> m, QString type) {

    string path = rootPath + "ingredients.csv";

    fstream writer(rootPath);
    //format map to be a string
    string mString;
    writer << name.toStdString() << type.toStdString() << mString << endl;
    writer.close();
}
vector<string> CSVhandler::readFromCSV() {}
}
