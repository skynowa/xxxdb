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
CPersonEdit::CPersonEdit(
    QWidget        *parent,
    QSqlTableModel *tableModel,
    const int      &currentRow
) :
    QDialog        (parent),
    _m_tmModel     (tableModel),
    _m_ciCurrentRow(currentRow)
{
    Q_ASSERT(NULL != _m_tmModel);
    Q_ASSERT(- 1  <  _m_ciCurrentRow);

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
    _initMain();
}
//---------------------------------------------------------------------------
void
CPersonEdit::_destruct() {
    qDeleteAll(_m_ltwGroups);
}
//---------------------------------------------------------------------------
void
CPersonEdit::_initMain() {
    m_Ui.setupUi(this);

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

    // tabwGroupsDetail
    {
        #if 0
            QTreeWidgetItem *item;

            QWidget *w = new QWidget(this);

            foreach(item, _m_ltwGroups) {
                m_Ui.tabwGroupsDetail->addTab(w, item->text(0));
            }
        #endif
    }

    // "Main" group
    {
        QSqlRecord srRecord = _m_tmModel->record(_m_ciCurrentRow);

        m_Ui.cboName->lineEdit()->setText( srRecord.value(CONFIG_DB_F_MAIN_NAME).toString() );
        m_Ui.cboAge->lineEdit()->setText ( srRecord.value(CONFIG_DB_F_MAIN_AGE ).toString() );
    }

    // bbxButtons
    {
        connect(m_Ui.bbxButtons, SIGNAL(clicked(QAbstractButton *)),
                this,            SLOT  (slot_bbxButtons_OnClicked(QAbstractButton *)));
    }
}
//---------------------------------------------------------------------------


/****************************************************************************
*   private slots
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CPersonEdit::slot_bbxButtons_OnClicked(
    QAbstractButton *button
)
{
    QDialogButtonBox::StandardButton sbType = m_Ui.bbxButtons->standardButton(button);
    switch (sbType) {
        case QDialogButtonBox::Reset: {
                _resetAll();
            }
            break;

        case QDialogButtonBox::Ok: {
                _saveAll();
                close();
            }
            break;

        case QDialogButtonBox::Cancel: {
                close();
            }
            break;

        case QDialogButtonBox::Apply: {
                _saveAll();
            }
            break;

        default: {
                Q_ASSERT(false);
            }
            break;
    }
}
//---------------------------------------------------------------------------


/****************************************************************************
*   private slots
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CPersonEdit::_resetAll() {
    m_Ui.cboName->lineEdit()->clear();
    m_Ui.cboAge->lineEdit()->clear();
}
//---------------------------------------------------------------------------
void
CPersonEdit::_saveAll() {
    QSqlRecord srRecord = _m_tmModel->record(_m_ciCurrentRow);

    {
        srRecord.setValue(CONFIG_DB_F_MAIN_NAME, m_Ui.cboName->lineEdit()->text());
        srRecord.setValue(CONFIG_DB_F_MAIN_AGE , m_Ui.cboAge->lineEdit()->text() );
    }

    _m_tmModel->setRecord(_m_ciCurrentRow, srRecord);
}
//---------------------------------------------------------------------------












