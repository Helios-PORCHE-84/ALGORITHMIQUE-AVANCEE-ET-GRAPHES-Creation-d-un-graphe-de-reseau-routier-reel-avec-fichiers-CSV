#include "graphe.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <arcs.csv> <noeuds.csv>" << std::endl;
        return 1;
    }

    Graphe graphe(argv[1], argv[2]);
    return 0;
}
