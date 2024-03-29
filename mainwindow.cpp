#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "liquid.h"
#include "solid.h"
#include "csvhandler.h"

#include <algorithm>
#include "QFile"

//preprocessor directives
#define EASY 0
#define MEDIUM 1
#define HARD 2

//global variable
vector<Recipe*> recipes;

#include <iostream>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    populateMap();

    for (const auto &p : allergies) {

        QListWidgetItem *item = new QListWidgetItem;
        item->setText(p.first);
        item->setCheckState(Qt::Unchecked);

        ui->viewAllergies->addItem(item);
    }
}

//operator overloading
void operator<<(std::map<QString, bool>& map, const QString& key) {
    map[key] = false;
}
// maybe overload something here to just take a string and auto add to map and set false
void MainWindow::populateMap() {
    allergies<<"Milk";
    allergies<<"Gluten";
    allergies<<"Soy";
    allergies<<"Peanuts";
    allergies<<"Tree nuts";
    allergies<<"Sesame";
    allergies<<"Crustaceans";
}

MainWindow::~MainWindow()
{
    //memory management
    for(Recipe * r : recipes) {
        delete r;
    }
    for(Ingredient *i : ingredients) {
        delete i;
    }
    recipes.clear();
    ingredients.clear();
    delete ui;
}

/*
 * 0 = view recipe
 * 1 = inspect ingredient
 * 2 = view ingredient
 * 3 = add recipe
 * 4 = inspect recipe
 * 5 = add ingredient
*/


void MainWindow::on_viewRecipes_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_addRecipe_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_viewIngredients_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}


void MainWindow::on_addIngredients_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}
//create recipe
void MainWindow::on_createRecipe_clicked() //create a recipe
{
    /* Recipe Has
     * Name X
     * Fav X
     * Makes X
     * Time it takes X
     * vector of ingredientAmount
     * Instructions X
     * Difficulty
     */

    if (tempIngredientAmount.size() > 0) {
        QString recipeName = ui->createRecipeName->text();
        int makes = ui->createRecipeMakes->value();
        bool fav = ui->createRecipeFav->isChecked();
        int time = ui->createRecipeTime->value();
        QString instructions = ui->createRecipeInstructions->toPlainText();

        //dietry union
        Recipe::DietaryUnion un;

        if(ui->createRecipeVegan->isChecked()) {
            un.dietary = 2;
        } else if(ui->createRecipeVegetarian->isChecked()) {
            un.dietary = 1;
        } else {
            un.dietary = 0;
        }

        //get Difficulty
        int diff = ui->createRecipeEasy->isChecked() ? 0 : (ui->createRecipeMedium->isChecked() ? 1 : 2);

        //create recipe
        Recipe *r = new Recipe(recipeName, diff, fav, makes, time, instructions, tempIngredientAmount, un);

        //add to recipe vector and add to list
        recipes.insert(recipes.end(), r);
        ui->listOfRecipes->addItem(recipeName);

        //reset fields
        ui->createRecipeName->setText("");
        ui->createRecipeMakes->setValue(0);
        ui->createRecipeFav->setCheckState(Qt::Unchecked);
        ui->createRecipeTime->setValue(0);
        ui->createRecipeInstructions->setText("");
        ui->createRecipeVegan->setCheckState(Qt::Unchecked);
        ui->createRecipeVegetarian->setCheckState(Qt::Unchecked);

        tempAllergies.clear();
        tempIngredientAmount.clear();
        ui->actualRecipeIngredients->clear();

        for(int row = 0; row < ui->createRecipeIngredients->count(); row++) { //might need to use size() instead of count()
            QListWidgetItem *item = ui->createRecipeIngredients->item(row);
            item->setHidden(false);
            item->setCheckState(Qt::Unchecked);
        }

    }
}

