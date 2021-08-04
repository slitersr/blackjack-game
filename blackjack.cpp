#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>


class Card
{
private:
	char temp_card; 
	int temp_value; 
	int temp_suite; 
	std::string temp_nameSuite;
	bool temp_given;
	int assignCardValue();

public:
	Card(char, int);
	Card(const Card&);
	int getCardValue() const;
	int getCardSuite() const;
	std::string getName() const;
	bool getIfGiven() const;
	char getCard() const;
	void setGiven(bool x);
	void nameCard();
};



int Card::assignCardValue()
{
	if(temp_card == 'A')
	{
		return 11;
		
	}
	
	else if (temp_card == 'Q' || temp_card == 'T' || temp_card == 'J') 
	{
		return 10;
	}
	else 
	{
		return (temp_card - '0');
	}
}



Card::Card(char cardValue, int suite)
{
	temp_card = cardValue;
	temp_value = assignCardValue();
	temp_suite = suite;
	temp_given = false;
}



Card::Card(const Card& card)
{
	temp_card = card.getCard();
	temp_value = card.getCardValue();
	temp_suite = card.getCardSuite();
	temp_nameSuite = card.getName();
	temp_given = card.getIfGiven();
}



int Card::getCardValue() const
{ 
	return temp_value; 
}



int Card::getCardSuite() const
{ 
	return temp_suite; 
}



std::string Card::getName() const
{ 
	return temp_nameSuite; 
}



bool Card::getIfGiven() const
{ 
	return temp_given; 
}



char Card::getCard() const
{ 
	return temp_card; 
}



void Card::setGiven(bool x)
{ 
	temp_given = x; 
}



void Card::nameCard()
{

	switch(temp_suite)
	{
		case 0: 
			temp_nameSuite = "Spades" ; 
			break;

		case 1: 
			temp_nameSuite = "Clubs" ; 
			break;
		
		case 2: 
			temp_nameSuite = "Hearts" ; 
			break;
		
		case 3: 
			temp_nameSuite = "Diamonds";
	}
	if(temp_card == 'A')
	{
		std::cout << "Ace";
	} 
	else if (temp_card == 'J')
	{ 
		std::cout << "Joker";
	}
	else if (temp_card == 'Q')
	{ 
		std::cout << "Queen";
	}
	else
	{ 
		std::cout << temp_value;
	}
	std::cout << " of " << temp_nameSuite << std::endl;
}




class Deck
{
private:
	std::vector<Card*> temp_deck;
public:
	Deck();
	void fillDeck();
	void shuffle() ;
	Card giveCard();
};



Deck::Deck()
{
	fillDeck();
	shuffle();
}



void Deck::fillDeck()
{
	for(int i = 1; i <= 12; ++i)
	{
		char c;
		switch(i)
		{
		case 1: 
		c = 'A'; 
		break;
		
		case 2: 
		c = '2'; 
		break;
		
		case 3: 
		c = '3'; 
		break;
		
		case 4: 
		c = '4'; 
		break;
		
		case 5: 
		c = '5'; 
		break;
		
		case 6: 
		c = '6'; 
		break;
		
		case 7: 
		c = '7'; 
		break;
		
		case 8: 
		c = '8'; 
		break;
		
		case 9: 
		c = '9'; 
		break;
		
		case 10: 
		c = 'T'; 
		break;
		
		case 11: 
		c = 'J'; 
		break;
		
		case 12: 
		c = 'Q';
		}	
		
		for(int n = 0; n <= 3; ++n)
		{
			temp_deck.push_back(new Card(c,n));
		}
	}
}



void Deck::shuffle()
{
	std::random_shuffle(temp_deck.begin(), temp_deck.end());
}



Card Deck::giveCard()
{
	for(int i = 0; i < temp_deck.size(); ++i)
	{
		if(!temp_deck[i]->getIfGiven())
		{
			temp_deck[i]->setGiven(1);
			return (*temp_deck[i]);
		}
	}
}



class Hand
{
private:
	std::vector<Card> temp_hand;

public:
	void initialize(Card, Card);
	void display();
	void displayAsDealer();
	void addCard(Card);
	int getNumOfCards();
	int getTotalVal();
};



void Hand::initialize(Card card1, Card card2)
{
	temp_hand.push_back(card1);
	temp_hand.push_back(card2);
}



void Hand::display()
{
	for(std::vector<Card>::iterator iter = temp_hand.begin(); iter != temp_hand.end(); (++iter))
	{
		iter->nameCard();
	}
}



void Hand::displayAsDealer()
{
	temp_hand[0].nameCard();
}



void Hand::addCard(Card card)
{
	std::cout << "\nTook out: ";
	card.nameCard();

	temp_hand.push_back(card);
}



