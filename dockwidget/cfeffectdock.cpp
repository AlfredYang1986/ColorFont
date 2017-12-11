#include "cfeffectdock.h"
#include <QTableView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QHBoxLayout>
#include "cfmainwindow.h"
#include "module/modulemanagement/cfmm.h"
#include "effectwidget/cfeffectwidget.h"
#include "shadowwidget/cfshadowwidget.h"
#include "bkgwidget/cfbkgwidget.h"
#include "hangupwidget/cfhangupwidget.h"
#include "fillwidget/cffillwidget.h"
#include "borderwidget/cfborderwidget.h"
#include "preparedwidget/cfpreparedwidget.h"

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

    {
        CFModuleManagement* cfmm = CFModuleManagement::queryInstance();
        CFFuncResults reVal = cfmm->pushMessage(QUERY_MODULE, QUERY_MAIN_WINDOW, CFFuncArguments());
        CFMainWindow* w = reVal.getV("main_window").value<CFMainWindow*>();

        QObject::connect(this, SIGNAL(signal_effectDockClosed()),
                         w, SLOT(slot_controlPanelClosed()));
    }
}

void CFEffectDock::setupFlag() {
    this->setObjectName(tr("effect dock"));
    this->setWidget(view);
    this->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
}

class object_predicate {
public:
    object_predicate(const QString& s) : _s(s) {}

    bool operator()(CFEffectWidget* eff) {
        return eff->objectName() == _s;
    }

    QString _s;
};

void CFEffectDock::slot_effectSelected(const QModelIndex& index) {
//    content->reset();

    QString str = index.data().toString();
    qDebug() << "select one : " << str;

    for (unsigned int index = 0; index < wds.count(); ++index) {
        wds.at(index)->setVisible(false);
    }

    QList<CFEffectWidget*>::iterator iter =
            std::find_if(wds.begin(), wds.end(), object_predicate(str));

    CFEffectWidget * w = 0;
    if (iter != wds.end()) {
        w = *iter;
        w->setVisible(true);
    } else {
        w = createSubPanelByName(str);
        w->setObjectName(str);
        w->setupContent();
        w->setControlPanel();
        main_layout->insertWidget(0, w);
        wds.append(w);
    }
}

CFEffectWidget* CFEffectDock::createSubPanelByName(const QString& name) {
    if (name == tr("效果模板")) {
        return new CFPreparedWidget();
    } else if (name == tr("阴影效果")) {
        return new CFShadowWidget();
    } else if (name == tr("霓虹效果")) {
        return new CFShadowWidget();
    } else if (name == tr("导入背景")) {
        return new CFBkgWidget();
    } else if (name == tr("导入挂件")) {
        return new CFHangupWidget();
    } else if (name == tr("填充效果")) {
        return new CFFillWidget();
    } else if (name == tr("边框效果")) {
        return new CFBorderWidget();
    } else if (name == tr("斜面浮雕")) {
        return new CFShadowWidget();
    } else {
        return NULL;
    }
}

void CFEffectDock::closeEvent(QCloseEvent *) {
    emit signal_effectDockClosed();
}
