#ifndef DATETIME_H
#define DATETIME_H
#include <QProcess>
#include <QDebug>
#include <QObject>
class DateTime : public QObject
{
    Q_PROPERTY(int getNtpStatus READ getNtpStatus WRITE setNtpStatus NOTIFY NtpStatusChanged)
    Q_PROPERTY(int TimeZone READ TimeZone WRITE setTimeZone NOTIFY TimeZoneChanged)
    Q_OBJECT
public:
    DateTime();
    int getNtpStatus();
    int TimeZone();
public slots:
    void setTimeZone(const int &_time_zone);
    void setDate(const QString &_date){
        process.start("date +%Y%m%d -s \""+_date+"\"");
    }
    void setTime(const QString &_time){
        process.start("date +%T -s \""+_time+"\"");
    }
    void setNtpStatus(const bool &_status){
        if(_status==getNtpStatus())
            return;
        if(_status)
        {
        process.start("systemctl enable ntp");
        process.waitForFinished();
        process.start("systemctl start ntp");
        process.waitForFinished();
        }
        else
        {
         process.start("systemctl disable ntp");
         process.waitForFinished();
         process.start("systemctl stop ntp");
         process.waitForFinished();
        }
        emit NtpStatusChanged();
    }
signals:
    void TimeZoneChanged();
    void NtpStatusChanged();
private:
    QProcess process;
};

#endif // DATETIME_H
