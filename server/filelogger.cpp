#include "filelogger.h"

#include <fstream>
#include <iostream>
#include <mutex>

struct FileLogger::PImpl
{
    std::ofstream stream;
    std::mutex mutex;
};

FileLogger::FileLogger(const std::string &filename) :
    m_pimpl(new PImpl)
{
    m_pimpl->stream.open(filename);
}

FileLogger::~FileLogger()
{
    
}

void FileLogger::write(const std::string &msg)
{
    std::lock_guard<std::mutex> lock(m_pimpl->mutex);

    std::cout << msg << std::endl;    
    m_pimpl->stream << msg << std::endl;
}
