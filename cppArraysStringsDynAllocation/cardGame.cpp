/*  cardGame.cpp
    
    Program setting up basics of a card game:

    - Create enumerations for card ranks + suits (not used to index 
      arrays)
    - Create struct called Card to contain rank and suit
    - Create function printCard() taking const Card as parameter and 
      prints card rank and suit as 2-letter code (e.g. jack of spades
      would print as JS)
    - Create a std::array to represent deck of cards
    - Create function createDeck to initialise std::array with one of
      each card.
    - Call createDeck from main
    - Create function printDeck() to take deck as a const ref and 
      prints cards in deck using for-each loop.
    - Create function shuffleDeck to shuffle cards using std::shuffle
    - Update main to shuffle deck and print
    - Create function getCardValue() to return value of a card 
      (J, Q, K = 10, A = 11)
*/

#include <iostream>
#include <array>
#include <algorithm>
#include <random>
#include <cassert>

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
    static std::mt19937 mt;

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

int main()
{
    auto deck{ createDeck() };
    printDeck(deck);

    shuffleDeck(deck);
    printDeck(deck);

    return 0;
}
