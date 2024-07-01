#include "client.h"

#include <chrono>
#include <sstream>
#include <thread>
#include <iomanip>

#include <tcpsocket.h>

void Client::run()
{
    while (1) {
        TcpSocket socket;
        socket.connect("127.0.0.1", m_port);

        std::ostringstream ss;
        ss << '[';
        
        {
            const auto now = std::chrono::system_clock::now();
            const auto nowAsTimeT = std::chrono::system_clock::to_time_t(now);
            const auto nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
            ss << std::put_time(std::localtime(&nowAsTimeT), "%Y-%m-%d %H:%M:%S");
            ss << '.' << std::setfill('0') << std::setw(3) << nowMs.count();
        }

        ss << "] ";
        ss << m_name;

        const auto msg = ss.str();
        socket.write(msg);

        std::this_thread::sleep_for(m_interval);
    }
}
