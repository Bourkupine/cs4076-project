#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "recipe.h"

vector<recipe> recipes;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    ui->listOfRecipes->addItem(recipeName);

}
