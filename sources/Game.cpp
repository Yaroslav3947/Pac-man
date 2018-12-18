#include "Game.hpp"

Game::Game(string  userMap[MAP_HEIGHT]){
	string obj("OX");
	string mapPiece(" .*#V");

	if (mapIsValid(userMap) == false)
		throw std::invalid_argument("Map is not valid");
	else{

	initView();
	map.reserve(MAP_HEIGHT);
	for (size_t i = 0; i < MAP_HEIGHT; i++){
		map[i].reserve(MAP_WIDTH);
		for (size_t j = 0; j < MAP_WIDTH; j++){
			if (obj.find(userMap[i][j]) != string::npos){
				initObjPool(userMap[i][j], i, j);
				initMap(' ', i, j);
			}else if (mapPiece.find(userMap[i][j]) != string::npos) 
				initMap(userMap[i][j], i, j);
		}
	}
	}

}
bool	Game::mapIsValid(string  userMap[MAP_HEIGHT]){
	size_t countPacman = 0;
	regex pacman("O");
	regex exitGame("V");
	regex valid("[#V*. OX]*");

	for (size_t i = 0; i < MAP_HEIGHT; i++){
		if ((userMap[i].size() != MAP_WIDTH - 1)
			|| (!regex_match(userMap[i], valid))
			|| (regex_search(userMap[i], exitGame) != false
				&& (i > 0 && i < MAP_WIDTH - 1)))
				return false;
		if (regex_search(userMap[i], pacman) == true){
			countPacman++;
			if (countPacman > 1)
				return false;
		}
	}
	return true;
}

void	Game::initView(){
	setlocale(LC_ALL, "");
	initscr();
	start_color();
	noecho();
	cbreak();
	timeout(0);
	curs_set(0);
	wMap = newwin(MAP_HEIGHT + 2, MAP_WIDTH + 2, 1, 1);
	wScore = newwin(3, MAP_WIDTH + 2, MAP_HEIGHT + 1, 1);
	box(wScore, 0, 0);
	wrefresh(wMap);
	wrefresh(wScore);
	usleep(1000);

	init_pair(COLOR_ROAD, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_BORDER, COLOR_BLACK, COLOR_YELLOW);
	init_pair(COLOR_GAMEOVER, COLOR_RED, COLOR_BLACK);

}
Game::~Game(){
	for (size_t i = 0; i < objPool.size(); i++)
		delete objPool.at(i);
	delwin(wMap);
	delwin(wScore);
	endwin();
}

void	Game::initMap(char c, size_t i, size_t j){
	if (c == '#')
		map[i][j] = make_pair(' ', COLOR_BORDER);
	else
		map[i][j] = make_pair(c, COLOR_ROAD);
}
void	Game::initObjPool(char c, size_t i, size_t j){
	if (c == 'O')
		objPool.push_front(new Pacman(j, i));
	else if (c == 'X')
		objPool.push_back(new Enemy(j, i));
}
void	Game::gameCycle(){

	int i = 0;

	showMap();
	while (userController()){
		moveObjects();
		if (objPool[0]->getStatus() != ALIVE)
			break ;
		showTheGame();
		usleep(393310);
		i++;
	}
	if (objPool[0]->getStatus() == KILLED)
		gameIsOver();
	else if (objPool[0]->getStatus() == WON)
		victory();
}
bool Game::userController(){
	int c;

	c = getch();
	if (c == DOWN || c == UP || c == LEFT || c == RIGHT)
		objPool[0]->setDirection(c);
	else if (c == KEY_ESC)
		return false;
	return true;
}

void	Game::showTheGame(){
	for (size_t i = 0; i < objPool.size(); i++)
		objPool.at(i)->showObj(wMap, wScore);
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

void	Game::gameIsOver() const{
	string gameIsOver = "GAME OVER";
	wattron(wMap, COLOR_PAIR(COLOR_GAMEOVER));
	mvwprintw(wMap, MAP_HEIGHT/2, MAP_WIDTH/2 - gameIsOver.size()/2, "%s", gameIsOver.c_str());
	wattroff(wMap, COLOR_PAIR(COLOR_GAMEOVER));
	wrefresh(wMap);
	usleep(3333333);

}

void	Game::victory() const{
	string gameIsOver = "VICTORY";
	wattron(wMap, COLOR_PAIR(COLOR_ROAD));
	mvwprintw(wMap, MAP_HEIGHT/2, MAP_WIDTH/2 - gameIsOver.size()/2, "%s", gameIsOver.c_str());
	wattroff(wMap, COLOR_PAIR(COLOR_ROAD));
	wrefresh(wMap);
	usleep(3333333);
}

void	Game::moveObjects(){
	for (size_t i = 0; i < objPool.size(); i++)
		objPool[i]->move(map, wMap, objPool);
}