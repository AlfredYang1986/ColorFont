#include "cfcolorselectpanel.h"
#include <QHBoxLayout>
#include <QSlider>
#include <QLineEdit>
#include <QIntValidator>

CFColorSelectPanel::CFColorSelectPanel(QWidget *parent)
    : QWidget(parent) {

    setupUi();
}

CFColorSelectPanel::~CFColorSelectPanel() {

}

void CFColorSelectPanel::setupUi() {
    QHBoxLayout* layout = new QHBoxLayout();

    slider = new QSlider();
    slider->setOrientation(Qt::Horizontal);
    slider->setRange(0, 255);
    slider->setValue(0);
    slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    le = new QLineEdit();
    le->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    le->setFixedWidth(30);
    le->setValidator(new QIntValidator(0, 255));

    layout->addWidget(slider);
    layout->addWidget(le);

    this->setLayout(layout);

    QObject::connect(slider, SIGNAL(valueChanged(int)),
                     this, SLOT(slot_sliderChanged(int)));

    QObject::connect(le, SIGNAL(textChanged(QString)),
                     this, SLOT(slot_editChanged(QString)));
}

void CFColorSelectPanel::slot_sliderChanged(int v) {
    le->setText(QString::number(v));
    emit signal_selectedColorChanged();
}

void CFColorSelectPanel::slot_editChanged(const QString &v) {
    slider->setValue(v.toInt());
    emit signal_selectedColorChanged();
}

int CFColorSelectPanel::getCurrentValue() const {
    QString str = le->text();
    if (str.isEmpty())
        return 0;
    else return str.toInt();
}
