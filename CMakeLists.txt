cmake_minimum_required(VERSION 3.5)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")

project(tic-tac-toe)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2 REQUIRED audio graphics network system window)

include_directories(
	${CMAKE_SOURCE_DIR}/include
)

add_executable(
	tic-tac-toe
	main.cpp
	src/Button.cpp
	${SFML_LIBRARIES}
)

target_link_libraries(tic-tac-toe ${SFML_LIBRARIES})

set(CMAKE_BUILD_TYPE Debug)

make_directory(img)
file(COPY ${CMAKE_SOURCE_DIR}/img/circle.png DESTINATION img)
file(COPY ${CMAKE_SOURCE_DIR}/img/cross.png  DESTINATION img)
file(COPY ${CMAKE_SOURCE_DIR}/img/normal.png DESTINATION img)