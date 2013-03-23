/**
 * \file   CColumns.cpp
 * \brief  select QTableView columns
 */


#include "CColumns.h"


/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CColumns::CColumns(
    QWidget        *a_parent,
    QSqlTableModel *a_model
) :
    QDialog (a_parent),
    _tmModel(a_model)
{
    _construct();
}
//------------------------------------------------------------------------------

/*******************************************************************************
*   private
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CColumns::_construct() {
    _initMain();
}
//------------------------------------------------------------------------------
void
CColumns::_destruct() {

}
//------------------------------------------------------------------------------
void
CColumns::_initMain() {
    ui.setupUi(this);

    // main
    {
        setWindowTitle(APP_COLUMNS_TITLE);
    }

    {
        struct SHeader {
            cint      section;
            cQVariant value;
        };

        const SHeader chdHeaders[] = {
            {0,  DB_CF_ID},

            // Main
            {1,  DB_CF_MAIN_NICK},
            {2,  DB_CF_MAIN_SURNAME},
            {3,  DB_CF_MAIN_NAME},
            {4,  DB_CF_MAIN_PATRONYMIC},
            {5,  DB_CF_MAIN_AGE},
            {6,  DB_CF_MAIN_HEIGHT},
            {7,  DB_CF_MAIN_WEIGHT},
            {8,  DB_CF_MAIN_HAIRLENGTH},
            {9,  DB_CF_MAIN_HAIRCOLOR},
            {10, DB_CF_MAIN_APPEARANCE},
            {11, DB_CF_MAIN_STATUS},

            // Phones
            {12, DB_CF_PHONES_MOBILE1},
            {13, DB_CF_PHONES_MOBILE2},
            {14, DB_CF_PHONES_MOBILE3},
            {15, DB_CF_PHONES_HOME},
            {16, DB_CF_PHONES_JOB},
            {17, DB_CF_PHONES_OTHER},

            // Address
            {18, DB_CF_ADDRESS_COUNTRY},
            {19, DB_CF_ADDRESS_CODE},
            {20, DB_CF_ADDRESS_CITY},
            {21, DB_CF_ADDRESS_DISTRICT},
            {22, DB_CF_ADDRESS_STREET},
            {23, DB_CF_ADDRESS_HOUSE},
            {24, DB_CF_ADDRESS_PORCH},
            {25, DB_CF_ADDRESS_FLOOR},
            {26, DB_CF_ADDRESS_APARTMENT},

            // E-mail
            {27, DB_CF_EMAIL_EMAIL},

            // Web
            {28, DB_CF_WEB_WEB},

            // Messengers
            {29, DB_CF_MESSENGERS_ICQ},
            {30, DB_CF_MESSENGERS_SKYPE},

            // Job
            {31, DB_CF_JOB_PROFESSION},
            {32, DB_CF_JOB_ADDRESS},
            {33, DB_CF_JOB_SALARY},
            {34, DB_CF_JOB_COMPANY},

            // Dates
            {35, DB_CF_DATES_BIRTHDAY},
            {36, DB_CF_DATES_BIRTHDAYFATHER},
            {37, DB_CF_DATES_BIRTHDAYMOTHER},
            {38, DB_CF_DATES_DAYDATING},
            {39, DB_CF_DATES_DAYFIRSTKISS},
            {40, DB_CF_DATES_DAYFIRSTSEX},

            // Interests
            {41, DB_CF_INTERESTS_HOBBY},
            {42, DB_CF_INTERESTS_SPORTS},
            {43, DB_CF_INTERESTS_SMOKING},
            {44, DB_CF_INTERESTS_ALCOHOL},
            {45, DB_CF_INTERESTS_DRUGS},

            // TODO: Periods

            // Etc
            {46, DB_CF_ETC_DATECREATION},
            {47, DB_CF_ETC_DATELASTCHANGE},

            // Notes
            {48, DB_CF_NOTES_NOTES},

            // Photos
            {49, DB_CF_PHOTOS_1},
            {50, DB_CF_PHOTOS_2},
            {51, DB_CF_PHOTOS_3},
            {52, DB_CF_PHOTOS_4},
            {53, DB_CF_PHOTOS_5},
            {54, DB_CF_PHOTOS_6},
            {55, DB_CF_PHOTOS_7},
            {56, DB_CF_PHOTOS_8},
            {57, DB_CF_PHOTOS_9},
            {58, DB_CF_PHOTOS_10},
            {59, DB_CF_PHOTOS_11},
            {60, DB_CF_PHOTOS_12},
            {61, DB_CF_PHOTOS_13},
            {62, DB_CF_PHOTOS_14},
            {63, DB_CF_PHOTOS_15},
            {64, DB_CF_PHOTOS_PRIMARY}
        };

        // set caption for DB fields
        CMain *wnd = static_cast<CMain *>(parent());

        for (int i = 0; i < _tmModel->columnCount(); ++ i) {
            cbool isVisible = !wnd->ui.tvInfo->isColumnHidden(i);

            QListWidgetItem *item = new QListWidgetItem(ui.lwItems);
            item->setCheckState( isVisible ? Qt::Checked : Qt::Unchecked);
            item->setText( chdHeaders[i].value.toString() );

            ui.lwItems->addItem(item);
        }
    }

    // signals, slots
    {
        connect(ui.bbxButtons, &QDialogButtonBox::clicked,
                this,          &CColumns::slot_bbxButtons_OnClicked);
    }
}
//------------------------------------------------------------------------------
void
CColumns::_saveAll() {
    CMain *wnd = static_cast<CMain *>(parent());

    for (int i = 0; i < _tmModel->columnCount(); ++ i) {
        cbool isVisible = (ui.lwItems->item(i)->checkState() == Qt::Checked) ? true : false;

        wnd->ui.tvInfo->setColumnHidden(i, !isVisible);
    }
}
//------------------------------------------------------------------------------
void
CColumns::slot_bbxButtons_OnClicked(
    QAbstractButton *a_button
)
{
    QDialogButtonBox::StandardButton sbRv = ui.bbxButtons->standardButton(a_button);
    switch (sbRv) {
        case QDialogButtonBox::Ok:
            _saveAll();
            close();
            break;
        case QDialogButtonBox::Cancel:
            close();
            break;
        case QDialogButtonBox::Apply:
            _saveAll();
            break;
        default:
            Q_ASSERT(false);
            break;
    }
}
//------------------------------------------------------------------------------
