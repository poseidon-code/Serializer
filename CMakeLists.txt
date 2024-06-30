cmake_minimum_required(VERSION 3.25)
project(serializer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# libserializer
set(LIBSERIALIZER_SOURCES
    "src/serializer.cpp"
    "src/stream.cpp"
    "src/byte_8.cpp"
    "src/byte_4.cpp"
    "src/byte_2.cpp"
    "src/byte_1.cpp"
)
set(LIBSERIALIZER_INCLUDE_DIRECTORIES 
    "include/"
)


# libserializer.a
add_library("${PROJECT_NAME}_static" STATIC ${LIBSERIALIZER_SOURCES})
target_include_directories("${PROJECT_NAME}_static" PUBLIC ${LIBSERIALIZER_INCLUDE_DIRECTORIES})
set_target_properties("${PROJECT_NAME}_static"
    PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}
    POSITION_INDEPENDENT_CODE ON
)


# libserializer.so
add_library("${PROJECT_NAME}_shared" SHARED ${LIBSERIALIZER_SOURCES})
target_include_directories("${PROJECT_NAME}_shared" PUBLIC ${LIBSERIALIZER_INCLUDE_DIRECTORIES})
set_target_properties("${PROJECT_NAME}_shared"
    PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}
    POSITION_INDEPENDENT_CODE ON
)
