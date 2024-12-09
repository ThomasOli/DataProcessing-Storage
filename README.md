## Running the code: ##
# Ensure you have a C++17-compatible compiler installed. On Linux or macOS, you can use g++: #

g++ -std=c++17 -O2 -o processing processing.cpp
./processing


# On Windows, you can install MinGW-w64 and then run: #

g++ -std=c++17 -O2 -o processing processing.cpp
./processing.exe

# Running the compiled binary will execute the tests in main() and print the output to the terminal. #

## Future Improvements for the Assignment: ##
To make this assignment more “official” in the future, it could be beneficial to provide clearer instructions on how transactions should behave if multiple calls to begin_transaction() occur (currently disallowed), or define a custom exception type for error handling. Additionally, adding tests that explicitly check behavior for edge cases (like empty keys or multiple updates within a single transaction) would ensure comprehensive validation. Another improvement would be providing a public API for listing all keys and their values, helping students verify state changes more easily. Finally, adding automated grading scripts or a more detailed rubric could streamline the grading process.
