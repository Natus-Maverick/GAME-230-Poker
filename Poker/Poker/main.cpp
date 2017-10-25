#include <iostream>
#include <string>
#include <ctime>

using namespace std;

int cash = 10;
string suits[4] = { "Spades", "Diamonds","Clubs","Hearts" };
int values[13] = { 2,3,4,5,6,7,8,9,10,11,12,13,14 };
string choice[5] = { "A: ","B: ","C: ","D: ","E: " };
string in;


struct card
{
	int value;
	string suit;
	card* next;
};

struct deck
{
	card* head;
};

deck* create_linked_list()
{
	deck* d = new deck;
	d->head = nullptr;
	return d;
}

void add_first(deck* d, card cc)
{
	card* c = new card;
	c->value = cc.value;
	c->suit = cc.suit;
	c->next = d->head;
	d->head = c;
}

void add_last(deck* d, card cc)
{
	if (d->head == nullptr)
	{
		add_first(d, cc);
		return;
	}

	card* temp = d->head;
	while (temp->next != nullptr)
		temp = temp->next;

	card* c = new card;
	c->value = cc.value;
	c->suit = cc.suit;
	c->next = nullptr;
	temp->next = c;
}

void print_items(deck* d)
{
	card* c = d->head;
	while (c != nullptr)
	{
		if (c->value <= 10)
		{
			cout << c->value << " of " << c->suit;
		}
		else if (c->value == 11)
		{
			cout << "Jack of " << c->suit;
		}
		else if (c->value == 12)
		{
			cout << "Queen of " << c->suit;
		}
		else if (c->value == 13)
		{
			cout << "King of " << c->suit;
		}
		else if (c->value == 14)
		{
			cout << "Ace of " << c->suit;
		}
		if (c->next != nullptr)
		{
			cout << ", ";
		}
		else
		{
			cout << "\n\n";
		}
		c = c->next;
	}
}

int count_items(deck* d)
{
	int count = 0;
	card* c = d->head;
	while (c != NULL)
	{
		++count;
		c = c->next;
	}
	return count;
}

card get_item(deck* d, int index)
{
	card* c = d->head;
	while (index > 0)
	{
		c = c->next;
		--index;
	}
	card re =
	{
		c->value,
		c->suit
	};
	return re;
}

void remove_first(deck* d)
{
	if (d->head == nullptr)
	{
		cout << "Error!" << endl;
		return;
	}

	card* c = d->head;
	d->head = c->next;
	delete c;
}

void remove_item(deck* d, int index)
{
	if (index == 0)
	{
		remove_first(d);
		return;
	}

	card* temp = d->head;
	while (index > 1)
	{
		temp = temp->next;
		--index;
	}

	card* c = temp->next;
	temp->next = c->next;
	delete c;
}

void del_linked_list(deck* d)
{
	card* c = d->head;
	while (c != nullptr)
	{
		card* temp = c;
		c = c->next;
		delete temp;
	}

	delete d;
}

void new_deck(deck* d)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			card temp =
			{
				values[j],
				suits[i],
				nullptr
			};
			add_last(d, temp);
		}
	}
}

void remain(deck* d)
{
	cout << "The deck contains " << count_items(d) << " cards.\n" << endl;
	print_items(d);
}

void draw(card array[5], deck* d)
{
	for (int i = 0; i < 5; i++)
	{
		int randomvalue = rand() % (52 - i);
		card temp = get_item(d, randomvalue);
		remove_item(d, randomvalue);
		array[i] = temp;
	}
}

int pay()
{
	int rest = --cash;
	cout << "You pay $1 and now have $" << rest << endl;
	return rest;
}

int main() {
	cout << "You currently have $" << cash << "\n" << endl;
	cash = pay();
	//New deck
	deck* d = create_linked_list();
	new_deck(d);
	srand(time(0));
	/*for (int i = 0; i < 52; i++)
	{
		int randomvalue = rand() % (52 - i);
		card temp = get_item(d, randomvalue);
		remove_item(d, randomvalue);
		add_last(d, temp);
	}*/
	card hand[5];
	draw(hand, d);
	cout << "Your hand contains:" << endl;
	for (int i = 0; i < 5; i++)
	{
		if (hand[i].value <= 10)
		{
			cout << choice[i] << hand[i].value << " of " << hand[i].suit << endl;
		}
		else if (hand[i].value == 11)
		{
			cout << choice[i] << "Jack of " << hand[i].suit << endl;
		}
		else if (hand[i].value == 12)
		{
			cout << choice[i] << "Queen of " << hand[i].suit << endl;
		}
		else if (hand[i].value == 13)
		{
			cout << choice[i] << "King of " << hand[i].suit << endl;
		}
		else if (hand[i].value == 14)
		{
			cout << choice[i] << "Ace of " << hand[i].suit << endl;
		}		
	}
	cout << "\nThe deck contains " << count_items(d) << " cards.\n" << endl;
	cout << "OPTIONS..." << endl;
	cout << "Type the letters for the cards you wish to keep. (i.e., \"acd\")" << endl;
	cout << "Type \"deck\" to view the cards remaining in the deck." << endl;
	cout << "Type \"none\" to discard all cards in your hand." << endl;
	cout << "Type \"all\" to keep all cards in your hand." << endl;
	cout << "Type \"exit\" to exit the game." << endl;
	cout << "Type \"swap\" to CHEAT and swap a card in your hand with one in the deck.(Debug Feature)" << endl;
	cout << "YOUR CHOICE: ";
	cin >> in;


	return 0;
}
