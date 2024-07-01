#include "server.h"

#include <thread>

#include <tcpsocket.h>

#include "ilogger.h"

void Server::run()
{        
    TcpSocket socket;
    socket.bind("0.0.0.0", m_port);
    socket.listen();

    while (1) {
        TcpSocket acceptedSocket = socket.accept();
        if (!acceptedSocket.isNull()) {
            std::thread([this, s = std::move(acceptedSocket)] () mutable {
                const auto data = s.read();
                if (data.empty()) {
                    return;
                }

                m_logger->write(data);
            }).detach();
        }
    }
}