#include "TADTokenRing.hpp"
#include <iostream>
int main() {
    TokenRing red("Computer1");
    red.setComputador("Computer2");
    red.setComputador("Computer3");
    red.pasaToken();
    red.pasaTrama("Computer1", "Computer2");
    red.deletComputador();
    red.pasaToken();
    red.setComputador("Computer4");
    red.pasaToken();
    red.pasaTrama("Computer2", "Computer4");
    return 0;

}