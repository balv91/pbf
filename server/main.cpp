#include <cstdlib>

#include "server.h"
#include "filelogger.h"

int main(int argc, char **argv)
{
    const auto port = static_cast<ushort>(std::strtoul(argv[1], nullptr, 10));

    Server s;
    s.setPort(port);
    s.setLogger(std::make_unique<FileLogger>("./log.txt"));

    s.run();

    return 0;
}