#include "Pacman.hpp"

Pacman::Pacman() : AGameObj(MAP_WIDTH / 2 - 1, MAP_HEIGHT - 3, 'O'), _score(0){
}
Pacman::Pacman(int const x, int const y){

}
Pacman::Pacman(Pacman const & other){
	*this = other;
}
Pacman & Pacman::operator = (Pacman const & other){
	if (this != &other){
		_score = other._score;
		_x = other._x;
		_y = other._y;
		_shape = other._shape;
		_direction = other._direction;
	}
	return *this;
}
Pacman::~Pacman(){}
void	Pacman::scoreImproving(wchar_t & food){
	if (food == '.')
		_score += 10;
	else
		_score+= 100;
}

void	Pacman::setScore(size_t const & score){
	_score = score;
}
void	Pacman::specialMoving(vector<vPair> &map, vector<AGameObj *> & objPool){
	for (size_t i = 1; i < objPool.size(); i++){
		if (objPool.at(i)->getX() == _x && objPool.at(i)->getY() == _y)
			isKilled();
	}
	if (map[_y][_x].first == '.' || map[_y][_x].first == '*'){
		scoreImproving(map[_y][_x].first);
		map[_y][_x].first = ' ';
	}
}
void	Pacman::showObj(WINDOW *wMap, WINDOW *wScore) const{

	showShape(wMap);
	mvwprintw(wScore, 1, 1, "SCORE: %d", _score);
}
size_t & Pacman::getScore(){
	return _score;
}