int Hand::getTotalVal()
{
	int sum = 0;
	for(std::vector<Card>::iterator iter = temp_hand.begin();iter != temp_hand.end(); (++iter))
	{
		sum += iter->getCardValue();
	}
	for(std::vector<Card>::iterator iter = temp_hand.begin();iter != temp_hand.end(); (++iter))
	{
		if((iter->getCardValue() == 11) && (sum > 21))
		{
			sum = sum - 10;
		}
	}
	return sum;
}



int Hand::getNumOfCards()
{
	return temp_hand.size();
}



class Player
{
protected:
	Deck temp_deck;
	Hand temp_hand;
	bool temp_canGetCards;
	int score;

public:
	Player(Deck deck);
	void stay();
	void hitMe();
	void seeCards();
	int getScore() const;
	bool lose(int);
	bool Win();
};




Player::Player(Deck deck)
{
	temp_canGetCards = 1;
	temp_deck = deck;
	temp_hand.initialize(deck.giveCard(), deck.giveCard());
}



void Player::stay()
{
	temp_canGetCards = 0;
	score = temp_hand.getTotalVal();
}



void Player::hitMe()
{
	if(temp_canGetCards) 
	{
		temp_hand.addCard(temp_deck.giveCard());
	}
	else
	{ 
		std::cout << "You can't recieve any more cards." << std::endl;
	}
}



bool Player::lose(int bet)
{
	if(temp_hand.getTotalVal() > 21)
	{
		std::cout << "You broke passed 21. You lose.\n" << std::endl;
		std::cout << "Your total is: " << temp_hand.getTotalVal() << std::endl;
		std::cout << "\nYou lost $" << bet << std::endl;
		return true;
	}
	return false;
}



bool Player::Win()
{
	return (temp_hand.getTotalVal() == 21 && temp_hand.getNumOfCards() == 2);
}



void Player::seeCards()
{
	std::cout << "Your cards: \n";
	temp_hand.display();
}



int Player::getScore() const
{ 
	return score; 
}



class Dealer : public Player 
{
public:
	using Player::Player;
	void seeCard();
	void game(Player,int);
};



void Dealer::seeCard()
{
	std::cout << "\nDealer's cards: \n";
	temp_hand.displayAsDealer();
	std::cout << std::endl;
}



void Dealer::game(Player play,int bet)
{
	while(temp_hand.getTotalVal() <= 21)
	{
		std::cout << "Cards: \n";
		temp_hand.display();
		std::cout << std::endl;
		if(temp_hand.getTotalVal() > play.getScore() && temp_hand.getTotalVal() <= 21)
		{
			std::cout << "The dealer won!\n" << std::endl;
			std::cout << "Your total is: " << play.getScore() << std::endl;
			std::cout << "\nYou lost $" << bet << std::endl;
			return;
		}
		if(temp_hand.getTotalVal() == play.getScore())
		{
			std::cout << "It's a tie! House wins by default." << std::endl;
			std::cout << "\nYour total is: " << play.getScore() << std::endl;
			std::cout << "\nYou lost $" << bet << std::endl;
			return;
		}
		hitMe();
	}
	if(temp_hand.getTotalVal() > 21)
	{
		
		std::cout << "\nThe dealer broke past 21, You win!\n" << std::endl;;
		std::cout << "Your total is: " << play.getScore() << std::endl;
		std::cout << "\nYou won $" << bet*2 << std::endl;
		return;
	}
}




int Bet()
{
	int bet;
	std::cout << "How much do you wish to bet: " << std::endl;
	std::cin >> bet;
	return bet;
}


void showControls()
{
	
	std::cout << "\nControls: " << std::endl << "Press 1 to take another card." << std::endl;
	std::cout << "Press 2 to stay.\n" << std::endl;
}



int main()
{
	int temp_bet;
	int play = 1;
	
	do
	{
		srand(time(0));
		Deck deck;
		Player player(deck);
		Dealer dealer(deck);
		char x;
		bool bbreak = 0;
		
		std::cout << "\n\nBegin by pressing 0 to start game!" << std::endl;
		std::cin >> x;
		std::cout << std::endl;
		if(x == '0')
		{
			temp_bet = Bet();
			showControls();
			player.seeCards();
			dealer.seeCard();
			std::cout << "\n";
		}

		if(player.Win())
		{
			std::cout << "You won!\n" << std::endl;
			std::cout << "You won " << temp_bet*2 << " $" << std::endl;
		}
		else if (dealer.Win())
		{
			std::cout << "The dealer won!\n" << std::endl;
			std::cout << "You lost " << temp_bet << " $" << std::endl;
		}
		else
		{
			while(!player.lose(temp_bet))
			{
				std::cout << "Select an option: ";
				std::cin >> x;
				std::cout << std::endl;
				if(x == '1')
				{
					player.hitMe();
				}
				else if(x == '2')
				{
					player.stay();
					dealer.game(player,temp_bet);
					break;
				}
			}
		}
		std::cout << "\n\nPress 0 to quit or 1 to play again: ";
		std::cin >> play;
		
	}while(play == 1);
	
	
	return 0;
}