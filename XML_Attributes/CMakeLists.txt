cmake_minimum_required(VERSION 3.16)

project(XML_Attributes LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Xml)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Xml)

add_executable(XML_Attributes
  main.cpp
)
target_link_libraries(XML_Attributes Qt${QT_VERSION_MAJOR}::Core Qt6::Xml)

include(GNUInstallDirs)
install(TARGETS XML_Attributes
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
