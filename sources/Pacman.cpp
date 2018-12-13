#include "Pacman.hpp"

Pacman::Pacman() : AGameObj(MAP_WIDTH / 2 - 1, MAP_HEIGHT - 3, L'🤠'), _lives(3), _score(0){
}
Pacman::Pacman(Pacman const & other) : AGameObj(other){
	*this = other;
}
Pacman & Pacman::operator = (Pacman const & other){
	if (this != &other){
		_lives = other._lives;
	}
	return *this;
}
Pacman::~Pacman(){}
void	Pacman::scoreImproving(){
	_score += 10;
}
void	Pacman::setLives(size_t const & lives){
	_lives = lives;
}
void	Pacman::setScore(size_t const & score){
	_score = score;
}
void	Pacman::specialMoving(vector<vPair> &map){
	if (map[_y][_x].first == '.'){
		scoreImproving();
		map[_y][_x].first = ' ';
	}
}
void	Pacman::showObj(WINDOW *wMap, WINDOW *wScore) const{

	showShape(wMap);
	mvwprintw(wScore, 1, 1, "lives: %d", _lives);
	mvwprintw(wScore, 2, 1, "score: %d", _score);
	mvwprintw(wScore, 1, 15, "x = %d", _x);
	mvwprintw(wScore, 2, 15, "y = %d", _y);

}