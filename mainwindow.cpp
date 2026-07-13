#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <tins/tins.h>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadInterfaces();

    packetBuffer = new PacketBuffer();
    ui->PacketsTableView->setModel(packetBuffer);

    ui->PacketsTableView->setStyleSheet(
        "QHeaderView::section {"
        "   background-color: #2c3e50;"
        "   color: white;"
        "   padding: 6px;"
        "   font-weight: bold;"
        "}"
        "QHeaderView::section:hover {"
        "   background-color: #4CAF50;"
        "   color: white;"
        "}"
        );
}

MainWindow::~MainWindow()
{
    if (worker) {
        worker->stopSniffing();
    }
    if (thread) {
        thread->quit();
        thread->wait();
    }

    delete ui;
}

void MainWindow::onPacketCaptured(const PacketInfo &info) {
    packetBuffer->addPacket(info);
}

void MainWindow::loadInterfaces() {
    auto interfaces = Tins::NetworkInterface::all();

    for (const auto& iface : interfaces) {
        if (!iface.is_up()) continue;
        try {
            Tins::Sniffer test(iface.name());
        } catch (...) {
            continue;
        }
        QString name = QString::fromStdString(iface.name());
        QString displayName = name;
        ui->ifaceComboBox->addItem(displayName, name);
    }

    if (ui->ifaceComboBox->count() == 0) {
        ui->ifaceComboBox->addItem("No accessable interfaces");
        ui->ifaceComboBox->setEnabled(false);
        ui->StartPushButton->setEnabled(false);
        ui->StopPushButton->setEnabled(false);
        ui->PausePushButton->setEnabled(false);
    }
}

void MainWindow::on_StartPushButton_clicked() {
    on_StopPushButton_clicked();

    QString iface = ui->ifaceComboBox->currentData().toString();
    if (iface.isEmpty()) return;

    thread = new QThread();
    worker = new SnifferWorker();
    worker->moveToThread(thread);

    connect(worker, &SnifferWorker::packetCaptured, this, &MainWindow::onPacketCaptured);
    connect(worker, &SnifferWorker::startRequested, worker, &SnifferWorker::startSniffing);

    connect(thread, &QThread::finished, worker, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);

    connect(thread, &QThread::started, this, [this, iface]() {
        if (worker)
            emit worker->startRequested(iface);
    });

    thread->start();
}

void MainWindow::on_StopPushButton_clicked() {
    if (worker) {
        worker->stopSniffing();
    }
    worker = nullptr;
    thread = nullptr;
}

void MainWindow::on_PausePushButton_clicked() {
    if (worker)
        worker->togglePause();
}

void MainWindow::on_IPPushButton_clicked() {
    if (!packetBuffer) return;

    QString ip = ui->IPLineEdit->text().trimmed();
    if (ip.isEmpty()) {
        packetBuffer->clearSearch();
    } else {
        packetBuffer->searchByIP(ip);
    }
}