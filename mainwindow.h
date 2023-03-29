#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <algorithm>

#include "customexception.h"
#include "qlistwidget.h"

#include "recipe.h"
#include "popup.h"

#include "csvhandler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
using namespace std;

class MainWindow : public QMainWindow, public CustomException, public csv::CSVhandler
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

    void on_createRecipeVegan_stateChanged(int arg1);

    void on_action_Quit_triggered();

    void on_searchForRecipe_clicked();

    void on_searchRecipeName_textChanged(const QString &arg1);

    void on_searchRecipeSlider_valueChanged(int value);

    void on_searchRecipeFav_stateChanged(int arg1);

    void on_actionSave_triggered();

    void on_actualRecipeIngredients_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    map<QString, bool> allergies;
    vector<Ingredient*> ingredients;
    vector<Ingredient*> searchIngredients;
    vector<Recipe*> searchRecipes;
    map<QString, bool> tempAllergies;
    vector<IngredientAmount> tempIngredientAmount;
    void populateMap();
};
#endif // MAINWINDOW_H
