#include "cfeffectdock.h"
#include <QTableView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QHBoxLayout>
#include "effectwidget/cfeffectwidget.h"
#include "shadowwidget/cfshadowwidget.h"

#include <QDebug>

CFEffectDock::CFEffectDock(QWidget* parent)
    : QDockWidget(parent) {

    setupUi();
    setupFlag();
}

CFEffectDock::~CFEffectDock() {
    if (view)
        delete view;
}

void CFEffectDock::setupUi() {
    view = new QWidget();
    main_layout = new QHBoxLayout();

    content = new QTableView();

    const QString sl[] = {
        tr("效果模板"),
        tr("阴影效果"),
        tr("霓虹效果"),
        tr("导入背景"),
        tr("导入挂件"),
        tr("填充效果"),
        tr("边框效果"),
        tr("斜面浮雕")
    };

    QStandardItemModel *qstmodel = new QStandardItemModel();

    for (unsigned int index = 0; index < sizeof(sl) / sizeof(QString); ++index) {
        QStandardItem* item = new QStandardItem(sl[index]);
        item->setData(sl[index]);
        qstmodel->appendRow(item);
    }

    content->setModel(qstmodel);
    content->setSelectionMode(QAbstractItemView::SingleSelection);
    content->setEditTriggers(QAbstractItemView::NoEditTriggers);
    content->setAutoFillBackground(false);
    content->verticalHeader()->setVisible(false);
    content->horizontalHeader()->setVisible(false);
    content->setFixedWidth(100);
    content->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    QObject::connect(content, SIGNAL(clicked(QModelIndex)),
                     this, SLOT(slot_effectSelected(QModelIndex)));

    main_layout->addWidget(content);
    view->setLayout(main_layout);
}

void CFEffectDock::setupFlag() {
    this->setObjectName(tr("effect dock"));
    this->setWidget(view);
    this->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
}

void CFEffectDock::slot_effectSelected(const QModelIndex& index) {
    content->reset();

    QString str = index.data().toString();
    qDebug() << "select one : " << str;

    for (unsigned int index = 0; index < wds.count(); ++index) {
        wds.at(index)->setVisible(false);
    }

    if (str == tr("阴影效果")) {
        CFEffectWidget * w = 0;
        if (wds.count() > 0) {
            w = wds.at(0);
            w->setMinimumWidth(100);
            w->setVisible(true);
        } else {
            w = new CFShadowWidget();
            w->setupContent();
            main_layout->insertWidget(0, w);
            wds.append(w);
        }
    }
}
