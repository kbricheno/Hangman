#include <iostream>
#include <vector>

void choose_solution(const std::vector<std::string>&, std::string&);

void find_unique_chars(const std::string&, std::vector<char>&);

int won_or_lost(const std::vector<char>&, const std::vector<char>&, const int&);

bool valid_input(const std::string&);

bool previous_guess(const std::string&, const std::vector<char>&);