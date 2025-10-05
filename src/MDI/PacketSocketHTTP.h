#ifndef PACKETSOCKETHTTP_H
#define PACKETSOCKETHTTP_H

#include <QObject>
#include <QNetworkAccessManager>
#include "PacketInOut.h"

class CPacketSocketHTTP : public QObject, public CPacketSocket
{
    Q_OBJECT
public:
    CPacketSocketHTTP();
    virtual ~CPacketSocketHTTP();
    // Set the sink which will receive the packets
    virtual void SetPacketSink(CPacketSink *pSink);
    // Stop sending packets to the sink
    virtual void ResetPacketSink(void);

    // Send packet to the socket
    void SendPacket(const std::vector<_BYTE>& vecbydata, uint32_t addr=0, uint16_t port=0);

    virtual bool SetDestination(const std::string& str);
    virtual bool SetOrigin(const std::string& str);

    virtual bool GetDestination(std::string& str);
    virtual bool GetOrigin(std::string& str);

    void poll();

private slots:
    void doPost(const QByteArray& vecbydata);
    void onPostFinished();
    void doGet();
    void onGetFinished();
    void onAuthRequired(QNetworkReply *reply, QAuthenticator *authenticator);

signals:
    void postDataReady(const QByteArray& vecbydata);
    void getReady();

private:



    std::vector<_BYTE>	writeBuf;
    std::string dest;
    std::string destScheme;
    std::string destHost;
    std::string destPath;
    std::string destUser;
    std::string destPassword;
    QNetworkAccessManager * pNetworkAccessManager;
    CPacketSink *pPacketSink;
    bool bGetInFlight;
};

#endif // PACKETSOCKETHTTP_H
