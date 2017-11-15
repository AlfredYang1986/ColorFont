#ifndef CFCOLORPREVIEWPANEL_H
#define CFCOLORPREVIEWPANEL_H

#include <QWidget>

class CFColorPreviewPanel : public QWidget {
    Q_OBJECT

public:
    explicit CFColorPreviewPanel(QWidget* parent = 0);
    ~CFColorPreviewPanel();

    void changeColor(const QColor& color);
protected:
    virtual void paintEvent(QPaintEvent *);

private:
    int r;
    int g;
    int b;
    int a;
};

#endif // CFCOLORPREVIEWPANEL_H
