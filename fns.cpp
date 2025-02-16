#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <regex>

void choose_solution(const std::vector<std::string>& options, std::string& result)
{
	int num = rand() % options.size();
	result = options[num];
}

void find_unique_chars(const std::string& word, std::vector<char>& unique_chars)
{
	for (int i = 0; i < word.size(); i++)
	{
		unique_chars.push_back(word[i]);
	}
}

int won_or_lost(const std::vector<char>& guesses, const std::vector<char>& answers, const int& remaining_guesses)
{
	if (remaining_guesses <= 0) return 1; // lost

	int correct_guesses = 0;

	for (char a : answers)
	{
		for (char g : guesses)
		{
			if (g == a) correct_guesses++;
		}
	}

	if (correct_guesses >= answers.size()) return 2; // won
	else return 0; // can continue
}

bool valid_input(const std::string& input) 
{
	std::regex regex_pattern("[a-zA-Z]");

	if (!std::regex_match(input, regex_pattern)) 
	{
		std::cout << "Please enter a letter: ";
		return false;
	}
	else return true;
}

bool previous_guess(const std::string& input, const std::vector<char>& guesses) 
{
	for (char g : guesses) 
	{
		if (g == input[0]) 
		{
			std::cout << "Please enter a letter you haven't already guessed: ";
			return true;
		}
	}

	return false;
}