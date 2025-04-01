# Qt Examples Collection

A repository containing various small, focused examples demonstrating different features of the Qt framework using C++.

## Purpose

This collection is intended for learning, practice, and quick reference for common Qt tasks. Each example resides in its own subdirectory and is built using CMake.

## Prerequisites

To build and run these examples, you will need:

1.  **Qt Framework:** Version 5.x or 6.x. Ensure the required modules for the specific examples are installed (check the example's notes or CMake file). For the initial examples, you need:
    *   `Core`
    *   `Xml`
2.  **CMake:** Version 3.10 or higher is recommended.
3.  **C++ Compiler:** A modern C++ compiler compatible with your Qt version (e.g., GCC, Clang, MSVC).

## Repository Structure

The repository is organized as follows:

Qt_Examples/

├── CMakeLists.txt # Root CMake file to add subdirectories

├── XML_Attributes/

├── XML_Items/ 

├── (More example directories later...)

└── README.md # This file

*   The root `CMakeLists.txt` primarily uses `add_subdirectory()` to include the example directories.
*   Each example subdirectory contains its own `CMakeLists.txt` defining the specific executable(s) and linking against the necessary Qt modules.

## Building the Examples

Simply open the top level CMakeLists.txt in Qt Creator and configure for a valid kit.  Click the "Build" button.

## Running the Examples

Select the example you want to run in Qt Creator and run it.

*(Note: The exact executable name might vary slightly depending on how it's defined in the subdirectory's `CMakeLists.txt` - adjust the commands if necessary).*

## Examples Included

### XML_Attributes

Simple example using Qt XML DOM classes to parse XML looking at attributes.

### XML_Items

Simple example using Qt XML DOM classes to parse XML.

*(More examples will be added here as the repository grows.)*

## Contributing

Contributions are welcome! If you find issues or want to add new examples:

1.  Open an Issue to discuss the change or bug.
2.  Fork the repository.
3.  Create a new branch for your feature or fix.
4.  Add your example in a new numbered subdirectory with its own `CMakeLists.txt`.
5.  Update the root `CMakeLists.txt` and this `README.md`.
6.  Submit a Pull Request.

## License

None
