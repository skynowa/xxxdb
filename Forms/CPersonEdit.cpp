/**
 * \file   CPersonEdit.h
 * \brief  edit person data
 */


#include "CPersonEdit.h"


/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CPersonEdit::CPersonEdit(QWidget *parent) :
    QDialog(parent)
{
    _construct();
}
//---------------------------------------------------------------------------
/*virtual*/
CPersonEdit::~CPersonEdit() {
    _destruct();
}
//---------------------------------------------------------------------------


/****************************************************************************
*   private
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CPersonEdit::_construct() {
    {
        m_Ui.setupUi(this);
    }

    // QTreeWidget
    {
        m_Ui.twGroups->setColumnCount(1);
        m_Ui.twGroups->setHeaderLabels(QStringList() << CONFIG_DATA_GROUP_HEADER);
        m_Ui.twGroups->setMinimumWidth(110);
        m_Ui.twGroups->setMaximumWidth(110);

        // top items
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_MAIN) );
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_PHONES) );
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_ADDRESS) );
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_EMAIL) );
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_WEB) );
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_MESSENGERS) );
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_JOB) );
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_STUDIES) );
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_DATES) );
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_INTERESTS) );
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_PERIODS) );
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_ETC) );
        _m_ltwGroups.push_back( new QTreeWidgetItem(m_Ui.twGroups, QStringList() << CONFIG_DATA_GROUP_NOTE) );

        m_Ui.twGroups->addTopLevelItems(_m_ltwGroups);

        m_Ui.twGroups->expandAll();
        m_Ui.twGroups->resizeColumnToContents(0);
    }

    {
        #if 0
            QTreeWidgetItem *item;

            QWidget *w = new QWidget(this);

            foreach(item, _m_ltwGroups) {
                m_Ui.tabwGroupsDetail->addTab(w, item->text(0));
            }
        #endif
    }

    {
        connect(m_Ui.bbxButtons, SIGNAL(clicked(QAbstractButton *)),
                this,            SLOT  (slot_bbxButtons_OnClicked(QAbstractButton *)));
    }
}
//---------------------------------------------------------------------------
void
CPersonEdit::_destruct() {
    qDeleteAll(_m_ltwGroups);
}
//---------------------------------------------------------------------------
void
CPersonEdit::_initMain() {

}
//---------------------------------------------------------------------------


/****************************************************************************
*   private slots
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CPersonEdit::slot_bbxButtons_OnClicked(QAbstractButton *button) {
    QDialogButtonBox::StandardButton sbType = m_Ui.bbxButtons->standardButton(button);
    switch (sbType) {
        case QDialogButtonBox::Reset: {

        }
        break;

        case QDialogButtonBox::Ok: {
                close();
            }
            break;

        case QDialogButtonBox::Cancel: {
                close();
            }
            break;

        case QDialogButtonBox::Apply: {

            }
            break;

        default: {
                Q_ASSERT(false);
            }
            break;
    }
}
//---------------------------------------------------------------------------
