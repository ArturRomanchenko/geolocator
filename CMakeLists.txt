cmake_minimum_required(VERSION 3.10)

project(TelegramBot)

# C++ standard version
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Paths to search for libraries and header files
include_directories(/usr/local/include)
include_directories(${PROJECT_SOURCE_DIR}/libs)  # Path to the folder with nlohmann/json.hpp
include_directories(${PROJECT_SOURCE_DIR}/include)  # Add the include directory

# Source files
file(GLOB SOURCES src/*.cpp)  # This will grab all .cpp files in the src directory

# Create an executable file
add_executable(telegram_bot ${SOURCES})

# Подключение библиотек
find_package(Boost REQUIRED COMPONENTS system thread)   # Required Boost Components
find_package(OpenSSL REQUIRED)                          # SSL library

# Checking and connecting the TgBot library
find_library(TGBOT_LIB TgBot /usr/local/lib)
if(NOT TGBOT_LIB)
    message(FATAL_ERROR "TgBot library not found in /usr/local/lib. Please verify installation.")
endif()

# Linking libraries
target_link_libraries(telegram_bot
    ${TGBOT_LIB}
    Boost::system
    Boost::thread
    OpenSSL::SSL
    OpenSSL::Crypto
    pthread
)
