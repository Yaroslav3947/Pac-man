#include "AGameObj.hpp"

AGameObj::AGameObj() : _x(0), _y(0), _shape(0), _direction(0), _status(1){
}
AGameObj::AGameObj(size_t const & x, size_t const & y, wchar_t const & shape) :
	_x(x), _y(y), _shape(shape), _direction(0), _status(1){
}

AGameObj::AGameObj(AGameObj const & other){
	*this = other;
}
AGameObj & AGameObj::operator = (AGameObj const & other){
	if (this != &other){
		_x = other._x;
		_y = other._y;
		_shape = other._shape;
		_direction = other._direction;
		_status = other._status;
	}
	return *this;
}
AGameObj::~AGameObj(){}
void	AGameObj::move(vector<vPair> & map, WINDOW *wMap, WINDOW *wScore, deque<AGameObj *> & objPool){
	int y = _y;
	int x = _x;

	specialMoving(map, objPool);
	moveCoord(x, y);
	if (coordOnTheBorder(map, x, y) || getStatus() != ALIVE)
		return ;
	cleanPosition(wMap, map);
	setX(x);
	setY(y);
	modifyCoord();
	if (coordOnTheBorder(map, _x, _y)){
		setStatus(KILLED);
		return ;
	}
	showObj(wMap, wScore);

}
void	AGameObj::moveCoord(int & x, int & y){
	if (_direction == LEFT || _direction == RIGHT)
		moveHorizontally(x);
	else if(_direction == UP || _direction == DOWN)
		moveVertically(y);
	
}
void	AGameObj::moveHorizontally(int & x){
	switch(_direction){
		case LEFT:
			x-=1;
		break ;
		case RIGHT:
			x+=1;
		break ;
	}
}
void	AGameObj::moveVertically(int & y){
	switch(_direction){
		case UP:
			y--;
		break ;
		case DOWN:
			y++;
		break ;
	}
}
bool	AGameObj::coordOnTheBorder(vector <vPair> & map, int x, int y) const{
	if (y >= 0 && x >= 0 && y < MAP_HEIGHT && x < MAP_WIDTH){
		if (map[y][x].second == COLOR_BORDER)
			return true;
		return false;
	}
	return false;
}
int &AGameObj::getX(){
	return _x;
}
int &AGameObj::getY(){
	return _y;
}
int	&AGameObj::getDirection(){
	return _direction;
}
void	AGameObj::setX(int const & x){
	_x = x;
}
void	AGameObj::setY(int const & y){
	_y = y;
}
void	AGameObj::setDirection(int const & direction){
	
	_direction = direction;
}
void	AGameObj::showShape(WINDOW *wMap) const{
	mvwprintw(wMap, _y, _x, "%c", _shape);
}
void	AGameObj::cleanPosition(WINDOW *wMap, vector<vPair> & map){
	mvwprintw(wMap, _y, _x, "%c", map[_y][_x].first);
}
void	AGameObj::modifyCoord(){
	modifyVertically();
	modifyHorizontally();
}
void	AGameObj::modifyHorizontally(){
	if (_x < 0)
		_x = MAP_WIDTH - 2;
	else if (_x >= MAP_WIDTH - 1)
		_x = 0;
}
void	AGameObj::modifyVertically(){
	if (_y < 0)
		_y = MAP_HEIGHT - 1;
	else if (_y > MAP_HEIGHT - 1)
		_y = 0;
}
short	& AGameObj::getStatus(){
	return _status;
}
void	AGameObj::setStatus(short const & status){
	_status = status;
}