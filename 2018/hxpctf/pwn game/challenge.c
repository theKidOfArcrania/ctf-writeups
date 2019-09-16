#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>

#define FIELD_WIDTH 10u
#define FIELD_HEIGHT 10u

#define X_MIN 0u
#define X_MAX FIELD_WIDTH - 1u

#define Y_MIN 0u
#define Y_MAX FIELD_HEIGHT - 1u

#define COLOR(X) "\x1B[" X "m"
#define COL_GREEN COLOR("32")
#define COL_RED COLOR("31")
#define COL_DEFAULT COLOR("0")

bool headless = false;

struct enemy {
	uint8_t cooldown;
	uint8_t prev_render_pos_x;
	uint8_t prev_render_pos_y;
	uint8_t pos_x;
	uint8_t pos_y;
	int8_t dx;
	int8_t dy;
};

struct player {
	uint8_t prev_render_pos_x;
	uint8_t prev_render_pos_y;
	uint8_t pos_x;
	uint8_t pos_y;
	uint64_t score;
	uint8_t lifes;
	int8_t dx;
	int8_t dy;
};

#define clear() printf(COL_DEFAULT "\033[H\033[J")
// move the cursor to the given position
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

#define goto_pos_xy(x, y) gotoxy(3*x+2u, y+2u);

#define HEART "o"
#define LU_CORNER "\xe2\x95\x94"
#define RU_CORNER "\xe2\x95\x97"
#define LL_CORNER "\xe2\x95\x9a"
#define RL_CORNER "\xe2\x95\x9d"
#define H_BOX "\xe2\x95\x90"
#define V_BOX "\xe2\x95\x91"
#define PLAYER COLOR("0") COLOR("7") "Oo"
#define ENEMY COLOR("91") COLOR("7") ":O" //"\xf0\x9f\x91\xbf"

#define csize(X) (sizeof(X) - 1u)

char wait_key()
{
	puts("\nPRESS ANY KEY TO CONTINUE; <q>: QUIT; <h>: TOGGLE HEADLESS...");
	char c = getchar();
	if (c == 'q')
		exit(0);
	else if (c == 'h')
		headless = !headless;
	return c;
}

void draw_enemy(struct enemy* e)
{
	e->prev_render_pos_x = e->pos_x;
	e->prev_render_pos_y = e->pos_y;
	goto_pos_xy(e->pos_x, e->pos_y);
	fwrite(ENEMY, 1, csize(ENEMY), stdout);
}

void draw_player(struct player* p)
{
	p->prev_render_pos_x = p->pos_x;
	p->prev_render_pos_y = p->pos_y;
	goto_pos_xy(p->pos_x, p->pos_y);
	fwrite(PLAYER, 1, csize(PLAYER), stdout);
	goto_pos_xy(p->pos_x, p->pos_y);
}

void draw_meta(struct player* p, struct enemy* e, char* realfield, char* targetfield)
{
	fwrite("Lifes: " COL_RED HEART HEART HEART, 1, csize("lifes: " COL_RED) + (csize(HEART)) * (p->lifes), stdout);
	fwrite("     ", 1, 5 - (p->lifes), stdout);
	printf(COL_DEFAULT "    Score: %lu     Position: (%u, %u) <%d, %d>         ", p->score, p->pos_x, p->pos_y, p->dx, p->dy);
  printf("\nEnemy Position: (%u, %u) <%d, %d>", e->pos_x, e->pos_y, e->dx, e->dy);
	uint16_t pos = p->pos_y * FIELD_WIDTH + p->pos_x;
	printf("\nCURRENT CELL: ");
	if(realfield[pos] == targetfield[pos])
		fwrite(COL_GREEN, csize(COL_GREEN), 1u, stdout);
	else
		fwrite(COL_RED, csize(COL_RED), 1u, stdout);
	printf("%02hhx -> %02hhx\n", realfield[pos], targetfield[pos]);
	fwrite(COL_DEFAULT, csize(COL_DEFAULT), 1u, stdout);
	puts("================== CONTROLS: ===================\n"
		"<w/a/s/d>: MOVE         <q>: QUIT\n"
		"<+/->: INC/DEC 1        <1/2>: INC/DEC 0x10\n"
		"<r>: SHOW REAL FIELD    <t>: SHOW TARGET FIELD\n"
		"<h>: TOGGLE HEADLESS    <f>: RENDER SINGLE IMAGE\n");

}

