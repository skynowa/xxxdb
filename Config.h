/**
 * \file  Config.h
 * \brief config
 */


#ifndef XXXDb_ConfigH
#define XXXDb_ConfigH
//------------------------------------------------------------------------------
// application
#define APP_NAME                     "XXXDb"
#define APP_ORG                      "Skynowa Studio"
#define APP_GUID                     APP_NAME"simple_guid"
#define APP_WINDOW_CLASS             "Qt5QWindow"  // for Qt 5.0.1, Qt 4 - QTool
#define APP_WIDTH                    1000
#define APP_HEIGHT                   600
#define APP_SIZE                     QSize(APP_WIDTH, APP_HEIGHT)

#define APP_MAIN_TITLE               APP_NAME + tr(" - accounting software for girls")
#define APP_PERSON_EDIT_TITLE        APP_NAME + tr(" - person editor")
#define APP_PHOTO_ALBUM_TITLE        APP_NAME + tr(" - photo album")
#define APP_ABOUT_TITLE              APP_NAME + tr(" - about")

// photo
#define PHOTO_NUM                    10
#define IMAGE_FORMATS                "*.bmp *.jpg *.jpeg *.gif *.tiff *.png *.xpm"
#define IMAGE_IS_CONVERT             true

#define PHOTO_WIDTH                  300
#define PHOTO_HEIGHT                 200
#define PHOTO_SIZE                   QSize(PHOTO_WIDTH, PHOTO_HEIGHT)
#define PHOTO_MARGIN                 2

#define PHOTO_MINI_WIDTH             120
#define PHOTO_MINI_HEIGHT            80
#define PHOTO_MINI_SIZE              QSize(PHOTO_MINI_WIDTH, PHOTO_MINI_HEIGHT)

// etc
#define BACKUP_DIR_NAME              "Backup"
#define INI_FILE_EXT                 ".ini"
#define INI_FILE_PATH                (QCoreApplication::applicationFilePath() + INI_FILE_EXT)
#define TABLEVIEW_ROW_HEIGHT         20
#define TEXT_NO_PHOTO                tr("No photo")

// DB tables, fields
#define DB_DIR_NAME                  "Db"
#define DB_FILE_EXT                  ".db"
#define DB_T_PERSON                  "t_person"

/*******************************************************************************
*   DB fields
*
*******************************************************************************/

#define DB_F_ID                      "f_id"

// Main
#define DB_F_MAIN_NICK               "f_main_nick"
#define DB_F_MAIN_SURNAME            "f_main_surname"
#define DB_F_MAIN_NAME               "f_main_name"
#define DB_F_MAIN_PATRONYMIC         "f_main_patronymic"
#define DB_F_MAIN_AGE                "f_main_age"
#define DB_F_MAIN_HEIGHT             "f_main_height"
#define DB_F_MAIN_WEIGHT             "f_main_weight"
#define DB_F_MAIN_HAIRLENGTH         "f_main_hairlength"
#define DB_F_MAIN_HAIRCOLOR          "f_main_haircolor"
#define DB_F_MAIN_APPEARANCE         "f_main_appearance"
#define DB_F_MAIN_STATUS             "f_main_status"

// Phones
#define DB_F_PHONES_MOBILE1          "f_phones_mobile1"
#define DB_F_PHONES_MOBILE2          "f_phones_mobile2"
#define DB_F_PHONES_MOBILE3          "f_phones_mobile3"
#define DB_F_PHONES_HOME             "f_phones_home"
#define DB_F_PHONES_JOB              "f_phones_job"
#define DB_F_PHONES_OTHER            "f_phones_other"

// Address
#define DB_F_ADDRESS_COUNTRY         "f_address_country"
#define DB_F_ADDRESS_CODE            "f_address_code"
#define DB_F_ADDRESS_CITY            "f_address_city"
#define DB_F_ADDRESS_DISTRICT        "f_address_district"
#define DB_F_ADDRESS_STREET          "f_address_street"
#define DB_F_ADDRESS_HOUSE           "f_address_house"
#define DB_F_ADDRESS_PORCH           "f_address_porch"
#define DB_F_ADDRESS_FLOOR           "f_address_floor"
#define DB_F_ADDRESS_APARTMENT       "f_address_apartment"

