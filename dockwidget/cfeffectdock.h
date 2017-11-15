#ifndef CFEFFECTDOCK_H
#define CFEFFECTDOCK_H

#include <QDockWidget>

class QWidget;
class QTableView;
class QHBoxLayout;
class CFEffectWidget;

class CFEffectDock : public QDockWidget {

    Q_OBJECT

public:
    explicit CFEffectDock(QWidget* parent = 0);
    ~CFEffectDock();

protected:
    void setupUi();
    void setupFlag();
    CFEffectWidget* createSubPanelByName(const QString& name);

signals:
    void applyEffect(const QString& name);

public slots:
    void slot_effectSelected(const QModelIndex&);

private:
    QWidget* view;
    QHBoxLayout* main_layout;
    QTableView* content;

    QList<CFEffectWidget*> wds;
};

#endif // CFEFFECTDOCK_H
