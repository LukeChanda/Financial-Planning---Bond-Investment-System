cmake_minimum_required(VERSION 3.12)
project(inputreader)

set(CMAKE_CXX_STANDARD 14)

add_executable(inputreader main.cpp InputReader.cpp InputReader.hpp TSVInputReader.cpp TSVInputReader.hpp CSVInputReader.cpp CSVInputReader.hpp FixedWidthInputReader.hpp InputField.hpp InputField.cpp Client.cpp Client.hpp Product.cpp Product.hpp Date.cpp Date.hpp RecordTransaction.cpp RecordTransaction.hpp)

