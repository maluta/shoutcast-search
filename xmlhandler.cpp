#include "xmlhandler.h"

#include <QDebug>
#include <QStyle>
#include <QTreeWidgetItem>

XmlHandler::XmlHandler(QTreeWidget *_treeWidget)
{

    treeWidget = _treeWidget;
    QStyle *style = treeWidget->style();

    folderIcon.addPixmap(style->standardPixmap(QStyle::SP_DirClosedIcon),
                         QIcon::Normal, QIcon::Off);
    folderIcon.addPixmap(style->standardPixmap(QStyle::SP_DirOpenIcon),
                         QIcon::Normal, QIcon::On);
    bookmarkIcon.addPixmap(style->standardPixmap(QStyle::SP_FileIcon));

}


bool XmlHandler::startElement(const QString & /* namespaceURI */,
                               const QString & /* localName */,
                               const QString &qName,
                               const QXmlAttributes &attributes)
{

    if (qName == "station") {
        item = new QTreeWidgetItem(treeWidget);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        item->setIcon(0, folderIcon);
        item->setText(0, attributes.value("name"));
        item->setText(1, attributes.value("ct"));
        item->setText(2, attributes.value("id"));
        item->setText(3, attributes.value("br"));
        item->setText(4, attributes.value("genre"));
        item->setText(5, attributes.value("mt"));
        item->setText(6, attributes.value("lc"));

    }

    currentText.clear();

    return true;
}

QTreeWidgetItem *XmlHandler::createChildItem(const QString &tagName)
{
    QTreeWidgetItem *childItem;
    if (item) {
        childItem = new QTreeWidgetItem(item);
    } else {
        childItem = new QTreeWidgetItem(treeWidget);
    }
    childItem->setData(0, Qt::UserRole, tagName);



    return childItem;
}
