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

void MainWindow::on_viewRecipes_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_addRecipe_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_viewIngredients_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}


void MainWindow::on_addIngredients_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

//create a recipe object
//display on recipe page
void MainWindow::on_createRecipe_clicked() //create a recipe
{
    QString recipeName = ui->lineEdit->text();
    if (!recipeName.isEmpty()) {
        Recipe r(recipeName);
        recipes.insert(recipes.end(), r);
        ui->listOfRecipes->addItem(r.getName());
        ui->lineEdit->setText("");
    }

}

void MainWindow::on_createIngredient_clicked()
{
    QString ingredientName = ui->lineEdit_2->text();
    int calAmount = ui->calAmount->value();

    map<QString, bool> temp;

    for(QListWidgetItem *item : tempAllergies) {
        temp[item->text()] = true;
    }

    //get map
    if (!ingredientName.isEmpty()) {
       Ingredient i(calAmount, ingredientName, temp);
       ingredients.insert(ingredients.end(), i);
       ui->listOfIngredients->addItem(i.getName());
       ui->lineEdit_2->setText("");
    }

}




void MainWindow::on_viewAllergies_itemClicked(QListWidgetItem *item)
{
    //TODO: make so when you uncheck it removes
    if(item->checkState() == Qt::Checked) {
        tempAllergies.insert(tempAllergies.end(), item);
    }
}

