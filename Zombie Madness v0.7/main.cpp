#include <iostream>
#include <ctime>
#include <cstdlib>
#include <curses.h>
#include <math.h>
#include "animations.h"

using namespace std;

char AdvMap[180][600];
char AdvMap_tmp[180][600];
char deserted_buildings[6][10][19] =
{
    "..................",
    ".################.",
    ".D....|.........#.",
    ".#....D.........#.",
    ".#....|---D-----#.",
    ".#....|.........#.",
    ".#....|.........#.",
    ".#....|.........#.",
    ".##D#_##__###__##.",
    "..................",
// space
    "..................",
    ".################.",
    ".#....|.........#.",
    ".#....D.........#.",
    ".#....|.........#.",
    ".#....|,........#.",
    ".#..............#.",
    ".#....|,........#.",
    ".##D#_##_______##.",
    "..................",
// space
    "..................",
    ".##D#############.",
    ".#..............#.",
    ".#-----------D--#.",
    ".#..............#.",
    ".#[OoOO|OOoO]-.-#.",
    ".#..............#.",
    ".#.....h_h_h_h_h#.",
    ".##D#[_________]#.",
    "..................",
// space
    "..................",
    ".################.",
    ".#....#.........#.",
    ".#....#,........#.",
    ".#..............#.",
    ".#....######D####.",
    ".#....#.........#.",
    ".#....#,........#.",
    ".##D-##___#######.",
    "..................",
// space
    "..................",
    ".----------D-----.",
    ".|..............|.",
    ".|..............|.",
    ".|..............|.",
    ".|--D-|.........|.",
    ".|....|.........D.",
    ".|....|.........|.",
    ".--D-------------.",
    "..................",
// space
    "..................",
    ".----D-----------.",
    ".|..............|.",
    ".|..............|.",
    ".|..............|.",
    ".|..............|.",
    ".|.....'...x....|.",
    ".|...#-x.....'-#|.",
    ".--D--x,......x--.",
    "..................",
};

bool NewGame = true;
bool survival_mode = false;

char BloodMap[18][60];
char AdvBloodMap[180][600];
char TrapMap[18][60];
char Map[18][60] = { "###########################################################",
                     "#                                                         #",
                     "#                                                         #",
                     "#                                                         #",
                     "#                                                         #",
                     "#                                                         #",
                     "#                                                         #",
                     "#                                                         #",
                     "#                                                         #",
                     "#                                                         #",
                     "#                                                         #",
                     "#                                                         #",
                     "#                                                         #",
                     "#                                                         #",
                     "#                                                         #",
                     "#                                                         #",
                     "#                                                         #",
                     "###########################################################"
                   };

char locations[20][18][60] = { "###########################################################",
                               "#                                                         #",
                               "#                                                         #",
                               "#      &                                                  #",
                               "#                                                         #",
                               "#                 0----B------D----B---0                  #",
                               "#                 |                    |                  #",
                               "#                 D                    D                  #",
                               "#                 |                    |                  #",
                               "#                 0---D-----D--0-------0                  #",
                               "#                 |AA   |      |                          #",
                               "#                 |++   |      |                          #",
                               "#                 0-----0--B---0                          #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "###########################################################",
                               // space
                               "###########################################################",
                               "#                                                         #",
                               "#                                                         #",
                               "#      &                                                  #",
                               "#                                                         #",
                               "#                           0----B---0                    #",
                               "#                           |      A+|                    #",
                               "#                           |        |                    #",
                               "#                   0---D---0        B                    #",
                               "#                   |                |                    #",
                               "#                   |    [=]         |                    #",
                               "#                   0------------B---0                    #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "###########################################################",
                               // space
                               "###########################################################",
                               "#                                                         #",
                               "#                                                         #",
                               "#      &                                                  #",
                               "#                                                         #",
                               "#                            |====|                       #",
                               "#                    0---------DD-----B--0                #",
                               "#                    |                   |                #",
                               "#                    B                   |                #",
                               "#                    |     _|BB BB|_     B                #",
                               "#                    |    |A        |    |                #",
                               "#                    |   |+          |   |                #",
                               "#                    0-------------------0                #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "###########################################################",
                               // space
                               "###########################################################",
                               "#                                                         #",
                               "#                                                         #",
                               "#      &                                                  #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                    0-------------B-----0                #",
                               "#                    |                   |-               #",
                               "#                    B                   D                #",
                               "#                    |             --D---|-               #",
                               "#                    |             |     |                #",
                               "#                    |             |   +A|                #",
                               "#                    0----B----D---------0                #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "###########################################################",
                               // space
                               "###########################################################",
                               "#                                                         #",
                               "#                                                         #",
                               "#      &                                                  #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                   0--------0----D----0                  #",
                               "#                   |A+      |         |                  #",
                               "#                   |        D         B                  #",
                               "#                   |        |         |                  #",
                               "#                   0-----B--0--D------0                  #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "###########################################################",
                               // space
                               "###########################################################",
                               "#                                                         #",
                               "#                                                         #",
                               "#      &                                                  #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                          0-B----0-B--0                  #",
                               "#                          |      |  +A|                  #",
                               "#                          |      |    |                  #",
                               "#                          0----D-0D---0                  #",
                               "#                          B      |                       #",
                               "#                          |      |                       #",
                               "#                          0-D----0                       #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "###########################################################",
                               // space
                               "###########################################################",
                               "#                 B                  B                    #",
                               "# &               B      |====|      B                    #",
                               "#    0-------B-------------DD-------------B----------0    #",
                               "#    |         | +A                  A+ |            |    #",
                               "#    |         |                        |            |    #",
                               "#    B         0========================0            |    #",
                               "#    |         |========================|            |    #",
                               "#    D                                               D    #",
                               "#    D             0----0         0----0             D    #",
                               "#    |---D---------|    |         |    |---D---------|    #",
                               "#    |             |    |         |    |             B    #",
                               "#    |             |    0--D---D--0    |             |    #",
                               "#    |             |      |=====|      |             |    #",
                               "#    0-------B--D--0     B|=====|B     0----------D--0    #",
                               "#                        BBBBBBBBB                        #",
                               "#                                                         #",
                               "###########################################################",
                               // space
                               "###########################################################",
                               "#                                                         #",
                               "#                                                         #",
                               "#   0----0    &                                           #",
                               "#   |A+  |         0---------- -----0----0                #",
                               "#   |    |         |__________D_____|____|                #",
                               "#   0-=--0         |                |    |                #",
                               "#   |_=__|         |                D    |                #",
                               "#                  |                |    B                #",
                               "#                  |                0----|                #",
                               "#                  |                |____|                #",
                               "#                  |                     |                #",
                               "#                  |                     |                #",
                               "#                  0--------0-D-0--------0                #",
                               "#                  |________|===|________|                #",
                               "#                           |===|                         #",
                               "#                                                         #",
                               "###########################################################",
                               // space
                               "###########################################################",
                               "#                                             |#          #",
                               "#                                             |#  0-----0 #",
                               "#    &                                        |#  |+   A| #",
                               "#                                             |#  |-   -| #",
                               "#                                             |#  |+   A| #",
                               "#                                             |#  |-   -| #",
                               "#                                             |#  |A   +| #",
                               "#                                             -#  |-   -| #",
                               "#                                             D   |A   +| #",
                               "#                                             D   0--D--0 #",
                               "#                                             -#          #",
                               "#                                             |#          #",
                               "#                                             |#          #",
                               "#                                             |#          #",
                               "#                                             |#          #",
                               "#                                             |#          #",
                               "###########################################################",
                               // space
                               "###########################################################",
                               "#                                                         #",
                               "#    &                                                    #",
                               "#                                                         #",
                               "#----D---------------B---------D----B-------------D-------#",
                               "#            BB                               BB          #",
                               "#            BB                               BB          #",
                               "#            BB                               BB          #",
                               "#            BB                               BB          #",
                               "#            BB                               BB          #",
                               "#            BB                               BB          #",
                               "#            BB                               BB          #",
                               "#            BB                               BB          #",
                               "#--------D----------D---------B----B-------D-----D---######",
                               "#                                                    #A++A#",
                               "#                                                    #    #",
                               "#                                                    D    #",
                               "###########################################################",
                               // space
                               "###########################################################",
                               "#   |    | | |   | | | | |###                             #",
                               "# & |  | | | | | |   | | |##0                             #",
                               "#   |  | | |   | | |   | |##|                             #",
                               "#   |--| | | | | | | |   |##|                             #",
                               "#          | | | | | |-| |##|                             #",
                               "#   |-|- | | | |   | | | |##|                             #",
                               "#   | |  | | | | | | | | |##|                             #",
                               "#---| |  | | | | | | | |-|--0            A+A+             #",
                               "#   | |  |   | | | |   |                 +A+A             #",
                               "# --| |  |---| | | | | | |--0                             #",
                               "#     |        | | | | | |##|                             #",
                               "# --| |- |---| | | | |-| |##|                             #",
                               "#   |    |   | | |   |   |##|                             #",
                               "#   |----| | |   |-| | | |##|                             #",
                               "#   |    | | |- -| |   | |##0                             #",
                               "#      |   |       | | | |###                             #",
                               "###########################################################",
                               // space
                               "###########################################################",
                               "#                                                         #",
                               "#                                                         #",
                               "#      &                                                  #",
                               "#                                                         #",
                               "#                             0-B---0---B-0               #",
                               "#                             |     |     |               #",
                               "#                             |     |     |               #",
                               "#                             |     D     |               #",
                               "#                             |     |     D               #",
                               "#                             |     |   +A|               #",
                               "#                             0-D-B-0-----0               #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "###########################################################",
                               // space
                               "###########################################################",
                               "#                                                         #",
                               "#                                                         #",
                               "#      &     0-----B-------------------------------0      #",
                               "#            |                                   A+|      #",
                               "#            B                                     B      #",
                               "#            |                                     |      #",
                               "#            |                                     |      #",
                               "#            D                                     D      #",
                               "#            |                                     |      #",
                               "#            |                                     |      #",
                               "#            |                                     |      #",
                               "#            |A+                                   |      #",
                               "#            0---D-B----------------D-----B--------0      #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "###########################################################",
                               // space
                               "###########################################################",
                               "#                                                         #",
                               "#                                                         #",
                               "#      &                                                  #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "#                                                         #",
                               "###########################################################",
                             };

class Trap
{
public:
    int damage;
    int range;
    int cost;
};

class Block
{
public:
    int cost;
};

class C4
{
public:
    int x;
    int y;
    bool set;
};

class BUL
{
public:
    int x;
    int y;
    bool Shot;
    char dir;
};

class GUN
{
public:
    int cap;
    int clips;
    int damage;
    int speedtime;
    int speedtick;
    BUL bullet[10000000];
    string name;
    string desc;
};

class Player
{
public:
    int y;
    int x;
    int HP;
    int MAXHP;
    int sight;
    double GOLD;
    Trap trap;
    Block block;
    C4 c4[10000000];
    int c4_max;
    int c4Ammo;
    GUN gun;
    char c;
    int damage;
    int ammo;
    char dir;
    int damage_min;
};

class Zombie
{
public:
    int y;
    int x;
    int HP;
    bool DEAD;
    int damage;
    int speedcount;
};


class Game
{
public:
    Player p1;
    Zombie zom[1000];
    int zombies_max;
    int spawntime;
    int zombies_dead;
    int zombies_alive;
    int zombies_damage_base;
    int zombies_damage_min;
    int damcost;
    int hpcost;
    int hprcost;
    int speed;
    int DayNightTime;
    int templvl;
    double bounty;
    bool RandHealth;
    int HP;
    int wave;
    string lastaction;
};
Game game;

void Movement();
void EMovement();
void DrawBlood();
void DrawC4();
void DrawBuls();
void DrawPlayer();
void DrawZoms();
void DrawGUI();
void Draw();

int dist(int y0,int x0,int y1,int x1)
{
    return pow(y0-y1,2)+pow(x0-x1,2);
}

extern char GameOver[100][25][80];


bool in_range(int y0,int x0,int y1,int x1,int r)
{
    return dist(y0,x0/2,y1,x1/2)<=pow(r,2);
}

