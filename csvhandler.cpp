#include "csvhandler.h"
#include <iostream>


using namespace std;

CSVhandler::CSVhandler() {
}

void CSVhandler::csvWriteI(Ingredient *i, QTextStream &ts) {

    QString s;

    s.append(i->getName() + ",");
    s.append(i->getType() + ",");
    for(const auto &a : i->getAllergies()) {
        if(!a.first.isEmpty()) {
            s.append(a.first + "|");
        }
    }
    s.append("\n");

    ts << s;
}


void CSVhandler::csvWriteR(Recipe *r, QTextStream &ts) {

    QString s;

    s.append(r->getName() + ",");
    s.append(QString::number(r->getFav()) + ",");
    s.append(QString::number(r->getTime()) + ",");
    s.append(QString::number(r->getMakes()) + ",");
    s.append(r->getInstructions() + ",");
    s.append(QString::number(r->getDifficulty()) + ",");
    s.append(QString::number(r->dietaryUnion.dietary) + ",");
    for(IngredientAmount* ia : r->getIngredientAmount()) {
        s.append(ia->getIngredient()->getName() + "|" + ia->getIngredient()->getType() + "|" + QString::number(ia->getAmount()) + "%");
    }
    s.append("\n");

    ts << s;


}

Ingredient* CSVhandler::csvReadI(QString str) {

    QStringList l = str.split(",");
    QString ingredientName = l.at(0);
    map<QString, bool> temp;

    if (l.at(2) != "") {

        QStringList al = l.at(2).split("|");

        for(int x = 0; x < al.capacity()-1; x++) {
            temp[al.at(x)] = true;
        }
    }

    Ingredient *i;

    if(l.at(1) == "g") i = new Solid("g", ingredientName, temp);

    else i = new Liquid("ml", ingredientName, temp);

    return i;

}
Recipe* CSVhandler::csvReadR(QString str) {

    QStringList l = str.split(",");
    QString rName = l.at(0);
    bool rFav = l.at(1) == "1" ? true : false;
    int rTime = l.at(2).toInt();
    int rMakes = l.at(3).toInt();
    QString rInstr = l.at(4);
    int diff = l.at(5).toInt();
    int un = l.at(6).toInt();

    vector<IngredientAmount*> ing;

    if(!l.at(7).isEmpty()) {

        QStringList ia = l.at(7).split("%");

        map<QString, bool> map;

        //ing
        //am

        for(int i = 0; i < ia.capacity()-1;i++) {


            if(!ia.at(i).isEmpty()) {

                QStringList temp = ia.at(i).split("|");

                QString name = temp.at(0);
                QString type = temp.at(1);
                int am = temp.at(2).toInt();

                Ingredient *ingredient;

                if(type == "g") ingredient = new Solid(type, name, map);
                else ingredient = new Liquid(type, name, map);
                IngredientAmount *newia = new IngredientAmount(ingredient, am);
                ing.push_back(newia);
            }
        }
    }

    Recipe *r = new Recipe(rName, diff, rFav, rMakes, rTime, rInstr, ing, un);
    return r;
}

