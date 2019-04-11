#include <iostream>

#include "Error/Error.hpp"
#include "Error/NullArgumentError.hpp"
#include "Structures/Buffer.hpp"
#include "Structures/Map.hpp"
#include "Structures/Ref.hpp"
#include "Structures/Refcounted.hpp"
#include "Structures/Vector.hpp"

#include "Val/Type.hpp"
#include "Val/TypeMismatchError.hpp"
#include "Val/VRef.hpp"

#include "Val/IxxVal.hpp"
#include "Val/UxxVal.hpp"
#include "Val/FxxVal.hpp"
#include "Val/BufVal.hpp"
#include "Val/VecVal.hpp"
#include "Val/MapVal.hpp"

int main ( int argc, char ** argv ) {
    std::cout << "OK" << std::endl;
    return 0;
}
