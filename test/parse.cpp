#include "utap/utap.h"

int main(int argc, char** argv) {
    UTAP::Document doc;
    parseXMLFile(argv[1], &doc, true);
}