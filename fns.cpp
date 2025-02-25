#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <regex>

std::string choose_solution(const std::vector<std::string>& options)
{
	// pick a number from the random seed, choose a word from the list of options
	int num = rand() % options.size();
	return options[num];
}

void find_unique_chars(const std::string& word, std::vector<char>& unique_chars)
{
	// add each unique letter in the solution to a list used for correct guesses
	std::vector<char> all_chars;

	for (int i = 0; i < word.size(); i++)
	{
		bool is_unique_char = true;
		for (char a : all_chars) 
		{
			if (word[i] == a) 
			{
				is_unique_char = false;
				break;
			}
		}

		if (is_unique_char) unique_chars.push_back(word[i]);
		all_chars.push_back(word[i]);
	}
}

std::string request_input() 
{
	std::string guess = "";
	std::cout << "Guess a letter: ";
	std::cin >> guess;
	std::cout << "\n";

	return guess;
}

int won_or_lost(const std::vector<char>& guesses, const std::vector<char>& answers, const int& remaining_guesses)
{
	// check the game state -- has the player won or lost?
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
	// check user input against an alphabet-only regex pattern to ensure valid entry
	std::regex regex_pattern("[a-zA-Z]");

	if (!std::regex_match(input, regex_pattern)) 
	{
		std::cout << "Please enter a letter: ";
		return false;
	}
	else return true;
}

bool input_in_list(const std::string& input, const std::vector<std::string>& list) 
{
	for (std::string item : list) 
	{
		if (input == item) return true;
	}
	return false;
}

bool previous_guess(const std::string& input, const std::vector<char>& guesses) 
{
	// check user input against a list of previous guesses to ensure guess is valid
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

std::string create_spaces(const std::string& solution, const std::vector<char>& correct_guesses) 
{
	std::string spaces;
	for (char s : solution)
	{
		std::string new_space = "";

		for (char c : correct_guesses)
		{
			if (s == c) 
			{
				new_space = { c }; // converting c into a string
			}
		}
		if (new_space == "") 
		{
			if (s == ' ') spaces.append(" ");
			else spaces.append("_");
		}
		spaces.append(new_space);
	}
	return spaces;
}

bool check_guess(const char& guess, const std::string& solution) 
{
	for (int i = 0; i < solution.size(); i++)
	{
		if (guess == solution[i]) return true;
	}
	return false;
}