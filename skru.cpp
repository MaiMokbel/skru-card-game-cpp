#include <stdio.h>
#include <string.h>
#include <time.h> 
#include <stdlib.h>
//The standard ANSI palette includes 8 basic colors and some of their bright versions.
#define BRIGHT_ORANGE "\033[38;2;255;165;0m" 
#define RESET       "\033[0m"
#define RED         "\033[1;31m"
#define BRIGHT_RED     "\033[1;31m"
#define BRIGHT_YELLOW  "\033[1;33m"
#define BRIGHT_BLUE    "\033[1;34m"
#define PASTEL_GREEN "\033[38;2;119;221;119m"
#define ORANGE       "\033[38;5;202m" // A nice orange
#define LIGHT_GREEN  "\033[38;5;120m" // A bright green
#define SKY_BLUE     "\033[38;5;117m" // A soft blue
#define GOLD         "\033[38;5;220m" // Gold-like yellow
#define HOT_PINK      "\033[38;2;255;105;180m"  // Hot pink
#define BRIGHT_WHITE   "\033[1;37m"

struct player_turn
{
	char player_card[7][7] = { "" };
	int score;
};

int check_epmty_card(char player_card[7][7], int player_card_index)
{
	if (strcmp(player_card[player_card_index], "") == 0 || player_card_index > 6)
	{
		return 0;
	}
	if (strcmp(player_card[player_card_index], "") != 0)
	{
		return 1;
	}
}

void printexist_playercards(char player_card[7][7], int player_index)     //// print the player cards that aren't empty  ////
{
	printf(BRIGHT_YELLOW"\nplayer %d cards :\n\n", player_index);
	for (int i = 0; i < 7; i++)
	{
		if (strcmp(player_card[i],"") != 0)
		{
			printf(SKY_BLUE"[#]\t");
		}
		else
		{
			printf(" \t");
		}
	}
	printf("\n");
}

void score(char player_card[7][7], int* player_score)
{
	(*player_score) = 0;
	for (int i = 0; i < 7; i++)
	{
		if (strcmp(player_card[i], "-1") == 0)
			(*player_score) -= 1;
		else if (strcmp(player_card[i], "skru_d") == 0 || strcmp(player_card[i], "") == 0 || strcmp(player_card[i], " ") == 0)
			(*player_score) += 0;
		else if (strcmp(player_card[i], "1") == 0)
			(*player_score) += 1;
		else if (strcmp(player_card[i], "2") == 0)
			(*player_score) += 2;
		else if (strcmp(player_card[i], "3") == 0)
			(*player_score) += 3;
		else if (strcmp(player_card[i], "4") == 0)
			(*player_score) += 4;
		else if (strcmp(player_card[i], "5") == 0)
			(*player_score) += 5;
		else if (strcmp(player_card[i], "6") == 0)
			(*player_score) += 6;
		else if (strcmp(player_card[i], "7") == 0)
			(*player_score) += 7;
		else if (strcmp(player_card[i], "8") == 0)
			(*player_score) += 8;
		else if (strcmp(player_card[i], "9") == 0)
			(*player_score) += 9;
		else if (strcmp(player_card[i], "10") == 0 || strcmp(player_card[i], "basra") == 0 || strcmp(player_card[i], "5d&hat") == 0 || strcmp(player_card[i], "5od") == 0 || strcmp(player_card[i], "ka3b_d") == 0)
			(*player_score) += 10;
		else if (strcmp(player_card[i], "+20") == 0)
			(*player_score) += 20;
		else if (strcmp(player_card[i], "skru") == 0)
			(*player_score) += 25;
	}
	//printf("your score is %d\n\n", player_score);
}