void render_field(char* field, char* targetfield, char* renderfield)
{
	uint8_t y = 0u;
	uint8_t x = 0u;
	clear();

	// draw the upper border
	fwrite(LU_CORNER, csize(LU_CORNER), 1u, stdout);
	for(x=0u; x < FIELD_WIDTH; x++)
		fwrite(H_BOX H_BOX H_BOX, 3*csize(H_BOX), 1u, stdout);
	fwrite(RU_CORNER "\n", csize(RU_CORNER "\n"), 1u, stdout);

	// draw the actual field
	for(y=0u; y < FIELD_HEIGHT; y++)
	{
		fwrite(V_BOX, csize(V_BOX), 1u, stdout);
		for(x=0u; x < FIELD_WIDTH; x++)
		{
			// make the field green, if it is correct, otherwise make it red
			uint16_t idx = y * FIELD_WIDTH + x;
			if(field[idx] == targetfield[idx])
				fwrite(COL_GREEN, csize(COL_GREEN), 1u, stdout);
			else
				fwrite(COL_RED, csize(COL_RED), 1u, stdout);
			printf("%02x ", renderfield[idx] & 0xff);
		}
		printf(COL_DEFAULT);
		fwrite(V_BOX "\n", csize(V_BOX "\n"), 1u, stdout);
	}

	// draw the lower border
	fwrite(LL_CORNER, csize(LL_CORNER), 1u, stdout);
	for(x=0u; x < FIELD_WIDTH; x++)
		fwrite(H_BOX H_BOX H_BOX, 3*csize(H_BOX), 1u, stdout);
	fwrite(RL_CORNER "\n", csize(RL_CORNER "\n"), 1u, stdout);
}

void render_all(struct enemy* e, struct player* p, char* field, char* targetfield, char* renderfield)
{
	render_field(field, targetfield, renderfield);
	draw_meta(p, e, field, targetfield);
	draw_enemy(e);
	draw_player(p);
}

void render_differential(struct enemy* e, struct player* p, char* field, char* targetfield, char* renderfield)
{
	uint8_t x, y;
	fwrite(COL_DEFAULT, csize(COL_DEFAULT), 1u, stdout);
	x = p->prev_render_pos_x;
	y = p->prev_render_pos_y;
	if((x != p->pos_x) || (y != p->pos_y))
	{
		goto_pos_xy(x, y);
		uint16_t idx = y * FIELD_WIDTH + x;
		if(field[idx] == targetfield[idx])
			fwrite(COL_GREEN, csize(COL_GREEN), 1u, stdout);
		else
			fwrite(COL_RED, csize(COL_RED), 1u, stdout);
		printf("%02x ", renderfield[idx] & 0xff);
	}

	x = e->prev_render_pos_x;
	y = e->prev_render_pos_y;
	if((x != e->pos_x) || (y != e->pos_y))
	{
		goto_pos_xy(x, y);
		uint16_t idx = y * FIELD_WIDTH + x;
		if(field[idx] == targetfield[idx])
			fwrite(COL_GREEN, csize(COL_GREEN), 1u, stdout);
		else
			fwrite(COL_RED, csize(COL_RED), 1u, stdout);
		printf("%02x ", renderfield[idx] & 0xff);
	}

	gotoxy(0, FIELD_HEIGHT + 3);
	fwrite(COL_DEFAULT, csize(COL_DEFAULT), 1u, stdout);
	draw_meta(p, e, field, targetfield);
	draw_enemy(e);
	draw_player(p);
}

