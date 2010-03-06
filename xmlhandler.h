#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#include <QXmlDefaultHandler>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QIcon>

QT_BEGIN_NAMESPACE
class QTreeWidget;
class QTreeWidgetItem;
QT_END_NAMESPACE

class XmlHandler : public QXmlDefaultHandler
{

public:
    XmlHandler(QTreeWidget *_treeWidget);
    bool startElement(const QString &namespaceURI, const QString &localName,
                      const QString &qName, const QXmlAttributes &attributes);


private:
    QTreeWidget *treeWidget;
    QTreeWidgetItem *item;
    QTreeWidgetItem *root;
    QTreeWidgetItem *link;

    QString currentText;
    QString errorStr;

    QIcon cdicon;

};

#endif // XMLHANDLER_H
