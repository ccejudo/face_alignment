# Face Alignment Module

This is a multipataform C++ project that align a face of an input image, identifying the eyes region to obtain a normalized rotation, translation, and scale representation of the face.

## Description

This is the 2nd module of a **Face Recognition** project. Functional and non-functional requirements can be found on the following link: https://trello.com/invite/b/5WHeFcX2/cf90313ec5cdf6685094467676a64ffd/face-recognition-module-2

## Visuals

## Installation
* Step 1 --> Download the project.
* Step 2 --> Extract de project.
* Step 3 --> On the 'CMakeLists.txt' file change the following:
* add_subdirectory(/Users/brias5/desktop/face_alignment/dlib-19.17 dlib_build) <-- Insert your path to dlib in here.
* Step 4 --> When making an instance of 'FaceAligner2' you can provide the path to the 'shape_predictor_5_face_landmarks', if you don't the constructor will automatically pull it from the Folder you already downloaded.
* Step 5 --> On the 'Input' file add the images you want to align, each one labeled in an ascendant order starting with 1. You can find a 100 images to test the project on the file.
* Step 6 --> Compile on the terminal using the command 'make' and then run the executable. On the 'Output' file you will find the aligned images. You can also observe on the terminal the size of each image, the points were the eyes are in the new image and the time taken by the function to align the image.

### Requirements
* Linux, Windows or macOS
* OpenCV
* Dlib

## Usage

## Authors and acknowledgment
* Cristopher Cejudo. Role:
* Martin Alegría. Role:
* Octavio Garduza. Role:
* Raziel Martínez. Role:
* Ruben Sánchez. Role:
* Sabrina Santana. Role:

* Leonardo Chang. Role: Project Manager

## Project status
⚠️ Under Maintenance ⚠️