void calculateScores(player_turn player[4], int* winner, int* loser) {

	*winner = 0, * loser = 0; //pointer decleration
	for (int i = 0; i < 4; i++) {
		score(player[i].player_card, &player[i].score);
		printf("Player %d's score: %d\n", i + 1, player[i].score);
		if (player[i].score > player[*loser].score)
			*loser = i; //value
		if (player[i].score < player[*winner].score)
			*winner = i; //value 
	}
}

void shuffle(char deck[60][7])
{ //Fisher-Yates Shuffle algorithm
	for (int i = 59; i > 0; i--)
	{
		int j = rand() % (i + 1); //generates a random number b/w 0 and i
		char temp[7]; //a temporary array temp to store one card from the deck
		strcpy(temp, deck[i]);
		strcpy(deck[i], deck[j]);
		strcpy(deck[j], temp);
	}
}

int check_deck(char deck[60][7])
{
	int flag = 0;
	for (int i = 0; i < 60; i++)
	{
		if (strcmp(deck[i], "X") != 0)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 0)
		return 0;
	else
		return 1;
}

void bos_f_war2tk(char player_card[7][7])
{
	int card_index;
	printf(BRIGHT_WHITE"Choose a card to see (1-7):\n");
	scanf("%d", &card_index);
	if (strcmp(player_card[card_index - 1], "") == 0 || card_index > 7 || card_index < 1) {
		printf(RED"THIS CARD IS EMPTY OR DOESN'T EXIST , TRY AGAIN\n");
		bos_f_war2tk(player_card);
	}
	else
	{
		printf(BRIGHT_WHITE"THE CARD IS :");
		printf(SKY_BLUE"[%s]\n", player_card[card_index - 1]);
	}
}

void bos_f_war2t_gherk(char player_card[7][7], player_turn player[4], int player_index)
{
	int player_num, card_index;
	printf(BRIGHT_WHITE"Choose a player to see their card (1-4):\n");
	scanf("%d", &player_num);
	if (player_num == player_index + 1) {
		printf(BRIGHT_RED"YOU CANT LOOK AT YOUR PAPER CHEATER (>_<)!!\n");
		bos_f_war2t_gherk(player_card, player, player_index);
		return;
	}
	else if (player_num < 1 || player_num>4) {
		printf(RED"PLAYER %d DOES'NT EXIST ,TRY AGAIN\n", player_num);
		bos_f_war2t_gherk(player_card, player, player_index);
	}
	else {
		printf(BRIGHT_WHITE"Choose a card to see(1-7):\n");
		scanf("%d", &card_index);
		while (strcmp(player[player_num - 1].player_card[card_index - 1], "") == 0 || card_index > 7 || card_index < 1)
		{
			printf(RED"THIS CARD IS EMPTY OR DOESN'T EXIST ,TRY AGAIN\n");
			scanf("%d", &card_index);
		}
		printf(BRIGHT_WHITE"THE CARD IS :");
		printf(SKY_BLUE"[%s]\n", player[player_num - 1].player_card[card_index - 1]);


	}
}

