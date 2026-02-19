#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "conio2.h"

const int dicesNo = 2, checkers = 15, beg3 = 3, beg5 = 5, mapW = 69, mapH = 19, mapX = 4, mapY = 2, fields = 24, bot12y = 17, top12y = 1, noD = 2, dub = 4;
const int menu_x = 85, dicesLine = 12, move_x = 85, move_y = 20, err_y = 25;
const char* err = "REMOVE ALL PIECES FROM BAND";
const char* err2 = "CANNOT SAVE DATA";
const char* err3 = "CANNOT LOAD DATA";
const char* save = "save.txt";
const char* record = "record.txt";

struct Match {
    int roundNo = 1;
    int redP = 0;
    int whiteP = 0;
};

struct Turn {
    int redBand = 0;
    int whiteBand = 0;
    int redHouse = 0;
    int whiteHouse = 0;
    bool redMove = false;
    int turnNo = 0;
};

struct Field {
    bool isRed = false;
    bool isWhite = false;
    int pieces = 0;
};

void shr(char**& map) {
    for (int y = 0; y < mapH; y++) {
        for (int x = mapW; x > 0; x--) {
            if (y > 0 && y < mapH) {
                if (x > 36 && x < mapW - 4) {
                    map[y][x + 1] = map[y][x];
                }
            }
        }
    }
}

char** generate_fields(char**& map) {
    for (int y = 0; y < mapH; y++) {
        for (int x = 0; x < mapW; x++) {
            if (!(y >= mapH / 2 - 1 && y <= mapH / 2 + 1)) {
                if ((x % 5 == 3 && y > 0 && y < mapH / 2 && (x < (mapW / 2) - 2 || x >(mapW / 2) + 2)) && y != mapH / 2 && x < mapW - 2) {
                    if (x % 10 == 3) {
                        map[y][x] = '\\';
                        map[y][x + 1] = '/';
                    }
                    else {
                        map[y][x] = '\'';
                        map[y][x + 1] = '\'';
                    }
                }
                else if ((x % 5 == 3 && y < mapH && y > mapH / 2 && (x < (mapW / 2) - 2 || x >(mapW / 2) + 2)) && y != mapH / 2 && y < mapH - 1 && x < mapW - 2) {
                    if (x % 10 == 8) {
                        map[y][x] = '/';
                        map[y][x + 1] = '\\';
                    }
                    else {
                        map[y][x] = '\'';
                        map[y][x + 1] = '\'';
                    }
                }
            }
        }
        map[y][mapW] = '\0';
    }
    shr(map);
    return map;
}

char** generate_map() {
    char** map = new char* [mapH];
    for (int i = 0; i < mapH; i++) {
        map[i] = new char[mapW];
    }
    for (int y = 0; y < mapH; y++) {
        for (int x = 0; x < mapW; x++) {
            if (x == 0 || x == (mapW - 1))
                map[y][x] = ':';
            else if (y == 0 || y == mapH - 1)
                map[y][x] = '=';
            else if ((x == mapW / 2 || x == mapW / 2 - 1 || x == mapW / 2 + 1) && y > 0 && y < mapH)
                map[y][x] = '|';
            else if (x == 1 || x == mapW - 2)
                map[y][x] = ':';

            else
                map[y][x] = ' ';
        }
    }
    return generate_fields(map);
}

void setup_pieces(Field*& field) {
    for (int i = 0; i < fields; i++) {
        if (i == 11 || i == 18 || i == 5 || i == 12) {
            field[i].pieces = 5;
            if (i == 11 || i == 18)
                field[i].isWhite = 1;
            else
                field[i].isRed = 1;
        }
        if (i == 7 || i == 16) {
            field[i].pieces = 3;
            if (i == 7)
                field[i].isRed = 1;
            else
                field[i].isWhite = 1;
        }
        if (i % 23 == 0) {
            field[i].pieces = 2;
            if (i == 23)
                field[i].isRed = 1;
            else
                field[i].isWhite = 1;
        }
    }
}

