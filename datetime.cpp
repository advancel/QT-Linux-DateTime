#include "datetime.h"

DateTime::DateTime()
{

}
int DateTime::getNtpStatus()
{
process.start("systemctl is-enabled ntp");
process.waitForFinished();
QString state;
state =process.readAllStandardOutput().replace("\n","").replace("\"","");
if(state=="enabled")
{
    qDebug()<<"Ntp is active";
    return 1;
}
else if(state=="disabled")
{
    qDebug()<<"Ntp is passive";
    return 0;
}
else
{
    qDebug()<<"Unexpected error when looking for ntp status. Probably it's not installed.";
    return -1;
}
}
int DateTime::TimeZone()
{
    process.start("date \+\"%Z\"");
    process.waitForFinished();
    QString state;
    int zone=0;
    state =process.readAllStandardOutput().replace("\n","").replace("\"","");
    qDebug()<<state;
    zone = state.toInt();
    if(zone<0)
    {
        zone=zone+(zone*2);
    }
    else if(zone>0)
    {
        zone=zone-(zone*2);
    }
    return zone;
}
void DateTime::setTimeZone(const int &_time_zone)
{
    process.start("timedatectl set-timezone Etc/GMT"+QString::number(_time_zone));
    emit TimeZoneChanged();
}
