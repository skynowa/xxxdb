/**
 * \file  Config.h
 * \brief config
 */


#ifndef XXXDb_ConfigH
#define XXXDb_ConfigH
//------------------------------------------------------------------------------
#include <QObject>
//------------------------------------------------------------------------------
// application
#define APP_NAME                    "XXXDb"
#define APP_ORG                     "SKYNOWA Studio"
#define APP_VERSION                 "1.0.0"
#define APP_GUID                    APP_NAME"simple_guid"
#define APP_WINDOW_CLASS            "Qt5QWindow"  // for Qt 5.0.1, Qt 4 - QTool
#define APP_WIDTH                   1000
#define APP_HEIGHT                  600
#define APP_SIZE                    QSize(APP_WIDTH, APP_HEIGHT)

#define APP_DIR_PLUGIN_PLATFORMS    "platforms"
#define APP_DIR_PLUGIN_SQLDRIVERS   "sqldrivers"
#define APP_DIR_PLUGIN_IMAGEFORMATS "imageformats"

#if defined(Q_WS_WIN)
    #define APP_LOCALE_CODEC        "Windows-1251"
#else
    #define APP_LOCALE_CODEC        "UTF-8"
#endif

// photo
#define PHOTO_NUM                   15
#define IMAGE_FORMATS               "*.bmp *.jpg *.jpeg *.gif *.tiff *.png *.xpm"
#define IMAGE_IS_CONVERT            true

#define PHOTO_WIDTH                 300
#define PHOTO_HEIGHT                200
#define PHOTO_SIZE                  QSize(PHOTO_WIDTH, PHOTO_HEIGHT)
#define PHOTO_MARGIN                2

#define PHOTO_MINI_WIDTH            120
#define PHOTO_MINI_HEIGHT           80
#define PHOTO_MINI_SIZE             QSize(PHOTO_MINI_WIDTH, PHOTO_MINI_HEIGHT)

// etc
#define BACKUP_DIR_NAME             "Backup"
#define INI_FILE_EXT                ".ini"
#define LANGS_DIR_NAME              "Langs"
#define LANGS_FILE_NAME_RU          "XXXDb_ru_RU.qm"
#define TABLEVIEW_ROW_HEIGHT        20
#define TEXT_NO_PHOTO               QObject::tr("No photo")
#define FIND_TEXT_WIDTH             180

// DB tables, fields
#define DB_DIR_NAME                 "Db"
#define DB_FILE_EXT                 ".db"
#define DB_T_PERSON                 "t_person"

/*******************************************************************************
*   DB fields
*
*******************************************************************************/

#define DB_F_ID                     "f_id"

// Main
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

// TODO: Periods

// Etc
#define DB_F_ETC_DATECREATION       "f_etc_datecreation"
#define DB_F_ETC_DATELASTCHANGE     "f_etc_datelastchange"

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


/*******************************************************************************
*   DB field records
*
*******************************************************************************/

struct SDbRecord
    ///< DB fields
{
    cint     index;    ///< index
    cQString field;    ///< DB field name
    cQString caption;  ///< QTableView header caption
};

typedef const SDbRecord cSDbRecord;