void move_enemy(struct enemy* e, struct player* p)
{
	// enemy will always make three steps and then pause for three steps
	if(e->cooldown < 3u)
	{
		// move towards player
		e->dx = p->pos_x - e->pos_x;
		e->dy = p->pos_y - e->pos_y;
		if(e->dx > 0)
			e->pos_x++;
		else if(e->dx < 0)
			e->pos_x--;
		if(e->dy > 0)
			e->pos_y++;
		else if(e->dy < 0)
			e->pos_y--;
	}
	if(e->cooldown == 0u)
	{
		e->dx = 0;
		e->dy = 0;
		e->cooldown = 6u;
	}
	e->cooldown--;
}

void damage_and_knock_back(struct enemy* e, struct player* p)
{
	if((e->pos_x == p->pos_x) && (e->pos_y == p->pos_y))
	{
		p->lifes--;
		if(e->dx > 0 && p->pos_x + 1 < X_MAX)
			p->pos_x++;
		else if(e->dx < 0 && p->pos_x - 1 >= X_MIN)
			p->pos_x--;
		if(e->dy > 0 && p->pos_y + 1 < Y_MAX)
			p->pos_y++;
		else if(e->dy < 0 && p->pos_y - 1 >= Y_MIN)
			p->pos_y--;
	}
}

void init_player(struct player* p)
{
	p->pos_x = 0u;
	p->pos_y = 0u;
	p->score = 500u;
	p->lifes = 3u;
}

void init_enemy(struct enemy* e)
{
	e->cooldown = 5u;
	e->pos_x = 0u;
	e->pos_y = 0u;
	e->dx = 0u;
	e->dy = 0u;
}

void modify_field(int8_t diff, struct player* p, char* field, char* targetfield, uint16_t idx)
{
	if(field[idx] == targetfield[idx])
	{
		// U STOOPID????
		if (p->score < 500u)
			p->score = 0u;
		else
			p->score -= 500u;
	}

	field[idx] += diff;

	if(field[idx] == targetfield[idx])
		p->score += 100;
}

bool action(char input, struct enemy* e, struct player* p, char* field, char* targetfield, char** renderfield)
{
	bool moved = false;
	p->dx = 0;
	p->dy = 0;
	uint16_t idx = p->pos_y * FIELD_WIDTH + p->pos_x;
	switch(input)
	{
		case 'w': 
			if(p->pos_y >= Y_MIN + 1)
				p->dy = -1;
			moved = true;
			break;
		case 's':
			if(p->pos_y <= Y_MAX - 1)
				p->dy = 1;
			moved = true;
			break;
		case 'a':
			if(p->pos_x >= X_MIN + 1)
				p->dx = -1;
			moved = true;
			break;
		case 'd':
			if(p->pos_x <= X_MAX - 1)
				p->dx = 1;
			moved = true;
			break;
		case '+':
			modify_field(1, p, field, targetfield, idx);
			moved = true;
			break;
		case '-':
			modify_field(-1, p, field, targetfield, idx);
			moved = true;
			break;
		case '1':
			modify_field(0x10, p, field, targetfield, idx);
			moved = true;
			break;
		case '2':
			modify_field(-0x10, p, field, targetfield, idx);
			moved = true;
			break;
		case 't':
			*renderfield = targetfield;
			break;
		case 'r':
			*renderfield = field;
			break;
		case 'f':
			render_all(e, p, field, targetfield, *renderfield);
			break;
		case 'h':
			headless = !headless;
			if(!headless)
				render_all(e, p, field, targetfield, *renderfield);
			break;
		default:
			break;
	}
	p->pos_x += p->dx;
	p->pos_y += p->dy;
	return moved;
}

void generate_field(char* field, uint16_t level)
{
	for(uint8_t x = 0; x < FIELD_WIDTH; x++)
	{
		for(uint8_t y = 0; y < FIELD_HEIGHT; y++)
		{
			field[y * FIELD_WIDTH + x] = 0x50u + (rand() % (level * 5u));
		}
	}
}

