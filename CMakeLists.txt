#
# This is a CMake makefile.  You can find the cmake utility and
# information about it at http://www.cmake.org
#

cmake_minimum_required (VERSION 3.1)
project(fr)

set (CMAKE_CXX_STANDARD 11)

 set(SOURCE 	clusteringAndIndexing/chinesewhispers.cpp
				clusteringAndIndexing/evaluator.cpp
				clusteringAndIndexing/glc.cpp
				common/common.cpp
				common/Utils.cpp
				face/FaceDescriptor_dking.cpp
				test_faceclust.cpp
    )

 set(HEADERS	clusteringAndIndexing/chinesewhispers.h
				clusteringAndIndexing/evaluator.h
				clusteringAndIndexing/glc.h
				common/common.h
				common/get_lfw_pairs.h
				common/Timing.h
				common/Utils.h
				face/FaceDescriptor_dking.h
				test_faceclust.h
        dlib/opencv.h
        dlib/image_processing.h
        dlib/image_processing/frontal_face_detector.h
        dlib/image_processing/render_face_detections.h
        dlib/gui_widgets.h
        dlib/image_io.h
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

add_subdirectory(/Users/cristophercejudo/Desktop/ITESM/5º_Semestre/Software_Modelling/face_alignment/dlib-19.17 dlib_build)

include_directories(${fr_include})

add_executable(fr FaceAligner.cpp)
# add_executable(fr FaceAligner.cpp ${SOURCE} ${HEADERS})
target_link_libraries(fr ${OpenCV_LIBS} dlib::dlib)
