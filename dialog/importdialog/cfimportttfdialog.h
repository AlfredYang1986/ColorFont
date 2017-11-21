#ifndef CFIMPORTTTFDIALOG_H
#define CFIMPORTTTFDIALOG_H

#include <QDialog>

class QWidget;

class CFImportTTFDialog : public QDialog {

    Q_OBJECT

public:
    explicit CFImportTTFDialog(QWidget* parent);
    ~CFImportTTFDialog();

protected:
    void setupUi();

private:

};


#endif // CFIMPORTTTFDIALOG_H
