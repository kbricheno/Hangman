#include <iostream>
#include <vector>
#include "fns.h"
#include <regex>

std::vector<std::string> fun_words = { "stupid", "idiot", "dumbass", "nincompoop", "dingus", "genius", "moron" };

std::string current_solution = "";
std::vector<char> unique_chars_in_solution;

int guesses_remaining = 6;
std::vector<char> chars_guessed = { 'f', 'a' };

int main() 
{
	srand(time(0));
	
	// decide word
	// TODO: import from text doc
	choose_solution(fun_words, current_solution);

	// find unique characters in solution
	find_unique_chars(current_solution, unique_chars_in_solution);

	// draw spaces, hanging pole

	std::string new_guess = "";
	std::cout << "Guess a letter: ";
	std::cin >> new_guess;
	std::cout << "\n";

	while (!valid_input(new_guess) || previous_guess(new_guess, chars_guessed))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> new_guess;
		std::cout << "\n";
	}

	std::cout << "Good letter!\n";

	// guess correct: draw letter in relevant spaces

	// guess incorrect: guesses_remaining--; draw next piece of Man

	// break

	// win state: all letters guessed successfully, print "you win"
	std::cout << "\nYou win!\n";

	// fail state: no remaining guesses, print "you lose"
	std::cout << "\nYou lose! This man is dead!\n";

	return 0;
}