//create ingredient
void MainWindow::on_createIngredient_clicked()
{
    QString ingredientName = ui->lineEdit_2->text();

    map<QString, bool> temp;

    for(int row = 0; row < ui->viewAllergies->count(); row++) {
        QListWidgetItem *item = ui->viewAllergies->item(row);
        if(item->checkState() == Qt::Checked)
            temp[item->text()] = true;
    }

    //check if it already exists (might reimplement this as it causes a warning)
    bool contains = false;
    for(Ingredient *i : ingredients) {
        if(i->getName()==ingredientName) {
            contains = true;
        }
    }

    if (!ingredientName.isEmpty() && !contains) {
        Ingredient *i;
        if(ui->isLiquid->isChecked()) {
            i = new Liquid("ml");

        } else {
            i = new Solid("g");

        }
        i->setName(ingredientName);
        i->setAllergies(temp);

        //insert into the ingredient array and display in the ingredient ListWidget in View Ingredients
        ingredients.insert(ingredients.end(), i);
        ui->listOfIngredients->addItem(i->getName());

        //resets fields
        ui->lineEdit_2->setText("");

        //sets allergy ticks to unchecked
        for(int row = 0; row < ui->viewAllergies->count(); row++) {
            QListWidgetItem *item = ui->viewAllergies->item(row);
            if (item->checkState() == Qt::Checked) item->setCheckState(Qt::Unchecked);
        }

        //make a new row in the ingredients list in Add Recipe
        QListWidgetItem *item = new QListWidgetItem(i->getName());
        item->setCheckState(Qt::Unchecked);
        ui->createRecipeIngredients->addItem(item);
    }

}

//delete an ingredient
//call deconstructor?? remove from array and all other places
void MainWindow::on_inspectIngredientDelete_clicked()
{
    bool b = false;
    bool *bp = &b;

    Popup *p = new Popup("Are you sure you want to delete", bp);

    p->setModal(true);
    p->exec();
    delete p;

    if(b) {
        for (Ingredient *i : ingredients) {
            if (i->getName() == ui->inspectIngredientName->text()) {
                //delete the ingredient


                //first remove from QListWidgets
                for(int z = 0; z < ui->listOfIngredients->count(); z++) {
                    QListWidgetItem* item = ui->listOfIngredients->item(z);
                    if (item->text() == i->getName()) {
                        //ui->listOfIngredients->removeItemWidget(item);
                        delete item;
                    }
                }
                for(int z = 0; z < ui->createRecipeIngredients->count(); z++) {
                    QListWidgetItem* item = ui->createRecipeIngredients->item(z);
                    if (item->text() == i->getName()) {
                        //ui->listOfIngredients->removeItemWidget(item);
                        delete item;
                    }
                }

                int pos;
                pos = distance(ingredients.begin(), std::find(ingredients.begin(), ingredients.end(), i));
                ingredients.erase(ingredients.begin() + pos);
            }
            ui->stackedWidget->setCurrentIndex(2);
        }
    }

}

void MainWindow::on_addIngredientToRecipe_clicked()
{
    try {
        int amount = ui->ingredientAmount->value();
        QListWidgetItem *item = ui->createRecipeIngredients->currentItem();

        if (item == nullptr) {throw ce::CustomException((char *)"No Ingredient was added");}

        for (Ingredient *i : ingredients) {

            if (i->getName() == item->text()) {
                //i is the ingredient we want
                IngredientAmount *ia = new IngredientAmount(i, amount);
                tempIngredientAmount.push_back(ia);
                item->setHidden(true);
                ui->actualRecipeIngredients->addItem(item->text());
                break;
            }
        }

        ui->ingredientAmount->setValue(0);

    } catch(ce::CustomException ce) {
        cout << ce.what() << endl;
    }
}

//view an ingredient
void MainWindow::on_viewIngredient_clicked()
{
    QListWidgetItem *item = ui->listOfIngredients->currentItem();
    ui->inspectIngredientAllergies->clear();

    for(Ingredient *i : ingredients) {
        //if ingredient name = item text then we have the igredient
        if(i->getName() == item->text()) {
            //set current page to inspect ingredient
            ui->stackedWidget->setCurrentIndex(1);

            //set variables in the page to equal the current Ingredient
            ui->inspectIngredientName->setText(i->getName());
            ui->inspectIngredientUnit->setText(i->getType());

            QString iClass = i->getType() == "g" ? "Solid" : "Liquid";
            ui->inspectIngredientType->setText(iClass);

            //loop through and add its allergies
            for(auto const &p : i->getAllergies()) {
                QListWidgetItem * item = new QListWidgetItem;
                item->setText(p.first);
                ui->inspectIngredientAllergies->addItem(item);
            }

        }
    }

}


