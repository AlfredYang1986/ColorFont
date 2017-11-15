#include "cfcolorbkg.h"

#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QRgb>
#include "cfcolorselectpanel.h"
#include "cfcolorpreviewpanel.h"

#include <QDebug>

CFColorBkg::CFColorBkg(QWidget *parent)
    : QWidget(parent) {

    setupUi();
}

CFColorBkg::~CFColorBkg() {

}

void CFColorBkg::setupUi() {

    QVBoxLayout* vl = new QVBoxLayout();

    QGridLayout* layout = new QGridLayout();
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 4);

    layout->setRowStretch(0, 1);
    layout->setRowStretch(1, 1);
    layout->setRowStretch(2, 1);
    layout->setRowStretch(3, 1);

    const QString ls[] = {
        tr("Red"),
        tr("Green"),
        tr("Blue"),
        tr("Alpha")
    };

    for (unsigned index = 0; index < sizeof(ls) / sizeof(QString); ++index) {
        QLabel* lb = new QLabel(ls[index]);
        layout->addWidget(lb, index, 0);
    }

    red_panel = new CFColorSelectPanel();
    layout->addWidget(red_panel, 0, 1);

    green_panel = new CFColorSelectPanel();
    layout->addWidget(green_panel, 1, 1);

    blue_panel = new CFColorSelectPanel();
    layout->addWidget(blue_panel, 2, 1);

    alpha_panel = new CFColorSelectPanel();
    layout->addWidget(alpha_panel, 3, 1);

    vl->addLayout(layout);

    QHBoxLayout* hl = new QHBoxLayout();
    hl->addSpacerItem(
                new QSpacerItem(0, 0,
                                QSizePolicy::Expanding, QSizePolicy::Fixed));

    prev_panel = new CFColorPreviewPanel();
    prev_panel->setFixedSize(50, 50);
    prev_panel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    hl->addWidget(prev_panel);

    hl->addSpacerItem(
                new QSpacerItem(0, 0,
                                QSizePolicy::Expanding, QSizePolicy::Fixed));

    vl->addLayout(hl);

    this->setLayout(vl);

    QObject::connect(red_panel, SIGNAL(signal_selectedColorChanged()),
                     this, SLOT(slot_selectedColorChanged()));
    QObject::connect(green_panel, SIGNAL(signal_selectedColorChanged()),
                     this, SLOT(slot_selectedColorChanged()));
    QObject::connect(blue_panel, SIGNAL(signal_selectedColorChanged()),
                     this, SLOT(slot_selectedColorChanged()));
    QObject::connect(alpha_panel, SIGNAL(signal_selectedColorChanged()),
                     this, SLOT(slot_selectedColorChanged()));
}

void CFColorBkg::slot_selectedColorChanged() {
    int r = red_panel->getCurrentValue();
    int g = green_panel->getCurrentValue();
    int b = blue_panel->getCurrentValue();
    int a = alpha_panel->getCurrentValue();

    prev_panel->changeColor(QColor(r, g, b, a));
    prev_panel->update();
}
