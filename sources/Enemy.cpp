#include "Enemy.hpp"
Enemy::Enemy(): AGameObj(25, 5, 'X'){

}
Enemy::Enemy(Enemy const & other) : AGameObj(other){
	*this = other;
}
Enemy & Enemy::operator = (Enemy const & other) {
	if (this != &other){
		_x = other._x;
		_y = other._y;
		_shape = other._shape;
		_direction = other._direction;
	}
	return *this;
}
Enemy::~Enemy(){}
void	Enemy::showObj(WINDOW *wMap, WINDOW *wScore) const{
	showShape(wMap);
	mvwprintw(wScore, 2, 27, "Enemy x = %d, y = %d direct = %c", _x, _y, _direction);
}
void	Enemy::specialMoving(vector<vPair> &map, vector<AGameObj *> objPool){

	chooseDirection(map, objPool);
	(void)map;
	(void)objPool;
}
void	Enemy::chooseDirection(vector<vPair> &map, vector<AGameObj *> objPool){
	int directions[4][3] = {{'s', 1, 0}, {'d', 0, 2}, {'w', -1, 0}, {'a', 0, -2}};
	int powDistance = 0;
	int minPowDistance = pow(MAP_HEIGHT, 2) + pow(MAP_WIDTH, 2);
	int savedXY[2] = {_y, _x};
	int xPowDist = 0;
	int yPowDist = 0;
	for (size_t i = 0; i < 4; i++){
		_y = savedXY[0] + directions[i][1];
		_x = savedXY[1] + directions[i][2];
		modifyCoord();
		if (coordOnTheBorder(map, _x, _y) == true)
			continue ;
		yPowDist = pow(objPool[0]->getY() - abs(_y), 2);
		xPowDist = pow(objPool[0]->getX() - abs(_x), 2);
		powDistance = abs(yPowDist + xPowDist);
		if (powDistance < minPowDistance){
			minPowDistance = powDistance;
			_direction = directions[i][0];
		}
	}
	_x = savedXY[1];
	_y = savedXY[0];
}
