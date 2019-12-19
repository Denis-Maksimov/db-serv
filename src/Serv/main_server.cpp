#include "main_SERVER.hpp"


int main(int argc, char *argv[]) {
    Network servr(1024);

    servr.init(8080);
    servr.working();



}


