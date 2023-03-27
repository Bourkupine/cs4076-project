#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QDebug>

#define EASY 0
#define MEDIUM 1
#define HARD 2

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
    allergies<<"Coconut";
}

MainWindow::~MainWindow()
{
    for(Recipe * r : recipes) {
        delete r;
    }
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

//create a recipe object
//display on recipe page
void MainWindow::on_createRecipe_clicked() //create a recipe
{
    QString recipeName = ui->createRecipeName->text();
    int makes = ui->createRecipeMakes->value();
    bool fav = ui->createRecipeFav->isChecked();
    int time = ui->createRecipeTime->value();
    QString instructions = ui->createRecipeInstructions->toPlainText();

    //we need to get allergies
    //loop through stuct
    //get ingredient
    //have temp allergies
    //add allergies
    //CRASH HERE
    for(int i = 0; i < tempStruct.size(); i++) {
        //Recipe::IngAndAm temp(*tempStruct.at(i).ingredient, tempStruct.at(i).amount);
        //tempAllergies = temp.ingredient->getAllergies();
        //instead loop through getAllergies and add the true ones;

        //for each allergy in ingredient tempStruct.at(i).ingredient
        //if allergy second = true,
        //and tempAllergy of allergy name = false
        //set allergy to true;


        Ingredient *ing = tempStruct.at(i).ingredient;

        //crash
        //map<QString, bool> all = ing->getAllergies();

        //it appears like temptStruct isnt getting filled with values
        //or ing isnt getting the value of tempStruct.at(i)
        for(auto const &p : ing->getAllergies()) {
            if(p.second == true) {
                tempAllergies[p.first] = true;
            }
        }
    }

    Recipe *r = new Recipe(recipeName, fav, makes, time, instructions, tempStruct, tempAllergies);
    recipes.insert(recipes.end(), r);
    ui->listOfRecipes->addItem(recipeName);
}

void MainWindow::on_createIngredient_clicked()
{
    QString ingredientName = ui->lineEdit_2->text();
    int calAmount = ui->calAmount->value();

    map<QString, bool> temp;

    for(int row = 0; row < ui->viewAllergies->count(); row++) {
        QListWidgetItem *item = ui->viewAllergies->item(row);
        if(item->checkState() == Qt::Checked)
            temp[item->text()] = true;
    }


    //check if it doesnt exist already
    //get map
    if (!ingredientName.isEmpty()) {
        Ingredient i(calAmount, ingredientName, temp);

        //insert into the ingredient array and display in the ingredient ListWidget in View Ingredients
        ingredients.insert(ingredients.end(), i);
        ui->listOfIngredients->addItem(i.getName());

        //resets fields
        ui->lineEdit_2->setText("");
        ui->calAmount->setValue(0);

        //sets allergy ticks to unchecked
        for(int row = 0; row < ui->viewAllergies->count(); row++) {
            QListWidgetItem *item = ui->viewAllergies->item(row);
            if (item->checkState() == Qt::Checked) item->setCheckState(Qt::Unchecked);
        }

        //make a new row in the ingredients list in Add Recipe
        QListWidgetItem *item = new QListWidgetItem(i.getName());
        item->setCheckState(Qt::Unchecked);
        ui->createRecipeIngredients->addItem(item);
    }

}


//edit an ingredient
//send to Add ingredient but fill out boxes with current ones
void MainWindow::on_inspectIngredientEdit_clicked()
{
    //set current window to Add Ingredient
    ui->stackedWidget->setCurrentIndex(5);

    QString name = ui->inspectIngredientName->text();

    for(Ingredient i : ingredients) {
        if(i.getName() == name) {

            ui->lineEdit_2->setText(name);
            ui->calAmount->setValue(i.getCal());

            map<QString, bool> m = i.getAllergies();
            //not working
            //its adds all, instead set ticks to be the true ones

            //for each allergy in viewAllergies
            //if it is in i.getAllergies then
            //set checkstate to true
            for(int j = 0; j < ui->viewAllergies->count(); j++) {
                if(ui->viewAllergies->item(j) /*something*/) {}
            }

//            for(auto const &p : i.getAllergies()) {
//                if(p.second == true) {
//                    //add allergies to the inspect ingredient allergy list
//                    ui->viewAllergies->currentItem()->setCheckState(Qt::Checked);
//                }
//            }


        }
    }

    //fill in values with current one

}

//delete an ingredient
//call deconstructor?? remove from array and all other places
void MainWindow::on_inspectIngredientDelete_clicked()
{

}


void MainWindow::on_addIngredientToRecipe_clicked()
{
    int amount = ui->ingredientAmount->value();
    QListWidgetItem *item = ui->createRecipeIngredients->currentItem();

    for(Ingredient i : ingredients) {
        string iName = i.getName().QString::toStdString();
        string itemName = item->text().toStdString();
        if (iName == itemName) {
            tempStruct.insert(tempStruct.end(), *new Recipe::IngAndAm(i, amount));
            item->setHidden(true);
            ui->actualRecipeIngredients->addItem(item -> text());
            break;
        }
    }
}


//view an ingredient
void MainWindow::on_viewIngredient_clicked()
{
    QListWidgetItem *item = ui->listOfIngredients->currentItem();


    //Ingredient i = getIngredientFromItem(item);

    for(Ingredient i : ingredients) {
        if(i.getName() == item->text()) {


            //set current page to inspect ingredient
            ui->stackedWidget->setCurrentIndex(1);

            //get ingredients info
            ui->inspectIngredientName->setText(i.getName());
            ui->inspectIngredientCal->setText(QString::number(i.getCal()));
            //not implemented yet ui->inspectIngredientUnit->setText();

            //loop through allergies and add the allgeries
            for(auto const &p : i.getAllergies()) {
                if(p.second == true) {
                    QListWidgetItem *item = new QListWidgetItem;
                    item->setText(p.first);
                    //add allergies to the inspect ingredient allergy list
                    ui->inspectIngredientAllergies->addItem(item);
                }
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

            //get recipe info
            ui->inspectRecipeName->setText(r->getName());
            ui->inspectRecipeInstructions->setText(r->getInstructions());
            Qt::CheckState checkstate = r->getFav() ? Qt::Checked : Qt::Unchecked;
            ui->inspectRecipeFav->setCheckState(checkstate);

            QString diff;

            switch(r->getDifficulty()) {
            case EASY : diff = "Easy"; break;
            case MEDIUM : diff = "Medium"; break;
            case HARD: diff = "Hard"; break;
            }

            ui->inspectRecipeDifficulty->setText(diff);
            ui->inspectRecipeTime->setText(QString::number(r->getTime()));
            ui->inspectRecipeMakes->setText(QString::number(r->getTime()));

            //set ingredients


        }
    }
}


void MainWindow::on_searchIngredientButton_clicked() //creates a duplicate for some reason
{
    QString search = ui->searchIngredientName->text();

    ui->listOfIngredients->clear();

    for(Ingredient i : ingredients) {
        QString iName = i.getName();

        if (iName.contains(search)) {
            searchIngredients.push_back(i);
        }

    }
    for(Ingredient i : searchIngredients) {

        ui->listOfIngredients->addItem(i.getName());

    }

    searchIngredients.clear();
}

