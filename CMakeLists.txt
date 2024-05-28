cmake_minimum_required(VERSION 3.10)
project(CryptoGraphix)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

set(DOTENV_INCLUDE_DIR "/home/v1rushb/smth/cpp-dotenv/include")
set(DOTENV_LIBRARY "/home/v1rushb/smth/cpp-dotenv/build/libcpp_dotenv.a")

include_directories(include)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("/usr/include/mysql")
include_directories("/usr/include/cryptopp")
include_directories(${DOTENV_INCLUDE_DIR})

add_executable(CryptoGraphix src/main.cpp src/ImageReader.cpp src/ImageWriter.cpp src/AES256Encryption.cpp src/IEncrypt.cpp src/GraphicsUtils)

link_directories("/usr/lib/mysql")

target_link_libraries(${PROJECT_NAME} PUBLIC ${OpenCV_LIBS})
target_link_libraries(${PROJECT_NAME} PUBLIC mysqlclient)
target_link_libraries(${PROJECT_NAME} PUBLIC ${DOTENV_LIBRARY})

find_library(CRYPTOPP_LIBRARIES NAMES cryptopp libcryptopp)
set_target_properties(CryptoGraphix PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")


if(CRYPTOPP_LIBRARIES)
    message(STATUS "Crypto++ library found")
    target_link_libraries(${PROJECT_NAME} PUBLIC ${CRYPTOPP_LIBRARIES})
else()
    message(FATAL_ERROR "Crypto++ library not found")
endif()
