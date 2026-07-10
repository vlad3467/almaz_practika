#ifndef PACKETBUFFER_H
#define PACKETBUFFER_H

#include <QAbstractTableModel>
#include <array>
#include "snifferworker.h"

class PacketBuffer : public QAbstractTableModel {
    Q_OBJECT

private:
    static const int bufferSize = 50;
    std::array<PacketInfo, bufferSize> buffer;
    int writeIndex = 0;
    int count = 0;
    QString searchIP;

    int realIndex(int tableRow) const;

public:
    explicit PacketBuffer(QObject *parent = nullptr);

    void addPacket(const PacketInfo &info);
    void searchByIP(const QString &ip);
    void clearSearch();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

#endif