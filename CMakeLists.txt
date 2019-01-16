cmake_minimum_required(VERSION 3.12)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR})

set(SUM_PARALLEL_SOURCE ${PROJECT_SOURCE_DIR}/SumParallel/main.cpp)
add_executable(SumParallel ${SUM_PARALLEL_SOURCE})

set(TASK_MANAGER_SOURCE
	${PROJECT_SOURCE_DIR}/TaskManager/main.cpp
	${PROJECT_SOURCE_DIR}/TaskManager/TaskManager.h
	${PROJECT_SOURCE_DIR}/TaskManager/TaskManager.cpp
	${PROJECT_SOURCE_DIR}/TaskManager/Task.h
)
add_executable(TaskManager ${TASK_MANAGER_SOURCE})
