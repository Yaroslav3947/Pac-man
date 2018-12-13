#include "AGameObj.hpp"

AGameObj::AGameObj() : _x(0), _y(0), _shape(0), _direction(0){
}
AGameObj::AGameObj(size_t const & x, size_t const & y, wchar_t const & shape) :
	_x(x), _y(y), _shape(shape), _direction(0){
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
	}
	return *this;
}
AGameObj::~AGameObj(){}
void	AGameObj::move(vector<vPair> & map, WINDOW *wMap, WINDOW *wScore){
	size_t y = _y;
	size_t x = _x;

	switch(_direction){
		case 'w':
			y--;
		break ;
		case 's':
			y++;
		break ;
		case 'a':
			x-=2;
		break ;
		case 'd':
			x+=2;
		break ;
	}
	if (coordOnTheBorder(map, x, y) || coordTheSame(x, y))
		return ;
	mvwprintw(wMap, _y, _x, "%C", map[_y][_x].first);
	_x = x;
	_y = y;
	specialMoving(map);
	showObj(wMap, wScore);

}

bool	AGameObj::coordOnTheBorder(vector <vPair> & map, size_t x, size_t y) const{
	if (map[y][x].second == COLOR_BORDER || map[y][x + 1].second == COLOR_BORDER)
		return true;
	return false;
}
bool	AGameObj::coordTheSame(size_t x, size_t y) const{
	return (x == _x && y == _y);
}
size_t &AGameObj::getX(){
	return _x;
}
size_t &AGameObj::getY(){
	return _y;
}
int	&AGameObj::getDirection(){
	return _direction;
}
void	AGameObj::setX(size_t const & x){
	_x = x;
}
void	AGameObj::setY(size_t const & y){
	_y = y;
}
void	AGameObj::setDirection(int const & direction){
	_direction = direction;
}
void	AGameObj::showShape(WINDOW *wMap) const{
	mvwprintw(wMap, _y, _x, "%C", _shape);
}