bool los(int y0,int x0,int y1,int x1,char opaque)
{
    //Bresenham's line algorithm
    bool steep=fabs(y1-y0)>fabs(x1-x0);
    if (steep)
    {
        swap(x0,y0);
        swap(x1,y1);
    }
    if (x0>x1)
    {
        swap(x0,x1);
        swap(y0,y1);
    }
    float err_num=0.0;
    int y=y0;
    for (int x=x0; x<=x1; x++)
    {
        if (x>x0 && x<x1)
        {
            if (steep)
            {
                if (opaque==Map[x][y])
                    return false;
            }
            else
            {
                if (opaque==Map[y][x])
                    return false;
            }
        }

        err_num+=(float)(fabs(y1-y0))/(float)(x1-x0);
        if (0.5<fabs(err_num))
        {
            y+=y1>y0?1:-1;
            err_num--;
        }
    }
    return true;
}

bool los2(int y0,int x0,int y1,int x1,char opaque)
{
    //Bresenham's line algorithm
    bool steep=fabs(y1-y0)>fabs(x1-x0);
    if (steep)
    {
        swap(x0,y0);
        swap(x1,y1);
    }
    if (x0>x1)
    {
        swap(x0,x1);
        swap(y0,y1);
    }
    float err_num=0.0;
    int y=y0;
    for (int x=x0; x<=x1; x++)
    {
        if (x>x0 && x<x1)
        {
            if (steep)
            {
                if (opaque==AdvMap[x][y])
                    return false;
            }
            else
            {
                if (opaque==AdvMap[y][x])
                    return false;
            }
        }

        err_num+=(float)(fabs(y1-y0))/(float)(x1-x0);
        if (0.5<fabs(err_num))
        {
            y+=y1>y0?1:-1;
            err_num--;
        }
    }
    return true;
}

void Gen_New_AdvMap()
{
    // floor
    for (int y = 0; y < 180; y++)
    {
        for (int x = 0; x < 600; x++)
        {
            AdvMap[y][x] = '.';
        }
    }
    // boarder walls
    for (int y = 0; y < 180; y++)
    {
        AdvMap[y][0] = '#';
        AdvMap[y][600] = '#';
    }
    for (int x = 0; x < 600; x++)
    {
        AdvMap[0][x] = '#';
        AdvMap[180][x] = '#';
    }
    // add player start position
    int y0 = rand()% 170 + 10;
    int x0 = rand()% 590 + 10;
    AdvMap[y0][x0] = '&';
    game.p1.y = y0;
    game.p1.x = x0;

    // place buildings
    int times_b = rand()% 500 + 100;

    for (int timesx = 0; timesx < times_b; timesx++)
    {

        bool space_free; // set space free
build:
        int building = rand()%6; // pick a building
        int yb = rand()% 175 + 2; // look for location y
        int xb = rand()% 595 + 2; // look for location x

        space_free = false; // reset space free to false
        for (int y2 = yb; y2 < yb+10; y2++) // check if space is taken
        {
            for (int x2 = xb; x2 < xb+18; x2++) // check if space is taken
            {
                if (AdvMap[y2][x2] == '.') // checking
                {
                    space_free = true;
                }
                else
                {
                    space_free = false;
                    goto build;
                }
            }
        }
        if (space_free == true)
        {
            for (int y = 0; y < 10; y++)
            {
                for (int x = 0; x < 18; x++)
                {
                    AdvMap[yb+y][xb+x] = deserted_buildings[building][y][x];
                }
            }

        }
        else
        {
            goto build;
        }
    }
}

void DrawBlood2()
{
    for (int i = 0; i < game.zombies_max; i++)
    {
        if (game.zom[i].DEAD == true)
        {
            BloodMap[game.zom[i].y][game.zom[i].x] = '%';
        }
    }
    for (int i = 0; i < game.zombies_max; i++)
    {
        if (game.zom[i].DEAD == false)
        {
            for (int y = 0; y < 18; y++)
            {
                for (int x = 0; x < 60; x++)
                {
                    if (AdvBloodMap[y][x] != 0)
                    {
                        if (AdvMap[y][x] == ' ')
                        {
                            if (in_range(game.p1.y,game.p1.x,y,x,game.p1.sight))
                            {
                                mvaddch(y,x,AdvBloodMap[y][x]|COLOR_PAIR(1));
                            }
                        }

                    }
                }
            }
        }
    }
}

int respawn_count = 0;
int respawn_count_max = 100;
int spawn_amount = 10;
int spawn_count = 0;

void DrawZoms2()
{
    for (int i = 0; i < game.zombies_max; i++)
    {
        if (game.zom[i].DEAD == false)
        {
            //if  (in_range(game.p1.y,game.p1.x,game.zom[i].y,game.zom[i].x,8) == true)
            //{
                int wx = 0;
                int wy = 0;
                for (int y = 0; y < LINES; y++)
                {
                    for (int x = 0; x < COLS; x++)
                    {
                        wx = game.p1.x - (COLS/2) + x;
                        wy = game.p1.y - (LINES/2) + y;
                    }
                }
                if ((wx < 0) || (wx > 600) || (wy < 0) || (wy > 180)) { }
                else
                {
                    mvaddch(wy,wx,'Z'|COLOR_PAIR(2));
                }
            //}
        }
    }
}

void Adv_zomInit()
{
    for (int i = 0; i < game.zombies_max; i++)
    {
        game.zom[i].DEAD = true;
    }
}
void Adv_respawnZom()
{
    spawn_count = 0;
    if (respawn_count >= respawn_count_max)
    {
        for (int i = 0; i < game.zombies_max; i++)
        {
            if (game.zom[i].DEAD == true)
            {
                while (spawn_count <= spawn_amount)
                {
step1:
                    game.zom[i].x = rand()%595+3;
                    game.zom[i].y = rand()%175+3;
                    if (AdvMap[game.zom[i].y][game.zom[i].x] != '.')
                    {
                        goto step1;
                    }
                    else
                    {
                        spawn_count++;
                        game.zom[i].DEAD = false;
                    }
                }
            }
        }
    }
    else
    {
        respawn_count++;
    }
}

void Draw_AdvMap()
{
    for (int y = 0; y < LINES; y++)
    {
        for (int x = 0; x < COLS; x++)
        {
            int wx = game.p1.x - (COLS/2) + x;
            int wy = game.p1.y - (LINES/2) + y;
            if ((wx < 0) || (wx > 600) || (wy < 0) || (wy > 180)) { }
            else
            {
                if (AdvMap[wy][wx] != 0)
                {
                    if ( (in_range(game.p1.y,game.p1.x,wy,wx,8))
                            && (los2(game.p1.y,game.p1.x,wy,wx,'#'))
                            && (los2(game.p1.y,game.p1.x,wy,wx,'|'))
                            && (los2(game.p1.y,game.p1.x,wy,wx,'-'))
                            && (los2(game.p1.y,game.p1.x,wy,wx,'D')))
                    {
                        if (AdvMap[wy][wx] == 'T')
                        {
                            mvaddch(y,x,AdvMap[wy][wx]|COLOR_PAIR(4));
                        }
                        else if (AdvMap[wy][wx] == '+')
                        {
                            mvaddch(y,x,AdvMap[wy][wx]|COLOR_PAIR(2)|A_BOLD);
                        }
                        else if (AdvMap[wy][wx] == 'B')
                        {
                            mvaddch(y,x,AdvMap[wy][wx]|COLOR_PAIR(5));
                        }
                        else if (AdvMap[wy][wx] == '*')
                        {
                            mvaddch(y,x,AdvMap[wy][wx]|COLOR_PAIR(5));
                        }
                        else if (AdvMap[wy][wx] == ',')
                        {
                            mvaddch(y,x,AdvMap[wy][wx]|COLOR_PAIR(5));
                        }
                        else if (AdvMap[wy][wx] == '.')
                        {
                            mvaddch(y,x,AdvMap[wy][wx]|COLOR_PAIR(5));
                        }
                        else if (AdvMap[wy][wx] == '#')
                        {
                            if (game.DayNightTime == 0)
                            {
                                mvaddch(y,x,'#'|COLOR_PAIR(8));
                            }
                            else
                            {
                                mvaddch(y,x,'#'|COLOR_PAIR(4));
                            }
                        }
                        else if (AdvMap[wy][wx] == '-')
                        {
                            if (game.DayNightTime == 0)
                            {
                                mvaddch(y,x,'-'|COLOR_PAIR(8));
                            }
                            else
                            {
                                mvaddch(y,x,'-'|COLOR_PAIR(4));
                            }
                        }
                        else if (AdvMap[wy][wx] == '|')
                        {
                            if (game.DayNightTime == 0)
                            {
                                mvaddch(y,x,'|'|COLOR_PAIR(8));
                            }
                            else
                            {
                                mvaddch(y,x,'|'|COLOR_PAIR(4));
                            }
                        }
                        else if (AdvMap[wy][wx] == '0')
                        {
                            if (game.DayNightTime == 0)
                            {
                                mvaddch(y,x,'0'|COLOR_PAIR(8));
                            }
                            else
                            {
                                mvaddch(y,x,'0'|COLOR_PAIR(4));
                            }
                        }
                        else if (AdvMap[wy][wx] == 'D')
                        {
                            mvaddch(y,x,'D'|COLOR_PAIR(5));
                        }
                        else
                        {
                            mvaddch(y,x,AdvMap[wy][wx]);
                        }
                    } // else { mvaddch(y,x,'%'); }
                }
            }
        }
    }
    DrawBlood2();
}

/*void Move_player()
{
    int key = getch();
    if (key == KEY_LEFT)
    {
        if (AdvMap[game.p1.y][(game.p1.x-1)] == '.')
        {
            game.p1.x--;
        }
    }
    else if (key == KEY_RIGHT)
    {
        if (AdvMap[game.p1.y][(game.p1.x+1)] == '.')
        {
            game.p1.x++;
        }
    }
    else if (key == KEY_UP)
    {
        if (AdvMap[(game.p1.y-1)][game.p1.x] == '.')
        {
            game.p1.y--;
        }
    }
    else if (key == KEY_DOWN)
    {
        if (AdvMap[(game.p1.y+1)][game.p1.x] == '.')
        {
            game.p1.y++;
        }
    }
    flushinp();
} */

bool zomAtPoint(int y, int x);
bool p1AtPoint(int y, int x);
bool GetChar(int y, int x, char c);
int ZomDir(int id,char dir);
int P1Dir(char dir);
int P1X();
int P1Y();
int GetZomID(int y, int x);
bool GetChar2(int y, int x, char c);

