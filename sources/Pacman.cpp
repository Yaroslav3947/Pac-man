#include "Pacman.hpp"

Pacman::Pacman() : AGameObj(MAP_WIDTH / 2 - 1, MAP_HEIGHT - 3, 'O'), _lives(3), _score(0){
}
Pacman::Pacman(Pacman const & other){
	*this = other;
}
Pacman & Pacman::operator = (Pacman const & other){
	if (this != &other){
		_lives = other._lives;
		_score = other._score;
		_x = other._x;
		_y = other._y;
		_shape = other._shape;
		_direction = other._direction;
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
void	Pacman::specialMoving(vector<vPair> &map, vector<AGameObj *> objPool){
	for (size_t i = 1; i < objPool.size(); i++){
		if (objPool.at(i)->getX() == _x && objPool.at(i)->getY() == _y)
			livesReduction();
	}
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
void	Pacman::livesReduction(){
	if (_lives > 1)
		_lives--;
}
bool	Pacman::isAlive(){
	return (_lives > 0);
}