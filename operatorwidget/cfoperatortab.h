#ifndef CFOPERATORTAB_H
#define CFOPERATORTAB_H

#include <QTabBar>

class QWidget;

class CFOperatorTab : public QTabBar {

    Q_OBJECT

public:
    explicit CFOperatorTab(QWidget* parent = 0);
    ~CFOperatorTab();

protected:
    void setupUi();
};

#endif // CFOPERATORTAB_H