void MainWindow::on_viewRecipe_2_clicked()
{
    QListWidgetItem *item = ui->listOfRecipes->currentItem();

    for(Recipe *r : recipes) {
        if(r->getName() == item->text()) {
            //set page to inspect recipe
            ui->stackedWidget->setCurrentIndex(4);

            //clear the QListWidget so dupes arent created
            ui->inspectRecipeIngredients->clear();

            //get recipe info
            QString diff;

            ui->inspectRecipeVegan->setCheckState(Qt::Unchecked);
            ui->inspectRecipeVegetarian->setCheckState(Qt::Unchecked);

            switch(r->getDifficulty()) {
            case EASY : diff = "Easy"; break;
            case MEDIUM : diff = "Medium"; break;
            case HARD: diff = "Hard"; break;
            };

            if(r->dietaryUnion.bits.vegan) {ui->inspectRecipeVegan->setCheckState(Qt::Checked); ui->inspectRecipeVegetarian->setCheckState(Qt::Checked);}
            else if(r->dietaryUnion.bits.vegetarian) ui->inspectRecipeVegetarian->setCheckState(Qt::Checked);
            //set recipe info
            ui->inspectRecipeName->setText(r->getName());
            ui->inspectRecipeInstructions->setText(r->getInstructions());
            if(r->getFav()) ui->inspectRecipeFav->setCheckState(Qt::Checked);
            else ui->inspectRecipeFav->setCheckState(Qt::Unchecked);
            ui->inspectRecipeDifficulty->setText(diff);
            ui->inspectRecipeTime->setText(QString::number(r->getTime()));
            ui->inspectRecipeMakes->setText(QString::number(r->getMakes()));

            //set ingredients

            for(IngredientAmount *ia : r->getIngredientAmount()) {
                QListWidgetItem *item = new QListWidgetItem;
                item->setText(QString::number(ia->getAmount()) + ia->getIngredient()->getType() + " | " + ia->getIngredient()->getName());
                ui->inspectRecipeIngredients->addItem(item);
            }
        }
    }
}


void MainWindow::on_searchIngredientButton_clicked() //creates a duplicate for some reason
{
    QString search = ui->searchIngredientName->text();

    //clear otherwise it creates dupes (since we are adding inside the second for loop)
    ui->listOfIngredients->clear();

    for(Ingredient *i : ingredients) {
        QString ingName = i->getName();

        //if the ingredient contains your search, add it to the searchIngredient vector
        if(ingName.toLower().contains(search.toLower())) {
            searchIngredients.push_back(i);
        }
    }

    //loop through searchIngredients and add them into the QListWidget
    for(Ingredient *i : searchIngredients) {
        ui->listOfIngredients->addItem(i->getName());
    }

    //clear searchIngredients so it gets reset each time
    searchIngredients.clear();
}

//dynamic typing
void MainWindow::on_searchIngredientName_textChanged(const QString &arg1)
{
    MainWindow::on_searchIngredientButton_clicked();
}

//Vegan option also ticks vegetarian
void MainWindow::on_createRecipeVegan_stateChanged(int arg1)
{
    if(arg1) ui->createRecipeVegetarian->setCheckState(Qt::Checked);
}


void MainWindow::on_action_Quit_triggered()
{
    this->close();
}


void MainWindow::on_searchForRecipe_clicked()
{

    //get filter
    bool favOnly = ui->searchRecipeFav->checkState();

    QString search = ui->searchRecipeName->text();
    int diff;

    if (ui->searchRecipeEasy->isChecked()) diff = 0;
    else if (ui->searchRecipeMedium->isChecked()) diff = 1;
    else diff = 2;

    ui->listOfRecipes->clear();

    for(Recipe *r : recipes) {
        QString recName = r->getName();

        if(recName.toLower().contains(search.toLower())) {
            searchRecipes.push_back(r);
        }
    }

    for(Recipe *r : searchRecipes) {

        if(favOnly) {
            if(r->getFav() && r->getDifficulty() == diff && r->getTime() <= ui->searchRecipeSlider->value()) ui->listOfRecipes->addItem(r->getName());
        }
        else
            if(r->getDifficulty() == diff && r->getTime() <= ui->searchRecipeSlider->value()) ui->listOfRecipes->addItem(r->getName());

    }

    searchRecipes.clear();

}


void MainWindow::on_searchRecipeName_textChanged(const QString &arg1)
{
    MainWindow::on_searchForRecipe_clicked();
}


void MainWindow::on_searchRecipeSlider_valueChanged(int value)
{
    string formatted;


    string ar[2];

    string *p = ar;

    ar[0] = value / 60 > 9 ? std::to_string(value/60) : ("0" + std::to_string(value/60));
    ar[1] = value % 60 > 9 ? std::to_string(value%60) : ("0" + std::to_string(value%60));

    formatted = *p + ":" + *(p+1);

    ui->searchRecipeTimer->setText(QString::fromStdString(formatted));
}


void MainWindow::on_searchRecipeFav_stateChanged(int arg1)
{
    on_searchForRecipe_clicked();
}


