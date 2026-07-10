#include "packetbuffer.h"
#include <QColor>

PacketBuffer::PacketBuffer(QObject *parent) : QAbstractTableModel(parent) {}

void PacketBuffer::addPacket(const PacketInfo &info) {
    buffer[writeIndex] = info;
    writeIndex = (writeIndex + 1) % bufferSize;
    if (count < bufferSize) count++;

    beginResetModel();
    endResetModel();
}

// Перевести номер строки таблицы в индекс буфера
int PacketBuffer::realIndex(int tableRow) const {
    if (searchIP.isEmpty()) {
        return (writeIndex - count + tableRow + bufferSize) % bufferSize;
    } else {
        int skipped = 0;
        for (int i = 0; i < count; i++) {
            int id = (writeIndex - count + i + bufferSize) % bufferSize;
            auto &p = buffer[id];
            if (p.src_ip == searchIP || p.dst_ip == searchIP) {
                if (skipped == tableRow) return id;
                skipped++;
            }
        }
        return -1;
    }
}

int PacketBuffer::rowCount(const QModelIndex &) const {
    if (searchIP.isEmpty()) return count;

    int matched = 0;
    for (int i = 0; i < count; i++) {
        int id = (writeIndex - count + i + bufferSize) % bufferSize;
        const auto &p = buffer[id];
        if (p.src_ip == searchIP || p.dst_ip == searchIP)
            matched++;
    }
    return matched;
}

int PacketBuffer::columnCount(const QModelIndex &) const {
    return 6;
}

QVariant PacketBuffer::data(const QModelIndex &index, int role) const {
    if (role != Qt::DisplayRole) return {};

    int i = realIndex(index.row());
    if (i < 0) return {};

    const auto &p = buffer[i];

    switch (index.column()) {
    case 0: return p.src_ip;
    case 1: return p.src_port;
    case 2: return p.dst_ip;
    case 3: return p.dst_port;
    case 4: return p.protocol;
    case 5: return p.protocol == "TCP" ? QVariant(p.sequence) : QVariant("-");
    }
    return {};
}

QVariant PacketBuffer::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole) return {};
    switch (section) {
    case 0: return "Source IP";
    case 1: return "Source Port";
    case 2: return "Dest IP";
    case 3: return "Dest Port";
    case 4: return "Protocol";
    case 5: return "Sequence";
    }
    return {};
}

void PacketBuffer::searchByIP(const QString &ip) {
    searchIP = ip;
    beginResetModel();
    endResetModel();
}

void PacketBuffer::clearSearch() {
    searchIP.clear();
    beginResetModel();
    endResetModel();
}