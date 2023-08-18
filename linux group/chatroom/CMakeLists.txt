cmake_minimum_required(VERSION 3.10)

project(ChatRoom)

# 添加可执行文件
add_executable(server user.cpp server/database.cpp server/server.cpp server/service_ser.cpp server/thread.cpp server/main.cpp Serialization.cpp Message.cpp group.cpp client/client.cpp File.cpp)
add_executable(client client/client.cpp client/service.cpp client/UI.cpp client/main.cpp Serialization.cpp server/database.cpp user.cpp Message.cpp group.cpp File.cpp)

# 创建一个文件夹
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/file)

# 添加头文件路径
target_include_directories(server PRIVATE server ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/client)
target_include_directories(client PRIVATE client ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/server)

# 设置编译选项
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# 添加链接库
find_library(HIREDIS_LIBRARY NAMES hiredis)
target_link_libraries(server ${HIREDIS_LIBRARY})
target_link_libraries(client ${HIREDIS_LIBRARY})



