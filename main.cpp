#include "server.hpp"

int main(int ac, char **av) {
    if (ac != 3) {
        std::cerr << "Use the following syntax: ./a.out <port> <password>" << endl;
        exit(-1);
    }
    Server server(av[1], av[2]);
    server.startServer(server);

}