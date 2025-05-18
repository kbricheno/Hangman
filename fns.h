#include <iostream>
#include <vector>

// Select the current solution from a list of words.
std::string choose_solution(const std::vector<std::string>& options);

// Create a list of the unique characters in the solution.
void find_unique_chars(const std::string& word, std::vector<char>& unique_chars);

// Receive input.
std::string request_input();
// Clear invalid input and ignore remaining characters in the input stream.
void clear_input();

// Check if this guess exactly equals the solution.
bool correct_answer(const std::string& input, const std::string solution);
// Check if this input is a single character in the latin alphabet.
bool valid_input(const std::string& input);
// Check if this guess has already been made.
bool previous_guess(const std::string& input, const std::vector<char>& guesses);

// Check whether the guessed letter appears in the list of unique chars taken from the solution.
bool check_guess(const char& guess, std::vector<char>& unique_chars);

// Generate and then print blanks, letters, and spaces for the current solution.
void draw_spaces(const std::string& solution, const std::vector<char>& correct_guesses);
// Print an ASCII hangman based on the number of incorrect guesses.
void draw_man(const std::vector<std::string>& men, const int correct_guesses, const int total_guesses);

// Check whether the user has run out of guesses or correctly guessed all of the unique chars in the solution.
int check_winstate(const int max_guesses, const int correct_guesses, const int total_guesses, const int answers);

// Check whether the input appears exactly within a list of strings.
bool input_in_list(const std::string& input, const std::vector<std::string>& list);