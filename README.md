RegexBuilder
=========

I - Installation
	Install git
	Install Qt >= 5
	Install CMake >= 2.5

II - Get the code
	Clone the repository.

III - Configure the build
	Include the directory mingw32-make.exe in the path.
	Launch CMake at the root of the project.
	Add the path entry "CMAKE_PREFIX_PATH" pointing to your Qt path (ex: C:/Qt/Qt5.3.1/5.3/mingw482_32).
	Set a solution directory to keep your workspace clean.
	Configure and generate your solution.

IV - Build the solution
	Go to your solution directory.
	Run mingw32-make.

V - Get the lib
	The lib is available in the "lib" directory.
	