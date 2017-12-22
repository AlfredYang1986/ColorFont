#ifndef CFEFFECTWIDGET_H
#define CFEFFECTWIDGET_H

#include <QWidget>

class QTabWidget;
class QPushButton;
class QHBoxLayout;

class CFEffectWidget : public QWidget {

    Q_OBJECT

public:
    enum EFFECT_INDEX {
        FILL_COLOR = 0x01,
        FILL_BKG = 0x02,
    };

public:
    explicit CFEffectWidget(QWidget* parent = 0);
    ~CFEffectWidget();

    virtual void setupUi();
    virtual void setupContent() = 0;
    virtual void setControlPanel() = 0;
    virtual QPushButton* setClearBtn();

signals:
    void signal_effectColorChanged(const QColor&, int e);

public slots:
    virtual void slot_effectColorChange(const QColor&);

protected:
    QTabWidget* tab;
    QWidget* panel;
};

#endif // CFEFFECTWIDGET_H
