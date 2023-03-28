#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <algorithm>

#include "qlistwidget.h"

#include "recipe.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_viewRecipes_clicked();

    void on_addRecipe_clicked();

    void on_viewIngredients_2_clicked();

    void on_addIngredients_clicked();

    void on_createRecipe_clicked();


    void on_createIngredient_clicked();


    void on_inspectIngredientEdit_clicked();

    void on_inspectIngredientDelete_clicked();

    void on_viewIngredient_clicked();

    void on_addIngredientToRecipe_clicked();

    void on_viewRecipe_2_clicked();

    void on_searchIngredientButton_clicked();

    void on_searchIngredientName_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    map<QString, bool> allergies;
    vector<Ingredient*> ingredients;
    vector<Ingredient*> searchIngredients;
    map<QString, bool> tempAllergies;
    //vector<Recipe::LiqAndAm> tempStruct;
    vector<IngredientAmount> tempStruct; //temp fix for above
    void populateMap();
};
#endif // MAINWINDOW_H