void draw_map(char**& map) {
    char indexes[6];
    int index = 13;
    int x = 2, y = 2, j = 0;

    for (int i = 0; i < fields / 2; i++) {
        gotoxy(x + 5 * i, y - 1);
        if (i == 6) {
            cputs("      ");
            x += 6;
            gotoxy(x + 5 * i, y - 1);
        }
        sprintf(indexes, "   %d", index++);
        cputs(indexes);
    }
    x -= 6;
    index = 12;

    for (j = 0; j < mapH; j++) {
        gotoxy(x, y + j);
        cputs(map[j]);
    }

    for (int i = 0; i < fields / 2; i++) {
        gotoxy(x + 5 * i, y + j);
        if (i == 6) {
            cputs("      ");
            x += 6;
            gotoxy(x + 5 * i, y + j);
        }
        sprintf(indexes, "   %d", index--);
        cputs(indexes);
    }
    x -= 5;
    gotoxy(mapW / 2, y + mapH / 2);
    cputs("BANDA");
}

void draw_score(Turn& turn, Match& match) {
    char* txt = new char[32];

    gotoxy(mapW / 2, 2 * mapY + mapH);
    sprintf(txt, "ROUND: %d", match.roundNo);
    cputs(txt);

    gotoxy(mapW / 2, 2 * mapY + mapH + 1);
    sprintf(txt, "TURN: %d", turn.turnNo);
    cputs(txt);

    textcolor(RED);
    gotoxy(mapW / 4, mapX + mapH);
    sprintf(txt, "P1: %d", match.redP);
    cputs(txt);

    textcolor(WHITE);
    gotoxy(mapW * 3 / 4, mapX + mapH);
    sprintf(txt, "P2: %d", match.whiteP);
    cputs(txt);
}

void draw_names(Turn& turn, Match& match) {
    char* txt = new char[32];

    gotoxy(mapX + mapW, mapY + mapH / 2);
    cputs("HOME");

    textcolor(RED);
    gotoxy(mapX + mapW, mapY + mapH / 4);
    sprintf(txt, "RED: %d", turn.redHouse);
    cputs(txt);
    gotoxy(mapW / 2 + 1, mapY + mapH / 4);
    sprintf(txt, "<>%d", turn.redBand);
    cputs(txt);


    textcolor(WHITE);
    gotoxy(mapX + mapW, (mapY + mapH) * 3 / 4 + 1);
    sprintf(txt, "WHITE: %d", turn.whiteHouse);
    cputs(txt);
    gotoxy(mapW / 2 + 1, (mapY + mapH) * 3 / 4 + 1);
    sprintf(txt, "<>%d", turn.whiteBand);
    cputs(txt);

    textcolor(LIGHTGREEN);
    delete[] txt;
}

void draw_pieces(Field*& field) {
    int y = 2, x = 5, i;
    for (i = fields / 2; i < fields; i++) {
        if (i == 18)
            x += 6;
        for (int j = 0; j < field[i].pieces; j++) {
            if (field[i].isRed)
                textcolor(RED);
            else
                textcolor(WHITE);
            gotoxy(x + 5 * (i - fields / 2), y + j + top12y);
            cputs("<>");
        }
    }
    x = x + 5 * (i - fields / 2);
    for (i = 0; i < fields / 2; i++) {
        if (i == 6)
            x -= 6;
        for (int j = 0; j < field[i].pieces; j++) {
            if (field[i].isRed)
                textcolor(RED);
            else
                textcolor(WHITE);
            gotoxy(x - 5 * (i + 1), y - j + bot12y);
            cputs("<>");
        }
    }
    textcolor(LIGHTGREEN);
}

void draw_menu() {
    int y = 1;
    gotoxy(menu_x, y++);
    cputs("<- -> = choose field");
    gotoxy(menu_x, y++);
    cputs("down arrow = choose dice");
    gotoxy(menu_x, y++);
    cputs("enter = make move");
    gotoxy(menu_x, y++);
    cputs("s = save game");
    gotoxy(menu_x, y++);
    cputs("l = load game");
    gotoxy(menu_x, y++);
    cputs("r = roll dices");
    gotoxy(menu_x, y++);
    cputs("q = exit");
}

void draw_dices(int* dices) {
    char* txt = new char[32];

    for (int i = 0; i < dicesNo; i++) {
        sprintf(txt, "Dice %d: %d \n", i + 1, dices[i]);
        gotoxy(menu_x, dicesLine + i);
        cputs(txt);
    }

    if (dices[0] == dices[1]) {
        gotoxy(menu_x, dicesLine + dicesNo);
        cputs("DUBLET");
    }

    delete[] txt;
}

