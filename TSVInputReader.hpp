// 958 370

#ifndef INPUTREADER_TSVINPUTREADER_HPP
#define INPUTREADER_TSVINPUTREADER_HPP

#include <istream>
#include <memory>

#include "InputReader.hpp"

// Tab-separated-values input reader
class TSVInputReader : public InputReader {
protected:
    virtual bool ProcessChar(const char in_char) override;
public:
    // Delegating constructor for InputReader base class
    TSVInputReader(std::shared_ptr<std::istream> input_stream)
    : InputReader(input_stream)
    {}
};

#endif //INPUTREADER_TSVINPUTREADER_HPP
