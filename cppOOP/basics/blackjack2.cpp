/*  blackjack2.cpp
    
    Program to play simplified Blackjack coded using classes.
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

constexpr int blackjack{ 21 };
constexpr int dealer_lim{ 17 };

class Card
{
public:
    enum Suit
    {
        Clubs,
        Diamonds,
        Hearts,
        Spades,
    
        n_suits,
    };
    
    enum Rank
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

private:
    Suit m_suit{};
    Rank m_rank{};

public:
    Card() = default;

    Card(Rank rank, Suit suit) : m_rank{ rank }, m_suit{ suit }
    {}

    void print() const
    {
        switch(m_rank)
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
        switch(m_suit)
        {
            case Suit::Clubs:       std::cout << 'C'; break;
            case Suit::Diamonds:    std::cout << 'D'; break;
            case Suit::Hearts:      std::cout << 'H'; break;
            case Suit::Spades:      std::cout << 'S'; break;
    
            default:                std::cout << '?'; break;
        }   
    }
    
    int value() const
    {
        switch(m_rank)
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
};

using FullDeck = std::array<Card, 52>;
using Index = FullDeck::size_type;

class Deck
{
private:
    FullDeck m_deck{};
    Index m_cardIndex{ static_cast<Index>(0) };

public:
    Deck()
    {
        Index index{ 0 };

        for (int suit{ 0 }; suit < static_cast<int>(Card::n_suits); ++suit)
        {
            for (int rank{ 0 }; rank < static_cast<int>(Card::n_ranks); ++rank)
            {
                m_deck[index] = { static_cast<Card::Rank>(rank), static_cast<Card::Suit>(suit) };
                ++index;
            }
        }
    }

    void print() const
    {
        for(const auto& card : m_deck)
        {
            card.print();
            std::cout << ' ';
        }
        std::cout << std::endl;
    }

    void shuffle()
    {
        // mt static so only seeded once
        static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    
        std::shuffle(m_deck.begin(), m_deck.end(), mt);
        
        // reset card m_cardIndex to start at top of deck again
        m_cardIndex = static_cast<Index>(0);
    }

    const Card& dealCard()
    {
        assert(m_cardIndex < m_deck.size() && "Reached end of deck\n");

        return m_deck[m_cardIndex++];
    }
};

class Player
{
private:
    int m_score{ 0 };
public:
    int drawCard(Deck& deck)
    {
        int value = deck.dealCard().value();
        m_score += value;

        return value;
    }

    int score() const
    {
        return m_score;
    }

    bool isBust() const
    {
        return (m_score > blackjack);
    }
};

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

void printGameStatus(Player& dealer, Player& player)
{
    std::cout << "Dealer sum: " << dealer.score() << std::endl;
    std::cout << "Player sum: " << player.score() << std::endl;
}

bool playerTurn(Deck& deck, Player& player)
{
    if (player.isBust())
    {
        std::cout << "You went bust!\n";
        return false;
    }
    else
    {
        auto playerCard{ player.drawCard(deck) };
        std::cout << "You were dealt a " << playerCard << ". Your current score is " << player.score() << '\n';
        
        if (player.isBust())
        {
            std::cout << "You went bust!\n";
            return false;
        }
        else
        {
            return hitOrStand();
        }
    }
}

void dealerTurn(Deck& deck, Player& dealer)
{
    while (dealer.score() <= dealer_lim)
    {
        auto dealerCard{ dealer.drawCard(deck) };
        std::cout << "The dealer drew a " << dealerCard << ". Their score is now " << dealer.score() << '\n';

        if (dealer.isBust())
        {
            std::cout << "The dealer went bust!\n";
            break;
        }
    }

}

bool playBlackjack(Deck& deck)
{
    Player dealer{};
    dealer.drawCard(deck);

    Player player{};
    player.drawCard(deck);
    player.drawCard(deck);

    printGameStatus(dealer, player);

    bool action{ hitOrStand() }; // Hit (true) or Stand (false)

    while (action == true)
    {
        action = playerTurn(deck, player);
    }
    

    if (player.isBust())
        return false; // Player lose
    else
    {
        dealerTurn(deck, dealer);

        if (dealer.isBust() or player.score() > dealer.score())
            return true; // Player win
        else
            return false; // Player lose
    }

    
}

int main()
{
//  Test Card class
//  const Card cardQueenHearts{ Card::rank_Q, Card::Hearts };
//  cardQueenHearts.print();
//  std::cout << cardQueenHearts.value() << '\n';

//  Test Deck class
//  Deck deck{};
//  deck.shuffle();
//  deck.print();
//  std::cout << deck.dealCard().value() << '\n' << deck.dealCard().value() << '\n';

//  Test Player class
//  Deck deck{};
//  deck.shuffle();

//  Player player{};
//  Player dealer{};

///*  C++ doesn't guarantee order of expression evaluation so don't use drawCard and score in same expression
// */
//  int playerCard{ player.drawCard(deck) }; 
//  std::cout << "Card value: " << playerCard << '\n';
//  std::cout << "Player: " << player.score() << '\n';
//  
//  int dealerCard{ dealer.drawCard(deck) };
//  std::cout << "Card value: " << dealerCard << '\n';
//  std::cout << "Dealer: " << dealer.score() << '\n';


    // Initialise deck
    Deck deck{};
    // Shuffle deck
    deck.shuffle();

    // Play blackjack
    bool player_win{ playBlackjack(deck) };

    if (player_win == true)
        std::cout << "Congratualtions! You win!\n";
    else
        std::cout << "Unlucky! You lose!\n";

    return 0;
}
