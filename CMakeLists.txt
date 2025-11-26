cmake_minimum_required(VERSION 3.10)
project(chatBot01)

set(CMAKE_CXX_STANDARD 17)
include_directories("C:/2024_Fall/cit66_Cpp/chatBot01/include")


# curl include path
include_directories("D:/bryza CIT-66/projects/myChatBot.cpp/libs/curl/curl-8.11.0_2-win64-mingw/include")

# nlohmann json include path
include_directories("D:/bryza CIT-66/projects/myChatBot.cpp/chatBot01/include")

# curl library path
link_directories("D:/bryza CIT-66/projects/myChatBot.cpp/libs/curl/curl-8.11.0_2-win64-mingw/lib")

add_executable(chatBot01
        chatBot01.cpp
        testBot01.cpp
)

# curl library
target_link_libraries(chatBot01 curl)
