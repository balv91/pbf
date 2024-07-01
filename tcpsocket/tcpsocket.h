#pragma once

#include <string>

class TcpSocket
{
public:
    TcpSocket();
    ~TcpSocket();

    TcpSocket(const TcpSocket &) = delete;
    TcpSocket(TcpSocket &&) noexcept;

    TcpSocket &operator=(const TcpSocket &) = delete;
    TcpSocket &operator=(TcpSocket &&) noexcept;

    bool isNull() const;

    void bind(const std::string &addr, ushort port);

    void listen();
    TcpSocket accept();

    void connect(const std::string &addr, ushort port);
    void disconnect();

    std::string read();
    void write(const std::string &data);
private:
    explicit TcpSocket(int s);

    int m_socket;
};