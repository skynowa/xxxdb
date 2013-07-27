/**
 * \file  CConfig.cpp
 * \brief configs
 */


#include "CConfig.h"


/*******************************************************************************
*   public
*
*******************************************************************************/

//------------------------------------------------------------------------------
cSDbRecord CConfig::dbRecords[] = {
    {0,  false,  DB_F_ID,                   QT_TR_NOOP("#")},

    // Main
    {1,  false,  DB_F_MAIN_NICK,            QT_TR_NOOP("Nick")},
    {2,  false,  DB_F_MAIN_SURNAME,         QT_TR_NOOP("Surname")},
    {3,  false,  DB_F_MAIN_NAME,            QT_TR_NOOP("Name")},
    {4,  false,  DB_F_MAIN_PATRONYMIC,      QT_TR_NOOP("Patronymic")},
    {5,  false,  DB_F_MAIN_AGE,             QT_TR_NOOP("Age")},
    {6,  false,  DB_F_MAIN_HEIGHT,          QT_TR_NOOP("Height")},
    {7,  false,  DB_F_MAIN_WEIGHT,          QT_TR_NOOP("Weight")},
    {8,  false,  DB_F_MAIN_HAIRLENGTH,      QT_TR_NOOP("Hair length")},
    {9,  false,  DB_F_MAIN_HAIRCOLOR,       QT_TR_NOOP("Hair color")},
    {10, false,  DB_F_MAIN_APPEARANCE,      QT_TR_NOOP("Appearance")},
    {11, false,  DB_F_MAIN_STATUS,          QT_TR_NOOP("Status")},

    // Phones
    {12, false,  DB_F_PHONES_MOBILE1,       QT_TR_NOOP("Mobile #1")},
    {13, false,  DB_F_PHONES_MOBILE2,       QT_TR_NOOP("Mobile #2")},
    {14, false,  DB_F_PHONES_MOBILE3,       QT_TR_NOOP("Mobile #3")},
    {15, false,  DB_F_PHONES_HOME,          QT_TR_NOOP("Phone home")},
    {16, false,  DB_F_PHONES_JOB,           QT_TR_NOOP("Phone job")},
    {17, false,  DB_F_PHONES_OTHER,         QT_TR_NOOP("Phone other")},

    // Address
    {18, false,  DB_F_ADDRESS_COUNTRY,      QT_TR_NOOP("Country")},
    {19, false,  DB_F_ADDRESS_CODE,         QT_TR_NOOP("Code")},
    {20, false,  DB_F_ADDRESS_CITY,         QT_TR_NOOP("City")},
    {21, false,  DB_F_ADDRESS_DISTRICT,     QT_TR_NOOP("District")},
    {22, false,  DB_F_ADDRESS_STREET,       QT_TR_NOOP("Street")},
    {23, false,  DB_F_ADDRESS_HOUSE,        QT_TR_NOOP("House")},
    {24, false,  DB_F_ADDRESS_PORCH,        QT_TR_NOOP("Porch")},
    {25, false,  DB_F_ADDRESS_FLOOR,        QT_TR_NOOP("Floor")},
    {26, false,  DB_F_ADDRESS_APARTMENT,    QT_TR_NOOP("Apartment")},

    // E-mail
    {27, false,  DB_F_EMAIL_EMAIL,          QT_TR_NOOP("E-mail")},

    // Web
    {28, false,  DB_F_WEB_WEB,              QT_TR_NOOP("Web")},

    // Messengers
    {29, false,  DB_F_MESSENGERS_ICQ,       QT_TR_NOOP("ICQ")},
    {30, false,  DB_F_MESSENGERS_SKYPE,     QT_TR_NOOP("Skype")},

    // Job
    {31, false,  DB_F_JOB_PROFESSION,       QT_TR_NOOP("Profession")},
    {32, false,  DB_F_JOB_ADDRESS,          QT_TR_NOOP("Address")},
    {33, false,  DB_F_JOB_SALARY,           QT_TR_NOOP("Salary")},
    {34, false,  DB_F_JOB_COMPANY,          QT_TR_NOOP("Company")},

    // Dates
    {35, false,  DB_F_DATES_BIRTHDAY,       QT_TR_NOOP("Birthday")},
    {36, false,  DB_F_DATES_BIRTHDAYFATHER, QT_TR_NOOP("Birthday father")},
    {37, false,  DB_F_DATES_BIRTHDAYMOTHER, QT_TR_NOOP("Birthday mother")},
    {38, false,  DB_F_DATES_DAYDATING,      QT_TR_NOOP("Day of dating")},
    {39, false,  DB_F_DATES_DAYFIRSTKISS,   QT_TR_NOOP("Day of 1-st kiss")},
    {40, false,  DB_F_DATES_DAYFIRSTSEX,    QT_TR_NOOP("Day of 1-st sex")},

    // Interests
    {41, false,  DB_F_INTERESTS_HOBBY,      QT_TR_NOOP("Hobby")},
    {42, false,  DB_F_INTERESTS_SPORTS,     QT_TR_NOOP("Sports")},
    {43, false,  DB_F_INTERESTS_SMOKING,    QT_TR_NOOP("Smoking")},
    {44, false,  DB_F_INTERESTS_ALCOHOL,    QT_TR_NOOP("Alcohol")},
    {45, false,  DB_F_INTERESTS_DRUGS,      QT_TR_NOOP("Drugs")},

    // TODO: Periods

    // Etc
    {46, false,  DB_F_ETC_DATECREATION,     QT_TR_NOOP("Date creation")},
    {47, false,  DB_F_ETC_DATELASTCHANGE,   QT_TR_NOOP("Date last change")},

    // Notes
    {48, false,  DB_F_NOTES_NOTES,          QT_TR_NOOP("Notes")},

    // Photos
    {49, true,   DB_F_PHOTOS_1,             QT_TR_NOOP("Photo #1")},
    {50, true,   DB_F_PHOTOS_2,             QT_TR_NOOP("Photo #2")},
    {51, true,   DB_F_PHOTOS_3,             QT_TR_NOOP("Photo #3")},
    {52, true,   DB_F_PHOTOS_4,             QT_TR_NOOP("Photo #4")},
    {53, true,   DB_F_PHOTOS_5,             QT_TR_NOOP("Photo #5")},
    {54, true,   DB_F_PHOTOS_6,             QT_TR_NOOP("Photo #6")},
    {55, true,   DB_F_PHOTOS_7,             QT_TR_NOOP("Photo #7")},
    {56, true,   DB_F_PHOTOS_8,             QT_TR_NOOP("Photo #8")},
    {57, true,   DB_F_PHOTOS_9,             QT_TR_NOOP("Photo #9")},
    {58, true,   DB_F_PHOTOS_10,            QT_TR_NOOP("Photo #10")},
    {59, true,   DB_F_PHOTOS_11,            QT_TR_NOOP("Photo #11")},
    {60, true,   DB_F_PHOTOS_12,            QT_TR_NOOP("Photo #12")},
    {61, true,   DB_F_PHOTOS_13,            QT_TR_NOOP("Photo #13")},
    {62, true,   DB_F_PHOTOS_14,            QT_TR_NOOP("Photo #14")},
    {63, true,   DB_F_PHOTOS_15,            QT_TR_NOOP("Photo #15")},
    {64, true,   DB_F_PHOTOS_PRIMARY,       QT_TR_NOOP("Photo primary")}
};
//------------------------------------------------------------------------------
