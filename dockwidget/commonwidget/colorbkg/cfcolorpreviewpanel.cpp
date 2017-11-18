#include "cfcolorpreviewpanel.h"
#include <QPainter>
#include <QDebug>

CFColorPreviewPanel::CFColorPreviewPanel(QWidget *parent)
    : QWidget(parent) {

}

CFColorPreviewPanel::~CFColorPreviewPanel() {

}

void CFColorPreviewPanel::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    QColor color = QColor(r, g, b, a);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(color, Qt::SolidPattern));
    painter.drawRect(this->rect());
}

void CFColorPreviewPanel::changeColor(const QColor &color) {
    r = color.red();
    g = color.green();
    b = color.blue();
    a = color.alpha();
}
