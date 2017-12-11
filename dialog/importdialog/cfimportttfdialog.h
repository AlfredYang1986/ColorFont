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

signals:
    void signal_importSuccess();

protected:
    void setupUi();

    void closeEvent(QCloseEvent*);

public slots:
    void slot_pageChanged(int);
    void slot_importCurrentFont();
    void slot_importCurrentSymbol();

private:
    QVector<FT_ULong> char_lst;
    FT_Face pc;
};


#endif // CFIMPORTTTFDIALOG_H
