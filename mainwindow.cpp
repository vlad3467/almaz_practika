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
        QString name = QString::fromStdString(iface.name());
        bool up = iface.is_up();

        QString displayName = name + (up ? " [UP]" : " [DOWN]");
        ui->ifaceComboBox->addItem(displayName, name);
    }
}

void MainWindow::on_StartPushButton_clicked() {
    on_StopPushButton_clicked();

    QString iface = ui->ifaceComboBox->currentData().toString();
    if (!thread) {
        thread = new QThread();
        worker = new SnifferWorker();
        worker->moveToThread(thread);

        connect(worker, &SnifferWorker::packetCaptured, this, &MainWindow::onPacketCaptured);
        connect(worker, &SnifferWorker::startRequested, worker, &SnifferWorker::startSniffing);
        connect(thread, &QThread::finished, worker, &QObject::deleteLater);

        thread->start();
    }

    emit worker->startRequested(iface);
}

void MainWindow::on_PausePushButton_clicked() {
    if (worker)
        worker->togglePause();
}

void MainWindow::on_StopPushButton_clicked() {
    if (worker) {
        worker->stopSniffing();
        thread->quit();
        thread->wait();
        worker = nullptr;
        thread = nullptr;
    }
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