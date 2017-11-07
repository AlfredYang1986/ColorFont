#ifndef CFPREVDIALOG_H
#define CFPREVDIALOG_H

#include <QDialog>

namespace Ui {
    class CFPrevDialog;
}

class CFPrevDialog : public QDialog {

    Q_OBJECT
public:
    explicit CFPrevDialog(QWidget *parent = 0);

signals:

public slots:

private:
    Ui::CFPrevDialog *ui;
};

#endif // CFPREVDIALOG_H
