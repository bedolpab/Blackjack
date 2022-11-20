#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>

#define SIMULATIONS 100
#define deckSize 52

using namespace std;

void makeDeck(vector<int> &deck);
void printDeck(vector<int> &deck);
void shuffleDeck(vector<int> &deck);
void giveCard(vector<int> &deck, vector<int> &hand);
int deckSum(vector<int> &hand);

int main()
{
    std::vector<int> deck;
    std::vector<int> ai_hand;
    std::vector<int> dealer_hand;

    // Seed random
    srand(time(NULL));

    int ai_score = 0;
    int dealer_score = 0;
    int total_games_played = 0;

    while (total_games_played < SIMULATIONS)
    {
        cout << "Current game: " << total_games_played << "\n" << endl;
        makeDeck(deck);
        shuffleDeck(deck);
        cout << "Deck created --"
             << endl;
        printDeck(deck);

        giveCard(deck, ai_hand);
        giveCard(deck, dealer_hand);
        giveCard(deck, ai_hand);
        giveCard(deck, dealer_hand);

        cout << "Giving cards -- "
             << endl;
        printDeck(deck);

        cout << "AI hand -- " << endl;
        auto aiHandSize = deckSum(ai_hand);
        cout << "Sum: " << aiHandSize << endl;
        cout << "\n"
             << endl;
        printDeck(ai_hand);

        cout << "Dealer hand -- " << endl;
        auto dealer_handSize = deckSum(dealer_hand);
        cout << "Sum: " << dealer_handSize << endl;
        cout << "\n"
             << endl;
        printDeck(dealer_hand);

        if (aiHandSize == 21)
        {
            cout << "Win" << endl;
        }
        else if (aiHandSize < 12)
        {
            for (int i = 0; i < ai_hand.size(); i++)
            {
                if (ai_hand[i] == 11)
                {
                    ai_hand[i] = 1;
                    break;
                }
            }
            while (aiHandSize < 12)
            {
                giveCard(deck, ai_hand);
                aiHandSize = deckSum(ai_hand);
                cout << "AI hand -- " << endl;
                cout << aiHandSize << endl;
                cout << "\n"
                     << endl;
                printDeck(ai_hand);
            }
        }
        else
        {
            cout << "AI Stay" << endl;
        }

        if (dealer_handSize < 16)
        {
            for (int i = 0; i < dealer_hand.size(); i++)
            {
                if (dealer_hand[i] == 11)
                {
                    dealer_hand[i] = 1;
                    break;
                }
            }
            while (dealer_handSize < 16)
            {
                giveCard(deck, dealer_hand);
                dealer_handSize = deckSum(dealer_hand);
                cout << "Dealer hand -- " << endl;
                cout << dealer_handSize << endl;
                cout << "\n"
                     << endl;
                printDeck(dealer_hand);
            }
        }
        else
        {
            cout << "Dealer Stay" << endl;
        }

        if (aiHandSize > 21)
        {
            cout << "AI Bust\n"
                 << endl;
            cout << "Dealer Win\n"
                 << endl;
            dealer_score++;
        }
        else if (dealer_handSize > 21)
        {
            cout << "Dealer Bust" << endl;
            cout << "AI Win\n"
                 << endl;
            ai_score++;
        }
        else if (aiHandSize > dealer_handSize)
        {
            cout << "AI Win" << endl;
            ai_score++;
        }
        else if (aiHandSize < dealer_handSize)
        {
            cout << "Dealer Win" << endl;
            dealer_score++;
        }
        else
        {
            cout << "Draw" << endl;
        }

        cout << "\n"
             << endl;
        cout << "AI Score: " << ai_score << endl;
        cout << "Dealer Score: " << dealer_score << endl;

        // clear deck, ai_hand, dealer_hand
        deck.clear();
        ai_hand.clear();
        dealer_hand.clear();

        total_games_played++;
    }

    if(ai_score > dealer_score)
    {
        cout << "Simulation winner - AI - " << ai_score << endl;
    }
    else if(ai_score < dealer_score)
    {
        cout << "Simulation winner - Dealer - " << dealer_score << endl;
    }
    else
    {
        cout << "Simulation Draw" << endl;
    }

    return 0;
}

// Function that passes in the vector 'deck'
void makeDeck(vector<int> &deck)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 1; j < 14; j++)
        {
            if (j == 1)
            {
                deck.push_back(11);
            }
            else if (j > 10)
            {
                deck.push_back(10);
            }
            else
            {
                deck.push_back(j);
            }
        }
    }
}

void printDeck(vector<int> &deck)
{
    for (int i = 0; i < deck.size(); i++)
    {
        std::cout << deck[i] << " ";
    }
    cout << "\n"
         << endl;
}

void shuffleDeck(vector<int> &deck)
{
    random_shuffle(deck.begin(), deck.end());
}

void giveCard(vector<int> &deck, vector<int> &hand)
{
    hand.push_back(deck.back());
    deck.pop_back();
}

int deckSum(vector<int> &hand)
{
    auto sum = reduce(hand.begin(), hand.end());
    return sum;
}