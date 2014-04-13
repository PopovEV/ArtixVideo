#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>
#include <QList>
#include <QDir>
#include <QDebug>

struct Parameter{
    QString value;
    QString name;
    QString type;
};

struct Query{
    int id;
    int num;
    int child;
    bool ischild;
    QString name;
    QString description;
    QString sql;
    QString tabName;
    QList<Parameter> ParameterList;
};

inline bool removeDir (const QString &path)
{
    QDir dir (path);

    const QFileInfoList fileList = dir.entryInfoList (QDir::AllEntries | QDir::NoDotAndDotDot);

    bool result = true;
    QFile file;

    for (QFileInfoList::const_iterator it = fileList.constBegin(),
            end = fileList.constEnd(); result && it != end; ++it) {
        const QString fileName = it->absoluteFilePath();

//        qDebug () << QString ("Remove ") + (it->isDir () ? "dir" : "file")
//                  << fileName;

        file.setFileName (fileName);

        result = it->isDir ()
                 ? removeDir (fileName)
                 : file.remove ();

        if (!result) {
            qDebug () << file.errorString ();
        }
    }

    return result && dir.rmdir (path);
}

#endif // GLOBAL_H