void draw_cursor(Field*& field, Turn& turn, int& index) {
    int x = index;
    if (turn.redMove)
        textcolor(RED);
    else
        textcolor(WHITE);
    if (index > fields / 2 - 1) {
        x %= 12;
        if (index >= fields * 3 / 4)
            gotoxy(5 * x + mapX + fields / 4, top12y);
        else
            gotoxy(5 * x + mapX, top12y);
    }
    if (index < 12) {
        if (index < fields / 4)
            gotoxy(mapW - 5 * x - mapX, mapH + mapY);
        else
            gotoxy(mapW - 5 * x - mapX - 6, mapH + mapY);
    }
    putch('>');
    textcolor(LIGHTGREEN);
}

void draw_choice(bool& dice) {
    if (dice)
        gotoxy(menu_x - 1, dicesLine);
    if (!dice)
        gotoxy(menu_x - 1, dicesLine + 1);
    putch('>');
}

void draw_game(Field*& field, Turn& turn, Match& match, char**& map, bool& dice, int*& dices, int& n, bool& rolled) {
    textbackground(BLACK);
    clrscr();
    textcolor(LIGHTGREEN);

    draw_menu();
    draw_map(map);
    draw_pieces(field);
    draw_names(turn, match);
    draw_score(turn, match);

    if (turn.turnNo > 0) {
        draw_cursor(field, turn, n);
        draw_dices(dices);
        draw_choice(dice);
    }
    textcolor(LIGHTGREEN);
    if (!rolled) {
        gotoxy(menu_x, dicesLine + 2);
        cputs("ROLL THE DICE");
    }
}

int set_cursor(Turn& turn, Field*& field) {
    int i;
    if (turn.redMove)
        i = fields - 1;
    else
        i = 0;
    while (1) {
        if (turn.redMove) {
            if (field[i].isRed)
                break;
            i--;
        }
        else {
            if (field[i].isWhite)
                break;
            i++;
        }
    }
    return i;
}

int* roll_dice(bool& dublet) {
    int* dices = new int[dicesNo];
    srand(time(NULL));
    for (int i = 0; i < dicesNo; i++) {
        dices[i] = rand() % 6 + 1;
    }
    if (dices[0] == dices[1])
        dublet = 1;
    else
        dublet = 0;
    return dices;
}

bool escape(Field*& field, Turn& turn) {
    int esc = 0;
    if (turn.redMove) {
        for (int i = 0; i < fields / 4; i++) {
            if (field[i].isRed)
                esc += field[i].pieces;
        }
        if (esc + turn.redHouse == checkers) {
            return true;
        }
        else
            return false;
    }
    else {
        for (int i = fields * 3 / 4; i < fields; i++) {
            if (field[i].isWhite)
                esc += field[i].pieces;
        }
        if (esc + turn.whiteHouse == checkers)
            return true;
        else
            return false;
    }
}

void left(Turn& turn, Field*& field, int& index) {
    int j = 1, i = index - 1;
    if (index > 1) {
        if (turn.redMove && i >= 0) {
            while (!field[i--].isRed) {
                j++;
            }
        }
        if (!turn.redMove && i >= 0) {
            while (!field[i--].isWhite) {
                j++;
            }
        }
        if (index - j >= 0)
            index = index - j;
    }
}

void right(Turn& turn, Field*& field, int& index) {
    int j = 1, i = index + 1;
    if (index < 23) {
        if (turn.redMove && i < 23) {
            while (!field[i++].isRed) {
                j++;
            }
        }
        if (!turn.redMove && i < 23) {
            while (!field[i++].isWhite) {
                j++;
            }
        }
        if (index + j <= 23)
            index = index + j;
    }
}

void move2(Turn& turn, Field*& field, int from, int m) {
    field[from].pieces--;
    field[from + m].pieces++;
    if (turn.redMove) {
        field[from + m].isWhite = 0;
        field[from + m].isRed = 1;
    }
    else {
        field[from + m].isWhite = 1;
        field[from + m].isRed = 0;
    }
}

void beat(Turn& turn, Field*& field, int from, int m) {
    if (turn.redMove) {
        if (field[from + m].isRed) {
            field[from + m].pieces++;
        }
        else if (field[from + m].isWhite) {
            field[from + m].isWhite = 0;
            field[from + m].isRed = 1;
            turn.whiteBand++;
        }
    }
    else if (!turn.redMove) {
        if (field[from + m].isWhite) {
            field[from + m].pieces++;
        }
        else if (field[from + m].isRed) {
            field[from + m].isWhite = 1;
            field[from + m].isRed = 0;
            turn.redBand++;
        }
    }
}

