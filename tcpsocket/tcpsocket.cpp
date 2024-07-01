#include "tcpsocket.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <stdexcept>

const int kNullSocket = -1;
const int kBacklog = 5;
const int kReadBufferSize = 128;

namespace {
    void fillSockAddrIn(sockaddr_in &sAddr, const std::string &addr, ushort port)
    {
        memset(&sAddr, 0, sizeof(sAddr));

        sAddr.sin_family = AF_INET;
        sAddr.sin_port = htons(port);
        
        if (inet_pton(AF_INET, addr.c_str(), &sAddr.sin_addr) < 1) {
            throw std::runtime_error("Bad address");
        }
    }
}

TcpSocket::TcpSocket()    
{
    m_socket = ::socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket == kNullSocket) {
        throw std::runtime_error("Bad socket");
    }
}

TcpSocket::TcpSocket(int s) :
    m_socket(s)
{

}

TcpSocket::~TcpSocket()
{
    disconnect();
}

TcpSocket::TcpSocket(TcpSocket &&other) noexcept
{
    *this = std::move(other);
}

TcpSocket &TcpSocket::operator=(TcpSocket &&other) noexcept
{
    if (this != &other) {
        m_socket = other.m_socket;
        other.m_socket = kNullSocket;
    }    

    return *this;
}

bool TcpSocket::isNull() const
{
    return m_socket == kNullSocket;
}

void TcpSocket::bind(const std::string &addr, ushort port)
{
    sockaddr_in sAddr;
    fillSockAddrIn(sAddr, addr, port);
    
    if (::bind(m_socket, reinterpret_cast<sockaddr *>(&sAddr), sizeof(sAddr)) == -1) {
        throw std::runtime_error("Failed to bind address");
    }
}

void TcpSocket::listen()
{
    if (::listen(m_socket, kBacklog) == -1) {
        throw std::runtime_error("Failed to listen");        
    }
}

TcpSocket TcpSocket::accept()
{
    return TcpSocket(::accept(m_socket, nullptr, nullptr));
}

void TcpSocket::connect(const std::string &addr, ushort port)
{
    sockaddr_in sAddr;
    fillSockAddrIn(sAddr, addr, port);

    if (::connect(m_socket, reinterpret_cast<sockaddr *>(&sAddr), sizeof(sAddr)) < 0) {
        throw std::runtime_error("Failed to connect");
    } 
}

void TcpSocket::disconnect()
{
    if (m_socket != kNullSocket) {
        close(m_socket);
        m_socket = kNullSocket;
    }
}

std::string TcpSocket::read()
{
    std::string data;

    char buf[kReadBufferSize];
    int n = -1;
    while ((n = ::recv(m_socket, &buf, sizeof(buf), 0)) > 0) {
        data.append(buf, n);
    }

    if (n < 0) {
        return std::string();
    }

    return data;
}

void TcpSocket::write(const std::string &data)
{
    int written = 0;

    while (written != data.size()) {
        int n = ::send(m_socket, data.data() + written, data.size() - written, 0);
        if (n < 0) {
            throw std::runtime_error("Failed to write data");
        }

        written += n;
    }
}
