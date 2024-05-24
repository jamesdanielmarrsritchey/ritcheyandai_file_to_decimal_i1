#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

std::string getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return std::string(*itr);
    }
    return "";
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args(argv, argv + argc);
    std::string source_filename = getCmdOption(argv, argv + argc, "--source_file");
    std::string destination_filename = getCmdOption(argv, argv + argc, "--destination_file");
    std::string delimiter = getCmdOption(argv, argv + argc, "--delimiter");

    if (delimiter == "\\n") {
        delimiter = "\n"; // treat as line ending
    } else if (delimiter == "\\t") {
        delimiter = "\t"; // treat as tab
    } else if (delimiter.empty()) {
        delimiter = " "; // default delimiter is space
    }

    if (!source_filename.empty() && !destination_filename.empty()) {
        std::ifstream source_file(source_filename);
        std::ofstream destination_file(destination_filename);
        if (source_file.is_open() && destination_file.is_open()) {
            char c;
            while (source_file.get(c)) {
                destination_file << static_cast<int>(c);
                if (!source_file.eof()) {
                    destination_file << delimiter;
                }
            }
            source_file.close();
            destination_file.close();
            return true;
        } else {
            std::cout << "Unable to open file." << std::endl;
        }
    } else {
        std::cout << "No source file or destination file was given." << std::endl;
    }

    return 0;
}