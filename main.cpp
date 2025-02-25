#include <iostream>
#include <vector>
#include "fns.h"
#include <regex>

std::vector<std::string> fun_words = { "stupid", "idiot", "dumbass", "nincompoop", "dingus", "genius", "moron", "silly billy", "numbnuts"};

int max_guesses = 6;

int main() 
{
	bool playing = true;
	while (playing)
	{
		// generate random seed (once each time the program runs)
		srand(time(0));

		// decide word
		// TODO: import from text doc
		// choose & set solution from list of word options
		std::string current_solution = choose_solution(fun_words);

		// find unique characters in solution
		std::vector<char> unique_chars_in_solution;
		find_unique_chars(current_solution, unique_chars_in_solution);

		// prepare guess variables
		int guesses_remaining = max_guesses;
		std::vector<char> guesses;
		std::vector<char> correct_guesses;

		// draw spaces, hanging pole
		std::string spaces = create_spaces(current_solution, correct_guesses);
		std::cout << spaces << "\n";

		bool game_over = false;

		while (!game_over)
		{
			std::cout << guesses_remaining << " guesses remaining.\n";

			// request guess input from user
			std::string new_guess = request_input();

			// validate user input
			while (!valid_input(new_guess) || previous_guess(new_guess, guesses))
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> new_guess;
				std::cout << "\n";
			}

			// check if guess is correct
			if (check_guess(new_guess[0], current_solution)) 
			{
				std::cout << "Nice!\n";
				correct_guesses.push_back(new_guess[0]);
			}

			else
			{
				std::cout << "Incorrect!\n";
				guesses_remaining--;
			}

			guesses.push_back(new_guess[0]);

			std::string spaces = create_spaces(current_solution, correct_guesses);
			std::cout << spaces << "\n";

			// guess incorrect: guesses_remaining--; draw next piece of Man

			// break
			if (guesses_remaining <= 0)
			{
				std::cout << "\nGame over!\n";
				game_over = true;
				break;
			}
			if (correct_guesses.size() >= unique_chars_in_solution.size())
			{
				std::cout << "\nYou win!\n";
				game_over = true;
				break;
			}
		}

		std::vector<std::string> affirmatives = { "y", "yes", "ye", "confirm", "accept" };
		std::vector<std::string> negatives = { "n", "no", "nah", "cancel", "negative" };
		std::string play_again_input = "";
		bool decided = false;

		std::cout << "Would you like to play again?\n";

		while (!decided) 
		{
			std::cin >> play_again_input;

			while (!valid_input(play_again_input))
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> play_again_input;
				std::cout << "\n\n";
			}
			if (input_in_list(play_again_input, negatives))
			{
				playing = false;
				decided = true;
			}
			else if (input_in_list(play_again_input, affirmatives))
			{
				playing = true;
				decided = true;
			}
			else 
			{
				std::cout << "Please enter yes or no.\n";
			}
		}
	}
	return 0;
}