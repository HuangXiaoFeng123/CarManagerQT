#ifndef DONXML_H
#define DONXML_H
#include <QString>
#include <QDomDocument>
#include <QDomProcessingInstruction>
#include <QDomElement>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QDateTime>
#include <QtXml>

class DonXML
{
public:
    DonXML();
    static void createXML(QString filePath);
    static void appendXML(QString filePath,QStringList list);
    static void writeXML(QDomDocument &doc,QDomElement &root,QStringList &list);
    static void readXML(QString filePath,
                        QStringList &fList,
                        QStringList &bList,
                        QStringList &pList,
                        QStringList &nList,
                        QStringList &tList);
};

#endif // DONXML_H
