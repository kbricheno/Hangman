#include <iostream>
#include <vector>

std::string choose_solution(const std::vector<std::string>& options);

void find_unique_chars(const std::string& word, std::vector<char>& unique_chars);

int won_or_lost(const std::vector<char>& guesses, const std::vector<char>& answers, const int& remaining_guesses);

std::string request_input();

bool valid_input(const std::string& input);

bool input_in_list(const std::string& input, const std::vector<std::string>& list);

bool previous_guess(const std::string& input, const std::vector<char>& guesses);

std::string create_spaces(const std::string& solution, const std::vector<char>& correct_guesses);

bool check_guess(const char& guess, const std::string& solution);