// E-mail
#define DB_F_EMAIL_EMAIL             "f_email_email"

// Web
#define DB_F_WEB_WEB                 "f_web_web"

// Messengers
#define DB_F_MESSENGERS_ICQ          "f_messengers_icq"
#define DB_F_MESSENGERS_SKYPE        "f_messengers_skype"

// Job
#define DB_F_JOB_PROFESSION          "f_job_profession"
#define DB_F_JOB_ADDRESS             "f_job_address"
#define DB_F_JOB_SALARY              "f_job_salary"
#define DB_F_JOB_COMPANY             "f_job_company"

// Dates
#define DB_F_DATES_BIRTHDAY          "f_dates_birthday"
#define DB_F_DATES_BIRTHDAYFATHER    "f_dates_birthdayfather"
#define DB_F_DATES_BIRTHDAYMOTHER    "f_dates_birthdaymother"
#define DB_F_DATES_DAYDATING         "f_dates_daydating"
#define DB_F_DATES_DAYFIRSTKISS      "f_dates_dayfirstkiss"
#define DB_F_DATES_DAYFIRSTSEX       "f_dates_dayfirstsex"

// Interests
#define DB_F_INTERESTS_HOBBY         "f_interests_hobby"
#define DB_F_INTERESTS_SPORTS        "f_interests_sports"
#define DB_F_INTERESTS_SMOKING       "f_interests_smoking"
#define DB_F_INTERESTS_ALCOHOL       "f_interests_alcohol"
#define DB_F_INTERESTS_DRUGS         "f_interests_drugs"

// TODO: Periods

// Etc
#define DB_F_ETC_DATECREATION        "f_etc_datecreation"
#define DB_F_ETC_DATELASTCHANGE      "f_etc_datelastchange"

// Notes
#define DB_F_NOTES_NOTES             "f_notes_notes"

// Photos
#define DB_F_PHOTOS_1                "f_photos_1"
#define DB_F_PHOTOS_2                "f_photos_2"
#define DB_F_PHOTOS_3                "f_photos_3"
#define DB_F_PHOTOS_4                "f_photos_4"
#define DB_F_PHOTOS_5                "f_photos_5"
#define DB_F_PHOTOS_6                "f_photos_6"
#define DB_F_PHOTOS_7                "f_photos_7"
#define DB_F_PHOTOS_8                "f_photos_8"
#define DB_F_PHOTOS_9                "f_photos_9"
#define DB_F_PHOTOS_10               "f_photos_10"
#define DB_F_PHOTOS_11               "f_photos_11"
#define DB_F_PHOTOS_12               "f_photos_12"
#define DB_F_PHOTOS_13               "f_photos_13"
#define DB_F_PHOTOS_14               "f_photos_14"
#define DB_F_PHOTOS_15               "f_photos_15"
#define DB_F_PHOTOS_PRIMARY_DBFIELD  "f_photos_primary_dbfield"


/*******************************************************************************
*   DB field captions
*
*******************************************************************************/

#define DB_CF_ID                     tr("#")

// Main
#define DB_CF_MAIN_NICK              tr("Nick")
#define DB_CF_MAIN_SURNAME           tr("Surname")
#define DB_CF_MAIN_NAME              tr("Name")
#define DB_CF_MAIN_PATRONYMIC        tr("Patronymic")
#define DB_CF_MAIN_AGE               tr("Age")
#define DB_CF_MAIN_HEIGHT            tr("Height")
#define DB_CF_MAIN_WEIGHT            tr("Weight")
#define DB_CF_MAIN_HAIRLENGTH        tr("Hair length")
#define DB_CF_MAIN_HAIRCOLOR         tr("Hair color")
#define DB_CF_MAIN_APPEARANCE        tr("Appearance")
#define DB_CF_MAIN_STATUS            tr("Status")

