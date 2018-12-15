#include <QString>
#include <QtTest>

#include "../sysinfoclient/sysinfoclient.h"
#include "../sysinfoserver/sysinfoserver.h"
#include "../sysinfo_api/log.h"
#include "../sysinfo_api/exception.h"
#include "../sysinfo_api/packet.h"

class ServerTest : public QObject
{
    Q_OBJECT

public:
    ServerTest(SysinfoServer& server)
        : m_server(server)
    {
        packetEmit();
        packetNoEmit();
        packetNotFound();
    }

private Q_SLOTS:
    void packetEmit()
    {
        try
        {
            API::Packet pkt(1, 50.0, 50.0, 200);
            m_server.onMessageReceived(QJsonDocument(pkt.toJson()).toJson());
        }
        catch (API::Exception&)
        {
            QVERIFY(false); // Should not throw.
        }
    }

    void packetNoEmit()
    {
        try
        {
            API::Packet pkt(2, 30.0, 10.0, 30);
            m_server.onMessageReceived(QJsonDocument(pkt.toJson()).toJson());
        }
        catch (API::Exception &)
        {
            QVERIFY(false); // Should not throw.
        }
    }

    void packetNotFound()
    {
        try
        {
            API::Packet pkt(3, 30.0, 10.0, 30);
            m_server.onMessageReceived(QJsonDocument(pkt.toJson()).toJson());
        }
        catch (API::Exception &)
        {
            QVERIFY(false); // Should not throw.
        }
    }

private:
    SysinfoServer &m_server;
};

class CClientTest : public QObject
{
    Q_OBJECT

public:
    CClientTest()
    {
        connect(&m_info, &Client::Sysinfo::scanFinished, this, &CClientTest::infoCollector);
        m_info.startScan();

        SysinfoClient client(QString::fromStdString("ws://localhost:1234"), 1);
        for (int count = 0; count < 5; ++count)
        {
            client.rescanInformation();
            QThread::msleep(40);
        }
    }

private Q_SLOTS:
    void infoCollector()
    {
        const API::Packet packet = m_info.makePacket(1);
        QVERIFY(packet.getMemoryLoad() > 0);
        QVERIFY(packet.getNumProcesses() > 0);

        QJsonDocument json_doc(packet.toJson());
        QVERIFY(!json_doc.isEmpty());
        qDebug() << json_doc.toJson(QJsonDocument::Indented);
    }

private:
    Client::Sysinfo m_info;
};

class SysinfoTest : public QObject
{
    Q_OBJECT

public:
    SysinfoTest() :
        m_server("config.xml", 1234)
    {
        qInstallMessageHandler(API::customLog);
    }

private Q_SLOTS:
    void communication()
    {
        while(1) {}
    }

    void testServer()
    {
        ServerTest serverTest(m_server);
    }

    void testClient()
    {
        CClientTest clientTest;
    }

private:
    SysinfoServer m_server;
};

QTEST_APPLESS_MAIN(SysinfoTest)

#include "tst_sysinfotest.moc"
