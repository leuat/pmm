#include "sidfile.h"

SidFile::SidFile()
{

}

void SidFile::Load(QString filename, QString path)
{
    m_path = path;
    m_fileName = filename;
    if (!filename.endsWith(".sid"))
        ErrorHandler::e.Error("Unable to load '" + filename +"', must be sid file!");
    QFile file(path + filename);

    if (!QFile::exists(path + filename))
        ErrorHandler::e.Error("Unable to locate '" + filename +"'");

    file.open(QIODevice::ReadOnly);
    m_blob = file.readAll();


    if (!(m_blob.at(0)=='P' && m_blob.at(1)=='S' && m_blob.at(2)=='I' && m_blob.at(3)=='D'))
        ErrorHandler::e.Error("File '" + filename +"' not identified as a SID file");

    m_loadAddress = m_blob.at(8)<<8 | m_blob.at(8+1)<<0;
    m_initAddress = m_blob.at(0xa)<<8 | m_blob.at(0xa+1)<<0;
    m_playAddress = m_blob.at(0xc)<<8 | m_blob.at(0xc+1)<<0;

    file.close();
}

void SidFile::Convert()
{
    m_outFile = m_fileName.remove(".sid");
    m_outFile = "_" + m_outFile + ".dat";

    if (QFile::exists(m_path + m_outFile))
        QFile::remove(m_path + m_outFile);

    QFile file(m_path + m_outFile);
    file.open(QIODevice::WriteOnly);
    int headerSize = 0x7C +2;
    // Should the +2 be included? FUCK!
    m_blob.remove(0,headerSize);
    file.write(m_blob);
    file.close();

}
