#include <iostream>

void run_test (
    const char * name,
    char result,
    const char * file,
    unsigned long line
) {
    if ( result ) {
        std::cout << "  [ .. ] " << name << "\n";
    } else {
        std::cout << "  [ !! ] " << name << "\n";
        std::cout << "    " << file << ":" << line << "\n";

    }
}

#define CHECK( cond )

int main ( int argc, char ** argv ) {
    std::cout << "OK" << std::endl;
    return 0;
}
