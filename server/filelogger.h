#pragma once

#include <memory>

#include "ilogger.h"

class FileLogger : public ILogger
{
public:
    explicit FileLogger(const std::string &filename);

    FileLogger(const FileLogger &) = delete;
    FileLogger(FileLogger &&) = delete;

    FileLogger &operator=(const FileLogger &) = delete;
    FileLogger &operator=(FileLogger &&) = delete;

    ~FileLogger();

    void write(const std::string &msg) override;
private:
    struct PImpl;    
    std::unique_ptr<PImpl> m_pimpl;
};
