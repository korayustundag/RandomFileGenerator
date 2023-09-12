#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#ifdef __linux__
#include <limits>
#endif

#define COLOR_RED     "\033[31m"
#define COLOR_RESET   "\033[0m"

/** 
* This function returns an exit code that indicates an invalid argument was passed to the program. The specific exit code depends on the operating system.
* 
* @return An exit code that indicates an invalid argument was passed to the program.
*/
int EXIT_BAD_ARG()
{
#if __linux__
    return 22;  // Linux: EINVAL - Invalid argument
#endif
    return 160; // Windows: ERROR_BAD_ARGUMENTS - One or more arguments are not correct.
}

void printHelp() {
    std::cout << "Usage: rfg [OPTIONS]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -s, --size SIZE   Set the size of the generated file in bytes" << std::endl;
    std::cout << "  -o, --out FILE    Set the output file path" << std::endl;
    std::cout << "  -h, --help        Show help message" << std::endl;
    std::cout << "  -v, --version     Show version information" << std::endl;
    std::cout << "  -l, --license     Show license information" << std::endl;
    std::cout << std::endl;
    std::cout << "Example:" << std::endl;
#if __linux__
    std::cout << "  ./rfg -s 512 -o randomfile.ext" << std::endl;
    std::cout << "  ./rfg --size 2048 --out randomfile2.ext" << std::endl;
#else
    std::cout << "  rfg.exe -s 512 -o randomfile.ext" << std::endl;
    std::cout << "  rfg.exe --size 2048 --out randomfile2.ext" << std::endl;
#endif
}

void printLicense()
{
    std::cout << "  Copyright (C) 2023 Koray USTUNDAG" << std::endl;
    std::cout << "  This program is free software: you can redistribute it and/or modify" << std::endl;
    std::cout << "  it under the terms of the GNU General Public License as published by" << std::endl;
    std::cout << "  the Free Software Foundation, either version 3 of the License, or" << std::endl;
    std::cout << "  (at your option) any later version.\n" << std::endl;
    std::cout << "  This program is distributed in the hope that it will be useful," << std::endl;
    std::cout << "  but WITHOUT ANY WARRANTY; without even the implied warranty of" << std::endl;
    std::cout << "  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the" << std::endl;
    std::cout << "  GNU General Public License for more details.\n" << std::endl;
    std::cout << "  You should have received a copy of the GNU General Public License" << std::endl;
    std::cout << "  along with this program.  If not, see <https://www.gnu.org/licenses/>" << std::endl;
}

/**
* This function converts a byte size to a human-readable string.
* @param len The number of bytes to convert.
* @return A string in the format <number> <unit>.
*/
std::string FormatByteSize(long long len)
{
    const std::string units[] = { "B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB" };
    int unitIndex = 0;
    double sizeDbl = static_cast<double>(len);
    while (sizeDbl >= 1024 && unitIndex < sizeof(units) / sizeof(units[0]) - 1)
    {
        sizeDbl /= 1024;
        unitIndex++;
    }
    return std::to_string(sizeDbl) + " " + units[unitIndex];
}

/**
* This function generates a random file of the specified size.
* 
* @param filePath: The file path to the output file.
* @param fileSizeInBytes: The size of the output file in bytes.
* @return None.
*/
void GenerateRandomFile(const std::string& filePath, long long fileSizeInBytes)
{
    std::ofstream fs(filePath, std::ios::binary);
    char buffer[1024];
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (long long bytesWritten = 0; bytesWritten < fileSizeInBytes; bytesWritten += sizeof(buffer))
    {
        for (int i = 0; i < sizeof(buffer); ++i)
        {
            buffer[i] = static_cast<char>(std::rand() % 256);
        }
        int bytesToWrite = static_cast<int>(std::min(static_cast<long long>(sizeof(buffer)), fileSizeInBytes - bytesWritten));
        fs.write(buffer, bytesToWrite);
    }
}

int main(int argc, char* argv[])
{
    std::string outputPath;
    long long fileSize = -1;

    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-s" || std::string(argv[i]) == "--size") {
            if (i + 1 < argc) {
                fileSize = std::atoll(argv[i + 1]);
                ++i;
            }
            else {
                printHelp();
                return EXIT_BAD_ARG();
            }
        }
        else if (std::string(argv[i]) == "-o" || std::string(argv[i]) == "--out") {
            if (i + 1 < argc) {
                outputPath = argv[i + 1];
                ++i;
            }
            else {
                printHelp();
                return EXIT_BAD_ARG();
            }
        }
        else if (std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help") {
            // Print help and exit
            printHelp();
            return 0;
        }
        else if (std::string(argv[i]) == "-v" || std::string(argv[i]) == "--version") {
            // Print version and exit
            std::cout << "Random File Generator version 1.0.0" << std::endl;
            return 0;
        }
        else if (std::string(argv[i]) == "-l" || std::string(argv[i]) == "--license") {
            // Print license information and exit
            std::cout << "Random File Generator is licensed under the GPLv3 license.\n" << std::endl;
            printLicense();
            return 0;
        }
        else {
            std::cerr << COLOR_RED << "Error: Unknown option '" << argv[i] << "'" << COLOR_RESET << std::endl;
            printHelp();
            return EXIT_BAD_ARG();
        }
    }

    // Check for missing arguments
    if (fileSize == -1 || outputPath.empty()) {
        printHelp();
        return EXIT_BAD_ARG();
    }

    std::cout << "Welcome to Random File Generator" << std::endl;
    std::cout << "Total File Size: " << FormatByteSize(fileSize) << std::endl;
    std::cout << "Creating file, Please wait..." << std::endl;
    GenerateRandomFile(outputPath, fileSize);
    std::cout << "Random file has been generated and saved." << std::endl;
    std::cout << "Press enter to exit...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return 0;
}
