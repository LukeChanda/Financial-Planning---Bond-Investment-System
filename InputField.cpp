// 958 370

#include "InputField.hpp"

#include <string>

std::ostream& operator<<(std::ostream& lhs, const InputField & rhs) {
    lhs << static_cast<std::string>(rhs);
    return lhs;
}