void enter(Turn& turn, Field*& field, int from, int& moves) {
    field[from].pieces--;
    if (turn.redMove) {
        if (field[from].pieces == 0)
            field[from].isRed = 0;
        turn.redHouse++;
        moves++;
    }
    else {
        if (field[from].pieces == 0)
            field[from].isWhite = 0;
        turn.whiteHouse++;
        moves++;
    }
}

void take(Turn& turn, Field*& f, int from, int m, int& moves, bool& dice, int& index) {
    moves++;
    if (f[from + m].pieces == 0)
        move2(turn, f, from, m);
    else if (f[from + m].pieces == 1) {
        beat(turn, f, from, m);
        f[from].pieces--;
    }
    else if (turn.redMove && f[from + m].isRed) {
        f[from].pieces--;
        f[from + m].pieces++;
    }
    else if (!turn.redMove && f[from + m].isWhite) {
        f[from].pieces--;
        f[from + m].pieces++;
    }
    else {
        moves--;
        dice = !dice;
    }
    if (f[from].pieces == 0) {
        f[from].isWhite = 0;
        f[from].isRed = 0;
    }
}

void band_white(Turn& turn, Field*& f, bool& dice, int& moves, int m, int& cnt) {
    if (f[m].pieces > 1 && f[m].isRed) {
        cnt++;
        dice = !dice;
    }
    else if (f[m].pieces == 1 && f[m].isRed) {
        beat(turn, f, 0, m);
        turn.whiteBand--;
        dice = !dice;
        moves++;
    }
    else if (f[m].isWhite || !f[m].isRed) {
        f[m].pieces++;
        turn.whiteBand--;
        f[m].isWhite = 1;
        dice = !dice;
        moves++;
    }
}

void band_red(Turn& turn, Field*& f, bool& dice, int& moves, int to, int& cnt) {
    if (f[to].pieces > 1 && f[to].isWhite) {
        cnt++;
        dice = !dice;
    }
    else if (f[to].pieces == 1 && f[to].isWhite) {
        beat(turn, f, 0, to);
        dice = !dice;
        turn.redBand--;
        moves++;
    }
    else if (f[to].isRed || !f[to].isWhite) {
        f[to].pieces++;
        turn.redBand--;
        f[to].isRed = 1;
        dice = !dice;
        moves++;
    }
}

void band(Turn& turn, Field*& f, bool& dice, int& moves, int m, int& cnt) {
    m--;
    int to = fields - m;
    if (turn.redMove) {
        to--;
        band_red(turn, f, dice, moves, to, cnt);
    }
    else if (!turn.redMove) {
        band_white(turn, f, dice, moves, m, cnt);
    }
    else {
        gotoxy(menu_x, err_y);
        cputs(err);
    }
}

void move(Turn& turn, Field*& f, int from, int m, int& moves, bool& dice, int& index, int& cnt) { // f = fields
    bool ent = false;
    ent = escape(f, turn);
    if ((turn.redBand == 0 && turn.redMove) || (turn.whiteBand == 0 && !turn.redMove)) {
        if (f[from].pieces > 0) {
            if (turn.redMove)
                m = m * -1;
            if ((from + m > fields - 1 && !turn.redMove) || (from + m < 0 && turn.redMove)) {
                if (ent) {
                    enter(turn, f, from, moves);
                    dice = !dice;
                }
            }
            else {
                take(turn, f, from, m, moves, dice, index);
                dice = !dice;
            }
        }
    }
    if ((turn.redBand > 0 && turn.redMove) || (turn.whiteBand > 0 && !turn.redMove)) {
        band(turn, f, dice, moves, m, cnt);
    }
}

