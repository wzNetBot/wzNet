cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)

project(wzBotNetPlugin)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Core REQUIRED)
add_definitions(-DQT_PLUGIN)
get_target_property(QtCore_location Qt5::Core LOCATION)

list(APPEND HEADERS ${PROJECT_SOURCE_DIR}/../warzone2100/lib/qtplugins/qtpluginsinterface.h)
list(APPEND Q_HEADERS ${PROJECT_SOURCE_DIR}/qbotnet.h ${PROJECT_SOURCE_DIR}/../warzone2100/lib/qtplugins/qtpluginsinterface.h)
list(APPEND Q_SOURCES ${PROJECT_SOURCE_DIR}/qbotnet.cpp)

add_library(${PROJECT_NAME} SHARED ${HEDARS} ${SOURCES} ${Q_HEDARS} ${Q_SOURCES} ${MOC_SOURCES})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
#target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} wzNetCapnp)