void k3b_dayer(char player_card[7][7], player_turn player[4])
{

	printf(LIGHT_GREEN"   \n       +--------------- ACTIONS ------------------+\n");
	printf(LIGHT_GREEN"      | 1. See Card from each Player including you|\n");
	printf(LIGHT_GREEN"      | 2. See Only Two Cards from you            |\n");
	printf(LIGHT_GREEN"      +-------------------------------------------+\n");
	int choice;
	scanf("%d", &choice);
	if (choice == 1)
	{
		int card_index;
		for (int i = 0; i < 4; i++)
		{

			for (int i = 0; ; i++) {
				printf(BRIGHT_WHITE"Choose the card you want to see from player %d (1-7):\n", i + 1);
				scanf("%d", &card_index);
				int k = check_epmty_card(player_card, card_index);
				if (k == 0 || card_index < 0 || card_index>6)
				{
					printf(RED"THIS CARD IS EMPTY OR DOESN'T EXIST (-_-) , TRY AGAIN\n");
					scanf("%d", &card_index);
				}
				if (k == 1)
				{
					break;
				}
			}
			printf(BRIGHT_WHITE"THE CARD IS :");
			printf(SKY_BLUE"[%s]\n", player[i].player_card[card_index - 1]);
		}
	}
	else if (choice == 2)
	{
		int card_index1, card_index2;
		for (int i = 0; ; i++)                               //////  check if the card that the user chooose is empty or not
		{

			printf(BRIGHT_WHITE"\nChoose two cards to see (1-7):\n");
			printf("choose card 1\n");
			scanf("%d", &card_index1);
			printf("choose card 2\n");
			scanf("%d", &card_index2);
			int k = check_epmty_card(player_card, card_index1);
			int s = check_epmty_card(player_card, card_index2);
			if (k == 0 || s == 0 || card_index1 < 1 || card_index1>7 || card_index2 < 1 || card_index2>7)
			{
				printf(RED"THIS CARD IS EMPTY OR DOESN'T EXIST (-_-) , TRY AGAIN\n");
			}
			if (k == 1 && s == 1)
			{
				break;
			}
		}
		printf(BRIGHT_WHITE"THE CARDS ARE :");
		printf(SKY_BLUE"\n [%s]\t [%s]", player_card[card_index1 - 1], player_card[card_index2 - 1]);
	}
	else
	{
		printf(BRIGHT_RED"INVAILD CHOICE PLEASE,TRY AGAIN \n");
		k3b_dayer(player_card, player);

	}
}

void khod_hat(char player_card[7][7], player_turn player[4], int player_index)
{
	int player_num, card_index1, card_index2;
	printf(BRIGHT_WHITE"Choose the player you want to swap cards with (1-4) :\n");
	scanf("%d", &player_num);
	if (player_num > 4 || player_num < 1)
	{
		printf(RED"PLAYER %d DOES'NT EXIST CHOOSE AGAIN (1-4)\n", player_num);
		khod_hat(player_card, player, player_index);
		return;
	}
	else
	{

		for (int i = 0; ; i++)//////  check if the card that the user chooose is empty or not
		{
			printf(BRIGHT_WHITE"Choose which one of their cards to swap(1-7):\n");
			scanf("%d", &card_index1);
			int k = check_epmty_card(player_card, card_index1);
			if (k == 0 || card_index1 < 1 || card_index1>7)
			{
				printf(RED"THIS CARD IS EMPTY OR DOESN'T EXIST (-_-) , TRY AGAIN\n");
			}
			if (k == 1)
			{
				break;
			}
		}

		char temp[7];
		int card_index2;
		for (int i = 0; ; i++)
		{
			printf(BRIGHT_WHITE"Choose which one of your cards to swap(1-7):\n");  ///// check if the card that the user chooose is empty or not
			scanf("%d", &card_index2);
			int k = check_epmty_card(player_card, card_index2);
			if (k == 0 || card_index2 < 1 || card_index2>7)
			{
				printf(RED"THIS CARD IS EMPTY OR DOESN'T EXIST (-_-) , TRY AGAIN\n");
			}
			if (k == 1)
			{
				break;
			}
		}
		strcpy(temp, player_card[card_index1 - 1]);
		strcpy(player[player_num - 1].player_card[card_index1 - 1], player_card[card_index2 - 1]);
		strcpy(player_card[card_index2 - 1], temp);
		if (player_num == player_index + 1)
		{
			printf(RED"YOU CAN'T GIVE OR TAKE FROM YOURSELF (O_O) !!\n");
			khod_hat(player_card, player, player_index);
			return;
		}
	}
}

