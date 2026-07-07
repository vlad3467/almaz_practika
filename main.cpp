#include <tins/tins.h>
#include <iostream>

struct Program{
    bool running = 1;
    void Start() {running = 1;};
    void Stop() {running = 0;};
    void Pause(); // Захват пакетов продолжается, просто в ui qt не выводится, потом сделаю, когда начну изучать qt
};

int main() {
    using namespace Tins;

    auto interfaces = NetworkInterface::all();
    Program* program = new Program();
    
    std::cout << "Доступные сетевые интерфейсы:" << "\n";
    for ( auto& iface : interfaces) {
        std::cout << "  - " << iface.name() 
                  << (iface.is_up() ? " [UP]" : " [DOWN]") << "\n";
    }

    std::string iface_name;
    std::cout << "Введи имя интерфейса: ";
    std::getline(std::cin, iface_name);

    try {
        SnifferConfiguration config;
        config.set_timeout(1000);
        Sniffer sniffer(iface_name, config);

        std::cout << "Слушаю..." << "\n";

        while (program->running) {
            Packet pkt = sniffer.next_packet();  // promiscuous mode дефолтный, для сниффинга, а у меня в ТЗ самописный аналог Wireshark, поэтому оставляю его
            IP* ip = pkt.pdu()->find_pdu<IP>();
            if (!ip) continue;

            std::cout << ip->src_addr() << " -> " << ip->dst_addr();

            if (const TCP* tcp = pkt.pdu()->find_pdu<TCP>()) {
                std::cout << "  TCP " << tcp->sport() << " -> " << tcp->dport()
                        << "  Seq=" << tcp->seq();
            } else if (const UDP* udp = pkt.pdu()->find_pdu<UDP>()) {
                std::cout << "  UDP " << udp->sport() << " -> " << udp->dport();
            }

            std::cout << "\n";
        }
    } 
    catch (std::exception& ex) {
        std::cout << "Ошибка: " << ex.what() << "\n";
        return 1;
    }

    delete program;
    return 0;
}