#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xmlhandler.h"

#include <QDebug>
#include <QUrl>
#include <QFile>

#define BASE_URL "yp.shoutcast.com"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    http = new QHttp(this);
    http->setHost(BASE_URL);

    /* creating connections */
    connect(ui->pushButton_Check,SIGNAL(clicked()),this,SLOT(check()));
    connect(http, SIGNAL(done(bool)), this, SLOT(showPage()));

    QStringList labels;
    labels << tr("Station Name") << tr("Current Track") << tr("ID") << tr("Bitrate") << tr("Genre") << tr("Format") << tr("Listeners");

    ui->treeWidget->header()->setResizeMode(QHeaderView::Interactive);
    ui->treeWidget->setHeaderLabels(labels);
    ui->treeWidget->clear();

    XmlHandler handler(ui->treeWidget);

    /* XML Parsing and Showing */

    QXmlSimpleReader reader;
    reader.setContentHandler(&handler);
    reader.setErrorHandler(&handler);

    QFile file("file.xml");
    file.open(QFile::ReadOnly | QFile::Text);

    QXmlInputSource xmlInputSource(&file);

    if (reader.parse(xmlInputSource))
        statusBar()->showMessage(tr("File loaded"), 2000);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showPage() {

    qDebug() << "MainWindow::showPage()";
    qDebug() << http->readAll();

}

void MainWindow::check() {

    qDebug() << "MainWindow::check()";

    QString s("/sbin/newxml.phtml?search=");
    s.append(ui->lineEdit->text());

    QByteArray path = QUrl::toPercentEncoding(s, "/?.=");
    http->get(path);
}

void MainWindow::changeEvent(QEvent *e)
{

    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
