#include "Game.hpp"

Game::Game(){
	initMap();
	initObjPool();
	initView();
}
Game::Game(Game const & other){
	*this = other;
}
Game & Game::operator = (Game const & other){
	objPool = other.objPool;
	//map = other.map;
	return *this;
}
//#include <term.h>
void	Game::initView(){
// /* One-time initialization near the beginning of your program */
// setupterm(NULL, STDOUT_FILENO, NULL);

// /* Enter bold mode */
// putp(enter_bold_mode);

// printf("I am bold\n");

// /* Turn it off! */
// putp(exit_attribute_mode);
	system("printf '\e[8;65;65t'");
	setlocale(LC_ALL, "");
	initscr();
	start_color();
	noecho();
	cbreak();
	timeout(0);
	curs_set(0);
	wMap = newwin(MAP_HEIGHT + 2, MAP_WIDTH + 4, 1, 1);
	wScore = newwin(4, MAP_WIDTH + 4, MAP_HEIGHT + 5, 1);
	box(wScore, 0, 0);
	wrefresh(wMap);
	wrefresh(wScore);
	//refresh();
	usleep(1000);

	init_pair(COLOR_ROAD, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_BORDER, COLOR_BLACK, COLOR_YELLOW);

}
Game::~Game(){
	delwin(wMap);
	delwin(wScore);
	endwin();
}

void	Game::initMap(){
	map.reserve(MAP_HEIGHT);
	for (int i = 0; i < MAP_HEIGHT; i++){
		map[i].reserve(MAP_WIDTH);
		for (int j = 0; j < MAP_WIDTH; j++){
			if (i == 0 || j == 0 || j == 1 || i == MAP_HEIGHT - 1 || j == MAP_WIDTH - 1 || j == MAP_WIDTH - 2)
				map[i][j] = make_pair(L' ', COLOR_BORDER);
			else
			map[i][j] =	j % 2 == 1 ? make_pair(L'.', COLOR_ROAD) : make_pair(L' ', COLOR_ROAD);
		}
	}
	map[5][0] = make_pair(L' ', COLOR_ROAD) ;
	map[5][1] = make_pair(L'.', COLOR_ROAD) ;
	map[5][MAP_WIDTH - 1] = make_pair(L'.', COLOR_ROAD) ;
	map[5][MAP_WIDTH - 2] = make_pair(L' ', COLOR_ROAD) ;
	map[0][5] = make_pair(L'.', COLOR_ROAD) ;
	map[1][5] = make_pair(L'.', COLOR_ROAD) ;
	map[MAP_HEIGHT - 1][5] = make_pair(L'.', COLOR_ROAD) ;
	map[MAP_HEIGHT - 1][5] = make_pair(L' ', COLOR_ROAD) ;


}
void	Game::initObjPool(){
	objPool.push_back(new Pacman());
	objPool.push_back(new Enemy());
}
void	Game::gameCycle(){

	int i = 0;

	showMap();
	objPool[0]->showObj(wMap, wScore);
	objPool[1]->showObj(wMap, wScore);//do while
	while (userController()){
		objPool[0]->move(map, wMap, wScore, objPool);
		objPool[1]->move(map, wMap, wScore, objPool);
		mvwprintw(wScore, 1, 25, "direct = %c i = %d", objPool[0]->getDirection(), i);
		showTheGame();
		usleep(393330);
		i++;
	}
}
bool Game::userController(){
	int c;

	c = getch();
	if (c == 's' || c == 'w' || c == 'a' || c == 'd')
		objPool[0]->setDirection(c);
	return true;
}

void	Game::showTheGame(){

	box(wScore, 0, 0);
	wrefresh(wMap);
	wrefresh(wScore);
}
void	Game::showMap() const{
	for (size_t i = 0; i < MAP_HEIGHT; i++){	
		for (size_t j = 0; j < MAP_WIDTH; j++){
			wattron(wMap, COLOR_PAIR(map[i][j].second));
				mvwprintw(wMap, i, j, "%C", map[i][j].first);
			wattroff(wMap, COLOR_PAIR(map[i][j].second));
		}
	}
}