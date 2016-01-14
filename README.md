# SudokuSolver
This is a simple GUI application written in C++ and wxWidgets that solves sudoku puzzles. It uses a backtracking algorithm to calculate the solution. It's certainly not the most efficient implementation out there, but the aim was to write the application in an object-oriented way that is hopefully easy to understand. 

#Building the Application
In order to build the complete application, it is necessary to first build wxWidgets (see https://wiki.wxwidgets.org/Compiling_Using_MSVC_On_The_Commandline for example) and define the system variable $WXWIN to point to the build. Note that the visual studio project files assume that wxWidgets has been built as a static library.

It should then be possible to build the application using the VS project files. Alternatively, you may wish to use the solver without the GUI component - all the necessary classes for this are contained in the SudokuSolver header and source files. I have also built a release myself which can be downloaded from the project page.

#Tests
There are tests for the SudokuSolver class in the Tests/ directory. This contains a seperate visual studio project for running the tests on the command line.
