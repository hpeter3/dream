#include "PacketSocketHTTP.h"
#include <string>
#include <sstream>
#include <iostream>
#include <QNetworkReply>
#include <QAuthenticator>

CPacketSocketHTTP::CPacketSocketHTTP(): bGetInFlight(false)
{
    pNetworkAccessManager = new QNetworkAccessManager(this);
    //connect(pNetworkAccessManager, &QNetworkAccessManager::finished, this, &CPacketSocketHTTP::onPostFinished);
    connect(this, &CPacketSocketHTTP::postDataReady, this, &CPacketSocketHTTP::doPost);
    connect(this, &CPacketSocketHTTP::getReady, this, &CPacketSocketHTTP::doGet);
    connect(pNetworkAccessManager, &QNetworkAccessManager::authenticationRequired, this, &CPacketSocketHTTP::onAuthRequired);


}
CPacketSocketHTTP::~CPacketSocketHTTP()
{

}

// Set the sink which will receive the packets
void CPacketSocketHTTP::SetPacketSink(CPacketSink *pSink)
{
    pPacketSink = pSink;
}

// Stop sending packets to the sink
void CPacketSocketHTTP::ResetPacketSink(void)
{
    pPacketSink = nullptr;
}

// Send packet to the socket
void CPacketSocketHTTP::SendPacket(const std::vector<_BYTE>& vecbydata, uint32_t addr, uint16_t port)
{
    QByteArray qdata(reinterpret_cast<const char*>(vecbydata.data()), vecbydata.size());
    emit postDataReady(qdata);
}

void CPacketSocketHTTP::doPost(const QByteArray& qdata)
{
    QNetworkRequest req(QString::fromStdString(dest));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/octet-stream");
    QNetworkReply *pReply =  pNetworkAccessManager->post(req, qdata);
    connect(pReply, &QNetworkReply::finished, this, &CPacketSocketHTTP::onPostFinished);
}

void CPacketSocketHTTP::onPostFinished()
{
    QNetworkReply * pReply = qobject_cast<QNetworkReply *>(sender());
    if (pReply->error() != 0)
    {
        std::cout<<"onFinished called; reply error num " <<pReply->error() << " string: " << pReply->errorString().toStdString() << std::endl;
    }
    pReply->deleteLater();
}
void CPacketSocketHTTP::poll()
{
    emit getReady();

}

void CPacketSocketHTTP::doGet()
{
    if (bGetInFlight)
        return;
    bGetInFlight = true;
    QNetworkRequest req(QString::fromStdString(dest));
    QNetworkReply *pReply =  pNetworkAccessManager->get(req);
    connect(pReply, &QNetworkReply::finished, this, &CPacketSocketHTTP::onGetFinished);
}

void CPacketSocketHTTP::onGetFinished()
{
    bGetInFlight = false;
    QNetworkReply * pReply = qobject_cast<QNetworkReply *>(sender());
    if (pReply->error() != 0)
    {
        std::cout<<"onGetFinished called; reply error num " <<pReply->error() << " string: " << pReply->errorString().toStdString() << std::endl;
    }
    QByteArray responseBody = pReply->readAll();
    std::vector<_BYTE> vecbydata(responseBody.begin(), responseBody.end());
    if (vecbydata.size() > 0)
    {
        std::cout<<"Received RCI data size " << vecbydata.size()<< std::endl;

        if (pPacketSink)
            pPacketSink->SendPacket(vecbydata);
    }

    pReply->deleteLater();
}

void CPacketSocketHTTP::onAuthRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
    authenticator->setUser(QString::fromStdString(destUser));
    authenticator->setPassword(QString::fromStdString(destPassword));
}

bool CPacketSocketHTTP::SetDestination(const std::string& str)
{

    std::istringstream iss(str);
    std::string user_pass;

    getline(iss, destScheme, ':');
    while (iss.peek()=='/')
        iss.get();


    if (str.find("@")!=std::string::npos)
    {
        getline(iss, user_pass, '@');
        size_t pos=user_pass.find(':');
        if (pos==std::string::npos)
        {
            destUser = user_pass;
            destPassword = "";
        }
        else
        {
            destUser = user_pass.substr(0, pos);
            destPassword = user_pass.substr(pos+1);
        }
        std::cout<<"User = " << destUser << " Pass = " << destPassword <<std::endl;
    }
    getline(iss, destHost, '/');
    getline(iss, destPath);
    dest = str;
    std::cout<<"dest scheme " << destScheme << " host " << destHost << " path " << destPath <<std::endl;

    if (destScheme == "https")
    {
        QSslConfiguration sslConfig;

        pNetworkAccessManager->connectToHostEncrypted(QString::fromStdString(destHost));


    }
    else {
        pNetworkAccessManager->connectToHost(QString::fromStdString(destHost));
    }
    return true;
}
bool CPacketSocketHTTP::SetOrigin(const std::string& str)
{
    return true;

}

bool CPacketSocketHTTP::GetDestination(std::string& str)
{
    str = dest;
    return true;

}

bool CPacketSocketHTTP::GetOrigin(std::string& str)
{
    return true;
}