cSDbRecord g_dbRecords[] = {
    {0,  DB_F_ID,                   QObject::tr("#")},

    // Main
    {1,  DB_F_MAIN_NICK,            QObject::tr("Nick")},
    {2,  DB_F_MAIN_SURNAME,         QObject::tr("Surname")},
    {3,  DB_F_MAIN_NAME,            QObject::tr("Name")},
    {4,  DB_F_MAIN_PATRONYMIC,      QObject::tr("Patronymic")},
    {5,  DB_F_MAIN_AGE,             QObject::tr("Age")},
    {6,  DB_F_MAIN_HEIGHT,          QObject::tr("Height")},
    {7,  DB_F_MAIN_WEIGHT,          QObject::tr("Weight")},
    {8,  DB_F_MAIN_HAIRLENGTH,      QObject::tr("Hair length")},
    {9,  DB_F_MAIN_HAIRCOLOR,       QObject::tr("Hair color")},
    {10, DB_F_MAIN_APPEARANCE,      QObject::tr("Appearance")},
    {11, DB_F_MAIN_STATUS,          QObject::tr("Status")},

    // Phones
    {12, DB_F_PHONES_MOBILE1,       QObject::tr("Mobile 1")},
    {13, DB_F_PHONES_MOBILE2,       QObject::tr("Mobile 2")},
    {14, DB_F_PHONES_MOBILE3,       QObject::tr("Mobile 3")},
    {15, DB_F_PHONES_HOME,          QObject::tr("Phone home")},
    {16, DB_F_PHONES_JOB,           QObject::tr("Phone job")},
    {17, DB_F_PHONES_OTHER,         QObject::tr("Phone other")},

    // Address
    {18, DB_F_ADDRESS_COUNTRY,      QObject::tr("Country")},
    {19, DB_F_ADDRESS_CODE,         QObject::tr("Code")},
    {20, DB_F_ADDRESS_CITY,         QObject::tr("City")},
    {21, DB_F_ADDRESS_DISTRICT,     QObject::tr("District")},
    {22, DB_F_ADDRESS_STREET,       QObject::tr("Street")},
    {23, DB_F_ADDRESS_HOUSE,        QObject::tr("House")},
    {24, DB_F_ADDRESS_PORCH,        QObject::tr("Porch")},
    {25, DB_F_ADDRESS_FLOOR,        QObject::tr("Floor")},
    {26, DB_F_ADDRESS_APARTMENT,    QObject::tr("Apartment")},

    // E-mail
    {27, DB_F_EMAIL_EMAIL,          QObject::tr("E-mail")},

    // Web
    {28, DB_F_WEB_WEB,              QObject::tr("Web")},

    // Messengers
    {29, DB_F_MESSENGERS_ICQ,       QObject::tr("ICQ")},
    {30, DB_F_MESSENGERS_SKYPE,     QObject::tr("Skype")},

    // Job
    {31, DB_F_JOB_PROFESSION,       QObject::tr("Profession")},
    {32, DB_F_JOB_ADDRESS,          QObject::tr("Address")},
    {33, DB_F_JOB_SALARY,           QObject::tr("Salary")},
    {34, DB_F_JOB_COMPANY,          QObject::tr("Company")},

    // Dates
    {35, DB_F_DATES_BIRTHDAY,       QObject::tr("Birthday")},
    {36, DB_F_DATES_BIRTHDAYFATHER, QObject::tr("Birthday father")},
    {37, DB_F_DATES_BIRTHDAYMOTHER, QObject::tr("Birthday mother")},
    {38, DB_F_DATES_DAYDATING,      QObject::tr("Day of dating")},
    {39, DB_F_DATES_DAYFIRSTKISS,   QObject::tr("Day of 1-st kiss")},
    {40, DB_F_DATES_DAYFIRSTSEX,    QObject::tr("Day of 1-st sex")},

    // Interests
    {41, DB_F_INTERESTS_HOBBY,      QObject::tr("Hobby")},
    {42, DB_F_INTERESTS_SPORTS,     QObject::tr("Sports")},
    {43, DB_F_INTERESTS_SMOKING,    QObject::tr("Smoking")},
    {44, DB_F_INTERESTS_ALCOHOL,    QObject::tr("Alcohol")},
    {45, DB_F_INTERESTS_DRUGS,      QObject::tr("Drugs")},

    // TODO: Periods

    // Etc
    {46, DB_F_ETC_DATECREATION,     QObject::tr("Date creation")},
    {47, DB_F_ETC_DATELASTCHANGE,   QObject::tr("Date last change")},

    // Notes
    {48, DB_F_NOTES_NOTES,          QObject::tr("Notes")},

    // Photos
    {49, DB_F_PHOTOS_1,             QObject::tr("Photo 1")},
    {50, DB_F_PHOTOS_2,             QObject::tr("Photo 2")},
    {51, DB_F_PHOTOS_3,             QObject::tr("Photo 3")},
    {52, DB_F_PHOTOS_4,             QObject::tr("Photo 4")},
    {53, DB_F_PHOTOS_5,             QObject::tr("Photo 5")},
    {54, DB_F_PHOTOS_6,             QObject::tr("Photo 6")},
    {55, DB_F_PHOTOS_7,             QObject::tr("Photo 7")},
    {56, DB_F_PHOTOS_8,             QObject::tr("Photo 8")},
    {57, DB_F_PHOTOS_9,             QObject::tr("Photo 9")},
    {58, DB_F_PHOTOS_10,            QObject::tr("Photo 10")},
    {59, DB_F_PHOTOS_11,            QObject::tr("Photo 11")},
    {60, DB_F_PHOTOS_12,            QObject::tr("Photo 12")},
    {61, DB_F_PHOTOS_13,            QObject::tr("Photo 13")},
    {62, DB_F_PHOTOS_14,            QObject::tr("Photo 14")},
    {63, DB_F_PHOTOS_15,            QObject::tr("Photo 15")},
    {64, DB_F_PHOTOS_PRIMARY,       QObject::tr("Photo primary")}
};

/*******************************************************************************
*   types
*
*******************************************************************************/

typedef QHash<QWidget *, QString> db_items_t;
typedef const db_items_t          cdb_items_t;
//------------------------------------------------------------------------------
#endif // XXXDb_ConfigH
