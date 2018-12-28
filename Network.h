#include <netinet/in.h>

namespace ge{

struct sockaddr_in
{
    short sin_family;
    unsigned short sin_port;
    struct in_addr sin_addr;
    char sin_zero[ 8 ]; // padding dla zachowania rozmiaru z struct sockaddr
};

struct sin_addr
{
    unsigned long s_addr;
}

}
