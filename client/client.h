#pragma once

#include <string>
#include <chrono>

class Client
{
public:
    void setPort(ushort port) { m_port = port; }
    void setName(const std::string &name) { m_name = name; }
    void setInternval(std::chrono::seconds interval) { m_interval = interval; }

    void run();    
private:
    ushort m_port;
    std::string m_name;
    std::chrono::seconds m_interval;
};
