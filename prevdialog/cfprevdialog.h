#ifndef CFPREVDIALOG_H
#define CFPREVDIALOG_H

#include <QSplitter>
class QListView;
class QTableView;

//namespace Ui {
//    class CFPrevDialog;
//}

class CFPrevDialog : public QSplitter {

    Q_OBJECT
public:
    explicit CFPrevDialog(QWidget *parent = 0);

signals:

public slots:
    void closeButton_toggle();

protected:
    void setupUI();
    void setLeftListViewModel();
    void setRightListViewModel();

private:
    QListView* left;
    QTableView* right;
};

#endif // CFPREVDIALOG_H