void khod_bs(char player_card[7][7], player_turn player[4], int player_index)
{
	int player_num;
	printf(BRIGHT_WHITE"Choose the player you want to give the card (1-4): \n");
	scanf("%d", &player_num);
	if (player_num > 4 || player_num < 1)
	{
		printf(RED"PLAYER %d DOES'NT EXIST CHOOSE AGAIN (1-4)\n", player_num);
		khod_bs(player_card, player, player_index);
		return;
	}
	if (player_num == player_index + 1)
	{
		printf(RED"YOU CAN'T GIVE YOURSELF (O_O) !!\n");
		khod_bs(player_card, player, player_index);
		return;
	}
	else
	{
		int card_index;
		for (int i = 0; ; i++) { ////  check if the card that the user chooose is empty or not
			printf(BRIGHT_WHITE"Choose which card to give (1-7):\n");
			scanf("%d", &card_index);
			int k = check_epmty_card(player_card, card_index);
			if (k == 0 || card_index > 7 || card_index < 1)
			{
				printf(BRIGHT_RED"THIS CARD IS EMPTY OR DOESN'T EXIST (-_-) , TRY AGAIN\n");

			}
			if (k == 1)
			{
				break;
			}
		}

		for (int i = 0; i < 7; i++)
		{
			if (strcmp(player[player_num - 1].player_card[i], "") == 0)///check empty spaces  to put the crad in the first empty space :)
			{
				strcpy(player[player_num - 1].player_card[i], player_card[card_index - 1]);
				strcpy(player_card[card_index - 1], " ");
				break;
			}
		}
		strcpy(player_card[card_index - 1], "");

	}

}

void basra(char player_card[7][7], char ground_card[61][7], int* ground_count)
{
	int card_index;
	printf(BRIGHT_WHITE"CHOOSE WHICH CARD TO 'BASRA' (^o^) (1 - 7) :\n");
	scanf("%d", &card_index);
	if (strcmp(player_card[card_index - 1], "") == 0 || card_index > 7 || card_index < 1)
	{
		printf(RED"THIS CARD IS EMPTY OR DOESN'T EXIST (-_-) , TRY AGAIN\n");
		basra(player_card, ground_card, ground_count);
	}
	else {
		(*ground_count)++;
		strcpy(ground_card[*ground_count], player_card[card_index - 1]);
		strcpy(player_card[card_index - 1], " ");
	}
}

