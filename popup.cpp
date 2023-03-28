#include "popup.h"
#include "ui_popup.h"

Popup::Popup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Popup)
{
    ui->setupUi(this);
}

Popup::Popup(QString s, bool *bp)
    : ui(new Ui::Popup)
    , bp(bp)
{
    ui->setupUi(this);
    ui->popupText->setText(s);
}



Popup::~Popup()
{
    delete ui;
}

//Cancel
void Popup::on_pushButton_3_clicked()
{
    this->close();
}

//Delete
void Popup::on_pushButton_4_clicked()
{
    *bp = true;
    this->close();
}