// Phones
#define DB_CF_PHONES_MOBILE1         tr("Mobile 1")
#define DB_CF_PHONES_MOBILE2         tr("Mobile 2")
#define DB_CF_PHONES_MOBILE3         tr("Mobile 3")
#define DB_CF_PHONES_HOME            tr("Phone home")
#define DB_CF_PHONES_JOB             tr("Phone job")
#define DB_CF_PHONES_OTHER           tr("Phone other")

// Address
#define DB_CF_ADDRESS_COUNTRY        tr("Country")
#define DB_CF_ADDRESS_CODE           tr("Code")
#define DB_CF_ADDRESS_CITY           tr("City")
#define DB_CF_ADDRESS_DISTRICT       tr("District")
#define DB_CF_ADDRESS_STREET         tr("Street")
#define DB_CF_ADDRESS_HOUSE          tr("House")
#define DB_CF_ADDRESS_PORCH          tr("Porch")
#define DB_CF_ADDRESS_FLOOR          tr("Floor")
#define DB_CF_ADDRESS_APARTMENT      tr("Apartment")

// E-mail
#define DB_CF_EMAIL_EMAIL            tr("E-mail")

// Web
#define DB_CF_WEB_WEB                tr("Web")

// Messengers
#define DB_CF_MESSENGERS_ICQ         tr("ICQ")
#define DB_CF_MESSENGERS_SKYPE       tr("Skype")

// Job
#define DB_CF_JOB_PROFESSION         tr("Profession")
#define DB_CF_JOB_ADDRESS            tr("Address")
#define DB_CF_JOB_SALARY             tr("Salary")
#define DB_CF_JOB_COMPANY            tr("Company")

// Dates
#define DB_CF_DATES_BIRTHDAY         tr("Birthday")
#define DB_CF_DATES_BIRTHDAYFATHER   tr("Birthday father")
#define DB_CF_DATES_BIRTHDAYMOTHER   tr("Birthday mother")
#define DB_CF_DATES_DAYDATING        tr("Day of dating")
#define DB_CF_DATES_DAYFIRSTKISS     tr("Day of 1-st kiss")
#define DB_CF_DATES_DAYFIRSTSEX      tr("Day of 1-st sex")

// Interests
#define DB_CF_INTERESTS_HOBBY        tr("Hobby")
#define DB_CF_INTERESTS_SPORTS       tr("Sports")
#define DB_CF_INTERESTS_SMOKING      tr("Smoking")
#define DB_CF_INTERESTS_ALCOHOL      tr("Alcohol")
#define DB_CF_INTERESTS_DRUGS        tr("Drugs")

// TODO: Periods

// Etc
#define DB_CF_ETC_DATECREATION       tr("Date creation")
#define DB_CF_ETC_DATELASTCHANGE     tr("Date last change")

// Notes
#define DB_CF_NOTES_NOTES            tr("Notes")

// Photos
#define DB_CF_PHOTOS_1               tr("Photo 1")
#define DB_CF_PHOTOS_2               tr("Photo 2")
#define DB_CF_PHOTOS_3               tr("Photo 3")
#define DB_CF_PHOTOS_4               tr("Photo 4")
#define DB_CF_PHOTOS_5               tr("Photo 5")
#define DB_CF_PHOTOS_6               tr("Photo 6")
#define DB_CF_PHOTOS_7               tr("Photo 7")
#define DB_CF_PHOTOS_8               tr("Photo 8")
#define DB_CF_PHOTOS_9               tr("Photo 9")
#define DB_CF_PHOTOS_10              tr("Photo 10")
#define DB_CF_PHOTOS_11              tr("Photo 11")
#define DB_CF_PHOTOS_12              tr("Photo 12")
#define DB_CF_PHOTOS_13              tr("Photo 13")
#define DB_CF_PHOTOS_14              tr("Photo 14")
#define DB_CF_PHOTOS_15              tr("Photo 15")
#define DB_CF_PHOTOS_PRIMARY_DBFIELD tr("Photo primary DB field")


/*******************************************************************************
*   types
*
*******************************************************************************/

typedef QHash<QWidget *, QString> db_items_t;
typedef const db_items_t          cdb_items_t;
//------------------------------------------------------------------------------
#endif // XXXDb_ConfigH
