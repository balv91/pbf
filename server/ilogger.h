#pragma once

class ILogger
{
public:
    virtual ~ILogger() = default;

    virtual void write(const std::string &msg) = 0;
};