void MainWindow::on_actionSave_triggered()
{

    //QFile fileI = QFile("..//cs4076_21332142//ingredients.csv"); // for QT
    QFile fileI = QFile(".//ingredients.csv"); // for exe
    fileI.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out = QTextStream(&fileI);
    CSVhandler h;
    for(Ingredient *i : ingredients) {

        h.csvWriteI(i, out);
    }
    fileI.close();
    ui->listOfIngredients->clear();
    ingredients.clear();
    ui->createRecipeIngredients->clear();

    //QFile fileR = QFile("..//cs4076_21332142//recipes.csv"); for qt
    QFile fileR = QFile(".//recipes.csv"); //for exe
    fileR.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream outR = QTextStream(&fileR);

    for(Recipe *r : recipes) {

        h.csvWriteR(r, outR);
    }
    fileR.close();
    ui->listOfRecipes->clear();
    recipes.clear();

}


void MainWindow::on_actualRecipeIngredients_itemClicked(QListWidgetItem *item)
{

    //remove from list
    //unhide

    for (Ingredient *i : ingredients) {
        if (i->getName() == item->text()) {

            //i is our ingredient
            //now find the corresponding ingredient amount

            for(int z = 0; z < ui->actualRecipeIngredients->count(); z++) {
                QListWidgetItem* item = ui->actualRecipeIngredients->item(z);
                if (item->text() == i->getName()) {
                    //ui->listOfIngredients->removeItemWidget(item);
                    delete item;
                }
            }
            for(int z = 0; z < ui->createRecipeIngredients->count(); z++) {
                QListWidgetItem* item = ui->createRecipeIngredients->item(z);
                if (item->text() == i->getName()) {
                    //ui->listOfIngredients->removeItemWidget(item);
                    item->setHidden(false);
                    item->setCheckState(Qt::Unchecked);
                }
            }

            //remove from the tempIngredientAmount vector
            for(IngredientAmount *ia : tempIngredientAmount) {
                if(ia->getIngredient()->getName() == i->getName()) {
                    int pos = distance(tempIngredientAmount.begin(), std::find(tempIngredientAmount.begin(), tempIngredientAmount.end(), ia));
                    tempIngredientAmount.erase(tempIngredientAmount.begin() + pos);
                }

            }

        }

    }
}

void MainWindow::on_inspectRecipeDelete_clicked() {
    bool b = false;
    bool *bp = &b;

    Popup *p = new Popup("Are you sure you want to delete", bp);

    p->setModal(true);
    p->exec();
    delete p;

    if(b) {

        for(Recipe *r : recipes) {

            if(r->getName() == ui->inspectRecipeName->text()) {

                for(int z = 0; z < ui->listOfRecipes->count(); z++) {
                    QListWidgetItem *item = ui->listOfRecipes->item(z);
                    if(item->text() == r->getName()) {
                        delete item;
                    }
                }
            }

            int pos;
            pos = distance(recipes.begin(), std::find(recipes.begin(), recipes.end(), r));
            recipes.erase(recipes.begin() + pos);
        }
        ui->stackedWidget->setCurrentIndex(0);
    }
}


void MainWindow::on_action_Open_triggered()
{

    //QFile fileI = QFile("..//cs4076_21332142//ingredients.csv"); (for QT)
    QFile fileI = QFile(".//ingredients.csv"); // for exe
    fileI.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in = QTextStream(&fileI);
    CSVhandler h;

    ui->listOfIngredients->clear();
    ingredients.clear();
    ui->createRecipeIngredients->clear();

    while(!in.atEnd()) {

        Ingredient *i;

        QString line = in.readLine();

        if(!line.isEmpty()) {

            //error here
            i = h.csvReadI(line);
        }
        ingredients.push_back(i);
        ui->listOfIngredients->addItem(i->getName());

        QListWidgetItem *item = new QListWidgetItem(i->getName());
        item->setCheckState(Qt::Unchecked);
        ui->createRecipeIngredients->addItem(item);

    }
    fileI.close();
    //*
    //QFile fileR = QFile("..//cs4076_21332142//recipes.csv"); (For QT)
    QFile fileR = QFile(".//recipes.csv"); //(works for EXE)
    fileR.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream inR = QTextStream(&fileR);

    ui->listOfRecipes->clear();
    recipes.clear();

    while(!inR.atEnd()) {

        Recipe* r;

        QString line = inR.readLine();

        if(!line.isEmpty()) {
            r = h.csvReadR(line);
        }

        recipes.push_back(r);
        ui->listOfRecipes->addItem(r->getName());

    }

    fileR.close();
    //*/
}


