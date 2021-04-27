cmake_minimum_required(VERSION 3.4)
project(Library)

set(SOURCE_FILES
        src/model/Client.cpp include/model/Client.h src/model/Ticket.cpp include/model/Ticket.h src/model/SingleTicket.cpp include/model/SingleTicket.h src/model/GroupTicket.cpp include/model/GroupTicket.h src/managers/ClientManager.cpp include/managers/ClientManager.h include/repositories/Repository.h src/managers/TicketManager.cpp include/managers/TicketManager.h src/model/Attraction.cpp include/model/Attraction.h src/repositories/AttractionList.cpp include/repositories/AttractionList.h src/managers/Aquarium.cpp include/managers/Aquarium.h include/model/typedefs.h include/model/Group.h include/model/Visitor.h)
#utwórz bibliotekę typu STATIC, SHARED albo MODULE ze wskazanych źródeł
add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)
target_include_directories(Library PUBLIC include/model)
target_include_directories(Library PUBLIC include/repositories)
target_include_directories(Library PUBLIC include/managers)
enable_testing()
set (Boost_DETAILED_FAILURE_MSG ON)
set (Boost_THREADAPI win32)
set (BOOST_ROOT "C:/DevSoft/boost_1_60_0")
set (Boost_LIBRARY_DIR  "C:/DevSoft/boost_1_60_0/lib")
set (Boost_COMPILER "-vc")
set (Boost_USE_STATIC_RUNTIME ON)  
set (Boost_DEBUG ON)
find_package (Boost 1.60.0 REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/model
        ${CMAKE_CURRENT_SOURCE_DIR}/include/managers
        ${CMAKE_CURRENT_SOURCE_DIR}/include/repositories
        ${Boost_INCLUDE_DIRS}
)

set(SOURCE_TEST_FILES
        test/master.cpp test/ClientTest.cpp test/TicketTest.cpp test/SingleTicketTest.cpp test/GroupTicketTest.cpp test/AttractionTest.cpp test/AttractionListTest.cpp test/RepositoryTest.cpp test/ClientManagerTest.cpp test/TicketManagerTest.cpp test/Aquarium.cpp include/model/Group.h)

add_executable (LibraryTest ${SOURCE_TEST_FILES})

#dołącz bibliotekę z testowanymi klasami oraz bibliotekę boost.test do programu testów
target_link_libraries (LibraryTest
        Library
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )

#dodaj test TestBiblioteki1. Instrukcji cmake add_test może być wiele.
#Dodatkowe parametry wpływają na szczegółowość generowanego raportu. Standardowo znajduje się on w Testing/Temporary.
add_test(LibraryTest1 LibraryTest
        --report_level=detailed
        --log_level=all
        --color_output=yes
        )

