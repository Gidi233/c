cmake_minimum_required(VERSION 3.10)

project(ChatRoom)

# 添加可执行文件
add_executable(server server/server.cpp server/database.cpp server/service_ser.cpp server/thread.cpp server/main.cpp Serialization.cpp user.cpp)
add_executable(client client/client.cpp client/service.cpp client/UI.cpp client/main.cpp Serialization.cpp user.cpp)


# 添加头文件路径
target_include_directories(server PRIVATE server ${CMAKE_SOURCE_DIR})
target_include_directories(client PRIVATE client ${CMAKE_SOURCE_DIR})

# 设置编译选项
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER g++)


# 添加链接库
# find_library(HIREDIS_LIBRARY NAMES hiredis)
# target_link_libraries(server ${HIREDIS_LIBRARY})
# target_link_libraries(client ${HIREDIS_LIBRARY})



