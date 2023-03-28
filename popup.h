#ifndef POPUP_H
#define POPUP_H

#include <QDialog>

namespace Ui {
class Popup;
}
class Popup : public QDialog
{
    Q_OBJECT

public:
    explicit Popup(QWidget *parent = nullptr);
    Popup(QString s, bool *bp);
    ~Popup();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Popup *ui;
    bool * bp;
};

#endif // POPUP_H
