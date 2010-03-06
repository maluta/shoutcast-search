#include "xmlhandler.h"

#include <QDebug>
#include <QStyle>
#include <QTreeWidgetItem>

XmlHandler::XmlHandler(QTreeWidget *_treeWidget)
{

    treeWidget = _treeWidget;
    QStyle *style = treeWidget->style();

    cdicon.addPixmap(style->standardPixmap(QStyle::SP_DriveDVDIcon));

    treeWidget->clear();
}


bool XmlHandler::startElement(const QString & /* namespaceURI */,
                               const QString & /* localName */,
                               const QString &qName,
                               const QXmlAttributes &attributes)
{

    if (qName == "station") {

        QString data;

        item = new QTreeWidgetItem(treeWidget);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        item->setIcon(0, cdicon);
        item->setText(0, attributes.value("name"));

        root = item;

        item = new QTreeWidgetItem(root);
        item->setText(0, "Current Track: "+attributes.value("ct"));

        item = new QTreeWidgetItem(root);
        item->setText(0, "ID: "+attributes.value("id"));

        item = new QTreeWidgetItem(root);
        item->setText(0, "Genre: "+attributes.value("genre"));

        item = new QTreeWidgetItem(root);
        item->setText(0, "Bitrate: "+attributes.value("br"));

        item = new QTreeWidgetItem(root);
        item->setText(0, "Format: "+attributes.value("mt"));

        item = new QTreeWidgetItem(root);
        item->setText(0, "Listeners: "+attributes.value("lc"));

        link = new QTreeWidgetItem(root);
        link->setText(0, "Playlist: http://yp.shoutcast.com/sbin/tunein-station.pls?id="+attributes.value("id"));
        link->setFlags(link->flags() | Qt::ItemIsEditable);
    }

    return true;
}

