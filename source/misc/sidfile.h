#ifndef SIDFILE_H
#define SIDFILE_H

#include <QString>
#include <QFile>
#include <QByteArray>
#include "source/errorhandler.h"

class SidFile
{
public:
    SidFile();
    QByteArray m_blob, m_stripped;
    unsigned int m_loadAddress, m_initAddress, m_playAddress;
    QString m_outFile, m_fileName, m_path;

    void Load(QString filename, QString path);
    void Convert();
};

#endif // SID_H

