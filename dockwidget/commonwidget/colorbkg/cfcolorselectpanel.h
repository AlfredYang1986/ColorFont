#ifndef CFCOLORSELECTPANEL_H
#define CFCOLORSELECTPANEL_H

#include <QWidget>

class QSlider;
class QLineEdit;

class CFColorSelectPanel : public QWidget {

    Q_OBJECT

public:
    explicit CFColorSelectPanel(QWidget* parent = 0);
    ~CFColorSelectPanel();

    int getCurrentValue() const;

signals:
    void signal_selectedColorChanged();

public slots:
    void slot_sliderChanged(int v);
    void slot_editChanged(const QString& v);

protected:
    void setupUi();

private:
    QSlider* slider;
    QLineEdit* le;
};

#endif // CFCOLORSELECTPANEL_H
