#ifndef CFOPERATORWIDGET_H
#define CFOPERATORWIDGET_H

#include <QMdiSubWindow>

#include <ft2build.h>
#include FT_FREETYPE_H

class QWidget;
class CFGLLineWidget;

class CFOperatorWidget : public QMdiSubWindow {

    Q_OBJECT

public:
    explicit CFOperatorWidget(QWidget* parent = 0);
    ~CFOperatorWidget();

    void pushCharacter(FT_Face face, FT_ULong charcode);
protected:
    void setupUi();

private:
    QVector<CFGLLineWidget*> contents;
};

#endif // CFOPERATORWIDGET_H
