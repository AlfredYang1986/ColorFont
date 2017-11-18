#ifndef CFCOLORBKG_H
#define CFCOLORBKG_H

#include <QWidget>

class QLineEdit;
class CFColorSelectPanel;
class CFColorPreviewPanel;

class CFColorBkg : public QWidget {

    Q_OBJECT

public:
    explicit CFColorBkg(QWidget* parent = 0);
    ~CFColorBkg();

public slots:
    void slot_selectedColorChanged();

protected:
    void setupUi();

private:
    CFColorSelectPanel* red_panel;
    CFColorSelectPanel* green_panel;
    CFColorSelectPanel* blue_panel;
    CFColorSelectPanel* alpha_panel;

    CFColorPreviewPanel* prev_panel;

};

#endif // CFCOLORBKG_H