void playermove(char ground_card[61][7], char player_card[7][7], char deck[60][7], int* ground_count, player_turn player[4], int current_round, int player_index, int* said_skru)
{
	printf("\n\n");
	printf(BRIGHT_WHITE"GROUND CARD IS ");
	printf(SKY_BLUE"[% s] \n\n", ground_card[*ground_count]);
	printf(LIGHT_GREEN"   \n      +--------- ACTIONS --------+\n");
	printf(LIGHT_GREEN"      | 1. Make Basra            |\n");
	printf(LIGHT_GREEN"      | 2. Take Ground Card      |\n");
	printf(LIGHT_GREEN"      | 3. Draw New Card         |\n");
	if (current_round >= 3 && *said_skru == -1) {
		printf(LIGHT_GREEN"      | 4. Say SKRUUU!!!         |\n");
	}
	printf(LIGHT_GREEN"      +--------------------------+\n");

	int choice;
	scanf("%d", &choice);

	switch (choice)
	{
	case 1: //BASRA
		if (*ground_count != 0)
		{
			printf(BRIGHT_WHITE"\nCHOOSE A CARD TO BASRA(1-7) (^o^):\n");
			int card_index;
			scanf("%d", &card_index);
			while (strcmp(player_card[card_index - 1], "") == 0 || card_index > 7 || card_index < 1) {
				printf(BRIGHT_RED"THIS CARD IS EMPTY OR DOESN'T EXIST (-_-) , TRY AGAIN \n");
				scanf("%d", &card_index);
			}
			if (strcmp(ground_card[*ground_count], player_card[card_index - 1]) == 0)
			{
				(*ground_count)++;
				strcpy(ground_card[*ground_count], player_card[card_index - 1]);
				strcpy(player_card[card_index - 1], "");
			}
			else if (strcmp(ground_card[*ground_count], player_card[card_index - 1]) != 0)
			{
				for (int i = 0; i < 7; i++)
				{
					if (strcmp(player_card[i], "") == 0)
					{
						strcpy(player_card[i], ground_card[*ground_count]);
						(*ground_count)--;
						printf(HOT_PINK"WRONG BASRA , TAKE BOTH CARDS (T_T)");
						break;
					}
				}
			}
		}
		else if (*ground_count == 0)
		{
			printf(BRIGHT_RED"CAN'T MAKE BASRA, YOU MUST DRAW A NEW CARD!!\n");
			playermove(ground_card, player_card, deck, ground_count, player, current_round, player_index, said_skru);
		}
		break;
	case 2: //
		if (*ground_count != 0)
		{
			printf(BRIGHT_WHITE"CHOOSE A CARD TO CHANGE(1-7)\n");
			int card_index;
			scanf("%d", &card_index);
			while (strcmp(player[player_index - 1].player_card[card_index - 1], "") == 0 || card_index > 7 || card_index < 1)
			{
				printf(BRIGHT_RED"THIS CARD IS EMPTY OR DOESN'T EXIST (-_-) ,TRY AGAIN \n");
				scanf("%d", &card_index);
			}
			char temp[7];
			strcpy(temp, ground_card[*ground_count]);
			strcpy(ground_card[*ground_count], player_card[card_index - 1]);
			strcpy(player_card[card_index - 1], temp);

		}
		else if (*ground_count == 0)
		{
			printf(BRIGHT_RED"THERE IS NO GROUND CARD, YOU MUST DRAW A NEW CARD!!\n");
			playermove(ground_card, player_card, deck, ground_count, player, current_round, player_index, said_skru);
		}
		break;
	case 3: //takes a new paper
		(*ground_count)++;
		int num;
		for (int i = 1; i < 60; i++)
		{
			if (strcmp(deck[i], "X"))
			{
				num = i;
				break;
			}
		}
		printf(BRIGHT_WHITE"\nTHE DRAWN CARD IS ");
		printf(SKY_BLUE"[% s]\n", deck[num]);
		printf(LIGHT_GREEN"   \n      +--------- ACTIONS --------+\n");
		printf(LIGHT_GREEN"      | 1. Take This Card         |\n");
		printf(LIGHT_GREEN"      | 2. Put It On The Ground   |\n");
		printf(LIGHT_GREEN"      +--------------------------+\n");

		int choice;
		scanf("%d", &choice);
		while (choice != 1 && choice != 2)
		{
			printf(BRIGHT_RED"INVAILD CHOICE PLEASE CHOOSE AGAIN: \n");
			scanf("%d", &choice);
		}

		if (choice == 1)
		{
			printf(BRIGHT_WHITE"CHOOSE A CARD TO CHANGE(1-7):\n");
			int card_index;
			scanf("%d", &card_index);
			while (strcmp(player_card[card_index - 1], "") == 0 || card_index > 7 || card_index < 1) {
				printf(BRIGHT_RED"THIS CARD IS EMPTY OR DOESN'T EXIST (-_-) ,TRY AGAIN \n");
				scanf("%d", &card_index);
			}
			strcpy(ground_card[*ground_count], player_card[card_index - 1]);
			strcpy(player_card[card_index - 1], deck[num]);
			strcpy(deck[num], "X");
		}
		else if (choice == 2) //put the card on the ground
		{
			strcpy(ground_card[*ground_count], deck[num]);
			strcpy(deck[num], "X");
			if (strcmp(ground_card[*ground_count], "7") == 0 || strcmp(ground_card[*ground_count], "8") == 0) //bos f wr2tk
				bos_f_war2tk(player_card);
			else if (strcmp(ground_card[*ground_count], "9") == 0 || strcmp(ground_card[*ground_count], "10") == 0) //bos f wr2t gherk
				bos_f_war2t_gherk(player_card, player, player_index);
			else if (strcmp(ground_card[*ground_count], "k3b_d") == 0) //k3b dayr
				k3b_dayer(player_card, player);
			else if (strcmp(ground_card[*ground_count], "5d&hat") == 0) //khod w hat
				khod_hat(player_card, player, player_index);
			else if (strcmp(ground_card[*ground_count], "5od") == 0) //khod bs
				khod_bs(player_card, player, player_index);
			else if (strcmp(ground_card[*ground_count], "basra") == 0) //basra
			{
				(*ground_count)++;
				basra(player_card, ground_card, ground_count);
			}
		}
		else
			printf(BRIGHT_RED"INVAILD CHOICE PLEASE CHOOSE AGAIN :(\n");
		break;

	case 4:
		if (current_round < 3) {
			printf(RED"YOU CAN SAY SKRU ONLY AFTER ROUND 3!\n TRY AGAIN \n");
			playermove(ground_card, player_card, deck, ground_count, player, current_round, player_index, said_skru);
		}
		else if (*said_skru != -1) {
			printf(RED" TOO LATE ,SOMEONE ALREADY SAID SKRU!\n TRY AGAIN \n");
			playermove(ground_card, player_card, deck, ground_count, player, current_round, player_index, said_skru);
		}
		else {

			*said_skru = player_index;
			printf(GOLD"Player %d said SKRU (^o^)! THIS WILL BE THE FINAL ROUND.\n", player_index + 1);
		}
		break;

	default:
	{
		printf(BRIGHT_RED"INVAILD CHOICE PLEASE TRY AGAIN :( \n");
		playermove(ground_card, player_card, deck, ground_count, player, current_round, player_index, said_skru);
	}
	}


	printf("\n\n");


}

