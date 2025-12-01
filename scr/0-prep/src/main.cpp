#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

int main() {

    std::cout << "Current path is " << std::filesystem::current_path() << '\n'; 


    // 1. Declare a string variable to hold each line as it's read
    std::string line;

    // 2. Open the file for reading using std::ifstream
    // Replace "filename.txt" with the path to your file
    std::ifstream file("../../../../filename.txt"); 

    // 3. Check if the file was successfully opened
    if (file.is_open()) {
        // 4. Use a while loop with std::getline() to read the file line by line
        // std::getline() returns the stream, which evaluates to true as long as 
        // a line is successfully read. It extracts and discards the newline character.
        while (std::getline(file, line)) {
            // 5. Process the line (here we print it to the console)
            std::cout << line << std::endl;
        }
        // 6. Close the file (optional, as the ifstream destructor does this automatically)
        file.close(); 
    } else {
        // Handle the error if the file cannot be opened
        std::cout << "Error: Unable to foo open file." << std::endl;
    }

    return 0;
}
