#pragma once

#include <memory>

class ILogger;

class Server
{
public:
    void setPort(ushort port) { m_port = port; }
    void setLogger(std::unique_ptr<ILogger> logger) { m_logger = std::move(logger); }

    void run();
private:
    ushort m_port;
    std::unique_ptr<ILogger> m_logger;
};
