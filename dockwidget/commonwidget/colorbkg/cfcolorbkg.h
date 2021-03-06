#ifndef CFCOLORBKG_H
#define CFCOLORBKG_H

#include <QWidget>

class QLineEdit;
class CFColorSelectPanel;
class CFColorPreviewPanel;
class CFEffectWidget;

class CFColorBkg : public QWidget {

    Q_OBJECT

public:
    explicit CFColorBkg(CFEffectWidget* container, QWidget* parent = 0);
    ~CFColorBkg();

signals:
    void signal_selectedBkgColorChanged(const QColor&);

public slots:
    void slot_selectedColorChanged();
    void slot_applyColorChange();

protected:
    void setupUi();

private:
    CFColorSelectPanel* red_panel;
    CFColorSelectPanel* green_panel;
    CFColorSelectPanel* blue_panel;
    CFColorSelectPanel* alpha_panel;

    CFColorPreviewPanel* prev_panel;

    CFEffectWidget* _c;

};

#endif // CFCOLORBKG_H
