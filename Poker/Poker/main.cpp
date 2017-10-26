#include <iostream>
#include <string>
#include <ctime>
#include <algorithm>
#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif

using namespace std;

int cash;
string suits[4] = { "Spades", "Diamonds","Clubs","Hearts" };
int values[13] = { 2,3,4,5,6,7,8,9,10,11,12,13,14 };
string choice[5] = { "A: ","B: ","C: ","D: ","E: " };
string in;
int index[5];
int sorted[5];
bool over;


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

void print_hand(deck* h)
{
	card* c = h->head;
	int i = 0;
	while (c != nullptr)
	{
		if (c->value <= 10)
		{
			cout << choice[i] << c->value << " of " << c->suit << endl;
		}
		else if (c->value == 11)
		{
			cout << choice[i] << "Jack of " << c->suit << endl;
		}
		else if (c->value == 12)
		{
			cout << choice[i] << "Queen of " << c->suit << endl;
		}
		else if (c->value == 13)
		{
			cout << choice[i] << "King of " << c->suit << endl;
		}
		else if (c->value == 14)
		{
			cout << choice[i] << "Ace of " << c->suit << endl;
		}
		i++;
		c = c->next;
	}
}

void update_hand(deck* h, int kept)
{
	card* c = h->head;
	int i = 0;
	cout << "\nYou kept " << kept << " and drew " << 5 - kept << " cards.\n";
	cout << "Your hand now contains:\n";
	while (c != nullptr)
	{
		if (c->value <= 10)
		{
			cout << choice[i] << c->value << " of " << c->suit;
		}
		else if (c->value == 11)
		{
			cout << choice[i] << "Jack of " << c->suit;
		}
		else if (c->value == 12)
		{
			cout << choice[i] << "Queen of " << c->suit;
		}
		else if (c->value == 13)
		{
			cout << choice[i] << "King of " << c->suit;
		}
		else if (c->value == 14)
		{
			cout << choice[i] << "Ace of " << c->suit;
		}
		if (kept > 0)
		{
			cout << "(kept)\n";
			kept--;
		}
		else
		{
			cout << "\n";
		}
		i++;
		c = c->next;
	}
	cout << "\n";
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

void none(deck* h, deck* g) 
{
	while (count_items(h) > 0)
	{
		card tmp = get_item(h, 0);
		add_first(g, tmp);
		remove_first(h);
	}
}

void draw_one(deck* d, deck* h, deck* g)
{
	if (count_items(d) > 0)
	{
		int randomvalue = rand() % count_items(d);
		card temp = get_item(d, randomvalue);
		remove_item(d, randomvalue);
		add_last(h, temp);
	}
	else
	{
		while (count_items(g) > 0)
		{
			card tmp = get_item(g, 0);
			add_first(d, tmp);
			remove_first(g);
		}
		draw_one(d, h, g);
	}
}

void draw_new(deck* h, deck* d, deck* g)
{
	for (int i = 0; i < 5; i++)
	{
		draw_one(d, h, g);
	}
}

void drop(card c, deck* g)
{
	add_first(g, c);
}

void def_sort(deck* h)
{
	int i = 0;
	card* c = h->head;
	while(c != nullptr)
	{
		sorted[i] = c->value;
		i++;
		c = c->next;
	}
	sort(sorted, sorted+5);
}

void all(deck* h)
{
	update_hand(h, 5);
}

void swap(deck* h, deck* d)
{
	card hand;
	int ind = 0;
	char s;
	cout << "Enter the letter of the card in hand:";
	cin >> s;
	cin.clear();
	cin.ignore(10000, '\n');
	if (s != 'a' && s != 'b' && s != 'c' && s != 'd' && s != 'e')
	{
		cout << "\nInvalid hand card.\n\n";
		return;
	}
	int v;
	cout << "Enter the value of the card in the deck to swap with:";
	cin >> v;
	cin.clear();
	cin.ignore(10000, '\n');
	if (v >= 2 && v <= 14)
	{

	}
	else
	{
		cout << "\nInvalid card value.\n\n";
		return;
	}
	string st;
	cout << "Enter the suit (c,d,h,s) of the card in the deck to swap with:";
	cin >> st;
	cin.clear();
	cin.ignore(10000, '\n');
	if (st == "c")
	{
		st = "Clubs";
	}
	else if (st == "d")
	{
		st = "Diamonds";
	}
	else if (st == "h")
	{
		st = "Hearts";
	}
	else if (st == "s")
	{
		st = "Spades";
	}
	else
	{
		cout << "\nInvalid card suit.\n\n";
		return;
	}
	card* c = d->head;
	while (c != nullptr)
	{
		if (c->value == v)
		{
			if (c->suit == st)
			{
				if (s == 'a')
				{
					ind = 0;					
				}
				else if (s == 'b')
				{
					ind = 1;
				}
				else if (s == 'c')
				{
					ind = 2;
				}
				else if (s == 'd')
				{
					ind = 3;
				}
				else if (s == 'e')
				{
					ind = 4;
				}
				hand = get_item(h, ind);
				card* hc = h->head;
				while (ind > 0)
				{
					hc = hc->next;
					--ind;
				}
				hc->value = v;
				hc->suit = st;
				c->value = hand.value;
				c->suit = hand.suit;
			}
		}
		c = c->next;
	}
	cout << "\nInvalid deck card.\n\n";
	return;
}

void check(deck* h)
{
	def_sort(h);
	card* c = h->head;
	while (c->next != nullptr)
	{
		if (c->suit != c->next->suit)
		{
			break;
		}
		c = c->next;
	}
	if (c->next != nullptr)
	{
		if ((sorted[0] == sorted[1] && sorted[3] == sorted[4])|| (sorted[0] == sorted[1] && sorted[1] != sorted[2] && sorted[2] == sorted[3]) || (sorted[1] == sorted[2] && sorted[2] != sorted[3] && sorted[3] == sorted[4]))
		{
			cash += 2;
			cout << "You got Two pair! You earned $2\nYou now have$" << cash << endl;
		}
		else if (sorted[0] == sorted[2] || sorted[1] == sorted[3] || sorted[2] == sorted[4])
		{
			if (sorted[0] == sorted[3] || sorted[1] == sorted[4])
			{
				cash += 25;
				cout << "You got Four of a kind! You earned $25\nYou now have$" << cash << endl;
			}
			else if ((sorted[0] == sorted[2]) && sorted[3] == sorted[4] || (sorted[2] == sorted[4] && sorted[0] == sorted[1]))
			{
				cash += 9;
				cout << "You got Full House! You earned $9\nYou now have$" << cash << endl;
			}
			else
			{
				cash += 3;
				cout << "You got Three of a kind! You earned $3\nYou now have$" << cash << endl;
			}
		}
		else if ((sorted[0] == sorted[1] && sorted [0] > 10 )|| (sorted[1] == sorted[2] && sorted[1] > 10) || (sorted[2] == sorted[3] && sorted[2] > 10) || (sorted[3] == sorted[4] && sorted[3] > 10))
		{
			cash += 1;
			cout << "You got a Pair! You earned $1\nYou now have$" << cash << endl;
		}
		else if (sorted[0] == sorted[1] - 1 && sorted[1] == sorted[2] - 1 && sorted[2] == sorted[3] - 1 && (sorted[3] == sorted[4] - 1 || sorted[0] == sorted[4] - 12))
		{
			cash += 4;
			cout << "You got a Straight! You earned $4\nYou now have$" << cash << endl;
		}
		else
		{
			cout << "No poker hand scored.\nYou earned $0\nYou now have$" << cash << endl;
			if (cash == 0)
			{
				cout << "GAME OVER...\nPress enter to exit...";
				cin.get();
				cin.ignore();
				over = true;
			}
		}
	}
	else
	{
		if (sorted[0] == sorted[1] - 1 && sorted[1] == sorted[2] - 1 && sorted[2] == sorted[3] - 1 && (sorted[3] == sorted[4] - 1 || sorted[0] == sorted[4] - 12))
		{
			if (sorted[0] == 10 && sorted[1] == 11 && sorted[2] == 12 && sorted[3] == 13 && sorted[4] == 14)
			{
				cash += 800;
				cout << "You got a ROYAL FLUSH! You earned $800\nYou now have$" << cash << endl;
			}
			else
			{
				cash += 50;
				cout << "You got a Straight Flush! You earned $50\nYou now have$" << cash << endl;
			}
		}
		else
		{
			cash += 6;
			cout << "You got a Flush! You earned $6\nYou now have$" << cash << endl;
		}
	}
}

int letters(string l, deck* h, deck* d, deck *g)
{
	int index[5] = { 0,0,0,0,0 };
	int dec = 0;
	for (int i = 0; i < l.length(); i++)
	{
		if (l[i] == 'a')
		{
			index[0] = 1;
		}
		else if (l[i] == 'b')
		{
			index[1] = 1;
		}
		else if (l[i] == 'c')
		{
			index[2] = 1;
		}
		else if (l[i] == 'd')
		{
			index[3] = 1;
		}
		else if (l[i] == 'e')
		{
			index[4] = 1;
		}
		else
		{
			cout << "Sorry, I didn't understand, please try again...\n\n";
			return -1;
			break;
		}
	}
	for (int j = 0; j < 5; j++)
	{
		if (index[j] == 0)
		{
			card tmp = get_item(h, j - dec);
			remove_item(h, j - dec);
			drop(tmp, g);
			dec++;
		}
	}
	for (int k = 0; k < dec; k++)
	{
		draw_one(d, h, g);
	}
	return dec;
}

int pay()
{
	int rest = --cash;
	cout << "You pay $1 and now have $" << rest << endl;
	return rest;
}

void decision(deck* h, deck* d, deck* g)
{
	cout << "\nYour hand contains:" << endl;
	print_hand(h);
	cout << "\nThe deck contains " << count_items(d) << " cards.\n" << endl;
	cout << "OPTIONS..." << endl;
	cout << "Type the letters for the cards you wish to keep. (i.e., \"acd\")" << endl;
	cout << "Type \"deck\" to view the cards remaining in the deck." << endl;
	cout << "Type \"none\" to discard all cards in your hand." << endl;
	cout << "Type \"all\" to keep all cards in your hand." << endl;
	cout << "Type \"exit\" to exit the game." << endl;
	cout << "Type \"swap\" to CHEAT and swap a card in your hand with one in the deck.(Debug Feature)" << endl;
	cout << "\nYOUR CHOICE: ";
	cin >> in;
	if (in == "none")
	{
		none(h, g);
		draw_new(h, d, g);
		update_hand(h,0);
		check(h);
		if (over == false)
		{
			cout << "Press enter to next round...";
			cin.get();
			cin.ignore();
			cout << "================================================\n";
			cash = pay();
			none(h, g);
			draw_new(h, d, g);
		}
		else if (over == true)
		{
			return;
		}
	}
	else if (in == "deck")
	{
		print_items(d);
	}
	else if (in == "all")
	{
		all(h);
		check(h);
		if (over == false)
		{
			cout << "Press enter to next round...";
			cin.get();
			cin.ignore();
			cout << "================================================\n";
			cash = pay();
			none(h, g);
			draw_new(h, d, g);
		}
		else if (over == true)
		{
			return;
		}
	}
	else if (in == "exit")
	{
		return;
	}
	else if (in == "swap")
	{
		swap(h, d);
	}
	else
	{
		int discard = letters(in, h, d, g);
		if(discard == -1)
		{

		}
		else
		{
			update_hand(h, 5 - discard);
			check(h);
			if (over == false)
			{
				cout << "Press enter to next round...";
				cin.get();
				cin.ignore();
				cout << "================================================\n";
				cash = pay();
				none(h, g);
				draw_new(h, d, g);
			}
			else if (over == true)
			{
				return;
			}
		}
	}
	decision(h, d, g);
}


int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF |
		_CRTDBG_LEAK_CHECK_DF);
	cash = 10;
	over = false;
	cout << "You currently have $" << cash << "\n" << endl;
	//New deck
	deck* d = create_linked_list();
	deck* g = create_linked_list();
	deck* h = create_linked_list();
	new_deck(d);
	srand(time(0));

	draw_new(h, d, g);
	cash = pay();
	decision(h, d, g);

	del_linked_list(d);
	del_linked_list(g);
	del_linked_list(h);
	return 0;
}
