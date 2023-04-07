#include <iostream>
#include<ncurse.h>
#include <unistd.h>
#include <vector>
#include <set>
#include <random>

using namespace std;

#define TIMER_NORMAL    100000
#define TIMER_CHANGE    5000
#define TIMER_MIN       10000
#define TIMER_MAX       200000

#define MAIN_COLOR      1
#define STAT_COLOR      2
#define PLAY_COLOR      3
#define MOVO_COLOR      4
#define REVO_COLOR      5
#define ENEM_COLOR      6


#define UP              'w'
#define DOWN            'x'
#define LEFT            'a'
#define RIGHT           'd'
#define UPLEFT          'q'
#define UPRIGHT         'e'
#define DOLEFT          'z'
#define DORIGHT         'c'

// global macros for screen size: LINES x COLS


void PrintKeypressed(WINDOW* win, char ch)
{
                mvwprintw(win,1,1,"Pressed %c",ch);
                wrefresh(win);
}

void PrintPosition(WINDOW* win, int x, int y, unsigned int timer)
{
                mvwprintw(win,1,25,"Position: %3d %3d", x, y);
                mvwprintw(win,1,60,"Timer: %10d", timer);
                wrefresh(win);

void UpdateTimer(unsigned int& timer, char ch)
{
        if (ch == '<') timer -= TIMER_CHANGE;
        if (ch == '>') timer += TIMER_CHANGE;
        if (timer < TIMER_MIN) timer = TIMER_MIN;
        if (timer > TIMER_MAX) timer = TIMER_MAX;
}

// moving object
class MOVO {
private:
        int xp, yp; // position
        int xd, yd; // direction (-+1 - left/right, top/bottom
        char o = '*';
        char e = ' ';
        int color;
        int bgcolor;
        int minx, maxx, miny, maxy;

        WINDOW* win;
public:
        MOVO (WINDOW* w, int x1, int y1, int x, int y, int c, int b, int mi_x, int ma_x, int mi_y, int ma_y) :
                win(w), xp(x1), yp(y1), xd(x), yd(y), color(c), bgcolor(b),
                minx(mi_x), maxx(ma_x), miny(mi_y), maxy(ma_y) { }
        void Show(int r)
        {
                wattron(win, COLOR_PAIR(color));
                mvwprintw(win,yp,xp,"%c",o); // starting point
                if (r) wrefresh(win);
        }
        void Hide(int r)
        {
                wattron(win, COLOR_PAIR(bgcolor));
                mvwprintw(win,yp,xp,"%c",e); // starting point
                if (r) wrefresh(win);
        }
        void UpdateDir(char ch)
          if (ch == LEFT) { xd = -1; yd = 0; } // LEFT
                else if (ch == RIGHT) { xd = 1; yd = 0; } // RIGHT
                else if (ch == UP) { xd = 0; yd = -1; } // UP
                else if (ch == DOWN) { xd = 0; yd = 1; } // DOWN
                else if (ch == UPLEFT) { xd = -1; yd = -1; }
                else if (ch == UPRIGHT) { xd = 1; yd = -1; }
                else if (ch == DOLEFT) { xd = -1; yd = 1; }
                else if (ch == DORIGHT) { xd = 1; yd = 1; }
        }
        void UpdatePos()
        {
                yp = yp + yd;
                xp = xp + xd;

                if (xp == maxx) xd = -1;
                else if (xp == minx) xd = 1;

                if (yp == maxy) yd = -1;
                else if (yp == miny) yd = 1;
        }

        int getX() { return xp; }
        int getY() { return yp; }
};


int main()
{
        // create main window (stdscr)
        int i;
        srand(time(NULL));

        WINDOW *mainwin;
        if ( (mainwin = initscr()) == NULL)
    cerr << "Error initializing ncurses!" << endl;
                exit(EXIT_FAILURE);
        }
        unsigned int timer = TIMER_NORMAL; // 100 000 microseconds

        start_color();
        init_pair(MAIN_COLOR, COLOR_WHITE, COLOR_BLACK);
        init_pair(STAT_COLOR, COLOR_BLACK, COLOR_BLUE);
        init_pair(PLAY_COLOR, COLOR_RED, COLOR_BLACK);
        init_pair(MOVO_COLOR, COLOR_BLUE, COLOR_WHITE);
        init_pair(REVO_COLOR, COLOR_BLUE, COLOR_BLACK);
        init_pair(ENEM_COLOR, COLOR_RED, COLOR_YELLOW);

        noecho();       // no result on the screen after pressing a key
        curs_set(0);    // hide cursor
        wattron(mainwin, COLOR_PAIR(MAIN_COLOR));

        // status init
        WINDOW *status;
        //              y_size,x_size,y_pos,x_pos
        status = subwin(mainwin,3,COLS,LINES-3,0);
        wattron(status, COLOR_PAIR(STAT_COLOR));
        box(status,0,0);
        string line(COLS-2,' ');
        mvwprintw(status,1,1,"%s",line.c_str());
        wrefresh(status);

        // playwin init
        WINDOW *playwin;
        playwin = subwin(mainwin,LINES-3,COLS,0,0);
        wattron(playwin, COLOR_PAIR(PLAY_COLOR));
        box(playwin,0,0);
        wrefresh(playwin);
   nodelay(playwin,TRUE);  // non-blocking reading a character in WINDOW playwin

        MOVO S(playwin, COLS/2, LINES/2, rand()%3 - 1, rand()%3 - 1, MOVO_COLOR, REVO_COLOR, 1, COLS-2, 1, LINES-5);

        vector <MOVO> Enemies;

        // MAIN LOOP (event handling) - moving object (despite of our action)
        char ch;
        PrintPosition(status, S.getX(), S.getY(),timer);
        S.Show(1);

        set <char> C;
        C.emplace(LEFT); C.emplace(RIGHT); C.emplace(UP); C.emplace(DOWN);
        C.emplace(UPLEFT); C.emplace(UPRIGHT); C.emplace(DOLEFT); C.emplace(DORIGHT);


        while ( 1 ) // MAIN LOOP
        {
                ch = wgetch(playwin);// we read a movement of object in playwin; unblocking
                if (ch == 'g') break; // leave while ( 1 )

                S.Hide(0);
                for(i=0; i<Enemies.size(); i++) Enemies[i].Hide(0);

                if (C.find(ch) != C.end())
                {
                        S.UpdateDir(ch);
                        PrintKeypressed(status, ch);
                }
                if (ch == '+')
                {
                        Enemies.push_back(MOVO(playwin, COLS/2, LINES/2, rand()%3 - 1, rand()%3 - 1, ENEM_COLOR, REVO_COLOR, 1, COLS-2, 1, LINES-5));
                }
                if (ch == '-')
  {
                        Enemies.pop_back();
                }

                if (ch == '<' || ch == '>') UpdateTimer(timer, ch);

                for(i=0; i < Enemies.size(); i++) Enemies[i].UpdatePos();
                S.UpdatePos();

                PrintPosition(status, S.getX(), S.getY(), timer);

                for(i=0; i < Enemies.size(); i++) Enemies[i].Show(0);
                S.Show(1);

                usleep(timer);
        }

        delwin(mainwin);
        endwin();
        return EXIT_SUCCESS;
}