void AdvMovement()
{
    int key = getch();
    if (key == 'q')
    {
        NewGame = false;
    }
    /*if (key == 'c')
    {
        placeC4();
    }
    if (key == 'd')
    {
        C4Det();
    }
    if (game.p1.gun.speedtick >= game.p1.gun.speedtime)   // check
    {
    }
    else
    {
        game.p1.gun.speedtick++;
    }
    if (key == ' ')
    {
        if (game.p1.ammo > 0)
        {
            if (game.p1.gun.speedtick >= game.p1.gun.speedtime)
            {
                shoot(game.p1.dir);
                game.p1.ammo -= 1;
                game.p1.gun.speedtick = 0;
            }
        }
        else
        {
            if (game.p1.gun.clips > 0)
            {
                game.p1.gun.clips -= 1;
                game.p1.ammo = game.p1.gun.cap;
            }
        }
    }*/
    if (key == KEY_UP)
    {
        game.p1.dir = 'u';
        if (zomAtPoint(P1Dir('u'),P1X()) == false)
        {
            if (GetChar2(P1Dir('u'),P1X(),'.'))
            {
                game.p1.y--;
            }
            else if (GetChar2(P1Dir('u'),P1X(),'='))
            {
                game.p1.y--;
            }
            else if (GetChar2(P1Dir('u'),P1X(),'+'))
            {
                game.p1.HP += 10;
                AdvMap[P1Dir('u')][P1X()] = '.';
            }
            else if (GetChar2(P1Dir('u'),P1X(),'A'))
            {
                if ((game.p1.ammo+5) > game.p1.gun.cap)
                {
                    game.p1.gun.cap += 1;
                }
                else
                {
                    game.p1.ammo += 5;
                }
                AdvMap[P1Dir('u')][P1X()] = '.';
            }
            else if (GetChar2(P1Dir('u'),P1X(),'D'))
            {
                game.p1.y -= 2;
            }
        }
        else
        {
            int dam = rand()%game.p1.damage;
            game.zom[GetZomID(P1Dir('u'),P1X())].HP -= dam;
        }
    }
    if (key == KEY_DOWN)
    {
        game.p1.dir = 'd';
        if (zomAtPoint(P1Dir('d'),P1X()) == false)
        {
            if (GetChar2(P1Dir('d'),P1X(),'.'))
            {
                game.p1.y++;
            }
            else if (GetChar2(P1Dir('d'),P1X(),'='))
            {
                game.p1.y++;
            }
            else if (GetChar2(P1Dir('d'),P1X(),'+'))
            {
                game.p1.HP += 10;
                AdvMap[P1Dir('d')][P1X()] = '.';
            }
            else if (GetChar2(P1Dir('d'),P1X(),'A'))
            {
                if ((game.p1.ammo+5) > game.p1.gun.cap)
                {
                    game.p1.gun.cap += 1;
                }
                else
                {
                    game.p1.ammo += 5;
                }
                AdvMap[P1Dir('d')][P1X()] = '.';
            }
            else if (GetChar2(P1Dir('d'),P1X(),'D'))
            {
                game.p1.y += 2;
            }
        }
        else
        {
            game.zom[GetZomID(P1Dir('d'),P1X())].HP -= rand()%game.p1.damage;
        }
    }
    if (key == KEY_LEFT)
    {
        game.p1.dir = 'l';
        if (zomAtPoint(P1Y(),P1Dir('l')) == false)
        {
            if (GetChar2(P1Y(),P1Dir('l'),'.'))
            {
                game.p1.x--;
            }
            else if (GetChar2(P1Y(),P1Dir('l'),'='))
            {
                game.p1.x--;
            }
            else if (GetChar2(P1Y(),P1Dir('l'),'+'))
            {
                game.p1.HP += 10;
                AdvMap[P1Y()][P1Dir('l')] = '.';
            }
            else if (GetChar2(P1Y(),P1Dir('l'),'A'))
            {
                if ((game.p1.ammo+5) > game.p1.gun.cap)
                {
                    game.p1.gun.cap += 1;
                }
                else
                {
                    game.p1.ammo += 5;
                }
                AdvMap[P1Y()][P1Dir('l')] = '.';
            }
            else if (GetChar2(P1Y(),P1Dir('l'),'D'))
            {
                game.p1.x -= 2;
            }
        }
        else
        {
            game.zom[GetZomID(P1Y(),P1Dir('l'))].HP -= rand()%game.p1.damage;
        }
    }
    if (key == KEY_RIGHT)
    {
        game.p1.dir = 'r';
        if (zomAtPoint(P1Y(),P1Dir('r')) == false)
        {
            if (GetChar2(P1Y(),P1Dir('r'),'.'))
            {
                game.p1.x++;
            }
            else if (GetChar2(P1Y(),P1Dir('r'),'='))
            {
                game.p1.x++;
            }
            else if (GetChar2(P1Y(),P1Dir('r'),'+'))
            {
                game.p1.HP += 10;
                AdvMap[P1Y()][P1Dir('r')] = '.';
            }
            else if (GetChar2(P1Y(),P1Dir('r'),'A'))
            {
                if ((game.p1.ammo+5) > game.p1.gun.cap)
                {
                    game.p1.gun.cap += 1;
                }
                else
                {
                    game.p1.ammo += 5;
                }
                AdvMap[P1Y()][P1Dir('r')] = '.';
            }
            else if (GetChar2(P1Y(),P1Dir('r'),'D'))
            {
                game.p1.x += 2;
            }
        }
        else
        {
            game.zom[GetZomID(P1Y(),P1Dir('r'))].HP -= rand()%game.p1.damage;
        }
    }
    flushinp();
}

bool ZOMINFOV2(int id,int raduis)
{
    if  (in_range(game.p1.y,game.p1.x,game.zom[id].y,game.zom[id].x,raduis)
            && los2(game.p1.y,game.p1.x,game.zom[id].y,game.zom[id].x,'#')
            && los2(game.p1.y,game.p1.x,game.zom[id].y,game.zom[id].x,'-')
            && los2(game.p1.y,game.p1.x,game.zom[id].y,game.zom[id].x,'0')
            && los2(game.p1.y,game.p1.x,game.zom[id].y,game.zom[id].x,'|') )
    {
        return true;
    }
    else
    {
        return false;
    }
}



#define UNSAFE (-1)
#define SAFEST (0)
#define BIGFRONTIER (2 * (18 + 60))

int SafetyMap[18][60];
typedef struct Point
{
public:
    int x;
    int y;
};

Point frontier1[BIGFRONTIER], frontier2[BIGFRONTIER];
Point *thisFrontier = frontier1, *nextFrontier = frontier2;

void DiffuseSafety()
{
    int thisFrontierLength = 0, nextFrontierLength = 0;

    // wipe the safety map
    for (int y = 0; y < 18; y++)
    {
        for (int x = 0; x < 59; x++)
        {
            SafetyMap[y][x] = UNSAFE;
        }
    }

    // scan the map to find house cells
    for (int y = 0; y < 18; y++)
    {
        for (int x = 0; x < 59; x++)
        {
            if (Map[y][x] = '.')
            {
                thisFrontier[thisFrontierLength++].x = x;
                thisFrontier[thisFrontierLength++].y = y;
                SafetyMap[y][x] = SAFEST;
            }
        }
    }

    int phase = SAFEST + 1;
    while (thisFrontierLength > 0)
    {
        // now add all neighbors to the next frontier
        for (int i = 0; i < thisFrontierLength; i++)
        {
            int x1 = thisFrontier[i].x, y1 = thisFrontier[i].y;

            // we're going to do the same thing in four directions.
            // you could make a macro or a function call for this.
            // but instead, I'm just looping over a dummy variable dir.
            for (int dir = 0; dir < 4; dir++)
            {
                int x, y;

                if (dir == 0)
                {
                    // east:
                    x = x1 + 1;
                    y = y1;
                }
                else if (dir == 1)
                {
                    // south:
                    x = x1;
                    y = y1 + 1;
                }
                else if (dir == 2)
                {
                    // west:
                    x = x1 - 1;
                    y = y1;
                }
                else if (dir == 3)
                {
                    // north:
                    x = x1;
                    y = y1 - 1;
                }

                if (SafetyMap[y][x] == UNSAFE)
                {
                    if (Map[y][x] = ' ')
                    {
                        thisFrontier[thisFrontierLength++].x = x;
                        thisFrontier[thisFrontierLength++].y = y;
                        SafetyMap[y][x] = phase;
                    }
                }
            }
        }

        // now switch the frontiers
        Point *swapFrontier = thisFrontier;
        thisFrontier = nextFrontier;
        nextFrontier = swapFrontier;

        thisFrontierLength = nextFrontierLength;
        nextFrontierLength = 0;

        // and advance the phase so the next frontier is slightly less safe
        phase++;
    }
}

void DrawAnimation(char Ani[100][25][80], int start, int end,int speed)
{
    for (int i = start; i < end; i++)
    {
        for (int y = 0; y < 25; y++)
        {
            for (int x = 0; x < 80; x++)
            {
                if (Ani[i][y][x] != 0)
                {
                    mvaddch(y,x,Ani[i][y][x]);
                }
            }
        }
        refresh();
        napms(speed);
    }
}

void DrawAnimation2(char Ani[100][20][80], int start, int end,int speed)
{
    for (int i = start; i < end; i++)
    {
        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 80; x++)
            {
                if (Ani[i][y][x] != 0)
                {
                    mvaddch(y,x,Ani[i][y][x]);
                }
            }
        }
        refresh();
        napms(speed);
    }
}


void SwitchTime()
{
    if (game.DayNightTime == 0)
    {
        game.DayNightTime = 1;
    }
    else
    {
        game.DayNightTime = 0;
    }
}