void save_game(int& moves, int& moveNo, bool& quit, bool& dice, bool& dublet, int*& dices, Turn& t, Match& m, Field*& field) {
    FILE* f = fopen(save, "w+");
    if (f == NULL) {
        gotoxy(1, err_y);
        cputs(err2);
        return;
    }
    int b, q, d, mov;
    q = quit ? 1 : 0;
    b = dublet ? 1 : 0;
    d = dice ? 1 : 0;
    mov = t.redMove ? 1 : 0;
    fprintf(f, "%d %d %d %d %d %d %d ", moves, moveNo, q, d, b, dices[0], dices[1]);
    fprintf(f, "%d %d %d ", m.redP, m.whiteP, m.roundNo);
    fprintf(f, "%d %d %d %d %d %d ", t.redBand, t.redHouse, t.redMove, t.turnNo, t.whiteBand, t.whiteHouse);
    for (int i = 0; i < fields; i++) {
        int r, w;
        r = field[i].isRed ? 1 : 0;
        w = field[i].isWhite ? 1 : 0;
        fprintf(f, "%d %d %d ", r, w, field[i].pieces);
    }
    fclose(f);
}

void load_game(int& moves, int& mNo, bool& quit, bool& dice, bool& dublet, int*& dices, Turn& t, Match& m, Field*& fi) {
    FILE* f = fopen(save, "r+");
    if (f == NULL) {
        gotoxy(menu_x, err_y);
        cputs(err3);
        return;
    }
    int b, q, d, mov;
    fscanf(f, "%d %d %d %d %d %d %d ", &moves, &mNo, &q, &d, &b, &dices[0], &dices[1]);
    quit = q == 1;
    dublet = b == 1;
    dice = d == 1;
    fscanf(f, "%d %d %d ", &m.redP, &m.whiteP, &m.roundNo);
    fscanf(f, "%d %d %d %d %d %d ", &t.redBand, &t.redHouse, &mov, &t.turnNo, &t.whiteBand, &t.whiteHouse);
    t.redMove = mov == 1;
    for (int i = 0; i < fields; i++) {
        int w, r;
        fscanf(f, "%d %d %d ", &r, &w, &fi[i].pieces);
        fi[i].isRed = r == 1;
        fi[i].isWhite = w == 1;
    }
    fclose(f);
}

void operate_roll(Turn& turn, int*& dices, bool& rolled, bool& quit, bool& dublet) {
    char zn = getch();
    if (zn == 'r') {
        dices = roll_dice(dublet);
        rolled = 1;
        draw_dices(dices);
    }
    else if (zn == 'q') {
        quit = 1;
    }
    else operate_roll(turn, dices, rolled, quit, dublet);
}

void operate_move(Turn& turn, Field*& field, Match& match, char**& map, int& index, bool& dice, int& moves, int*& dices, bool& rolled, bool& quit, char zn, bool& dublet, int& cnt) {
    if (zn == '\r') {
        if (dice) {
            move(turn, field, index, dices[0], moves, dice, index, cnt);
        }
        else if (!dice) {
            move(turn, field, index, dices[1], moves, dice, index, cnt);
        }
    }
    else if (zn == 'q') {
        quit = 1;
    }
    else operate_move(turn, field, match, map, index, dice, moves, dices, rolled, quit, zn, dublet, cnt);
    draw_game(field, turn, match, map, dice, dices, index, rolled);
}

void operate_turn(Turn& turn, Field*& field, Match& match, bool& rolled, int& index) {
    index = set_cursor(turn, field);
    turn.redMove = !turn.redMove;
    turn.turnNo++;
    if (turn.redHouse == 15 || turn.whiteHouse == 15) {
        turn.turnNo = 0;
        match.roundNo++;
        turn.redHouse = 0;
        turn.whiteHouse = 0;
        setup_pieces(field);
        if (turn.redHouse == 15) {
            match.redP++;
            if (turn.whiteBand > 0)
                match.redP += 2;
            else if (turn.whiteHouse == 0)
                match.redP++;
        }
        else if (turn.whiteHouse == 15) {
            match.whiteP++;
            if (turn.redBand > 0)
                match.whiteP += 2;
            else if (turn.redHouse == 0)
                match.whiteP++;
        }
    }
}

void operate_arrows(char& zn, int& zero, Turn& t, Field*& f, int& i, int moves, bool& dice, int cnt) {
    if (zn == 0) {
        zero = 1;
        zn = getch();
        if (zn == 0x4b)
            left(t, f, i);
        else if (zn == 0x4d)
            right(t, f, i);
        else if (zn == 0x50 && moves == 0 && cnt == 0)
            dice = !dice;
    }
}

