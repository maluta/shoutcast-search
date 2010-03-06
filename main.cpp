/****************************************************************************
**
** Copyright (C) 2010 Tiago Maluta
** Contact: Tiago Maluta (maluta@unifei.edu.br)
**
** This code is licensed under GPLv3
**
****************************************************************************/

#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