int main()
{
	char deck[60][7] = { "1","1","1","1","2","2","2","2","3","3","3","3","4","4","4","4","5","5","5","5","6","6","6","6",
	 "7", "7", "7", "7", "8", "8", "8", "8", "9", "9", "9", "9", "10", "10", "10", "10", "-1", "skru_d", "skru_d","skru_d", "skru", "skru", "+20" ,
	 "+20", "+20", "+20", "basra", "basra", "5d&hat", "5d&hat", "5d&hat", "5d&hat","skru", "5od", "k3b_d", "k3b_d" };
	srand(time(0)); //to generate diff random numbers each round

	shuffle(deck);
	//for (int i = 0; i < 60; i++)
	//{
		//printf(ORANGE"[%s]\t", deck[i]); // to print shuffled cards
	//}

	char ground_card[61][7] = { " " };
	int ground_count = 1;
	int current_round = 1;
	int said_skru = -1;
	player_turn player[4];
	strcpy(ground_card[ground_count], deck[0]);
	strcpy(deck[0], "X");
	printf("\n\n");

	for (int p = 0; p < 4; p++)
	{

		for (int i = 0; i < 4; i++)
		{
			int c;
			do
			{
				c = rand() % 60;
			} while ((strcmp(deck[c], "X") == 0));
			strcpy(player[p].player_card[i], deck[c]);
			strcpy(deck[c], "X");
		}
		//printf("\n\n");
	}

	printf("\n\n");

	printf(GOLD"        {======================}\n");
	printf(GOLD"        {====== ROUND 1 =======}\n");
	printf(GOLD"        {======================}\n");
	printf("\n\n");

	for (int p = 0; p < 4; p++)
	{
		printf(BRIGHT_ORANGE"IT IS PLAYER'S --> % d's TURN : \n\n", p + 1);
		printf(BRIGHT_ORANGE"YOUR CARDS ARE:");
		printf(SKY_BLUE"\t[% s]\t[% s]\t[#]\t[#]\n", player[p].player_card[0], player[p].player_card[1]);
		playermove(ground_card, player[p].player_card, deck, &ground_count, player, current_round, p, &said_skru);
	}
	printf("\n\n");
	current_round = 2;
	int flag = 1;

	while (check_deck(deck)) {
		printf(GOLD"         {======================}\n");
		printf(GOLD"         {====== ROUND %d ======}\n", current_round);
		printf(GOLD"         {======================}\n");
		printf("\n\n");

		for (int p = 0; p < 4; p++) {
			if (p == said_skru) {
				printf(GOLD"Player %d said SKRU! Game Over!\n", said_skru + 1);
				goto end_game;
			}

			printf(BRIGHT_ORANGE"\nIT IS PLAYER'S --> %d's TURN:\n", p + 1);
			printf(BRIGHT_WHITE"YOUR CARDS:\n\n" SKY_BLUE"[#]\t[#]\t[#]\t[#]\n", player[p].player_card[0], player[p].player_card[1]);
			playermove(ground_card, player[p].player_card, deck, &ground_count, player, current_round, p, &said_skru);

			if (check_deck(deck) == 0) {
				printf(BRIGHT_RED"\n\nWE ARE OUT OF CARDS, GAME OVER!\n\n" RESET);
				goto end_game;
			}
		}

		current_round++;
	}
end_game:
	printf(BRIGHT_YELLOW"\n============================\n\n");
	printf("\n\n");
	printf(BRIGHT_BLUE "\n+===========================+\n");
	printf(BRIGHT_BLUE "|         GAME OVER!        |\n");
	printf(BRIGHT_BLUE "+===========================+\n\n");
	for (int i = 0; i < 4; i++) {
		printf(BRIGHT_YELLOW"PLAYER %d CARDS:\t", i + 1);
		for (int j = 0; j < 7; j++) {
			if (strcmp(player[i].player_card[j], "") != 0)
				printf(SKY_BLUE"[%s]\t", player[i].player_card[j]);
		}
		printf("\n\n");
	}
	int winner, loser;
	calculateScores(player, &winner, &loser);
	printf("\n\n");
	printf("\n");
	printf(PASTEL_GREEN"******************************\n");
	printf(PASTEL_GREEN"*      \\\\  WINNER  //        *\n");
	printf(PASTEL_GREEN"*     ================       *\n");
	printf(PASTEL_GREEN"*       PLAYER  %d            *\n", winner + 1);
	printf(PASTEL_GREEN"*       %d POINTS            *\n", player[winner].score);
	printf(PASTEL_GREEN"*     ================       *\n");
	printf(PASTEL_GREEN"*    CONGRATULATIONS!!!      *\n");
	printf(PASTEL_GREEN"******************************\n");
	printf("\n");
	printf(ORANGE"------------------------------\n");
	printf(ORANGE"|          LOSER             |\n");
	printf(ORANGE"|      ============          |\n");
	printf(ORANGE"|       PLAYER %d             |\n", loser + 1);
	printf(ORANGE"|       %d POINTS            |\n", player[loser].score);
	printf(ORANGE"|      ============          |\n");
	printf(ORANGE"|    BETTER LUCK NEXT TIME   |\n");
	printf(ORANGE"------------------------------" RESET"\n");

	printf("\n\n");


	int play_again;
	printf(LIGHT_GREEN"   \n       +--------------- ACTIONS ------------------+\n");
	printf(LIGHT_GREEN"      | 1.             Play again                 |\n");
	printf(LIGHT_GREEN"      | 2.             End game                   |\n");
	printf(LIGHT_GREEN"      +-------------------------------------------+\n");
	scanf("%d", &play_again);
	while (play_again != 1 && play_again != 0)
	{
		printf(BRIGHT_RED"INVAILD CHOICE PLEASE CHOOSE AGAIN: " RESET);
		scanf("%d", &play_again);
	}
	if (play_again == 0)
		return 0;
	else if (play_again == 1)
		main();
	return 0;

}