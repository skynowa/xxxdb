/**
 * \file  Config.h
 * \brief config
 */


#ifndef PickupDb_ConfigH
#define PickupDb_ConfigH
//-----------------------------------------------------------------------------
// main window
#define CONFIG_ORG_NAME                     "Skynowa Studio"
#define CONFIG_APP_NAME                     "PickupDB"
#define CONFIG_APP_WIDTH                    1000
#define CONFIG_APP_HEIGHT                   600

// photo
#define CONFIG_PHOTO_NUM                    10
#define CONFIG_PHOTO_WIDTH                  300
#define CONFIG_PHOTO_HEIGHT                 200
#define CONFIG_PHOTO_SIZE                   QSize(CONFIG_PHOTO_WIDTH, CONFIG_PHOTO_HEIGHT)
#define CONFIG_IMAGE_FORMATS                "*.bmp *.jpg *.jpeg *.gif *.tiff *.png *.xpm"
#define CONFIG_IMAGE_IS_CONVERT             true

#define CONFIG_PHOTO_MINI_WIDTH             120
#define CONFIG_PHOTO_MINI_HEIGHT            80
#define CONFIG_PHOTO_MINI_SIZE              QSize(CONFIG_PHOTO_MINI_WIDTH, CONFIG_PHOTO_MINI_HEIGHT)

// resources
#define CONFIG_RES_MAIN_ICON                ":/App.ico"

// etc
#define CONFIG_BACKUP_DIR_NAME              "Backups"
#define CONFIG_DB_FILE_EXT                  ".db"
#define CONFIG_GUID                         "PickupDB_simple_guid"
#define CONFIG_TABLEVIEW_ROW_HEIGHT         20
#define CONFIG_TEXT_NO_PHOTO                "No photo"

// DB tables, fields
#define CONFIG_DB_T_PERSON                  "t_person"


#define CONFIG_DB_F_ID                      "f_id"

// Main
#define CONFIG_DB_F_MAIN_NICK               "f_main_nick"
#define CONFIG_DB_F_MAIN_SURNAME            "f_main_surname"
#define CONFIG_DB_F_MAIN_NAME               "f_main_name"
#define CONFIG_DB_F_MAIN_PATRONYMIC         "f_main_patronymic"
#define CONFIG_DB_F_MAIN_AGE                "f_main_age"
#define CONFIG_DB_F_MAIN_HEIGHT             "f_main_height"
#define CONFIG_DB_F_MAIN_WEIGHT             "f_main_weight"
#define CONFIG_DB_F_MAIN_HAIRLENGTH         "f_main_hairlength"
#define CONFIG_DB_F_MAIN_HAIRCOLOR          "f_main_haircolor"
#define CONFIG_DB_F_MAIN_APPEARANCE         "f_main_appearance"
#define CONFIG_DB_F_MAIN_AGREEMENT          "f_main_agreement"

// Phones
#define CONFIG_DB_F_PHONES_MOBILE1          "f_phones_mobile1"
#define CONFIG_DB_F_PHONES_MOBILE2          "f_phones_mobile2"
#define CONFIG_DB_F_PHONES_MOBILE3          "f_phones_mobile3"
#define CONFIG_DB_F_PHONES_HOME             "f_phones_home"
#define CONFIG_DB_F_PHONES_JOB              "f_phones_job"
#define CONFIG_DB_F_PHONES_OTHER            "f_phones_other"

// Address
#define CONFIG_DB_F_ADDRESS_COUNTRY         "f_address_country"
#define CONFIG_DB_F_ADDRESS_CODE            "f_address_code"
#define CONFIG_DB_F_ADDRESS_CITY            "f_address_city"
#define CONFIG_DB_F_ADDRESS_DISTRICT        "f_address_district"
#define CONFIG_DB_F_ADDRESS_STREET          "f_address_street"
#define CONFIG_DB_F_ADDRESS_HOUSE           "f_address_house"
#define CONFIG_DB_F_ADDRESS_PORCH           "f_address_porch"
#define CONFIG_DB_F_ADDRESS_FLOOR           "f_address_floor"
#define CONFIG_DB_F_ADDRESS_APARTMENT       "f_address_apartment"

// E-mail
#define CONFIG_DB_F_EMAIL_EMAIL             "f_email_email"

// Web
#define CONFIG_DB_F_WEB_WEB                 "f_web_web"

// Messengers
#define CONFIG_DB_F_MESSENGERS_ICQ          "f_messengers_icq"
#define CONFIG_DB_F_MESSENGERS_SKYPE        "f_messengers_skype"

// Job
#define CONFIG_DB_F_JOB_PROFESSION          "f_job_profession"
#define CONFIG_DB_F_JOB_ADDRESS             "f_job_address"
#define CONFIG_DB_F_JOB_SALARY              "f_job_salary"
#define CONFIG_DB_F_JOB_COMPANY             "f_job_company"

// Dates
#define CONFIG_DB_F_DATES_BIRTHDAY          "f_dates_birthday"
#define CONFIG_DB_F_DATES_BIRTHDAYFATHER    "f_dates_birthdayfather"
#define CONFIG_DB_F_DATES_BIRTHDAYMOTHER    "f_dates_birthdaymother"
#define CONFIG_DB_F_DATES_DAYDATING         "f_dates_daydating"
#define CONFIG_DB_F_DATES_DAYFIRSTKISS      "f_dates_dayfirstkiss"
#define CONFIG_DB_F_DATES_DAYFIRSTSEX       "f_dates_dayfirstsex"

// Interests
#define CONFIG_DB_F_INTERESTS_HOBBY         "f_interests_hobby"
#define CONFIG_DB_F_INTERESTS_SPORTS        "f_interests_sports"
#define CONFIG_DB_F_INTERESTS_SMOKING       "f_interests_smoking"
#define CONFIG_DB_F_INTERESTS_ALCOHOL       "f_interests_alcohol"
#define CONFIG_DB_F_INTERESTS_DRUGS         "f_interests_drugs"

// TODO: Periods

// Etc
#define CONFIG_DB_F_ETC_DATECREATION        "f_etc_datecreation"
#define CONFIG_DB_F_ETC_DATELASTCHANGE      "f_etc_datelastchange"

// Notes
#define CONFIG_DB_F_NOTES_NOTES             "f_notes_notes"

// Photos
#define CONFIG_DB_F_PHOTOS_1                "f_photos_1"
#define CONFIG_DB_F_PHOTOS_2                "f_photos_2"
#define CONFIG_DB_F_PHOTOS_3                "f_photos_3"
#define CONFIG_DB_F_PHOTOS_4                "f_photos_4"
#define CONFIG_DB_F_PHOTOS_5                "f_photos_5"
#define CONFIG_DB_F_PHOTOS_6                "f_photos_6"
#define CONFIG_DB_F_PHOTOS_7                "f_photos_7"
#define CONFIG_DB_F_PHOTOS_8                "f_photos_8"
#define CONFIG_DB_F_PHOTOS_9                "f_photos_9"
#define CONFIG_DB_F_PHOTOS_10               "f_photos_10"
#define CONFIG_DB_F_PHOTOS_11               "f_photos_11"
#define CONFIG_DB_F_PHOTOS_12               "f_photos_12"
#define CONFIG_DB_F_PHOTOS_13               "f_photos_13"
#define CONFIG_DB_F_PHOTOS_14               "f_photos_14"
#define CONFIG_DB_F_PHOTOS_15               "f_photos_15"
#define CONFIG_DB_F_PHOTOS_PRIMARY_DBFIELD  "f_photos_primary_dbfield"

//-----------------------------------------------------------------------------
#endif // PickupDb_ConfigH
