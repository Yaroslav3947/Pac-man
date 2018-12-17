#include "Game.hpp"

Game::Game(){

}
Game::Game(char userMap[MAP_HEIGHT][MAP_WIDTH]){
	initView();
	map.reserve(MAP_HEIGHT);
	for (size_t i = 0; i < MAP_HEIGHT; i++){
		map[i].reserve(MAP_WIDTH);
		for (size_t j = 0; j < MAP_WIDTH; j++){
			if (userMap[i][j] == ' ' || userMap[i][j] == '.' || userMap[i][j] == '#')
				initMap(userMap[i][j], i, j);
			else if (userMap[i][j] == 'O' || userMap[i][j] == 'X'){
				initObjPool(userMap[i][j], i, j);
				initMap(' ', i, j);
			}
		}
	}
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
	system("printf '\e[8;65;35t'");
	setlocale(LC_ALL, "");
	initscr();
	start_color();
	noecho();
	cbreak();
	timeout(0);
	curs_set(0);
	wMap = newwin(MAP_HEIGHT + 2, MAP_WIDTH + 4, 1, 1);
	wScore = newwin(3, MAP_WIDTH + 4, MAP_HEIGHT + 1, 1);
	box(wScore, 0, 0);
	wrefresh(wMap);
	wrefresh(wScore);
	//refresh();
	usleep(1000);

	init_pair(COLOR_ROAD, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_BORDER, COLOR_BLACK, COLOR_YELLOW);
	init_pair(COLOR_GAMEOVER, COLOR_RED, COLOR_BLACK);

}
Game::~Game(){
	delwin(wMap);
	delwin(wScore);
	endwin();
}

void	Game::initMap(char c, size_t i, size_t j){
	switch(c){
		case ' ':
		map[i][j] = make_pair(' ', COLOR_ROAD);
		break ;
		case '.':
		map[i][j] = make_pair('.', COLOR_ROAD);
		break ;
		case '#':
		map[i][j] = make_pair(' ', COLOR_BORDER);
		break ;
		default:
		map[i][j] = make_pair(' ', COLOR_ROAD);
	}

}
void	Game::initObjPool(char c, size_t i, size_t j){
	if (c == 'O')
		objPool.push_front(new Pacman(j, i));
	else
		objPool.push_back(new Enemy(j, i));
}
void	Game::gameCycle(){

	int i = 0;

	showMap();
	while (userController()){
		moveObjects();
		if (objPool[0]->isAlive() == false)
			break ;
		showTheGame();
		usleep(393310);
		i++;
	}
	gameIsOver();
}
bool Game::userController(){
	int c;

	c = getch();
	if (c == 's' || c == 'w' || c == 'a' || c == 'd')
		objPool[0]->setDirection(c);
	else if (c == KEY_ESC)
		return false;
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

void	Game::gameIsOver(){
	string gameIsOver = "GAME OVER";
	wattron(wMap, COLOR_PAIR(COLOR_GAMEOVER));
	mvwprintw(wMap, MAP_HEIGHT/2, MAP_WIDTH/2 - gameIsOver.size()/2, "%s", gameIsOver.c_str());
	wattroff(wMap, COLOR_PAIR(COLOR_GAMEOVER));
	wrefresh(wMap);
	usleep(3333333);

}

void	Game::moveObjects(){
	for (size_t i = 0; i < objPool.size(); i++)
		objPool[i]->move(map, wMap, wScore, objPool);
}