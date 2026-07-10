#ifndef SNIFFERWORKER_H
#define SNIFFERWORKER_H

#include <QObject>
#include <atomic>

struct PacketInfo {
    QString src_ip;
    uint16_t src_port = 0;
    QString dst_ip;
    uint16_t dst_port = 0;
    QString protocol;
    uint32_t sequence = 0;
};

class SnifferWorker : public QObject {
    Q_OBJECT

public:
    explicit SnifferWorker(QObject *parent = nullptr);

public slots:
    void startSniffing(const QString &iface_name);
    void stopSniffing();
    void togglePause();

signals:
    void packetCaptured(const PacketInfo &info);
    void startRequested(const QString &iface_name);

private:
    std::atomic<bool> running{false};
    std::atomic<bool> paused{false};
};

#endif