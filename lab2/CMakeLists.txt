cmake_minimum_required(VERSION 3.23)
project(lab2)

set(CMAKE_CXX_STANDARD 14)

set(GOOGLETEST_VERSION 1.14.0)
add_subdirectory(googletest/googletest)
enable_testing()

add_executable(lab2 main.cpp
Operation.h
OperationRegistrar.h
OperationFactory.h
Interpreter.h Interpreter.cpp
Utilities.h Utilities.cpp
Reader.h Reader.cpp
Writer.h Writer.cpp


IfOperation.h IfOperation.cpp

AddOperation.h AddOperation.cpp 
SubOperation.h SubOperation.cpp 
MulOperation.h MulOperation.cpp 
DivOperation.h DivOperation.cpp 
ModOperation.h ModOperation.cpp

EqOperation.h EqOperation.cpp
GtOperation.h GtOperation.cpp
LtOperation.h LtOperation.cpp
DupOperation.h DupOperation.cpp 
DropOperation.h DropOperation.cpp
SwapOperation.h SwapOperation.cpp
RotOperation.h RotOperation.cpp
DotOperation.h DotOperation.cpp
OverOperation.h OverOperation.cpp
EmitOperation.h EmitOperation.cpp
CrOperation.h CrOperation.cpp
DotQuoteOperation.h DotQuoteOperation.cpp
ForOperation.h ForOperation.cpp

Tests.cpp)

target_link_libraries(lab2 gtest_main)

