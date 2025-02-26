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
			if (word[i] == ' ') // don't save spaces as unique/guessable chars
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
	std::cin >> guess;
	std::cout << "\n";

	return guess;
}

void clear_input() 
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool correct_answer(const std::string& input, const std::string solution)
{
	if (input == solution) return true;
	else return false;
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

bool check_guess(const char& guess, std::vector<char>& unique_chars)
{
	for (int i = 0; i < unique_chars.size(); i++)
	{
		if (guess == unique_chars[i]) return true;
	}
	return false;
}

void draw_spaces(const std::string& solution, const std::vector<char>& correct_guesses) 
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
	std::cout << spaces << "\n\n";
}

void draw_man(const std::vector<std::string>& men, const int correct_guesses, const int total_guesses)
{
	// print string in men vector equal to number of incorrect guesses so far, clamped to max size of men vector
	std::cout << men[abs(correct_guesses - total_guesses > (int)men.size() - 1 ? (int)men.size() - 1 : correct_guesses - total_guesses)] << "\n";
}

int check_winstate(const int max_guesses, const int correct_guesses, const int total_guesses, const int answers)
{
	if (correct_guesses >= answers) return 1; // won
	if (max_guesses - (total_guesses - correct_guesses) <= 0) return 2; // lost
	return 0; // keep playing
}

bool input_in_list(const std::string& input, const std::vector<std::string>& list) 
{
	for (std::string item : list) 
	{
		if (input == item) return true;
	}
	return false;
}