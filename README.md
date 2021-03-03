# RayTracing

Simple Ray Tracing Algorithm in C++

## Hierarchy

The main() function is found in RayTracing.cpp.

Thanks to a XML file, placed in the sub-folder "files", you can initialize a 3D scene that will be rendered by the Camera, an essential component.

The output is a bitmap image to be found in the same sub-folder "files".

All the external code used in this project is placed in "libs". These libraries were used to handle XML format and BMP image format.

## XML structure

Materials are placed in the node <materials>. Same for <objects> (plane and/or sphere), and <lights>.

The camera is placed in the node <camera>. This is an important component. Failing to initialize it properly will lead to the program simply not running.

I have provided an example file with at least one example of each children node.

```
NB: directional vector is not do be confused with rotation vector. The base rotation of the Camera is (0, 0, 0), yet its directional vector is (0, 0, -1), as a convention.
```
