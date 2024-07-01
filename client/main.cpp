#include <cstdlib>

#include "client.h"

int main(int argc, char **argv)
{
    const std::string name(argv[1]);
    const auto port = static_cast<ushort>(std::strtoul(argv[2], nullptr, 10));
    const std::chrono::seconds interval(std::strtoul(argv[3], nullptr, 10));

    Client c;
    c.setPort(port);
    c.setName(name);
    c.setInternval(interval);
    c.run();

    return 0;
}
