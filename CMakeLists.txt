cmake_minimum_required(VERSION 3.12)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR})

set(TASK_MANAGER_SOURCE
	${PROJECT_SOURCE_DIR}/TaskManager/taskManager.cpp
	${PROJECT_SOURCE_DIR}/TaskManager/task.h
	${PROJECT_SOURCE_DIR}/TaskManager/worker.h
	${PROJECT_SOURCE_DIR}/TaskManager/worker.cpp
	${PROJECT_SOURCE_DIR}/TaskManager/blockingQueue.h
)
add_library(task_manager ${TASK_MANAGER_SOURCE})
set_target_properties(task_manager PROPERTIES
	PUBLIC_HEADER "${PROJECT_SOURCE_DIR}/TaskManager/taskManager.h"
	PUBLIC_HEADER "${PROJECT_SOURCE_DIR}/TaskManager/task.h"
)

set(WEB_SERVER_SOURCE
	"${PROJECT_SOURCE_DIR}/WebServer/main.cpp"
	"${PROJECT_SOURCE_DIR}/WebServer/webServer.cpp"
	"${PROJECT_SOURCE_DIR}/WebServer/webServer.h"
)
add_executable(web_server ${WEB_SERVER_SOURCE})
target_link_libraries(web_server task_manager wsock32)
