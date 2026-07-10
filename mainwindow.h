#include <QMainWindow>
#include "snifferworker.h"
#include "packetbuffer.h"

class QThread;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onPacketCaptured(const PacketInfo &info);

    void on_StartPushButton_clicked();

    void on_PausePushButton_clicked();

    void on_StopPushButton_clicked();

    void on_IPPushButton_clicked();

private:
    void loadInterfaces();

    Ui::MainWindow *ui  = nullptr;
    PacketBuffer *packetBuffer  = nullptr;
    SnifferWorker *worker  = nullptr;
    QThread *thread  = nullptr;
};