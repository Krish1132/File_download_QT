#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
//    typedef struct dimension {
//        int dim;
//    } Dimension;
    QVector<int> getDims() const;


private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
