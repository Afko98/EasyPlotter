#include "Plotter.h"
#include <iostream>
#include <filesystem>
#include <string>

Plotter::Plotter()
{
    // Get the current directory where the executable is located
    std::filesystem::path currentPath = std::filesystem::current_path();

    // Build the relative path to gnuplot.exe
    std::filesystem::path gnuplotPath = currentPath / "gnuplot" / "bin" / "gnuplot.exe";

    // Convert the path to string
    std::string pathStr = gnuplotPath.string();

    // Escape backslashes in the path for Windows format
    std::string escapedPath;
    for (char ch : pathStr) {
        if (ch == '\\') {
            escapedPath += '\\';  // Add an extra backslash
        }
        escapedPath += ch;
    }

    // Add quotes around the path
    escapedPath = "\"" + escapedPath + "\"";
    std::cout << "Path is " << escapedPath;

    // Initialize the Gnuplot object with the escaped path
    gp = new Gnuplot(escapedPath);
}
