#Minimalna wersja cmake konieczna do zbudowania tego projektu
cmake_minimum_required(VERSION 3.4)

#Parametry konfiguracyjne platformy programistycznej i flagi kompilatora
#set(CMAKE_CXX_COMPILER g++)#g++ jako kompilator C++
#set(CMAKE_C_COMPILER gcc)#gcc jako kompilator C
set(CMAKE_CXX_STANDARD 11)#Standard C++ 11, bez tego parametru g++ użyje wartości domyślnej. Dla g++ od wersji 6 jest to C++14
set(CMAKE_CXX_STANDARD_REQUIRED ON)#Określony wyżej standard C++ jest wymagany

#Profil debug i maksymalny poziom debug info g3 oraz format debug info na dwarf-4 (musi być gdb w wersji 7). BUILD_TYPE może być ustawiony na:
#empty,
#Debug,
#Release,
#RelWithDebInfo
#MinSizeRel
#Ustawiono dodatkowo flagi debug generujące informację dla debuggera
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "-g3 -gdwarf-4")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -gdwarf-4")
#Ustaw nazwę projektu i język na C++
project(Aquarium)
enable_language(CXX)
#W specjalnym pliku compile_commands.json można podejrzeć wszystkie operacje kompilatora wraz z parametrami, 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
#uwzględnij podprojek znajdujący się w podkatalogu program. Musi być w nim pliki CMakeLists.txt
add_subdirectory(program)
add_subdirectory(library)
#include_directories(library/include/model)
#include_directories(library/include/repositories)
#include_directories(library/include/managers)
#include_directories(library)
#include_directories(program/include)
#add_executable(introduction
#        program/src/main.cpp
#        program/CMakeLists.txt
#        CMakeLists.txt
#        library/include/model/Client.h
#        library/src/model/Client.cpp
#        library/include/model/Attraction.h
#        library/src/model/Attraction.cpp
#        library/include/model/Group.h
#        library/include/model/GroupTicket.h
#        library/src/model/GroupTicket.cpp
#        library/include/model/SingleTicket.h
#        library/src/model/SingleTicket.cpp
#        library/include/model/Ticket.h
#        library/src/model/Ticket.cpp
#        library/include/model/typedefs.h
#        library/include/model/Visitor.h
#        library/include/managers/Aquarium.h
#        library/src/managers/Aquarium.cpp
#        library/include/managers/ClientManager.h
#        library/src/managers/ClientManager.cpp
#        library/include/managers/TicketManager.h
#        library/src/managers/TicketManager.cpp
#        library/include/repositories/AttractionList.h
#        library/src/repositories/AttractionList.cpp
#        library/include/repositories/Repository.h)

#Włączenie testów powoduje pojawienie się celu test w makefiles
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra -Werror")

add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})