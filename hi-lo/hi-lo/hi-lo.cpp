#include <iostream>
#include <chrono>
#include <limits>

// Function to ignore the remaining characters in the input buffer
void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Function to handle the guessing logic
bool correctlyGuessed(int randomNumber)
{
    int guess{};
    constexpr int maxTries = 7;

    for (int tries = 1; tries <= maxTries; ++tries)
    {
        // Prompt for the user's guess
        while (true)
        {
            std::cout << "Guess #" << tries << ": ";
            if (!(std::cin >> guess))
            {
                std::cin.clear();
                ignoreLine();
                std::cout << "Invalid input. Please enter a number.\n";
            }
            else if (guess >= 1 && guess <= 100)
            {
                ignoreLine();
                break;
            }
            else
            {
                ignoreLine();
                std::cout << "Number out of range. Please enter a number from 1 to 100.\n";
            }
        }

        // Compare the guess with the random number
        if (guess < randomNumber)
        {
            std::cout << guess << " is too low.\n";
        }
        else if (guess > randomNumber)
        {
            std::cout << guess << " is too high.\n";
        }
        else
        {
            // Guessed correctly
            return true;
        }
    }

    // Ran out of tries
    std::cout << "Sorry, you lose. The correct number was " << randomNumber << ". Better luck next time!\n";
    return false;
}

// Pseudo-random number generator based on XOR shift algorithm
unsigned int prng()
{
    static unsigned long x{ static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()) };
    x ^= (x << 13);
    x ^= (x >> 17);
    x ^= (x << 5);
    return x & 0x7FFFFFFF;
}

int main()
{
    // Game introduction
    std::cout << "Let's play a game. I'm thinking of a number between 1 and 100. You have 7 tries to guess it.\n";

    while (true)
    {
        // Check if the user guessed correctly
        if (correctlyGuessed(prng() % 100 + 1))
        {
            std::cout << "Congratulations, you win!\n";
        }

        // Prompt to play again
        char playAgain{};
        while (true)
        {
            std::cout << "Would you like to play again (y/n)? ";
            std::cin >> playAgain;
            ignoreLine();

            // Input validation for play again prompt
            if (playAgain == 'y' || playAgain == 'n')
            {
                break;
            }
            else
            {
                std::cout << "Please enter 'y' for yes or 'n' for no.\n";
            }
        }

        // Check if the user wants to play again or exit the game
        if (playAgain == 'n')
        {
            std::cout << "Thank you for playing. Goodbye!\n";
            break;
        }
        else
        {
            std::cout << "Let's play again! I'm thinking of another number between 1 and 100!\n";
        }
    }
}