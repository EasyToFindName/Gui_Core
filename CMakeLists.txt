cmake_minimum_required(VERSION 3.5)

project(GUI_Core LANGUAGES CXX)

set(SFML_STATIC_LIBRARIES true)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)


set(INCLUDE_DIR "./inc")
set(SRC_DIR "./src")
set(EXECUTABLE_NAME ${PROJECT_NAME}_example)

set(OUTPUT_DIRECTORY_PATH "${CMAKE_SOURCE_DIR}/output")

set(SOURCES 
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

install(DIRECTORY "${CMAKE_SOURCE_DIR}/inc/" DESTINATION "${OUTPUT_DIRECTORY_PATH}/include")

option(BUILD_EXAMPLE "Build exectuable example" ON)
if(BUILD_EXAMPLE)
    add_executable(${EXECUTABLE_NAME} ${SRC_DIR}/main.cpp)

    set_target_properties(${EXECUTABLE_NAME} PROPERTIES
        CXX_STANDARD 14
        RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIRECTORY_PATH}/bin"
    )

    target_link_libraries(${EXECUTABLE_NAME} ${PROJECT_NAME})

    get_target_property(RESOURCE_PATH ${EXECUTABLE_NAME} RUNTIME_OUTPUT_DIRECTORY)
    install(DIRECTORY "${CMAKE_SOURCE_DIR}/res" DESTINATION "${RESOURCE_PATH}")
endif()