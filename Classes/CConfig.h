/**
 * \file  CConfig.h
 * \brief configs
 */


#ifndef XXXDb_ConfigH
#define XXXDb_ConfigH
//-------------------------------------------------------------------------------------------------
#include <QObject>
//-------------------------------------------------------------------------------------------------
// application
#define APP_NAME                    "XXXDb"
#define APP_ORG                     "SKYNOWA Studio"
#define APP_VERSION                 "1.0.0"
#define APP_GUID                    APP_NAME"simple_guid"
#define APP_WINDOW_CLASS            "Qt5QWindow"  // for Qt 5.0.1, Qt 4 - QTool
#define APP_WIDTH                   1000
#define APP_HEIGHT                  600
#define APP_SIZE                    QSize(APP_WIDTH, APP_HEIGHT)
#define APP_PLUGINS_DIR_NAME        "Plugins"

// photo
#define PHOTO_NUM                   15

#define PHOTO_WIDTH                 300
#define PHOTO_HEIGHT                200
#define PHOTO_SIZE                  QSize(PHOTO_WIDTH, PHOTO_HEIGHT)
#define PHOTO_MARGIN                2

#define PHOTO_MINI_WIDTH            120
#define PHOTO_MINI_HEIGHT           80
#define PHOTO_MINI_SIZE             QSize(PHOTO_MINI_WIDTH, PHOTO_MINI_HEIGHT)

// etc
#define LANGS_FILE_NAME_RU          "XXXDb_ru_RU.qm"
#define TABLEVIEW_ROW_HEIGHT        20
#define FIND_TEXT_WIDTH             180
#define SIDEBAR_WIDTH               326


/**************************************************************************************************
*    DB tables, fields
*
**************************************************************************************************/

#define DB_T_PERSON                 "t_person"

// Main
#define DB_F_ID                     "f_id"
#define DB_F_MAIN_NICK              "f_main_nick"
#define DB_F_MAIN_SURNAME           "f_main_surname"
#define DB_F_MAIN_NAME              "f_main_name"
#define DB_F_MAIN_PATRONYMIC        "f_main_patronymic"
#define DB_F_MAIN_AGE               "f_main_age"
#define DB_F_MAIN_HEIGHT            "f_main_height"
#define DB_F_MAIN_WEIGHT            "f_main_weight"
#define DB_F_MAIN_HAIRLENGTH        "f_main_hairlength"
#define DB_F_MAIN_HAIRCOLOR         "f_main_haircolor"
#define DB_F_MAIN_APPEARANCE        "f_main_appearance"
#define DB_F_MAIN_STATUS            "f_main_status"

// Phones
#define DB_F_PHONES_MOBILE1         "f_phones_mobile1"
#define DB_F_PHONES_MOBILE2         "f_phones_mobile2"
#define DB_F_PHONES_MOBILE3         "f_phones_mobile3"
#define DB_F_PHONES_HOME            "f_phones_home"
#define DB_F_PHONES_JOB             "f_phones_job"
#define DB_F_PHONES_OTHER           "f_phones_other"

// Address
#define DB_F_ADDRESS_COUNTRY        "f_address_country"
#define DB_F_ADDRESS_CODE           "f_address_code"
#define DB_F_ADDRESS_CITY           "f_address_city"
#define DB_F_ADDRESS_DISTRICT       "f_address_district"
#define DB_F_ADDRESS_STREET         "f_address_street"
#define DB_F_ADDRESS_HOUSE          "f_address_house"
#define DB_F_ADDRESS_PORCH          "f_address_porch"
#define DB_F_ADDRESS_FLOOR          "f_address_floor"
#define DB_F_ADDRESS_APARTMENT      "f_address_apartment"

// E-mail
#define DB_F_EMAIL_EMAIL            "f_email_email"

// Web
#define DB_F_WEB_WEB                "f_web_web"

// Messengers
#define DB_F_MESSENGERS_ICQ         "f_messengers_icq"
#define DB_F_MESSENGERS_SKYPE       "f_messengers_skype"

// Job
#define DB_F_JOB_PROFESSION         "f_job_profession"
#define DB_F_JOB_ADDRESS            "f_job_address"
#define DB_F_JOB_SALARY             "f_job_salary"
#define DB_F_JOB_COMPANY            "f_job_company"

// Dates
#define DB_F_DATES_BIRTHDAY         "f_dates_birthday"
#define DB_F_DATES_BIRTHDAYFATHER   "f_dates_birthdayfather"
#define DB_F_DATES_BIRTHDAYMOTHER   "f_dates_birthdaymother"
#define DB_F_DATES_DAYDATING        "f_dates_daydating"
#define DB_F_DATES_DAYFIRSTKISS     "f_dates_dayfirstkiss"
#define DB_F_DATES_DAYFIRSTSEX      "f_dates_dayfirstsex"

// Interests
#define DB_F_INTERESTS_HOBBY        "f_interests_hobby"
#define DB_F_INTERESTS_SPORTS       "f_interests_sports"
#define DB_F_INTERESTS_SMOKING      "f_interests_smoking"
#define DB_F_INTERESTS_ALCOHOL      "f_interests_alcohol"
#define DB_F_INTERESTS_DRUGS        "f_interests_drugs"

// Periods
#define DB_F_PERIODS_BEGIN          "f_periods_begin"
#define DB_F_PERIODS_DURATION       "f_periods_duration"
#define DB_F_PERIODS_CYCLE_DURATION "f_periods_cycle_duration"

// Etc
#define DB_F_ETC_DATECREATION       "f_etc_datecreation"
#define DB_F_ETC_DATELASTCHANGE     "f_etc_datelastchange"
#define DB_F_ETC_ATTACHMENT         "f_etc_attachment"

// Notes
#define DB_F_NOTES_NOTES            "f_notes_notes"

// Photos
#define DB_F_PHOTOS_1               "f_photos_1"
#define DB_F_PHOTOS_2               "f_photos_2"
#define DB_F_PHOTOS_3               "f_photos_3"
#define DB_F_PHOTOS_4               "f_photos_4"
#define DB_F_PHOTOS_5               "f_photos_5"
#define DB_F_PHOTOS_6               "f_photos_6"
#define DB_F_PHOTOS_7               "f_photos_7"
#define DB_F_PHOTOS_8               "f_photos_8"
#define DB_F_PHOTOS_9               "f_photos_9"
#define DB_F_PHOTOS_10              "f_photos_10"
#define DB_F_PHOTOS_11              "f_photos_11"
#define DB_F_PHOTOS_12              "f_photos_12"
#define DB_F_PHOTOS_13              "f_photos_13"
#define DB_F_PHOTOS_14              "f_photos_14"
#define DB_F_PHOTOS_15              "f_photos_15"
#define DB_F_PHOTOS_PRIMARY         "f_photos_primary"


/**************************************************************************************************
*   DB field records
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
struct SDbRecord
    ///< DB fields
{
    const int   index;      ///< index
    const bool  isNonUi;    ///< is non UI DB field
    const char *field;      ///< DB field name
    const char *caption;    ///< QTableView header caption
};

typedef const SDbRecord cSDbRecord;
//-------------------------------------------------------------------------------------------------
class CConfig :
    public QObject
{
    Q_OBJECT

public:
    static cSDbRecord dbRecords[69];  ///< array of DB fields
};
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   types
*
**************************************************************************************************/

typedef QHash<QWidget *, QString> db_items_t;
typedef const db_items_t          cdb_items_t;
//-------------------------------------------------------------------------------------------------
#endif // XXXDb_ConfigH
