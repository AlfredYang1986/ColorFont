#ifndef CFOPERATORWIDGET_H
#define CFOPERATORWIDGET_H

#include <QMdiSubWindow>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "dockwidget/effectwidget/cfeffectwidget.h"

class QWidget;
class CFGLLineWidget;

class CFOperatorWidget : public QMdiSubWindow {

    Q_OBJECT

public:
    explicit CFOperatorWidget(QWidget* parent = 0);
    ~CFOperatorWidget();

    void pushCharacter(FT_Face face, FT_ULong charcode);
    void setCurrentFillColor(const QColor& color);

    void save();
    void saveAs(const QString& path);

    void loadPath(const QString& path);
    void setFillColor(const QColor& c);
    void setBKGColor(const QColor& c);
protected:
    void setupUi();

private:
    QVector<CFGLLineWidget*> contents;
    QString file_path;
    QVector<std::pair<FT_Face, FT_ULong> > storage;
//    QVector<std::pair<int, > > property;
    QColor fill_color;
};

#endif // CFOPERATORWIDGET_H