bool zomAtPoint(int y, int x)
{
    for (int i = 0; i < 1000; i++)
    {
        if (game.zom[i].y == y)
        {
            if (game.zom[i].x == x)
            {
                if (game.zom[i].DEAD == false)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool p1AtPoint(int y, int x)
{
    if (game.p1.y == y)
    {
        if (game.p1.x == x)
        {
            return true;
        }
    }
    return false;
}

bool GetChar(int y, int x, char c)
{
    if (Map[y][x] == c)
    {
        return true;
    }
    return false;
}

bool GetChar2(int y, int x, char c)
{
    if (AdvMap[y][x] == c)
    {
        return true;
    }
    return false;
}


int ZomDir(int id,char dir)
{
    if (dir == 'u')
    {
        return (game.zom[id].y - 1);
    }
    if (dir == 'd')
    {
        return (game.zom[id].y + 1);
    }
    if (dir == 'l')
    {
        return (game.zom[id].x - 1);
    }
    if (dir == 'r')
    {
        return (game.zom[id].x + 1);
    }
    return 0;
}

int P1Dir(char dir)
{
    if (dir == 'u')
    {
        return (game.p1.y - 1);
    }
    if (dir == 'd')
    {
        return (game.p1.y + 1);
    }
    if (dir == 'l')
    {
        return (game.p1.x - 1);
    }
    if (dir == 'r')
    {
        return (game.p1.x + 1);
    }
    return 0;
}

int P1X()
{
    return game.p1.x;
}

int P1Y()
{
    return game.p1.y;
}


void SetZomSettings(int max, int speed, int hp, int damage_base,double bounty)
{
    game.zombies_max = max;
    game.speed = speed;
    game.HP = hp;
    game.zombies_damage_base = damage_base;
    game.bounty = bounty;
    for (int i = 0; i < max; i++)
    {
        game.zom[i].HP = hp;
        game.zom[i].damage = rand()%damage_base;
    }
}

void respawnZom()
{
    for (int i = 0; i < game.zombies_max; i++)
    {
step1:
        game.zom[i].y = rand()%16+1;
        game.zom[i].x = rand()%55+3;
        if (Map[game.zom[i].y][game.zom[i].x] != ' ')
        {
            goto step1;
        }
        game.zom[i].DEAD = false;
    }
}



int GetZomID(int y, int x)
{
    for (int i = 0; i < game.zombies_max; i++)
    {
        if (game.zom[i].DEAD == false)
        {
            if (game.zom[i].y == y)
            {
                if (game.zom[i].x == x)
                {
                    return i;
                }
            }
        }
    }
    return 0;
}

/*               */
/*               */
/*               */
/*               */
/*               */
/*               */

void ClearBlood()
{
    for (int y = 0; y < 18; y++)
        for (int x = 0; x < 60; x++)
            BloodMap[y][x] = 0;
}

void ChangeLocation(int location)
{
    ClearBlood();
    for (int y = 0; y < 18; y++)
    {
        for (int x = 0; x < 60; x++)
        {
            Map[y][x] = locations[location][y][x];
            if (locations[location][y][x] == '&')
            {
                game.p1.x = x;
                game.p1.y = y;
                Map[y][x] = ' ';
            }
        }
    }
}

void init()
{
    initscr();
    nodelay(stdscr,1);
    keypad(stdscr,1);
    noecho();
    nonl();
    curs_set(0);
    srand(time(NULL));
    start_color();
    init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2,COLOR_GREEN,COLOR_BLACK);
    init_pair(3,COLOR_WHITE,COLOR_BLACK);
    init_pair(4,COLOR_WHITE,COLOR_BLACK);
    init_pair(5,COLOR_CYAN,COLOR_BLACK);
    init_pair(6,COLOR_BLACK,COLOR_BLACK);
    init_pair(7,COLOR_CYAN,COLOR_BLACK);
    init_pair(8,COLOR_YELLOW,COLOR_BLACK);
    init_pair(9,COLOR_RED,COLOR_BLACK);
    init_pair(10,COLOR_RED,COLOR_RED);
}


void DrawBuls()
{
    for (int i = 0; i < 1000; i++)
    {
        if (game.p1.gun.bullet[i].Shot == true)
        {
            mvaddch(game.p1.gun.bullet[i].y,game.p1.gun.bullet[i].x,ACS_DEGREE);
        }
    }
}

bool shoot(char direction)
{
    for (int i = 0; i < 1000; i++)
    {
        if (game.p1.gun.bullet[i].Shot == false)
        {
            game.p1.gun.bullet[i].dir = direction;
            game.p1.gun.bullet[i].x = game.p1.x;
            game.p1.gun.bullet[i].y = game.p1.y;
            game.p1.gun.bullet[i].Shot = true;
            return true;
        }
    }
    return false;
}

void BulMovement()
{
    for (int i = 0; i < 1000; i++)
    {
        if (game.p1.gun.bullet[i].Shot == true)
        {
            if (game.p1.gun.bullet[i].dir == 'u')
            {
                if (zomAtPoint((game.p1.gun.bullet[i].y-1),game.p1.gun.bullet[i].x) == false)
                {
                    if (GetChar((game.p1.gun.bullet[i].y-1),game.p1.gun.bullet[i].x,' ') == false )
                    {
                        game.p1.gun.bullet[i].Shot = false;
                    }
                    else
                    {
                        game.p1.gun.bullet[i].y--;
                    }
                }
                else
                {
                    game.zom[GetZomID((game.p1.gun.bullet[i].y-1),game.p1.gun.bullet[i].x)].HP -= game.p1.gun.damage;
                    game.p1.gun.bullet[i].Shot = false;
                }
            }
            else if (game.p1.gun.bullet[i].dir == 'd')
            {
                if (zomAtPoint((game.p1.gun.bullet[i].y+1),game.p1.gun.bullet[i].x) == false)
                {
                    if (GetChar((game.p1.gun.bullet[i].y+1),game.p1.gun.bullet[i].x,' ') == false )
                    {
                        game.p1.gun.bullet[i].Shot = false;
                    }
                    else
                    {
                        game.p1.gun.bullet[i].y++;
                    }
                }
                else
                {
                    game.zom[GetZomID((game.p1.gun.bullet[i].y+1),game.p1.gun.bullet[i].x)].HP -= game.p1.gun.damage;
                    game.p1.gun.bullet[i].Shot = false;
                }
            }
            else if (game.p1.gun.bullet[i].dir == 'l')
            {
                if (zomAtPoint(game.p1.gun.bullet[i].y,(game.p1.gun.bullet[i].x-1)) == false)
                {
                    if (GetChar(game.p1.gun.bullet[i].y,(game.p1.gun.bullet[i].x-1),' ') == false )
                    {
                        game.p1.gun.bullet[i].Shot = false;
                    }
                    else
                    {
                        game.p1.gun.bullet[i].x--;
                    }
                }
                else
                {
                    game.zom[GetZomID(game.p1.gun.bullet[i].y,(game.p1.gun.bullet[i].x-1))].HP -= game.p1.gun.damage;
                    game.p1.gun.bullet[i].Shot = false;
                }
            }
            else if (game.p1.gun.bullet[i].dir == 'r')
            {
                if (zomAtPoint(game.p1.gun.bullet[i].y,(game.p1.gun.bullet[i].x+1)) == false)
                {
                    if (GetChar(game.p1.gun.bullet[i].y,(game.p1.gun.bullet[i].x+1),' ') == false )
                    {
                        game.p1.gun.bullet[i].Shot = false;
                    }
                    else
                    {
                        game.p1.gun.bullet[i].x++;
                    }
                }
                else
                {
                    game.zom[GetZomID(game.p1.gun.bullet[i].y,(game.p1.gun.bullet[i].x+1))].HP -= game.p1.gun.damage;
                    game.p1.gun.bullet[i].Shot = false;
                }
            }
        }
    }
}


bool C4detfov(int id,int raduis)
{
    int raduisy = raduis*2;
    for (int i = 0; i < 10; i++)
    {
        Movement();
        EMovement();
        Draw();
        DrawBlood();
        DrawBuls();
        DrawPlayer();
        DrawZoms();
        DrawGUI();
        for (int yy = game.p1.c4[id].y-raduisy; yy <= game.p1.c4[id].y+raduisy; yy++)
        {
            for (int xx = game.p1.c4[id].x-raduis; xx <= game.p1.c4[id].x+raduis; xx++)
            {
                if (Map[yy][xx] != 0)
                {
                    if (in_range(game.p1.c4[id].y,game.p1.c4[id].x,yy,xx,raduis))
                    {
                        for (int i = 0; i < game.zombies_max; i++)
                        {
                            if (game.zom[i].DEAD == false)
                            {
                                if (in_range(game.zom[i].y,game.zom[i].x,yy,xx,raduis/2))
                                {
                                    game.zom[i].DEAD -= 200;
                                }
                            }
                        }
                        if (p1AtPoint(yy,xx))
                        {
                            game.p1.HP -= 20;
                        }
                        if (Map[yy][xx] != '#')
                        {
                            Map[yy][xx] = ' ';
                        }
                        int tempint = rand()%2;
                        if (tempint == 0)
                        {
                            mvaddch(yy,xx,rand()%254+67|COLOR_PAIR(9));
                        }
                        else if (tempint == 1)
                        {
                            mvaddch(yy,xx,rand()%254+67|COLOR_PAIR(9)|A_BOLD);
                        }
                    }
                }
            }
        }
        refresh();
        napms(50);
    }
    game.p1.c4[id].set = false;
    return true;
}

void DrawC4()
{
    for (int i = 0; i < game.p1.c4_max; i++)
    {
        if (game.p1.c4[i].set == true)
        {
            mvaddch(game.p1.c4[i].y,game.p1.c4[i].x,'C');
        }
    }
}

bool placeC4()
{
    for (int i = 0; i < game.p1.c4Ammo; i++)
    {
        if (game.p1.c4[i].set == false)
        {
            game.p1.c4[i].y = game.p1.y;
            game.p1.c4[i].x = game.p1.x;
            game.p1.c4[i].set = true;
            game.p1.c4Ammo -= 1;
            return true;
        }
    }
    return false;
}

int C4Det()
{
    int count = 0;
    for (int i = 0; i < game.p1.c4_max; i++)
    {
        if (game.p1.c4[i].set == true)
        {
            C4detfov(i,5);
        }
    }
}

void Movement()
{
    int key = getch();
    if (key == 'q')
    {
        NewGame = false;
    }
    if (key == 'c')
    {
        placeC4();
    }
    if (key == 'd')
    {
        C4Det();
    }
    if (game.p1.gun.speedtick >= game.p1.gun.speedtime)   // check
    {
    }
    else
    {
        game.p1.gun.speedtick++;
    }
    if (key == ' ')
    {
        if (game.p1.ammo > 0)
        {
            if (game.p1.gun.speedtick >= game.p1.gun.speedtime)
            {
                shoot(game.p1.dir);
                game.p1.ammo -= 1;
                game.p1.gun.speedtick = 0;
            }
        }
        else
        {
            if (game.p1.gun.clips > 0)
            {
                game.p1.gun.clips -= 1;
                game.p1.ammo = game.p1.gun.cap;
            }
        }
    }
    if (key == KEY_UP)
    {
        game.p1.dir = 'u';
        if (zomAtPoint(P1Dir('u'),P1X()) == false)
        {
            if (GetChar(P1Dir('u'),P1X(),' '))
            {
                game.p1.y--;
            }
            else if (GetChar(P1Dir('u'),P1X(),'='))
            {
                game.p1.y--;
            }
            else if (GetChar(P1Dir('u'),P1X(),'+'))
            {
                game.p1.HP += 10;
                Map[P1Dir('u')][P1X()] = ' ';
            }
            else if (GetChar(P1Dir('u'),P1X(),'A'))
            {
                if ((game.p1.ammo+5) > game.p1.gun.cap)
                {
                    game.p1.gun.cap += 1;
                }
                else
                {
                    game.p1.ammo += 5;
                }
                Map[P1Dir('u')][P1X()] = ' ';
            }
            else if (GetChar(P1Dir('u'),P1X(),'D'))
            {
                game.p1.y -= 2;
            }
        }
        else
        {
            int dam = rand()%game.p1.damage;
            game.zom[GetZomID(P1Dir('u'),P1X())].HP -= dam;
        }
    }
    if (key == KEY_DOWN)
    {
        game.p1.dir = 'd';
        if (zomAtPoint(P1Dir('d'),P1X()) == false)
        {
            if (GetChar(P1Dir('d'),P1X(),' '))
            {
                game.p1.y++;
            }
            else if (GetChar(P1Dir('d'),P1X(),'='))
            {
                game.p1.y++;
            }
            else if (GetChar(P1Dir('d'),P1X(),'+'))
            {
                game.p1.HP += 10;
                Map[P1Dir('d')][P1X()] = ' ';
            }
            else if (GetChar(P1Dir('d'),P1X(),'A'))
            {
                if ((game.p1.ammo+5) > game.p1.gun.cap)
                {
                    game.p1.gun.cap += 1;
                }
                else
                {
                    game.p1.ammo += 5;
                }
                Map[P1Dir('d')][P1X()] = ' ';
            }
            else if (GetChar(P1Dir('d'),P1X(),'D'))
            {
                game.p1.y += 2;
            }
        }
        else
        {
            game.zom[GetZomID(P1Dir('d'),P1X())].HP -= rand()%game.p1.damage;
        }
    }
    if (key == KEY_LEFT)
    {
        game.p1.dir = 'l';
        if (zomAtPoint(P1Y(),P1Dir('l')) == false)
        {
            if (GetChar(P1Y(),P1Dir('l'),' '))
            {
                game.p1.x--;
            }
            else if (GetChar(P1Y(),P1Dir('l'),'='))
            {
                game.p1.x--;
            }
            else if (GetChar(P1Y(),P1Dir('l'),'+'))
            {
                game.p1.HP += 10;
                Map[P1Y()][P1Dir('l')] = ' ';
            }
            else if (GetChar(P1Y(),P1Dir('l'),'A'))
            {
                if ((game.p1.ammo+5) > game.p1.gun.cap)
                {
                    game.p1.gun.cap += 1;
                }
                else
                {
                    game.p1.ammo += 5;
                }
                Map[P1Y()][P1Dir('l')] = ' ';
            }
            else if (GetChar(P1Y(),P1Dir('l'),'D'))
            {
                game.p1.x -= 2;
            }
        }
        else
        {
            game.zom[GetZomID(P1Y(),P1Dir('l'))].HP -= rand()%game.p1.damage;
        }
    }
    if (key == KEY_RIGHT)
    {
        game.p1.dir = 'r';
        if (zomAtPoint(P1Y(),P1Dir('r')) == false)
        {
            if (GetChar(P1Y(),P1Dir('r'),' '))
            {
                game.p1.x++;
            }
            else if (GetChar(P1Y(),P1Dir('r'),'='))
            {
                game.p1.x++;
            }
            else if (GetChar(P1Y(),P1Dir('r'),'+'))
            {
                game.p1.HP += 10;
                Map[P1Y()][P1Dir('r')] = ' ';
            }
            else if (GetChar(P1Y(),P1Dir('r'),'A'))
            {
                if ((game.p1.ammo+5) > game.p1.gun.cap)
                {
                    game.p1.gun.cap += 1;
                }
                else
                {
                    game.p1.ammo += 5;
                }
                Map[P1Y()][P1Dir('r')] = ' ';
            }
            else if (GetChar(P1Y(),P1Dir('r'),'D'))
            {
                game.p1.x += 2;
            }
        }
        else
        {
            game.zom[GetZomID(P1Y(),P1Dir('r'))].HP -= rand()%game.p1.damage;
        }
    }
    flushinp();
}




void Draw()
{
    for (int y = 0; y < 18; y++)
    {
        for (int x = 0; x < 60; x++)
        {
            if (Map[y][x] != 0)
            {
                if  (in_range(game.p1.y,game.p1.x,y,x,game.p1.sight)
                        && los(game.p1.y,game.p1.x,y,x,'#')
                        && los(game.p1.y,game.p1.x,y,x,'-')
                        && los(game.p1.y,game.p1.x,y,x,'0')
                        && los(game.p1.y,game.p1.x,y,x,'|') )
                {
                    if (Map[y][x] == 'T')
                    {
                        mvaddch(y,x,Map[y][x]|COLOR_PAIR(4));
                    }
                    else if (Map[y][x] == '+')
                    {
                        mvaddch(y,x,Map[y][x]|COLOR_PAIR(2)|A_BOLD);
                    }
                    else if (Map[y][x] == 'B')
                    {
                        mvaddch(y,x,Map[y][x]|COLOR_PAIR(5));
                    }
                    else if (Map[y][x] == '*')
                    {
                        mvaddch(y,x,Map[y][x]|COLOR_PAIR(5));
                    }
                    else if (Map[y][x] == ',')
                    {
                        mvaddch(y,x,Map[y][x]|COLOR_PAIR(5));
                    }
                    else if (Map[y][x] == '.')
                    {
                        mvaddch(y,x,Map[y][x]|COLOR_PAIR(5));
                    }
                    else if (Map[y][x] == ' ')
                    {
                        if (game.DayNightTime == 0)
                        {
                            mvaddch(y,x,'.'|COLOR_PAIR(4));
                        }
                        else
                        {
                            mvaddch(y,x,'.'|COLOR_PAIR(6));
                        }
                    }
                    else if (Map[y][x] == '#')
                    {
                        if (game.DayNightTime == 0)
                        {
                            mvaddch(y,x,'#'|COLOR_PAIR(8));
                        }
                        else
                        {
                            mvaddch(y,x,'#'|COLOR_PAIR(4));
                        }
                    }
                    else if (Map[y][x] == '-')
                    {
                        if (game.DayNightTime == 0)
                        {
                            mvaddch(y,x,'-'|COLOR_PAIR(8));
                        }
                        else
                        {
                            mvaddch(y,x,'-'|COLOR_PAIR(4));
                        }
                    }
                    else if (Map[y][x] == '|')
                    {
                        if (game.DayNightTime == 0)
                        {
                            mvaddch(y,x,'|'|COLOR_PAIR(8));
                        }
                        else
                        {
                            mvaddch(y,x,'|'|COLOR_PAIR(4));
                        }
                    }
                    else if (Map[y][x] == '0')
                    {
                        if (game.DayNightTime == 0)
                        {
                            mvaddch(y,x,'0'|COLOR_PAIR(8));
                        }
                        else
                        {
                            mvaddch(y,x,'0'|COLOR_PAIR(4));
                        }
                    }
                    else if (Map[y][x] == 'D')
                    {
                        mvaddch(y,x,'D'|COLOR_PAIR(5));
                    }
                    else if (Map[y][x] == 'A')
                    {
                        mvaddch(y,x,'A'|COLOR_PAIR(2));
                    }
                    else
                    {
                        mvaddch(y,x,Map[y][x]|COLOR_PAIR(3));
                    }
                }
            }
        }
    }
}

void DrawNOFOV()
{
    for (int y = 0; y < 18; y++)
    {
        for (int x = 0; x < 60; x++)
        {
            if (Map[y][x] == 'T')
            {
                mvaddch(y,x,Map[y][x]|COLOR_PAIR(4));
            }
            else if (Map[y][x] == '+')
            {
                mvaddch(y,x,Map[y][x]|COLOR_PAIR(2)|A_BOLD);
            }
            else if (Map[y][x] == 'B')
            {
                mvaddch(y,x,Map[y][x]|COLOR_PAIR(5));
            }
            else if (Map[y][x] == '*')
            {
                mvaddch(y,x,Map[y][x]|COLOR_PAIR(5));
            }
            else if (Map[y][x] == ',')
            {
                mvaddch(y,x,Map[y][x]|COLOR_PAIR(5));
            }
            else if (Map[y][x] == '.')
            {
                mvaddch(y,x,Map[y][x]|COLOR_PAIR(5));
            }
            else if (Map[y][x] == ' ')
            {
                if (game.DayNightTime == 0)
                {
                    mvaddch(y,x,'.'|COLOR_PAIR(4));
                }
                else
                {
                    mvaddch(y,x,'.'|COLOR_PAIR(6));
                }
            }
            else if (Map[y][x] == '#')
            {
                if (game.DayNightTime == 0)
                {
                    mvaddch(y,x,'#'|COLOR_PAIR(8));
                }
                else
                {
                    mvaddch(y,x,'#'|COLOR_PAIR(4));
                }
            }
            else if (Map[y][x] == '-')
            {
                if (game.DayNightTime == 0)
                {
                    mvaddch(y,x,'-'|COLOR_PAIR(8));
                }
                else
                {
                    mvaddch(y,x,'-'|COLOR_PAIR(4));
                }
            }
            else if (Map[y][x] == '|')
            {
                if (game.DayNightTime == 0)
                {
                    mvaddch(y,x,'|'|COLOR_PAIR(8));
                }
                else
                {
                    mvaddch(y,x,'|'|COLOR_PAIR(4));
                }
            }
            else if (Map[y][x] == '0')
            {
                if (game.DayNightTime == 0)
                {
                    mvaddch(y,x,'0'|COLOR_PAIR(8));
                }
                else
                {
                    mvaddch(y,x,'0'|COLOR_PAIR(4));
                }
            }
            else if (Map[y][x] == 'D')
            {
                mvaddch(y,x,'D'|COLOR_PAIR(5));
            }
            else if (Map[y][x] == 'A')
            {
                mvaddch(y,x,'A'|COLOR_PAIR(2));
            }
            else
            {
                mvaddch(y,x,Map[y][x]|COLOR_PAIR(3));
            }
        }
    }
}

void DrawBlood()
{
    for (int i = 0; i < game.zombies_max; i++)
    {
        if (game.zom[i].DEAD == true)
        {
            BloodMap[game.zom[i].y][game.zom[i].x] = '%';
        }
    }
    for (int i = 0; i < game.zombies_max; i++)
    {
        if (game.zom[i].DEAD == false)
        {
            for (int y = 0; y < 18; y++)
            {
                for (int x = 0; x < 60; x++)
                {
                    if (BloodMap[y][x] != 0)
                    {
                        if (Map[y][x] == ' ')
                        {
                            if (in_range(game.p1.y,game.p1.x,y,x,game.p1.sight))
                            {
                                mvaddch(y,x,BloodMap[y][x]|COLOR_PAIR(1));
                            }
                        }

                    }
                }
            }
        }
    }
}

void DrawPlayer()
{
    if (game.p1.c == '*')
    {
        mvaddch(game.p1.y,game.p1.x,game.p1.c|COLOR_PAIR(1)|A_BOLD);
    }
    else
    {
        if (game.DayNightTime == 0)
        {
            mvaddch(game.p1.y,game.p1.x,game.p1.c|COLOR_PAIR(8)|A_BOLD);
        }
        else
        {
            mvaddch(game.p1.y,game.p1.x,game.p1.c|COLOR_PAIR(6)|A_BOLD);
        }
    }
    if (game.p1.dir == 'r')
    {
        mvaddch(game.p1.y,game.p1.x+1,Map[game.p1.y][(game.p1.x+1)]|COLOR_PAIR(6)|A_BLINK);
    }
    else if (game.p1.dir == 'l')
    {
        mvaddch(game.p1.y,game.p1.x-1,Map[game.p1.y][(game.p1.x-1)]|COLOR_PAIR(6)|A_BLINK);
    }
    if (game.p1.dir == 'u')
    {
        mvaddch(game.p1.y-1,game.p1.x,Map[(game.p1.y-1)][game.p1.x]|COLOR_PAIR(6)|A_BLINK);
    }
    if (game.p1.dir == 'd')
    {
        mvaddch(game.p1.y+1,game.p1.x,Map[(game.p1.y+1)][game.p1.x]|COLOR_PAIR(6)|A_BLINK);
    }
}

void DrawGUI()
{
    attrset(COLOR_PAIR(1));
    mvprintw(19,0,"Zombies Dead : %i",game.zombies_dead);
    attrset(COLOR_PAIR(1)|A_BOLD);
    mvprintw(20,0,"Zombies Alive : %i",game.zombies_alive);
    attrset(COLOR_PAIR(2)|A_BOLD);
    mvprintw(21,0,"HP : %i/%i",game.p1.HP,game.p1.MAXHP);
    attrset(COLOR_PAIR(8)|A_BOLD);
    mvprintw(22,0,"Wave : %i",game.wave);
    attrset(COLOR_PAIR(5)|A_BOLD);
    mvprintw(23,0,"Ammo : %i  Clips : %i",game.p1.ammo,game.p1.gun.clips);
    attrset(COLOR_PAIR(8));
    mvprintw(24,0,"C4 : %i/%i",game.p1.c4Ammo,game.p1.c4_max);
    attrset(COLOR_PAIR(0)|A_BOLD);
}

bool P1INFOV(int id,int raduis)
{
    int raduisy = raduis*2;
    for (int yy = game.zom[id].y-raduisy; yy <= game.zom[id].y+raduisy; yy++)
    {
        for (int xx = game.zom[id].x-raduis; xx <= game.zom[id].x+raduis; xx++)
        {
            if (Map[yy][xx] != 0)
            {
                if  (in_range(game.zom[id].y,game.zom[id].x,game.p1.y,game.p1.x,raduis)
                        && los(game.zom[id].y,game.zom[id].x,game.p1.y,game.p1.x,'#')
                        && los(game.zom[id].y,game.zom[id].x,game.p1.y,game.p1.x,'-')
                        && los(game.zom[id].y,game.zom[id].x,game.p1.y,game.p1.x,'0')
                        && los(game.zom[id].y,game.zom[id].x,game.p1.y,game.p1.x,'|') )
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool ZOMINFOV(int id,int raduis)
{
    int raduisy = raduis*2;
    for (int yy = game.p1.y-raduisy; yy <= game.zom[id].y+raduisy; yy++)
    {
        for (int xx = game.p1.x-raduis; xx <= game.zom[id].x+raduis; xx++)
        {
            if (Map[yy][xx] != 0)
            {
                if  (in_range(game.p1.y,game.p1.x,game.zom[id].y,game.zom[id].x,raduis)
                        && los(game.p1.y,game.p1.x,game.zom[id].y,game.zom[id].x,'#')
                        && los(game.p1.y,game.p1.x,game.zom[id].y,game.zom[id].x,'-')
                        && los(game.p1.y,game.p1.x,game.zom[id].y,game.zom[id].x,'0')
                        && los(game.p1.y,game.p1.x,game.zom[id].y,game.zom[id].x,'|') )
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void FOV(int id,int raduis)
{
    int raduisy = raduis*2;
    for (int yy = game.zom[id].y-raduisy; yy <= game.zom[id].y+raduisy; yy++)
    {
        for (int xx = game.zom[id].x-raduis; xx <= game.zom[id].x+raduis; xx++)
        {
            if (Map[yy][xx] != 0)
            {
                if  (in_range(game.zom[id].y,game.zom[id].x,yy,xx,raduis)
                        && los(game.zom[id].y,game.zom[id].x,yy,xx,'#')
                        && los(game.zom[id].y,game.zom[id].x,yy,xx,'-')
                        && los(game.zom[id].y,game.zom[id].x,yy,xx,'0')
                        && los(game.zom[id].y,game.zom[id].x,yy,xx,'|') )
                {
                    if (Map[yy][xx] == ' ')
                    {
                        mvaddch(yy,xx,'.'|COLOR_PAIR(7));
                    }
                }
            }
        }
    }
}

void P1FOV(int raduis)
{
    int raduisy = raduis*2;
    for (int yy = game.p1.y-raduisy; yy <= game.p1.y+raduisy; yy++)
    {
        for (int xx = game.p1.x-raduis; xx <= game.p1.x+raduis; xx++)
        {
            if (Map[yy][xx] != 0)
            {
                if  (in_range(game.p1.y,game.p1.x,yy,xx,raduis)
                        && los(game.p1.y,game.p1.x,yy,xx,'#')
                        && los(game.p1.y,game.p1.x,yy,xx,'-')
                        && los(game.p1.y,game.p1.x,yy,xx,'0')
                        && los(game.p1.y,game.p1.x,yy,xx,'|') )
                {
                    if (Map[yy][xx] == ' ')
                    {
                        mvaddch(yy,xx,'.'|COLOR_PAIR(7));
                    }
                }
            }
        }
    }
}

void MoveRand(int i)
{
    int dir = rand()%4;
    if (dir == 0)   // move down
    {
        if (zomAtPoint((game.zom[i].y+1),game.zom[i].x) == false)
        {
            if (Map[(game.zom[i].y+1)][game.zom[i].x] == ' ')
            {
                game.zom[i].y++;
            }
        }
    }
    if (dir == 1)   // move up
    {
        if (zomAtPoint((game.zom[i].y-1),game.zom[i].x) == false)
        {
            if (Map[(game.zom[i].y-1)][game.zom[i].x] == ' ')
            {
                game.zom[i].y--;
            }
        }
    }
    if (dir == 2)   // move left
    {
        if (zomAtPoint(game.zom[i].y,(game.zom[i].x-1)) == false)
        {
            if (Map[game.zom[i].y][(game.zom[i].x-1)] == ' ')
            {
                game.zom[i].x--;
            }
        }
    }
    if (dir == 3)   // move right
    {
        if (zomAtPoint(game.zom[i].y,(game.zom[i].x+1)) == false)
        {
            if (Map[game.zom[i].y][(game.zom[i].x+1)] == ' ')
            {
                game.zom[i].x++;
            }
        }
    }

}

void DrawZoms()
{
    int dead_count = 0;
    int alive_count = 0;
    for (int i = 0; i < game.zombies_max; i++)
    {
        if (game.zom[i].DEAD == false)
        {
            alive_count++;
            if (ZOMINFOV(i,game.p1.sight))
            {
                mvaddch(game.zom[i].y,game.zom[i].x,'Z'|COLOR_PAIR(2));
            }
        }
        else
        {
            dead_count++;
        }
    }
    game.zombies_alive = alive_count;
    game.zombies_dead = dead_count;
}

void EMovement()
{
    for (int i = 0; i < game.zombies_max; i++)
    {
        if (game.zom[i].DEAD == false)
        {
            if (game.zom[i].speedcount >= game.speed)
            {
                if (game.zom[i].y < game.p1.y)
                {
                    if (p1AtPoint(ZomDir(i,'d'),game.zom[i].x) == false)
                    {
                        if (zomAtPoint(ZomDir(i,'d'),game.zom[i].x) == false)
                        {
                            if (GetChar(ZomDir(i,'d'),game.zom[i].x,' '))
                            {
                                if (game.DayNightTime == 1)
                                {
                                    if (P1INFOV(i,4))
                                    {
                                        game.zom[i].y++;
                                    }
                                    else
                                    {
                                        MoveRand(i);
                                    }
                                }
                                else
                                {
                                    if (P1INFOV(i,8))
                                    {
                                        game.zom[i].y++;
                                    }
                                    else
                                    {
                                        MoveRand(i);
                                    }
                                }
                            }
                            else if (GetChar(ZomDir(i,'d'),game.zom[i].x,'T'))
                            {
                                game.zom[i].HP -= game.p1.trap.damage;
                                Map[ZomDir(i,'d')][game.zom[i].x] = ' ';
                            }
                            else if (GetChar(ZomDir(i,'d'),game.zom[i].x,'B'))
                            {
                                Map[ZomDir(i,'d')][game.zom[i].x] = '*';
                            }
                            else if (GetChar(ZomDir(i,'d'),game.zom[i].x,'D'))
                            {
                                Map[ZomDir(i,'d')][game.zom[i].x] = '*';
                            }
                            else if (GetChar(ZomDir(i,'d'),game.zom[i].x,'*'))
                            {
                                Map[ZomDir(i,'d')][game.zom[i].x] = ',';
                            }
                            else if (GetChar(ZomDir(i,'d'),game.zom[i].x,','))
                            {
                                Map[ZomDir(i,'d')][game.zom[i].x] = '.';
                            }
                            else if (GetChar(ZomDir(i,'d'),game.zom[i].x,'.'))
                            {
                                Map[ZomDir(i,'d')][game.zom[i].x] = ' ';
                            }
                        }
                    }
                    else
                    {
                        game.p1.HP -= rand()%game.zombies_damage_base;
                        game.p1.c = '*';
                    }
                }
                if (game.zom[i].y > game.p1.y)
                {
                    if (p1AtPoint(ZomDir(i,'u'),game.zom[i].x) == false)
                    {
                        if (zomAtPoint(ZomDir(i,'u'),game.zom[i].x) == false)
                        {
                            if (GetChar(ZomDir(i,'u'),game.zom[i].x,' '))
                            {
                                if (game.DayNightTime == 1)
                                {
                                    if (P1INFOV(i,4))
                                    {
                                        game.zom[i].y--;
                                    }
                                    else
                                    {
                                        MoveRand(i);
                                    }
                                }
                                else
                                {
                                    if (P1INFOV(i,8))
                                    {
                                        game.zom[i].y--;
                                    }
                                    else
                                    {
                                        MoveRand(i);
                                    }
                                }
                            }
                            else if (GetChar(ZomDir(i,'u'),game.zom[i].x,'T'))
                            {
                                game.zom[i].HP -= game.p1.trap.damage;
                                Map[ZomDir(i,'u')][game.zom[i].x] = ' ';
                            }
                            else if (GetChar(ZomDir(i,'u'),game.zom[i].x,'B'))
                            {
                                Map[ZomDir(i,'u')][game.zom[i].x] = '*';
                            }
                            else if (GetChar(ZomDir(i,'u'),game.zom[i].x,'D'))
                            {
                                Map[ZomDir(i,'u')][game.zom[i].x] = '*';
                            }
                            else if (GetChar(ZomDir(i,'u'),game.zom[i].x,'*'))
                            {
                                Map[ZomDir(i,'u')][game.zom[i].x] = ',';
                            }
                            else if (GetChar(ZomDir(i,'u'),game.zom[i].x,','))
                            {
                                Map[ZomDir(i,'u')][game.zom[i].x] = '.';
                            }
                            else if (GetChar(ZomDir(i,'u'),game.zom[i].x,'.'))
                            {
                                Map[ZomDir(i,'u')][game.zom[i].x] = ' ';
                            }
                        }
                    }
                    else
                    {
                        game.p1.HP -= rand()%game.zombies_damage_base;
                        game.p1.c = '*';
                    }
                }
                if (game.zom[i].x < game.p1.x)
                {
                    if (p1AtPoint(game.zom[i].y,ZomDir(i,'r')) == false)
                    {
                        if (zomAtPoint(game.zom[i].y,ZomDir(i,'r')) == false)
                        {
                            if (GetChar(game.zom[i].y,ZomDir(i,'r'),' '))
                            {
                                if (game.DayNightTime == 1)
                                {
                                    if (P1INFOV(i,4))
                                    {
                                        game.zom[i].x++;
                                    }
                                    else
                                    {
                                        MoveRand(i);
                                    }
                                }
                                else
                                {
                                    if (P1INFOV(i,8))
                                    {
                                        game.zom[i].x++;
                                    }
                                    else
                                    {
                                        MoveRand(i);
                                    }
                                }
                            }
                            else if (GetChar(game.zom[i].y,ZomDir(i,'r'),'T'))
                            {
                                game.zom[i].HP -= game.p1.trap.damage;
                                Map[game.zom[i].y][ZomDir(i,'r')] = ' ';
                            }
                            else if (GetChar(game.zom[i].y,ZomDir(i,'r'),'B'))
                            {
                                Map[game.zom[i].y][ZomDir(i,'r')] = '*';
                            }
                            else if (GetChar(game.zom[i].y,ZomDir(i,'r'),'D'))
                            {
                                Map[game.zom[i].y][ZomDir(i,'r')] = '*';
                            }
                            else if (GetChar(game.zom[i].y,ZomDir(i,'r'),'*'))
                            {
                                Map[game.zom[i].y][ZomDir(i,'r')] = ',';
                            }
                            else if (GetChar(game.zom[i].y,ZomDir(i,'r'),','))
                            {
                                Map[game.zom[i].y][ZomDir(i,'r')] = '.';
                            }
                            else if (GetChar(game.zom[i].y,ZomDir(i,'r'),'.'))
                            {
                                Map[game.zom[i].y][ZomDir(i,'r')] = ' ';
                            }
                        }
                    }
                    else
                    {
                        game.p1.HP -= rand()%game.zombies_damage_base;
                        game.p1.c = '*';
                    }
                }
                if (game.zom[i].x > game.p1.x)
                {
                    if (p1AtPoint(game.zom[i].y,ZomDir(i,'l')) == false)
                    {
                        if (zomAtPoint(game.zom[i].y,ZomDir(i,'l')) == false)
                        {
                            if (GetChar(game.zom[i].y,ZomDir(i,'l'),' '))
                            {
                                if (game.DayNightTime == 1)
                                {
                                    if (P1INFOV(i,4))
                                    {
                                        game.zom[i].x--;
                                    }
                                    else
                                    {
                                        MoveRand(i);
                                    }
                                }
                                else
                                {
                                    if (P1INFOV(i,8))
                                    {
                                        game.zom[i].x--;
                                    }
                                    else
                                    {
                                        MoveRand(i);
                                    }
                                }
                            }
                            else if (GetChar(game.zom[i].y,ZomDir(i,'l'),'T'))
                            {
                                game.zom[i].HP -= game.p1.trap.damage;
                                Map[game.zom[i].y][ZomDir(i,'l')] = ' ';
                            }
                            else if (GetChar(game.zom[i].y,ZomDir(i,'l'),'B'))
                            {
                                Map[game.zom[i].y][ZomDir(i,'l')] = '*';
                            }
                            else if (GetChar(game.zom[i].y,ZomDir(i,'l'),'D'))
                            {
                                Map[game.zom[i].y][ZomDir(i,'l')] = '*';
                            }
                            else if (GetChar(game.zom[i].y,ZomDir(i,'l'),'*'))
                            {
                                Map[game.zom[i].y][ZomDir(i,'l')] = ',';
                            }
                            else if (GetChar(game.zom[i].y,ZomDir(i,'l'),','))
                            {
                                Map[game.zom[i].y][ZomDir(i,'l')] = '.';
                            }
                            else if (GetChar(game.zom[i].y,ZomDir(i,'l'),'.'))
                            {
                                Map[game.zom[i].y][ZomDir(i,'l')] = ' ';
                            }
                        }
                    }
                    else
                    {
                        game.p1.HP -= rand()%game.zombies_damage_base;
                        game.p1.c = '*';
                    }
                }
                game.zom[i].speedcount = 0;
            }
            else
            {
                game.zom[i].speedcount++;
            }
        }
    }
}

void SetZomDead()
{
    for (int i = 0; i < game.zombies_max; i++)
    {
        if (game.zom[i].HP <= 0)
        {
            game.zom[i].DEAD = true;
        }
    }
}



class Cur
{
public:
    int y;
    int x;
    int c;
};
Cur cp;

int TrapCount()
{
    int count = 0;
    for (int y = 0; y < 18; y++)
    {
        for (int x = 0; x < 60; x++)
        {
            if (TrapMap[y][x] == 'T')
            {
                count++;
            }
        }
    }
    return count;
}

int BlockCount()
{
    int count = 0;
    for (int y = 0; y < 18; y++)
    {
        for (int x = 0; x < 60; x++)
        {
            if (TrapMap[y][x] == 'B')
            {
                count++;
            }
        }
    }
    return count;
}

void ClearTraps()
{
    for (int y = 0; y < 18; y++)
        for (int x = 0; x < 60; x++)
            if (TrapMap[y][x] != ' ')
            {
                TrapMap[y][x] = ' ';
            }
}

void DrawTrapMap()
{
    for (int y = 0; y < 18; y++)
    {
        for (int x = 0; x < 60; x++)
        {
            if (TrapMap[y][x] != ' ')
            {
                mvaddch(y,x,TrapMap[y][x]);
            }
        }
    }
}

void PlaceTraps()
{
    for (int y = 0; y < 18; y++)
    {
        for (int x = 0; x < 60; x++)
        {
            if (Map[y][x] == ' ')
            {
                if (TrapMap[y][x] == 'T')
                {
                    Map[y][x] = TrapMap[y][x];
                }
            }
        }
    }
}

void PlaceBlocks()
{
    for (int y = 0; y < 18; y++)
    {
        for (int x = 0; x < 60; x++)
        {
            if (Map[y][x] == ' ')
            {
                if (TrapMap[y][x] == 'B')
                {
                    Map[y][x] = TrapMap[y][x];
                }
            }
        }
    }
}

bool inTrapSetUp = true;
bool inGunSetUp = true;
int totalcost = 0;
void CurMovement()
{
    int key = getch();
    if (key == KEY_UP)
    {
        if (GetChar((cp.y-1),cp.x,'#') == false)
        {
            cp.y--;
        }
    }
    if (key == KEY_DOWN)
    {
        if (GetChar((cp.y+1),cp.x,'#') == false)
        {
            cp.y++;
        }
    }
    if (key == KEY_LEFT)
    {
        if (GetChar(cp.y,(cp.x-1),'#') == false)
        {
            cp.x--;
        }
    }
    if (key == KEY_RIGHT)
    {
        if (GetChar(cp.y,(cp.x+1),'#') == false)
        {
            cp.x++;
        }
    }
    if (key == 't')
    {
        if (p1AtPoint(cp.y,cp.x) == false)
        {
            TrapMap[cp.y][cp.x] = 'T';
        }
    }
    if (key == 'b')
    {
        if (p1AtPoint(cp.y,cp.x) == false)
        {
            TrapMap[cp.y][cp.x] = 'B';
        }
    }
    if (key == 's')
    {
        inTrapSetUp = false;
        ClearTraps();
    }
    if (key == 'c')
    {
        ClearTraps();
    }
    if (key == ' ')
    {
        if (game.p1.GOLD >= totalcost)
        {
            game.p1.GOLD -= totalcost;
            PlaceTraps();
            PlaceBlocks();
            inTrapSetUp = false;
        }
    }
    flushinp();
}

void SetUpTraps()
{
    clear();
    inTrapSetUp = true;
    ClearTraps();
    nodelay(stdscr,1);
    cp.x = 1;
    cp.y = 1;
    while (inTrapSetUp == true)
    {
        totalcost = game.p1.trap.cost*TrapCount();
        totalcost += game.p1.block.cost*BlockCount();
        CurMovement();
        DrawNOFOV();
        DrawTrapMap();
        DrawPlayer();
        mvaddch(cp.y,cp.x,'X');
        attrset(COLOR_PAIR(8));
        mvprintw(19,0,"Cost : %i$ ",totalcost);
        attrset(COLOR_PAIR(8)|A_BOLD);
        mvprintw(20,0,"Cash : %.2f $",game.p1.GOLD);
        attrset(COLOR_PAIR(2)|A_BOLD);
        mvprintw(21,0,"Press t key to place traps, b to place blocks, s key to go back");
        attrset(COLOR_PAIR(5)|A_BOLD);
        mvprintw(22,0,"Press space set and buy traps, c to clear");
        refresh();
        napms(50);
    }
}

void GunShop()
{
    clear();
    inGunSetUp = true;
    nodelay(stdscr,0);
    int selpos = 0;
    while (inGunSetUp == true)
    {
        clear();
        if (selpos == 0)
        {
            attrset(COLOR_PAIR(2)|A_BOLD);
            mvprintw(0,0,"Buy Clips[+1] - 50$ <");
            attrset(COLOR_PAIR(0));
            mvprintw(1,0,"Upgrade Capacity[+5] - 150$");
            mvprintw(2,0,"Upgrade Damage[+1] - 150$");
        }
        else if (selpos == 1)
        {
            attrset(COLOR_PAIR(0));
            mvprintw(0,0,"Buy Clips[+1] - 50$");
            attrset(COLOR_PAIR(2)|A_BOLD);
            mvprintw(1,0,"Upgrade Capacity[+5] - 150$ <");
            attrset(COLOR_PAIR(0));
            mvprintw(2,0,"Upgrade Damage[+1] - 150$");
        }
        else if (selpos == 2)
        {
            attrset(COLOR_PAIR(0));
            mvprintw(0,0,"Buy Clips[+1] - 50$");
            mvprintw(1,0,"Upgrade Capacity[+5] - 150$ ");
            attrset(COLOR_PAIR(2)|A_BOLD);
            mvprintw(2,0,"Upgrade Damage[+1] - 150$ <");
        }
        attrset(COLOR_PAIR(1)|A_BOLD);
        mvprintw(15,0,"Damage : %i",game.p1.gun.damage);
        attrset(COLOR_PAIR(5)|A_BOLD);
        mvprintw(16,0,"Capacity : %i",game.p1.gun.cap);
        attrset(COLOR_PAIR(2));
        mvprintw(17,0,"Clips : %i",game.p1.gun.clips);

        attrset(COLOR_PAIR(8)|A_BOLD);
        mvprintw(20,0,"Cash : %.2f $",game.p1.GOLD);
        attrset(COLOR_PAIR(5)|A_BOLD);
        mvprintw(21,0,"Press s key to go back");
        attrset(COLOR_PAIR(2)|A_BOLD);
        mvprintw(22,0,"Press space to buy");
        refresh();

        int key = getch();
        if (key == 's')
        {
            inGunSetUp = false;
        }
        else if (key == ' ')
        {
            if (selpos == 0)
            {
                if (game.p1.GOLD >= 50)
                {
                    game.p1.gun.clips++;
                    game.p1.GOLD -= 50;
                }
            }
            else if (selpos == 1)
            {
                if (game.p1.GOLD >= 150)
                {
                    game.p1.gun.cap += 5;
                    game.p1.GOLD -= 150;
                }
            }
            else if (selpos == 2)
            {
                if (game.p1.GOLD >= 150)
                {
                    game.p1.gun.damage++;
                    game.p1.GOLD -= 150;
                }
            }
        }
        else if (key == KEY_UP)
        {
            selpos -= 1;
        }
        else if (key == KEY_DOWN)
        {
            selpos += 1;
        }
        if (selpos < 0)
        {
            selpos = 0;
        }
        if (selpos > 2)
        {
            selpos = 2;
        }
    }
}

void PlaceRandomHealth()
{
    for (int i = 0; i < 2; i++)
    {
tryy2:
        int y2 = rand()%16+1;
        int x2 = rand()%55+3;
        if (Map[y2][x2] == ' ')
        {
            Map[y2][x2] = '+';
        }
        else
        {
            goto tryy2;
        }
    }
}

int GetBonus()
{
    int bonus = 0;
    for (int y = 0; y < 18; y++)
    {
        for (int x = 0; x < 60; x++)
        {
            if (Map[y][x] == '|')
            {
                bonus += 10;
            }
            else if (Map[y][x] == '=')
            {
                bonus += 10;
            }
            else if (Map[y][x] == '0')
            {
                bonus += 10;
            }
            else if (Map[y][x] == '-')
            {
                bonus += 10;
            }
            else if (Map[y][x] == '[')
            {
                bonus += 10;
            }
            else if (Map[y][x] == ']')
            {
                bonus += 10;
            }
            else if (Map[y][x] == '_')
            {
                bonus += 10;
            }
        }
    }
    return bonus;
}

void Upgrade()
{
    clear();
    bool inUpgradeMode = true;
    nodelay(stdscr,0);
    int selpos = 0;
    game.p1.GOLD += game.bounty*(double)game.zombies_max;
    while (inUpgradeMode == true)
    {
        clear();
        if (selpos == 0)
        {
            attrset(COLOR_PAIR(2)|A_BOLD);
            mvprintw(0,0,"Damage Upgrade[+1] - %i$ < ",game.damcost);
            attrset(COLOR_PAIR(0));
            mvprintw(1,0,"Heal[+5] - 1$");
            mvprintw(2,0,"Health Upgrade[+10] - %i$",game.hpcost);
            mvprintw(3,0,"Random Health Packs - 20$");
            mvprintw(4,0,"C4 Charges - 500$");
        }
        else if (selpos == 1)
        {
            attrset(COLOR_PAIR(0));
            mvprintw(0,0,"Damage Upgrade[+1] - %i$",game.damcost);
            attrset(COLOR_PAIR(2)|A_BOLD);
            mvprintw(1,0,"Heal[+5] - 1$ < ");
            attrset(COLOR_PAIR(0));
            mvprintw(2,0,"Health Upgrade[+10] - %i$",game.hpcost);
            mvprintw(3,0,"Random Health Packs - 20$");
            mvprintw(4,0,"C4 Charges - 500$");
        }
        else if (selpos == 2)
        {
            attrset(COLOR_PAIR(0));
            mvprintw(0,0,"Damage Upgrade[+1] - %i$",game.damcost);
            mvprintw(1,0,"Heal[+5] - 1$");
            attrset(COLOR_PAIR(2)|A_BOLD);
            mvprintw(2,0,"Health Upgrade[+10] - %i$ < ",game.hpcost);
            attrset(COLOR_PAIR(0));
            mvprintw(3,0,"Random Health Packs - 20$");
            mvprintw(4,0,"C4 Charges - 500$");
        }
        else if (selpos == 3)
        {
            attrset(COLOR_PAIR(0));
            mvprintw(0,0,"Damage Upgrade[+1] - %i$",game.damcost);
            mvprintw(1,0,"Heal[+5] - 1$");
            mvprintw(2,0,"Health Upgrade[+10] - %i$",game.hpcost);
            attrset(COLOR_PAIR(2)|A_BOLD);
            mvprintw(3,0,"Random Health Packs - 20$ < ");
            attrset(COLOR_PAIR(0));
            mvprintw(4,0,"C4 Charges - 500$");
        }
        else if (selpos == 4)
        {
            attrset(COLOR_PAIR(0));
            mvprintw(0,0,"Damage Upgrade[+1] - %i$",game.damcost);
            mvprintw(1,0,"Heal[+5] - 1$");
            mvprintw(2,0,"Health Upgrade[+10] - %i$",game.hpcost);
            mvprintw(3,0,"Random Health Packs - 20$ ");
            attrset(COLOR_PAIR(2)|A_BOLD);
            mvprintw(4,0,"C4 Charges - 500$ < ");
            attrset(COLOR_PAIR(0));
        }
        attrset(COLOR_PAIR(8)|A_BOLD);
        mvprintw(6,0,"Cash : %.2f $",game.p1.GOLD);
        attrset(COLOR_PAIR(1)|A_BOLD);
        mvprintw(7,0,"Damage : %i-%i",game.p1.damage_min,game.p1.damage);
        attrset(COLOR_PAIR(2)|A_BOLD);
        mvprintw(8,0,"HP : %i/%i",game.p1.HP,game.p1.MAXHP);
        attrset(COLOR_PAIR(8));
        mvprintw(9,0,"C4 : %i/%i",game.p1.c4Ammo,game.p1.c4_max);
        attrset(COLOR_PAIR(0));
        mvprintw(17,0,"Wave : %i",game.wave);
        mvprintw(18,0,"Zombies Hp : %i   Zombies Damage : %i-%i",game.HP,game.zombies_damage_min,game.zombies_damage_base);
        attrset(COLOR_PAIR(5)|A_BOLD);
        mvprintw(20,0,"Press space key to buy");
        attrset(COLOR_PAIR(2)|A_BOLD);
        mvprintw(21,0,"Press b key to build");
        attrset(COLOR_PAIR(1)|A_BOLD);
        mvprintw(22,0,"Press g key to upgrade gun");
        attrset(COLOR_PAIR(8)|A_BOLD);
        mvprintw(23,0,"Press s key to start");
        int input = getch();
        if (input == KEY_DOWN)
        {
            selpos++;
        }
        else if (input == KEY_UP)
        {
            selpos--;
        }
        else if (input == 's')
        {
            inUpgradeMode = false;
        }
        else if (input == 'b')
        {
            SetUpTraps();
        }
        else if (input == 'g')
        {
            GunShop();
        }
        else if (input == ' ')
        {
            if (selpos == 0)
            {
                if (game.p1.GOLD >= game.damcost)
                {
                    game.p1.GOLD -= game.damcost;
                    game.p1.damage++;
                    game.p1.damage_min++;
                    game.damcost += 5;
                }
            }
            if (selpos == 2)
            {
                if (game.p1.GOLD >= game.hpcost)
                {
                    game.p1.GOLD -= game.hpcost;
                    game.p1.MAXHP += 10;
                    game.hpcost += 5;
                }
            }
            if (selpos == 3)
            {
                if (game.p1.GOLD >= 20)
                {
                    game.p1.GOLD -= 20;
                    PlaceRandomHealth();
                }
            }
            else if (selpos == 1)
            {
                if (game.p1.GOLD >= 1)
                {
                    if (game.p1.HP != game.p1.MAXHP)
                    {
                        game.p1.GOLD -= 1;
                        game.p1.HP += 5;
                    }
                }
            }
            else if (selpos == 4)
            {
                if (game.p1.GOLD >= 500)
                {
                    if (game.p1.c4Ammo < game.p1.c4_max)
                    {
                        game.p1.GOLD -= 500;
                        game.p1.c4Ammo++;
                    }
                }
            }
        }
        if (selpos < 0)
        {
            selpos = 0;
        }
        if (selpos > 4)
        {
            selpos = 4;
        }
        if (game.p1.HP > game.p1.MAXHP)
        {
            game.p1.HP = game.p1.MAXHP;
        }
        refresh();
    }
    nodelay(stdscr,1);
    clear();
}

void Story()
{
    clear();
    bool inmenu = true;
    bool upgrade = false;
    nodelay(stdscr,1);
    while(inmenu == true)
    {
        if (game.DayNightTime == 0)
        {
            mvprintw(0,0,"Day State : Day");
        }
        else
        {
            mvprintw(0,0,"Day State : Night");
        }
        mvprintw(2,0,"Wave Profit : %.2f $",game.bounty*(double)game.zombies_max);
        mvprintw(4,0,"Press u key to upgrade");
        refresh();
        int key = getch();
        if (key = 'u')
        {
            upgrade = true;
            inmenu = false;
        }
    }
    Upgrade();
}

void Story2()
{
    clear();
    bool inmenu = true;
    bool upgrade = false;
    nodelay(stdscr,1);
    while(inmenu == true)
    {
        if (game.DayNightTime == 0)
        {
            mvprintw(0,0,"Day State : Day");
        }
        else
        {
            mvprintw(0,0,"Day State : Night");
        }
        mvprintw(2,0,"Wave Profit : %.2f $",game.bounty*(double)game.zombies_max);
        mvprintw(3,0,"Building Bonus : %i $",GetBonus());
        mvprintw(5,0,"You Move To A New Location");
        mvprintw(8,0,"Press u key to upgrade");
        refresh();
        int key = getch();
        if (key == 'u')
        {
            upgrade = true;
            inmenu = false;
        }
    }
    game.p1.GOLD += GetBonus();
    Upgrade();
}

int main()
{
    init();
    bool GameOver = false;
    nodelay(stdscr,0);
diff:
    clear();
    DrawAnimation(MainMenuAni,0,1,1);
    refresh();
    int mai = getch();
    if (mai == 'a')
    {
        DrawAnimation(MainMenuAni,0,10,80);
        survival_mode = false;
        // adventure
    }
    else if (mai == 's')
    {
        DrawAnimation(MainMenuAni,0,10,80);
        clear();
        DrawAnimation(DiffMenuAni,0,1,1);
        refresh();
        int dif = getch();
        if (dif == 'e')
        {
            survival_mode = true;
            DrawAnimation(DiffMenuAni,0,10,80);
            game.p1.y = 9;
            game.p1.x = 30;
            game.p1.HP = 50;
            game.p1.damage = 15;
            game.p1.c = '@';
            game.p1.MAXHP = 50;
            game.speed = 30;
            game.zombies_max = 4;
            game.wave = 1;
            game.HP = 10;
            game.zombies_damage_base = 3;
            game.bounty = 1;
            game.p1.trap.cost = 10;
            game.p1.GOLD = 1000;
            game.p1.trap.damage = 100;
            game.p1.block.cost = 10;
            game.damcost = 100;
            game.hpcost = 175;
            game.p1.c4_max = 3;
        }
        else if (dif == 'n')
        {
            survival_mode = true;
            DrawAnimation(DiffMenuAni,0,10,80);
            game.p1.y = 9;
            game.p1.x = 30;
            game.p1.HP = 50;
            game.p1.damage = 8;
            game.p1.c = '@';
            game.p1.MAXHP = 50;
            game.speed = 20;
            game.zombies_max = 6;
            game.wave = 1;
            game.HP = 10;
            game.zombies_damage_base = 6;
            game.bounty = 0.50;
            game.p1.trap.cost = 10;
            game.p1.GOLD = 1000;
            game.p1.trap.damage = 100;
            game.p1.block.cost = 10;
            game.damcost = 100;
            game.hpcost = 175;
            game.p1.c4_max = 3;
        }
        else if (dif == 'h')
        {
            survival_mode = true;
            DrawAnimation(DiffMenuAni,0,10,80);
            game.p1.y = 9;
            game.p1.x = 30;
            game.p1.HP = 50;
            game.p1.damage = 8;
            game.p1.c = '@';
            game.p1.MAXHP = 50;
            game.speed = 10;
            game.zombies_max = 8;
            game.wave = 1;
            game.HP = 10;
            game.zombies_damage_base = 9;
            game.bounty = 0.50;
            game.p1.trap.cost = 10;
            game.p1.GOLD = 1000;
            game.p1.trap.damage = 100;
            game.p1.block.cost = 10;
            game.damcost = 100;
            game.hpcost = 175;
            game.p1.c4_max = 3;
        }
        else if (dif == 'c')
        {
            survival_mode = true;
            DrawAnimation(DiffMenuAni,0,10,80);
            clear();
            endwin();
            game.p1.y = 9;
            game.p1.x = 30;
            game.p1.HP = 50;
            game.p1.damage = 8;
            game.p1.c = '@';
            game.p1.MAXHP = 50;
            game.speed = 10;
            game.zombies_max = 8;
            game.wave = 1;
            game.HP = 10;
            game.zombies_damage_base = 9;
            game.bounty = 0.50;
            game.p1.trap.cost = 10;
            game.p1.GOLD = 1000;
            game.p1.trap.damage = 100;
            game.p1.block.cost = 10;
            game.damcost = 100;
            game.hpcost = 175;
            cout << "Enter player max HP : ";
            cin >> game.p1.MAXHP;
            cout << endl;
            game.p1.HP = game.p1.MAXHP;
            cout << "Enter players starting damage : ";
            cin >> game.p1.damage;
            cout << endl;
            cout << "Enter max amount of c4 : ";
            cin >> game.p1.c4_max;
            cout << endl;
            cout << "Enter starting cash amount : ";
            cin >> game.p1.GOLD;
            cout << endl;
            cout << "Enter bounty for each kill : ";
            cin >> game.bounty;
            cout << endl;
            cout << "Enter the amount of zombies to start with : ";
            cin >> game.zombies_max;
            cout << endl;
            cout << "Enter zombies starting damage : ";
            cin >> game.zombies_damage_base;
            cout << endl;
            cout << "Enter the starting speed(30 slow, 0 fast)" << endl << ": ";
            cin >> game.speed;
            cout << endl;
            init();
        }
        else
        {
            goto diff;
        }
    }
    else
    {
        goto diff;
    }
    if (survival_mode == true)
    {
        SetZomSettings(game.zombies_max,game.speed,game.HP,game.zombies_damage_base,game.bounty);
        respawnZom();

        game.p1.gun.speedtime = 5;
        game.p1.gun.clips = 1;
        game.p1.gun.cap = 10;
        game.p1.ammo = 10;
        game.p1.gun.damage = 5;

        int temphp = game.p1.HP;
        int tempammo = game.p1.ammo;
        nodelay(stdscr,0);
        clear();
        DrawAnimation(MenuAni,0,45,50);
        getch();
        DrawAnimation(MenuAni,46,100,50);
        clear();
        mvprintw(0,0,"                      Instructions                    ");
        mvprintw(1,2,"+ = health packs - heals 10 health when you pick it up");
        mvprintw(2,2,"T = traps - traps do 100 damage to a zombie that stands on it");
        mvprintw(3,2,"Z = Zombie - they get faster and harder to kill");
        mvprintw(4,2,"@ = You - you are the only serviver left alive");
        mvprintw(5,2,"buttons:");
        mvprintw(6,2,"s - cancel/skip");
        mvprintw(7,2,"c - clear(trap menu)/Set C4");
        mvprintw(8,2,"d - Detonate C4");
        mvprintw(9,2,"t - set trap(trap menu)");
        mvprintw(10,2,"space - action/buy/shoot");
        mvprintw(11,2,"arrow keys - move player/selection");
        mvprintw(12,2,"q - quit game");
        mvprintw(13,2,"Attacking : move into a zombie to attack it");
        getch();
        nodelay(stdscr,1);
        game.templvl = 5;
        clear();
        ChangeLocation(rand()%13);
        Story();
        game.wave = 1;
        game.p1.sight = 12;
        while (NewGame == true)
        {
            if (game.p1.c == '*')
            {
                game.p1.c = '@';
            }
            if (game.p1.HP > game.p1.MAXHP)
            {
                game.p1.HP = game.p1.MAXHP;
            }
            if (game.p1.HP <= 0)
            {
                GameOver = true;
                NewGame = false;
            }
            if (game.speed < 1)
            {
                game.speed = 1;
            }
            if (game.zombies_dead >= game.zombies_max)
            {
                if (game.wave >= game.templvl)
                {
                    game.templvl += 5;
                    game.zombies_damage_min++;
                    game.zombies_damage_base++;
                    SetZomSettings(game.zombies_max+4,game.speed-1,game.HP+1,game.zombies_damage_base,game.bounty+0.50);
                    game.wave++;
                    SwitchTime();
                    ChangeLocation(rand()%13);
                    clear();
                    DrawAnimation2(MoveLoca,0,57,50);
                    respawnZom();
                    Story2();
                }
                else
                {
                    SetZomSettings(game.zombies_max+4,game.speed-1,game.HP+1,game.zombies_damage_base,game.bounty+0.50);
                    game.wave++;
                    SwitchTime();
                    respawnZom();
                    Story();
                }
            }
            SetZomDead();
            //erase();
            //fillmap();
            temphp = game.p1.HP;
            tempammo = game.p1.ammo;
            Movement();
            BulMovement();
            EMovement();
            erase();
            Draw();
            if (game.DayNightTime == 0)
            {
                game.p1.sight = 12;
                P1FOV(game.p1.sight);
            }
            else
            {
                game.p1.sight = 8;
                P1FOV(game.p1.sight);
            }
            DrawBlood();
            DrawBuls();
            DrawPlayer();
            DrawZoms();
            DrawC4();
            DrawGUI();
            refresh();
            napms(50);
            //if (temphp != game.p1.HP) { clear(); }
            //else if (tempammo != game.p1.ammo) { clear(); }
        }
        clear();
        DrawAnimation(GameOAni,0,19,150);
        mvprintw(1,0,"press space to exit");
        while (GameOver == true)
        {
            int wait = getch();
            if (wait == ' ')
            {
                GameOver = false;
            }
        }
    }
    else
    {
        game.p1.HP = 50;
        game.p1.damage = 15;
        game.p1.c = '@';
        game.p1.MAXHP = 50;
        game.speed = 30;
        game.zombies_max = 1000;
        game.wave = 1;
        game.HP = 10;
        game.zombies_damage_base = 3;
        game.bounty = 1;
        game.p1.trap.cost = 10;
        game.p1.GOLD = 1000;
        game.p1.trap.damage = 100;
        game.p1.block.cost = 10;
        game.damcost = 100;
        game.hpcost = 175;
        game.p1.c4_max = 3;
        Gen_New_AdvMap();
        nodelay(stdscr,0);
        NewGame = true;
        Adv_zomInit();
        SetZomSettings(game.zombies_max,game.speed-1,game.HP+1,game.zombies_damage_base,game.bounty+0.50);
        game.zom[0].x = 10;
        game.zom[0].y = 10;
        while (NewGame == true)
        {
            Adv_respawnZom();
            SetZomDead();
            //Move_player();
            AdvMovement();
            clear();
            Draw_AdvMap();
            mvaddch(12,40,'@');
            DrawZoms2();
            refresh();
            napms(50);
        }
    }
    clear();
    endwin();
    return 0;
}
