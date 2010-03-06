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
    connect(ui->pushButton_Check,SIGNAL(clicked()),this,SLOT(search()));
    connect(http, SIGNAL(done(bool)), this, SLOT(showPage()));

    QStringList labels;
    labels << tr("Stations");

    ui->treeWidget->header()->setResizeMode(QHeaderView::ResizeToContents);
    ui->treeWidget->setHeaderLabels(labels);
    ui->treeWidget->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showPage() {

    QFile f("file.xml");
    f.open(QFile::WriteOnly | QFile::Text);
    f.write(http->readAll());
    f.close();

    XmlHandler handler(ui->treeWidget);

    /* XML Parsing and Showing */
    QXmlSimpleReader reader;
    reader.setContentHandler(&handler);
    reader.setErrorHandler(&handler);

    QFile file("file.xml");
    file.open(QFile::ReadOnly | QFile::Text);

    QXmlInputSource xmlInputSource(&file);

    if (reader.parse(xmlInputSource))
        statusBar()->showMessage(tr("Search Finished"), 3000);

}

void MainWindow::search() {

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
