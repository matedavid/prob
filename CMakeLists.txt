project(prob)

include_directories(test PRIVATE header)
file(GLOB SOURCES "source/*.cpp" "header/*.h" )

add_executable(build/prob ${SOURCES})
