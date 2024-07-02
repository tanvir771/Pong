cmake_minimum_required(VERSION 3.29.3)

project(Project_Pong
	VERSION 1.0.0
	LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD             14)
set(CMAKE_CXX_STANDARD_REQUIRED    ON)
set(CMAKE_CXX_EXTENSIONS          OFF)

include(FetchContent)
set(SFML_LIB_NAME SFML)

FetchContent_DECLARE(
	${SFML_LIB_NAME}
	GIT_REPOSITORY https://github.com/SFML/SFML
	GIT_TAG 2.5.1
	GIT_SHALLOW FALSE
)

FetchContent_MakeAvailable(${SFML_LIB_NAME})

set(PONG_TARGET_NAME Project_Pong)

add_executable(${PONG_TARGET_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/src/Application.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/Application.h
	
	${CMAKE_CURRENT_SOURCE_DIR}/src/Objects.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/Objects.h

	${CMAKE_CURRENT_SOURCE_DIR}/src/Player.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/Player.h
)

target_include_directories(${PONG_TARGET_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PONG_TARGET_NAME} PUBLIC sfml-graphics)
target_link_libraries(${PONG_TARGET_NAME} PUBLIC sfml-window)
target_link_libraries(${PONG_TARGET_NAME} PUBLIC sfml-system)
target_link_libraries(${PONG_TARGET_NAME} PUBLIC sfml-audio)


function(CopyLibToTarget LIB_NAME TARGET_NAME)
	add_custom_command(TARGET ${TARGET_NAME}
	POST_BUILD
	COMMAND
	${CMAKE_COMMAND} -E copy_if_different
	$<TARGET_FILE:${LIB_NAME}>
	$<TARGET_FILE_DIR:${TARGET_NAME}>
	)
endfunction()

CopyLibToTarget(sfml-graphics ${PONG_TARGET_NAME})
CopyLibToTarget(sfml-window ${PONG_TARGET_NAME})
CopyLibToTarget(sfml-system ${PONG_TARGET_NAME})
CopyLibToTarget(sfml-audio ${PONG_TARGET_NAME})