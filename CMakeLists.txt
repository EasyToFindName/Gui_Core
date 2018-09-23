cmake_minimum_required(VERSION 3.5)

project(GUI_Core LANGUAGES CXX)

set(SFML_STATIC_LIBRARIES true)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

set(INCLUDE_DIR "./Gui_Core/inc")
set(SRC_DIR "./Gui_Core/src")

set(OUTPUT_DIRECTORY_PATH "${CMAKE_SOURCE_DIR}/output")

set(SOURCES 
    ${INCLUDE_DIR}/CenterLayout.h
    ${INCLUDE_DIR}/Container.h
    ${INCLUDE_DIR}/DefaultButton.h
    ${INCLUDE_DIR}/DragAndDrop.h
    ${INCLUDE_DIR}/Gui.h
    ${INCLUDE_DIR}/GuiActiveElem.h
    ${INCLUDE_DIR}/GuiElem.h
    ${INCLUDE_DIR}/HorizontalLayout.h
    ${INCLUDE_DIR}/Image.h
    ${INCLUDE_DIR}/Interfaces.h
    ${INCLUDE_DIR}/Layout.h
    ${INCLUDE_DIR}/ResourceCacher.h
    ${INCLUDE_DIR}/TextLabel.h
    ${INCLUDE_DIR}/VerticalLayout.h


    ${SRC_DIR}/CenterLayout.cpp
    ${SRC_DIR}/Container.cpp
    ${SRC_DIR}/DefaultButton.cpp
    ${SRC_DIR}/DragAndDrop.cpp
    ${SRC_DIR}/Gui.cpp
    ${SRC_DIR}/GuiActiveElem.cpp
    ${SRC_DIR}/GuiElem.cpp
    ${SRC_DIR}/HorizontalLayout.cpp
    ${SRC_DIR}/Image.cpp
    ${SRC_DIR}/Layout.cpp
    ${SRC_DIR}/ResourceCacher.cpp
    ${SRC_DIR}/TextLabel.cpp
    ${SRC_DIR}/VerticalLayout.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 14
    ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY_PATH}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY_PATH}/lib"
)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} sfml-system sfml-graphics sfml-window)

install(DIRECTORY "${CMAKE_SOURCE_DIR}/Gui_Core/inc/" DESTINATION "${OUTPUT_DIRECTORY_PATH}/include")

option(BUILD_EXAMPLE "Build exectuable example" ON)
if(BUILD_EXAMPLE)
    add_subdirectory(example)
endif()