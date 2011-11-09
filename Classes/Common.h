/**
 * \file  Common.h
 * \brief common header
 */


#ifndef CONSOLE_COMMON_H
#define CONSOLE_COMMON_H
//---------------------------------------------------------------------------
//Core
#include <Qt>
#include <QtGlobal>
#include <QTextCodec>
#include <QDebug>
#include <QClipboard>

//GUI
#include <QtGui>
#include <QCoreApplication>
#include <QApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <QMainWindow>
#include <QDesktopWidget>
#include <QWidget>
#include <QShortcut>

//
#include <QList>
#include <QStringList>
#include <QSettings>
#include <QFile>

//Sql
#include <QtSql>
#include <QSqlTableModel>

//table
#include <QHeaderView>
#include <QItemSelectionModel>
#include <QStandardItemModel>
#include <QTableView>

//network
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
//#include <QJson>

//other
#include <QImage>

//xLib
#include <xLib/Common/xCommon.h>

//---------------------------------------------------------------------------
#define qNOT_IMPL               { QMessageBox::warning(this, qApp->applicationName(), tr(__FUNCTION__) + tr(": Not implemented")); }
#define qMSG(s)                 { QMessageBox::information(NULL, qApp->applicationName(), tr(s)); }
#define qCHECK_REF(var, object) { if (false == var) { QMessageBox::critical(0, qApp->applicationName(), object.lastError().text(),  QMessageBox::Cancel); } }
#define qCHECK_PTR(var, object) { if (false == var) { QMessageBox::critical(0, qApp->applicationName(), object->lastError().text(), QMessageBox::Cancel); } }
//---------------------------------------------------------------------------
#endif // CONSOLE_COMMON_H
