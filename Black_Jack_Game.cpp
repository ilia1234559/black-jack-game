#include <iostream>
#include <array>
#include <algorithm>
#include <ctime>
using namespace std;

enum class BlackJackResult
{
	BLACKJACK_DEALER_WIN,
	BLACKJACK_PLAYER_WIN,
	BLACKJACK_DROW
};

enum class Suit
{
	CLUBS,			//кресты
	DIAMONDS,		//бубны
	HEARTS,			//червы
	SPADES,			//пики
	MAX_SUITE
};

enum class Number
{
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE,
	MAX_NUMBER
};

struct Card
{
	Number number;
	Suit suit;
};


string returnNumber(Number number)				
{
	switch (number)
	{
	case Number::TWO:
		return "2";
		break;
	case Number::THREE:
		return "3";
		break;
	case Number::FOUR:
		return "4";
		break;
	case Number::FIVE:
		return "5";
		break;
	case Number::SIX:
		return "6";
		break;
	case Number::SEVEN:
		return "7";
		break;
	case Number::EIGHT:
		return "8";
		break;
	case Number::NINE:
		return "9";
		break;
	case Number::TEN:
		return "10";
		break;
	case Number::JACK:
		return "J";
		break;
	case Number::QUEEN:
		return "Q";
		break;
	case Number::KING:
		return "K";
		break;
	case Number::ACE:
		return "A";
		break;
	default:
		return "ERROR";
		break;
	}
}			
string returnSuit(Suit suit)
{
	switch (suit)
	{
	case Suit::CLUBS:
		return "C";
		break;
	case Suit::DIAMONDS:
		return "D";
		break;
	case Suit::HEARTS:
		return "H";
		break;
	case Suit::SPADES:
		return "S";
		break;
	default:
		return "ERROR";
		break;
	}
}
void printCard(Card &card) //печать одной карты
{
	cout << returnNumber(card.number) << returnSuit(card.suit) << ' ';
}



void printDeck(array<Card, 52> &deck) // печать всей деки
{
	for (Card &card : deck)
	{
		printCard(card);	
	}
	cout << '\n';
}

void swapCard(Card &card1, Card &card2)
{
	swap(card1.number, card2.number);
	swap(card1.suit, card2.suit);
}

int getRandomNumber(const int &min, const int &max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void shuffleDeck(array<Card, 52> &deck)			//перетасовка
{
	int current = getRandomNumber(0, 51);
	for (int i = 0; i < 52;++i)
	{
		int nextIndex = getRandomNumber(0, 51);
		swapCard(deck[current], deck[nextIndex]);
		current = nextIndex;
	}
}

int getCardValue(const Card &card)
{
	switch (card.number)
	{
	case Number::TWO:			return 2;
	case Number::THREE:			return 3;
	case Number::FOUR:			return 4;
	case Number::FIVE:			return 5;
	case Number::SIX:			return 6;
	case Number::SEVEN:			return 7;
	case Number::EIGHT:			return 8;
	case Number::NINE:			return 9;
	case Number::TEN:			return 10;
	case Number::JACK:			return 10;
	case Number::QUEEN:			return 10;
	case Number::KING:			return 10;
	case Number::ACE:			return 11;
	}
	return 0;
}

bool getPlayerChoice()
{
	cout << "(h) to hit or (s) to stand: ";
	char choice;
	while (1)
	{
		cin >> choice;
		cin.ignore(32767, '\n');
		if (choice != 'h' && choice != 's')
			cout << "(h) to hit or (s) to stand! ";
		else if (choice == 'h')
			return true;
		else if (choice == 's')
			return false;
	}
}

BlackJackResult playBlackJack(array<Card, 52> &deck)
{
	shuffleDeck(deck);
	Card* cardPtr = &deck[0];
	int playerResult = 0;
	int dealerResult = 0;
	dealerResult = getCardValue(*cardPtr++);
	playerResult = getCardValue(*cardPtr++) + getCardValue(*cardPtr++);
	while (1)
	{
		cout << "your score is " << playerResult << endl;
  		if (playerResult > 21)
			return BlackJackResult::BLACKJACK_DEALER_WIN;
		if (playerResult == 21)
			return BlackJackResult::BLACKJACK_PLAYER_WIN;
		if (getPlayerChoice())                                        /////////////////////true - hit, false - stand
		{
			playerResult += getCardValue(*cardPtr++);
		}
		else
			break;
	}
	while (dealerResult < 17)
	{
		cout << "the Dealer now has " << dealerResult << endl;
		system("pause");
		dealerResult += getCardValue(*cardPtr++);
	}
	cout << "the Dealer now has " << dealerResult << endl;

	if (dealerResult > 21)
		return BlackJackResult::BLACKJACK_PLAYER_WIN;

	if (dealerResult > playerResult)
		return BlackJackResult::BLACKJACK_DEALER_WIN;
	else if (dealerResult == playerResult)
		return BlackJackResult::BLACKJACK_DROW;
	else
		return BlackJackResult::BLACKJACK_PLAYER_WIN;
}


int main()
{
	srand(static_cast<unsigned int>(time(0)));
	rand();
	array<Card, 52> deck;
	int card = 0;
	for (int suit = 0; suit < static_cast<int>(Suit::MAX_SUITE); ++suit)					//присваиваем значения картам
		for (int number = 0; number < static_cast<int>(Number::MAX_NUMBER); ++number)
		{
			deck[card].number = static_cast<Number>(number);
			deck[card].suit = static_cast<Suit>(suit);
			++card;
		}
	shuffleDeck(deck);
	switch (playBlackJack(deck))
	{
	case BlackJackResult::BLACKJACK_DEALER_WIN: cout << "You lose!\n"; break;
	case BlackJackResult::BLACKJACK_PLAYER_WIN: cout << "You win!\n"; break;
	case BlackJackResult::BLACKJACK_DROW: cout << "DROW!\n"; break;
	}
	system("pause");
	return 0;
}
