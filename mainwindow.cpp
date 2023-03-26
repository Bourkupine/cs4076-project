#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    populateMap();


    ui->setupUi(this);

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

    //loop through all values and get the ticked ones along with ingredient and amount
    //convert them to structs
    //insert into vector
    //for(QListWidgetItem *item : )


//    if (!recipeName.isEmpty()) {
//        Recipe r(recipeName, fav, makes, time, instructions, ingredients, allergies);
//        recipes.insert(recipes.end(), r);
//        ui->listOfRecipes->addItem(r.getName());
//        ui->createRecipeName->setText("");
//    }

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

}

//delete an ingredient
//call deconstructor?? remove from array and all other places
void MainWindow::on_inspectIngredientDelete_clicked()
{

}


//view an ingredient
void MainWindow::on_viewIngredient_clicked()
{
    QListWidgetItem *item = ui->listOfIngredients->currentItem();

    for(Ingredient i : ingredients) {
        if(i.getName() == item->text()) { //i is our ingredient

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