void operate_keys2(int*& d, bool& r, bool& dice, Field*& f, Turn& t, bool& quit, int& i, char**& map, Match& m, int& moves, bool& dublet, int& moveNo, bool& op, char zn, int& cnt) {
    if (zn == '\r' && r) {
        operate_move(t, f, m, map, i, dice, moves, d, r, quit, zn, dublet, cnt);
        if (t.redHouse == 15 || t.whiteHouse == 15)
            operate_turn(t, f, m, r, i);  // t - turn, f - field, m - match, r - rolled, i - index
        op = 1;
    }
    else if (zn == 's')
        save_game(moves, moveNo, quit, dice, dublet, d, t, m, f);
    else if (zn == 'l')
        load_game(moves, moveNo, quit, dice, dublet, d, t, m, f);
}

void operate_keys(int*& d, bool& r, bool& dice, Field*& f, Turn& t, bool& quit, int& i, char**& map, Match& m, int& moves, bool& dublet, int& moveNo, int& cnt) {
    while (1) {
        int zero = 0;
        char zn = getch();
        operate_arrows(zn, zero, t, f, i, moves, dice, cnt);
        if (zero == 0) {
            bool op = 0;
            if (zn == 'r') {
                if (!r) {
                    d = roll_dice(dublet);
                    if (dublet)
                        moveNo = dub;
                    r = 1;
                }
                else
                    operate_keys(d, r, dice, f, t, quit, i, map, m, moves, dublet, moveNo, cnt);
            }
            operate_keys2(d, r, dice, f, t, quit, i, map, m, moves, dublet, moveNo, op, zn, cnt);
            if (op) {
                break;
            }
            if (zn == 'q') {
                quit = 1;
                break;
            }
        }
        draw_game(f, t, m, map, dice, d, i, r); // f - field, t - turn, m - match, d - dices, i - index
    }
}

void decide_first(Turn& turn, Field*& field, int*& dices, bool& rolled, bool& quit, Match& match, char**& map, int& index, bool& dublet) {
    while (1) {
        operate_roll(turn, dices, rolled, quit, dublet);
        if (quit)
            break;
        if (dices[0] > dices[1]) {
            turn.redMove = 0;
            turn.turnNo++;
            gotoxy(menu_x, dicesLine + 2);
            cputs("WHITE MOVES FIRST");
            break;
        }
        else if (dices[0] < dices[1]) {
            turn.redMove = 1;
            turn.turnNo++;
            gotoxy(menu_x, dicesLine + 2);
            cputs("RED MOVES FIRST");
            break;
        }
        else {
            gotoxy(menu_x, dicesLine + 2);
            cputs("TIE, ROLL AGAIN");
        }
    }
    index = set_cursor(turn, field);
}

void game(int& i, int& moves, int& moveNo, bool& quit, bool& dice, bool& dublet, int*& dices, char**& map, Turn& turn, Match& m, Field*& f) {
    do {
        bool r = 0;
        int cnt = 0;
        moveNo = 2;
        draw_game(f, turn, m, map, dice, dices, i, r);

        if (turn.turnNo == 0) {
            decide_first(turn, f, dices, r, quit, m, map, i, dublet);
            if (!quit)
                operate_roll(turn, dices, r, quit, dublet);
            draw_game(f, turn, m, map, dice, dices, i, r);
        }
        if (turn.turnNo > 0) {
            while (moves < moveNo && cnt != moveNo) {
                operate_keys(dices, r, dice, f, turn, quit, i, map, m, moves, dublet, moveNo, cnt);
                if (quit || turn.turnNo == 0)
                    break;
            }
            r = 0;
            if (turn.turnNo > 0)
                operate_turn(turn, f, m, r, i);
        }
        moves = 0;
    } while (!quit);
}

int main() {
    int index = 0, moves = 0, moveNo = 2;
    bool quit = 0, dice = 1, dublet = 0;
    int* dices = new int[dicesNo];
    char** map = generate_map();
    Turn turn;
    Match match;
    Field* field = new Field[fields];
    setup_pieces(field);

    settitle("Hubert Zedlewski 193339"); // sets the window title
    _setcursortype(_NOCURSOR); // hide the blinking cursor

    game(index, moves, moveNo, quit, dice, dublet, dices, map, turn, match, field);

    gotoxy(1, err_y);
    _setcursortype(_NORMALCURSOR);  // show the cursor so it will be
    // visible after the program ends

    return 0;
}