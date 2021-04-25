#include<bits/stdc++.h>
using namespace std;

struct card
{
	int size;//大小
	int design;//花色
	card() {
		size = -1;
		design = -2;
	}
	card(int init_size, int init_design) {
		size = init_size;
		design = init_design;
	}
};

bool cmp(card a, card b) {
	//按 size 升序排序，若 size 相等则按 design 升序排序
	if (a.size != b.size)
		return a.size < b.size;
	return a.design < b.design;
	/*
	从小到大排序用a<b
	从大到小用a>b
	*/
}

class card_play
{
public:
	vector<card> all_card;//牌堆
	vector<card> cards_in_hand;//手牌
	card card1;
	card card2;
	int designs;//花色数
	int sizes;//大小数

	card_play(int sum_size, int sum_design) {
		designs = sum_design;
		sizes = sum_size;
		all_card.reserve(designs * sizes + 10);
		for (int i = 0; i < designs; i++)
			for (int j = 0; j < sizes; j++) {
				card new_card(j, i);
				all_card.push_back(new_card);
			}
	}
	~card_play(){}

	void display() {
		printf("牌堆：\n");
		for (unsigned int i = 0; i < all_card.size(); i++)
			printf("%d, %d\n", all_card[i].size, all_card[i].design);
		printf("手牌：\n");
		for (unsigned int i = 0; i < cards_in_hand.size(); i++)
			printf("%d, %d\n", cards_in_hand[i].size, cards_in_hand[i].design);
	}

	int find_index(card card) {
		int num = all_card.size();
		for (unsigned int index = 0; index < num; index++)
			if (all_card[index].size == card.size && all_card[index].design == card.design)
				return index;
		return -1;
	}
	void get_card(int a1, int b1, int a2, int b2) {
		cards_in_hand.reserve(5);
		card1.size = a1;
		card1.design = b1;
		card2.size = a2;
		card2.design = b2;
		cards_in_hand.push_back(card1);
		all_card.erase(all_card.begin() + find_index(card1));
		cards_in_hand.push_back(card2);
		all_card.erase(all_card.begin() + find_index(card2));
	}
	int juege() {
		if (type4(cards_in_hand) && type5(cards_in_hand))
			return 1;
		else if (type2(cards_in_hand))
			return 2;
		else if (type3(cards_in_hand))
			return 3;
		else if (type4(cards_in_hand))
			return 4;
		else if (type5(cards_in_hand))
			return 5;
		else if (type6(cards_in_hand))
			return 6;
		else if (type7(cards_in_hand))
			return 7;
		else if (type8(cards_in_hand))
			return 8;
		else
			return 9;
	}
	void play() {
		int result[10];
		for (int i = 0; i < 10; i++)
			result[i] = 0;
		int num = all_card.size();
		for (int i = 0; i < num-2; i++) {
			for (int j = i + 1; j < num - 1; j++) {
				for (int k = j + 1; k < num; k++) {
					cards_in_hand.push_back(all_card[i]);
					cards_in_hand.push_back(all_card[j]);
					cards_in_hand.push_back(all_card[k]);
					sort(cards_in_hand.begin(), cards_in_hand.begin() + 5, cmp);
					result[juege()]++;
					cards_in_hand.clear();
					cards_in_hand.push_back(card1);
					cards_in_hand.push_back(card2);
				}
			}
		}
		for (int i = 1; i < 10; i++)
			printf("%d ", result[i]);
	}

	bool type2(vector<card> cards) {
		int counts = 0;
		for (unsigned int i = 0; i < 2; i++) {
			for (unsigned int j = i + 1; j < 5; j++) 
				if (cards[i].size == cards[j].size)
					counts++;
			if (counts == 3)
				return true;
			else
				counts = 0;
		}
		return false;
	}
	bool type3(vector<card> cards) {
		int minC = cards[0].size;
		int maxC = cards[4].size;
		int count_min = 0, count_max = 0;
		for (unsigned int i = 0; i < 5; i++) {
			if (cards[i].size == minC)
				count_min++;
			if (cards[i].size == maxC)
				count_max++;
		}
		if ((count_min == 2 && count_max == 3) || (count_min == 3 && count_max == 2))
			return true;
		else
			return false;
	}
	bool type4(vector<card> cards) {
		int design = cards[0].design;
		for (unsigned int i = 1; i < 5; i++)
			if (cards[i].design != design)
				return false;
		return true;
	}
	bool type5(vector<card> cards) {
		for (unsigned int i = 1; i < 5; i++)
			if (cards[i].size != cards[0].size + i)
				return false;
		return true;
	}
	bool type6(vector<card> cards) {
		int counts = 0;
		for (unsigned int i = 0; i < 3; i++) {
			for (unsigned int j = i + 1; j < 5; j++) {
				if (cards[i].size == cards[j].size)
					counts++;
				if (counts == 2) {
					//display();
					return true;
				}
			}
			counts = 0;
		}
		return false;
	}
	bool type7(vector<card> cards) {
		if (cards[0].size == cards[1].size) {
			if (cards[3].size == cards[4].size) {
				return true;
			}
			else {
				if (cards[2].size == cards[3].size) {
					//display();
					return true;
				}
			}
		}
		else {
			if (cards[1].size == cards[2].size && cards[3].size == cards[4].size) {
				//display();
				return true;
			}
		}
		return false;
	}
	bool type8(vector<card> cards) {
		int counts = 0;
		for (unsigned int i = 0; i < 4; i++) {
			for (unsigned int j = i + 1; j < 5; j++)
				if (cards[i].size == cards[j].size)
					counts++;
			if (counts == 1)
				return true;
		}
		return false;
	}
};

int  main() 
{
	int a, b, a1, b1, a2, b2;
	cin >> a >> b;
	card_play game(a,b);
	cin >> a1 >> b1 >> a2 >> b2;
	game.get_card(a1, b1, a2, b2);
	game.play();
	return 0;
}