# CMake

CMake is a tool for desribing the steps of building and linking software without tying that description to a specific toolchain. This makes it possible to create makefiles (or projects or whatever) that work for multiple systems. This description is put into a CMakeLists.txt using the declarative commands of the [CMake scripting language](https://cmake.org/cmake/help/latest/manual/cmake-commands.7.html).

Using either the CMake graphical user interface, commonly called cmake-gui, or the CMake command line tool scripts for a specific compiler toolchain can be created. These can accept input from the person building the software or search the system for a default compiler and tools. This is also the point where build options are specified. General build options like compiler flags or settings for debug, release and optimization can be. Robot specific options like choosing static or dynamic builds can be set here as well.

CMake strongly encourages out of source builds. Most conventional build systems encourage creating the build artifacts (object files, executables, etc...) in the same directories as the source. This has advantages if build artifacts are to be shared, but this has complications when trying to remove them, keep them outside version control or maintain multiple builds with the same source on the same machine. When using CMake the directory with the source code and the directory the will happen in must be specificied

## Robot CMake Support

CMake supports a ton of platforms and build tool chains. Here are 
some that were specifically targeted to work with Robot:

* Windows
    * Visual Studio 14 - 2015
    * MinGW with Ninja
    * MinGW with Makefiles
    * Visual Studio 12 - 2013 - (Experimental)
    * Visual Studio 11 - 2012 - (Experimental)
    * Visual Studio 10 - 2010 - (Experimental)
*Linux
    * Clang with Ninja
    * Clang with Makefiles
    * GCC with Ninja
    * GCC with Makefiles
* Mac OS X - (Experimental)
    * Clang - (Experimental)
    * GCC - (Experimental)

## Using Cmake

You can read the [official CMake Tutorial](https://cmake.org/cmake-tutorial/) or get a brief versions here. Choose if you want to use the command like or the cmake-gui. The command line is easier to automate and can be called from your IDE, continuous integration system or other automation, but the cmake-gui could be easier to learn and allow easier access to options

### CMake Command Line

If you already have the [Robot prerequisites](http://getrobot.net/docs/usage.html) and cmake installed here is the simplest way to prepare the build on one of the systems listed above:

```
git clone https://github.com/Robot/robot.git
mkdir robot-build
cd robot-build
cmake ../robot
```

Then depending on your platform and compiler toolchaing you can will use a command like one of the following to actually perform the build 

* `make` - Common Unix make.
* `mingw32-make` - Windows MinGW Make
* `ninja` - Google's high performance ninja build system.
* `msbuild robot.sln` - From a visual studio command on windows will invoke msvc.

This glosses over many important details.

#### Generators

The line `cmake ../robot` has many potential options. The folder being passed is the source directory and the current directory will be used as the output directory.

CMake uses [Generators](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html) to decide what kinds of scripts to emit. If not specified it will perform a perfunctory check and attempt to emit some reasonable default. If you have a specific requirement you can check what generators are available on you system with 'cmake --help'. These can be used as follows:

For MinGW makefiles on windows:

```
cmake ../robot -G"MinGW Makefiles"
```

For Visual Studio 2015 on windows:

```
cmake ../robot -G"Visual Studio 14 2015"
```

For MinGW ninja on windows or Linux with ninja and GCC on most Linux distros:

```
cmake ../robot -G"Ninja"
```

Just passing `-G` and generator will determine what build system is used. This might determine the compiler as well, because not all build systems are compatible with all compilers. Some generators will provide different support for different IDEs like Eclipse, Code::Blocks, Borland and Codelite.

#### CMake variables

If you want to change any of the [Useful CMake variables](http://www.vtk.org/Wiki/CMake_Useful_Variables#Compilers_and_Tools) including `CMAKE_BUILD_TYPE` for debug/release or `CMAKE_CXX_COMPILER` for the compiler you can do this with the -D flag. If not specified a sane minimal setting for any variable will be used. Here are some examples for setting compiler flags in groups for debug or release optimization:

For release builds with reasonable optimization for the chosen compiler:

```
cmake ../robot -DCMAKE_BUILD_TYPE=Release
```

For debug builds with reasonable no optimizations:

```
cmake ../robot -DCMAKE_BUILD_TYPE=Debug
```

The variable `CMAKE_CXX_FLAGS` can be used for other flags on per compiler basis. For more possibilities see the [Useful CMake variables](http://www.vtk.org/Wiki/CMake_Useful_Variables) page in the CMake documentation.

One option that was added custom in Robot is a switch for enabling or disabling static or dynamic build support. This defaults to building static libraries. It can be controlled by settings the `BuildStatic` CMake variable to "ON" or "OFF". Here is an example building dynamic libraries:

```
cmake ../robot -DBuildStatic=OFF
```

#### Putting it Together

These options can be combined almost arbitrarily. The following example will build a release version of robot with the ninja build system and the clang compiler to make a dynamic library:

```
cmake ../robot -G"Ninja" -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=clang -DBuildStatic=OFF
```

### CMake-gui
The use
https://cmake.org/runningcmake/