char* main_loop(char* score_buf)
{
	srand(0);
	uint16_t level = 1;
	char field[FIELD_WIDTH * FIELD_HEIGHT];
	char targetfield[FIELD_WIDTH * FIELD_HEIGHT];
	generate_field(field, level);
	generate_field(targetfield, level);
	struct player p;
	init_player(&p);
	struct enemy e;
	init_enemy(&e);
	p.pos_x = FIELD_WIDTH / 2u;
	p.pos_y = FIELD_HEIGHT / 2u;
	char* renderfield = field;
	if(!headless)
		render_all(&e, &p, field, targetfield, renderfield);
	while((p.lifes > 0u))
	{
		char input;
		fread(&input, 1u, 1u, stdin);
		if(input == 'q')
		{
			puts("EXITING");
			break;
		}
		if(action(input, &e, &p, field, targetfield, &renderfield))
		{
			if(!memcmp(field, targetfield, FIELD_WIDTH * FIELD_HEIGHT))
			{
				clear();
				puts("NO ONE EVER CAME THIS FAR! WHAT DO WE DO NOW???\n"
					"LET'S JUST THROW ANOTHER LEVEL AT YOU...\n");
				p.score += 2000;
				wait_key();
				level++;
				generate_field(targetfield, level);
			}
			if(p.score > 1)
				p.score--;
			move_enemy(&e, &p);
			damage_and_knock_back(&e, &p);
		}
		if(!headless)
			render_differential(&e, &p, field, targetfield, renderfield);
	}
	snprintf(score_buf, 256u, "GAME OVER, YOUR SCORE: %lu!\nPRESS ENTER TO EXIT!\n", p.score);
	return score_buf;
}

void show_tutorial()
{
	clear();
	puts("============ TUTORIAL ============\n"
		 "First of all...\n"
		 "If you are playing remotely, you should start this game using \n\n"
		 "stty -icanon min 1 time 0 && nc <IP> <PORT>\n\n"
		 "If you haven't done so, netcat will buffer your input and you will be missing\n"
		 "out on all the fun, so you should consider restarting the game (press <q> to quit).\n"
		 "You can also press <s> to skip the Tutorial.\n"
		 "You can press <h> any time in order to turn headless mode on or off.\n"
		 "In headless mode the field is not rendered unless you press <f>, which can be used for reducing the network traffic.\n"
		 );
	if(wait_key() == 's' || headless)
		return;
	puts("In this game you are given a target field consisting of multiple cells which you need to recreate.\n"
		 "Press <t> to show your target field and <r> to show the real field.\n"
		 "Use <w>, <a>, <s>, <d> to move through the field and <+> and <-> to increment or decrement the field you are currently standing on (values are given in hex).\n"
		 "You can also increment and decrement in steps of 0x10 by using the keys <1> and <2>\n"
		 "Once the target and the real field are equal, you beat the level.\n");
	if(wait_key() == 's' || headless)
		return;
	puts("This is a monster: " ENEMY COL_DEFAULT);
	puts("Do not get eaten by the monster! We are legally required to tell you that we will not cover for your doctor's bill if you get (partially) eaten by the monster!\n");
	if(wait_key() == 's' || headless)
		return;
	puts("Actually we probably aren't required to tell you that but we do so anyway...\n");
	if(wait_key() == 's' || headless)
		return;
	puts("You won't get a flag for making a new highscore (you'll get it if you pwn the game) but if you can make it, you will receive great glory and you will always be remembered!\n");
	if(wait_key() == 's' || headless)
		return;
	puts("Actually no... you won't be remembered, since we did not implement a highscore-list, so you are playing just for fun! ;)\n");
	puts("Are you ready?");
	if(wait_key() == 's' || headless)
		return;
}

int main(int argc, char** argv)
{
	char score_buf[2048]; // I LIKE BIG BUFFERS AND I CANNOT LIE!

	// Make sure keypresses are not echoed and are sent immediately
	// Does not affect remote, though
	static struct termios oldt, newt;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON);
	newt.c_lflag &= ~(ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	setvbuf(stdout, NULL, _IONBF, 0u);
	setvbuf(stdin, NULL, _IONBF, 0u);

	show_tutorial();

	char* end_text = main_loop(score_buf);
	char c;
	do {
		clear();
		fwrite(end_text, sizeof(char), strlen(end_text), stdout);
	} while((c = getchar()) != '\n' && c != 'q');

	// Reset terminal mode
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return 0u;
}
