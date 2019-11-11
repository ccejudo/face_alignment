#
# This is a CMake makefile.  You can find the cmake utility and
# information about it at http://www.cmake.org
#

cmake_minimum_required (VERSION 3.1)
project(fr)

set (CMAKE_CXX_STANDARD 11)

 set(SOURCE
        cvui.cpp
	#showmanyimages.cpp
    )


# automatic OpenCV finding
find_package(OpenCV REQUIRED)

# if not, use manual specification of the OpenCVConfig.cmake path
# and comment previous line of automatic finding
#find_package(OpenCV REQUIRED PATHS /usr/local/share/OpenCV NO_DEFAULT_PATH)


if(OpenCV_FOUND)
	message("-- Opencv Found")
endif()

set(fr_include 	/usr/local/include
	)

include_directories(${fr_include})

add_executable(fr cvui.cpp ${SOURCE} ${HEADERS})
#add_executable(fr showmanyimages.cpp ${SOURCE} ${HEADERS})
# add_executable(fr cvui.h ${SOURCE} ${HEADERS})

target_link_libraries(fr ${OpenCV_LIBS})
