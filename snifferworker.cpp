#include "snifferworker.h"
#include <tins/tins.h>
#include <QDebug>

SnifferWorker::SnifferWorker(QObject *parent) : QObject(parent) {}

void SnifferWorker::startSniffing(const QString &iface_name) {
    running = true;
    paused = false;

    try {
        Tins::SnifferConfiguration config;
        config.set_timeout(1000);
        Tins::Sniffer sniffer(iface_name.toStdString(), config);

        while (running) {
            Tins::Packet pkt = sniffer.next_packet();
            if (!pkt) continue;

            const Tins::IP* ip = pkt.pdu()->find_pdu<Tins::IP>();
            if (!ip) continue;

            PacketInfo info;
            info.src_ip = QString::fromStdString(ip->src_addr().to_string());
            info.dst_ip = QString::fromStdString(ip->dst_addr().to_string());

            if (const Tins::TCP* tcp = pkt.pdu()->find_pdu<Tins::TCP>()) {
                info.protocol = "TCP";
                info.src_port = tcp->sport();
                info.dst_port = tcp->dport();
                info.sequence = tcp->seq();
            } else if (const Tins::UDP* udp = pkt.pdu()->find_pdu<Tins::UDP>()) {
                info.protocol = "UDP";
                info.src_port = udp->sport();
                info.dst_port = udp->dport();
            } else {
                continue;
            }

            if (!paused) {
                emit packetCaptured(info);
            }
        }
    } catch (std::exception& ex) {
        qDebug() << "Error:" << ex.what();
    }
}

void SnifferWorker::stopSniffing() {
    running = false;
}

void SnifferWorker::togglePause() {
    paused = !paused;
}