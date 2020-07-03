// 958 370

#ifndef INPUTREADER_INPUTFIELD_HPP
#define INPUTREADER_INPUTFIELD_HPP

#include <string>
#include <ostream>

class InputField {
private:
    // Field value
    std::string field_value_;
public:
    // Inline Constructor
    InputField(const std::string & value) : field_value_{value} {}

    operator std::string() const {return field_value_;}
    operator int() {return std::stoi(field_value_);}
    operator double() const {return std::stod(field_value_);}
};

std::ostream& operator<<(std::ostream& lhs, const InputField & rhs);

#endif //INPUTREADER_INPUTFIELD_HPP
