#ifndef WAVFILE_H
#define WAVFILE_H

#include <QtCore/qobject.h>
#include <QtCore/qfile.h>
#include <QtMultimedia/QAudioFormat>

class WavFile
{
public:
    WavFile(const QAudioFormat &format = QAudioFormat(),
            qint64 dataLength = 0);

    // Reads WAV header and seeks to start of data
    bool readHeader(QIODevice &device, QByteArray *buffer);

    // Writes WAV header
    bool writeHeader(QIODevice &device);

    // Read PCM data
    qint64 readData(QIODevice &device, QByteArray &buffer,
                    QAudioFormat outputFormat = QAudioFormat());

    const QAudioFormat& format() const;
    qint64 dataLength() const;

    static qint64 headerLength();

    static bool writeDataLength(QIODevice &device, qint64 dataLength);

private:
    QAudioFormat m_format;
    qint64 m_dataLength;
};

#endif
