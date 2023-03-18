#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    if(ui->plainTextEdit->toPlainText().QString::toInt() == 0 && ui->plainTextEdit->toPlainText().QString::toFloat() == 0) {
        QMessageBox::information(this, tr("Hello"), tr("Please enter an integer!"));
//        reject();
    }
    else accept();
}

QVector<int> Dialog::getDims() const{
    QVector<int> dims(0);
    dims.push_back(ui->plainTextEdit->toPlainText().QString::toInt());
    return dims;
}
