/*  blackjack.cpp
    
    Program to play simplified Blackjack.
    Create function playBlackjack() to accept shuffled cards as a 
    parameter, implement rules defined below (use other functions as 
    necessary), return true if player wins, false if loses.

    Rules:
    - Dealer starts with one card
    - Player starts with two cards
    - Player goes first
    - Player can repeatedly "hit" or "stand"
    - If player "stands", turn is over and score is calculated based off
      cards they've been dealt
    - If player "hits", get another card whose value is added to their
      total score
    - Ace counted as an 11 here (usually 1 or 11 depending)
    - If player scores > 21, go bust and lose
    - Dealer goes after player
    - Dealer repeatedly draws until they reach a score of 17 or more, at
      which point they stand
    - If dealer goes over score of 21, they bust and player wins 
    - Else, if player score > dealer score, player wins
    - Draws and player score < dealer score are considered losses.

    Only keep track of sum of card values, not the specific cards dealt.
*/

#include <iostream>
#include <array>
#include <algorithm>
#include <random>
#include <cassert>
#include <vector>
#include <ctime>

enum class Suit
{
    Clubs,
    Diamonds,
    Hearts,
    Spades,

    n_suits,
};

enum class Rank
{
    rank_2,
    rank_3,
    rank_4,
    rank_5,
    rank_6,
    rank_7,
    rank_8,
    rank_9,
    rank_10,
    rank_J,
    rank_Q,
    rank_K,
    rank_A,

    n_ranks,
};

struct Card
{
    Suit suit{};
    Rank rank{};
};

void printCard(const Card& card)
{
    switch(card.rank)
    {
        case Rank::rank_2:      std::cout << '2'; break;
        case Rank::rank_3:      std::cout << '3'; break;
        case Rank::rank_4:      std::cout << '4'; break;
        case Rank::rank_5:      std::cout << '5'; break;
        case Rank::rank_6:      std::cout << '6'; break;
        case Rank::rank_7:      std::cout << '7'; break;
        case Rank::rank_8:      std::cout << '8'; break;
        case Rank::rank_9:      std::cout << '9'; break;
        case Rank::rank_10:     std::cout << "10"; break;
        case Rank::rank_J:      std::cout << 'J'; break;
        case Rank::rank_Q:      std::cout << 'Q'; break;
        case Rank::rank_K:      std::cout << 'K'; break;
        case Rank::rank_A:      std::cout << 'A'; break;

        default:                std::cout << '?'; break;
    }   
    switch(card.suit)
    {
        case Suit::Clubs:       std::cout << 'C'; break;
        case Suit::Diamonds:    std::cout << 'D'; break;
        case Suit::Hearts:      std::cout << 'H'; break;
        case Suit::Spades:      std::cout << 'S'; break;

        default:                std::cout << '?'; break;
    }   
}

using Deck = std::array<Card, 52>;
using Index = Deck::size_type;
Deck createDeck()
{

    Deck deck{};
    Index index{ 0 };

    for (int suit{ 0 }; suit < static_cast<int>(Suit::n_suits); ++suit)
    {
        for (int rank{ 0 }; rank < static_cast<int>(Rank::n_ranks); ++rank)
        {
            deck[index].suit = static_cast<Suit>(suit);
            deck[index].rank = static_cast<Rank>(rank);
            ++index;
        }
    }

    return deck;
}

void printDeck(const Deck& deck)
{
    for(const auto& card : deck)
    {
        printCard(card);
        std::cout << ' ';
    }
    std::cout << std::endl;
}

void shuffleDeck(Deck& deck)
{
    // mt static so only seeded once
    static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

    std::shuffle(deck.begin(), deck.end(), mt);
}

int getCardValue(Card& card)
{
    switch(card.rank)
    {
        case Rank::rank_2:      return 2; 
        case Rank::rank_3:      return 3; 
        case Rank::rank_4:      return 4; 
        case Rank::rank_5:      return 5; 
        case Rank::rank_6:      return 6; 
        case Rank::rank_7:      return 7; 
        case Rank::rank_8:      return 8; 
        case Rank::rank_9:      return 9; 
        case Rank::rank_10:     return 10;
        case Rank::rank_J:      return 10; 
        case Rank::rank_Q:      return 10; 
        case Rank::rank_K:      return 10; 
        case Rank::rank_A:      return 11; 

        default:
            assert(false && "Card rank not in enum class Rank");
            return 0;
    }   
}

bool hitOrStand()
{
    while (true)
    {
        char action{};
        std::cout << "(h) to hit, or (s) to stand: ";
        std::cin >> action;

        switch (action)
        {
            case 'h':   return true;
            case 's':   return false;
        }
    }
}

void printGameStatus(int dealer, int player)
{
    std::cout << "Dealer sum: " << dealer << std::endl;
    std::cout << "Player sum: " << player << std::endl;
}

bool playBlackjack(Deck& deck)
{
    int dealer{ getCardValue(deck[0]) }; // First card is dealer's
    int player{ getCardValue(deck[1]) + getCardValue(deck[2]) };
    // Next two cards are player's
    int card_no{ 3 };

    printGameStatus(dealer, player);

    bool action{ hitOrStand() }; // Hit (true) or Stand (false)

    while (action == true)
    {
        player = player + getCardValue(deck[card_no]);
        ++card_no;
        printGameStatus(dealer, player);
        action = hitOrStand();
    }
    
    constexpr int blackjack{ 21 };
    constexpr int dealer_lim{ 17 };

    if (player > blackjack)
        return false; // Player lose
    else
    {
        while (dealer <= dealer_lim)
        {
            dealer = dealer + getCardValue(deck[card_no]);
            ++card_no;
            printGameStatus(dealer, player);
        }
        
        if (dealer > blackjack)
            return true; // Player win
        else if (player > dealer)
            return true; // Player win
        else
            return false; // Player lose
    }

    
}

int main()
{
    // Initialise deck
    auto deck{ createDeck() };
    // Shuffle deck
    shuffleDeck(deck);

    // Play blackjack
    bool player_win{ playBlackjack(deck) };

    if (player_win == true)
        std::cout << "Congratualtions! You win!\n";
    else
        std::cout << "Unlucky! You lose!\n";

    return 0;
}
