#ifndef CFIMPORTTTFDIALOG_H
#define CFIMPORTTTFDIALOG_H

#include <QDialog>
#include "../../common/funcargs/cfargs.h"

class QWidget;
class QTableWidget;
class QGridLayout;

class CFImportTTFDialog : public QDialog {

    Q_OBJECT

public:
    explicit CFImportTTFDialog(
            FT_Face face,
            QWidget* parent = 0);
    ~CFImportTTFDialog();


protected:
    void setupUi();

public slots:
    void slot_pageChanged(int);

private:
//    QTableWidget* table;
    QVector<FT_ULong> char_lst;

    FT_Face pc;
};


#endif // CFIMPORTTTFDIALOG_H
