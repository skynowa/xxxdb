/**
 * \file  Config.h
 * \brief config
 */


#ifndef PickupDb_ConfigH
#define PickupDb_ConfigH
//---------------------------------------------------------------------------
// main window
#define CONFIG_ORG_NAME                 "Skynowa Studio"
#define CONFIG_APP_NAME                 "PickupDB"
#define CONFIG_APP_WIDTH                1000
#define CONFIG_APP_HEIGHT               600


// DB tables, fields
#define CONFIG_DB_T_PERSON              "t_person"

#define CONFIG_DB_F_ID                  "f_id"
#define CONFIG_DB_F_MAIN_NAME           "f_main_name"
#define CONFIG_DB_F_MAIN_AGE            "f_main_age"
#define CONFIG_DB_F_PHOTO_1             "f_photo_1"


// photo
#define CONFIG_PHOTO_WIDTH              300
#define CONFIG_PHOTO_HEIGHT             200
#define CONFIG_IMAGE_FORMATS            "*.bmp *.jpg *.jpeg *.gif *.tiff *.png *.xpm"
#define CONFIG_IMAGE_IS_CONVERT         true


// resources
#define CONFIG_RES_MAIN_ICON            ":/App.ico"


// etc
#define CONFIG_BACKUP_DIR_NAME          "Backups"
#define CONFIG_DB_FILE_EXT              ".db"
#define CONFIG_GUID                     "PickupDB_simple_guid"
#define CONFIG_TABLEVIEW_ROW_HEIGHT     20
#define CONFIG_TEXT_NO_PHOTO            "No photo"
//---------------------------------------------------------------------------
#endif // PickupDb_ConfigH
