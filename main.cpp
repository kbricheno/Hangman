#include <iostream>
#include <vector>
#include "fns.h"
#include <regex>
#include <cmath>

// add more words to choose from here
std::vector<std::string> cool_animals = { "tyrannosaurus rex", "diplodocus longus", "ankylosaurus magniventris", "spinosaurus aegyptiacus", "triceratops horridus", "pachycephalosaurus wyomingensis", "otodus megalodon", "dunkleosteus terrelli", "carnotaurus sastrei", "quetzalcoatlus northropi" };

// when asked to play again, user must enter a value that exactly matches one of these strings
std::vector<std::string> affirmatives = { "y", "yes", "ye", "confirm", "accept" };
std::vector<std::string> negatives = { "n", "no", "nah", "cancel", "negative" };

// number of guesses is determined by the length of this vector; break the man up into smaller pieces to add more guesses
std::vector<std::string> men = {
"_____\n|   |\n|   \n|   \n|  \n|____\n",
"_____\n|   |\n|   O\n|   \n|  \n|____\n",
"_____\n|   |\n|   O\n|   |\n|  \n|____\n",
"_____\n|   |\n|   O\n|  /|\n|  \n|____\n",
"_____\n|   |\n|   O\n|  /|\\\n|  \n|____\n",
"_____\n|   |\n|   O\n|  /|\\\n|  /\n|____\n",
"_____\n|   |\n|   O\n|  /|\\\n|  /\\\n|____\n" };

/*
_____
|   |
|   O
|  /|\
|  /\
|____

*/

int main()
{
	bool playing = true;
	while (playing)
	{
		/////////////////////////////////////////////////////////////////////////////////// set-up
		// generate random seed (once each time the program runs)
		srand(time(0));

		// choose & set solution from list of word options
		// TODO: import from text doc
		std::string current_solution = choose_solution(cool_animals);

		// find unique characters in solution
		std::vector<char> unique_chars_in_solution;
		find_unique_chars(current_solution, unique_chars_in_solution);

		// prepare guess variables
		std::vector<char> guesses;
		std::vector<char> correct_guesses;

		// draw spaces, pole
		draw_man(men, correct_guesses.size(), guesses.size());
		draw_spaces(current_solution, correct_guesses);

		bool game_over = false;
		while (!game_over) ////////////////////////////////////////////////////////////// game
		{
			std::cout << men.size() - 1 - (guesses.size() - correct_guesses.size()) << " guess(es) remaining.\n";

			// prepare to receive a guess from the user
			std::string new_guess = "";
			std::cout << "Guess a letter: ";

			// input validation
			bool validated = false;
			while (!validated)
			{
				// receive input
				new_guess = request_input();

				// check if user straight up nailed it (guessed correct word)
				if (correct_answer(new_guess, current_solution)) validated = true;

				// otherwise input must be a) a letter, and b) not a letter previously guessed
				else if (!valid_input(new_guess)) clear_input();
				else if (previous_guess(new_guess, guesses)) clear_input();
				else validated = true;
			}

			// check correct answer again outside validation loop so we can break out of the game loop
			if (correct_answer(new_guess, current_solution))
			{
				draw_man(men, correct_guesses.size(), guesses.size());
				draw_spaces(current_solution, unique_chars_in_solution);
				std::cout << "You nailed it!\n";
				game_over = true;
				break;
			}
			// otherwise check if guess is correct
			else if (check_guess(new_guess[0], unique_chars_in_solution))
			{
				std::cout << "\n\nNice!\n";
				correct_guesses.push_back(new_guess[0]);
			}
			else
			{
				std::cout << "\n\nIncorrect!\n";
			}

			// whether or not the guess is correct, add it to this vector to keep track of all guesses
			guesses.push_back(new_guess[0]);

			// draw the updated man and spaces
			draw_man(men, correct_guesses.size(), guesses.size());
			draw_spaces(current_solution, correct_guesses);

			// check to see if the player won or lost
			int win_state = check_winstate(men.size() - 1, correct_guesses.size(), guesses.size(), unique_chars_in_solution.size());
			switch (win_state)
			{
				case 0: // keep playing; continue the loop
					continue;
				case 1: // win state
					std::cout << "You win!\n";
					game_over = true;
					break;
				case 2: // lose state
					std::cout << "Game over! The word was '" << current_solution << "'.\n";
					game_over = true;
					break;
				default:
					continue;
			}
		}

		/////////////////////////////////////////////////////////////////////////////////// play again?
		
		std::string play_again_input = "";
		std::cout << "Would you like to play again?\n";

		bool decided = false;
		while (!decided) 
		{
			// receive input
			play_again_input = request_input();

			// check if input is found in list of negatives; break out of both loops
			if (input_in_list(play_again_input, negatives))
			{
				playing = false;
				decided = true;
			}
			// check if input is found in list of affirmatives; break out of deciding loop
			else if (input_in_list(play_again_input, affirmatives)) 
			{ 
				playing = true;
				decided = true; 
			}
			else // input was not valid, try again
			{
				std::cout << "Please enter 'yes' or 'no'.\n";
				clear_input();
			}
		}
	}
	return 0;
}