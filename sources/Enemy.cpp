#include "Enemy.hpp"
Enemy::Enemy(): AGameObj(25, 5, 'X'){

}
Enemy::Enemy(int const x, int const y) : AGameObj(x, y, 'X'){

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
	mvwprintw(wScore, 2, 1, "Enemy x = %d, y = %d direct = %c", _x, _y, _direction);
}
void	Enemy::specialMoving(vector<vPair> &map, vector<AGameObj *> & objPool){
	chooseDirection(map, objPool);
	if (objPool.at(0)->getX() == _x && objPool.at(0)->getY() == _y)
		objPool[0]->isKilled();
	// if (isIntersection(objPool))
	// 	setDirection(0);
	// for (size_t i = 0; i < objPool.size(); i++){
	// 	if (objPool.at(i)->getX() == _x && objPool.at(i)->getY() == _y){
	// 		if (i == 0)
	// 			objPool[i]->isKilled();
	// 		else if (getDirection() == 0)
	// 			objPool[i]->setDirection(0);
	// 	}
	// }
	
}
void	Enemy::chooseDirection(vector<vPair> &map, vector<AGameObj *> & objPool){
	int directions[4][3] = {{'s', 1, 0}, {'d', 0, 1}, {'w', -1, 0}, {'a', 0, -1}};
	int powDistance = 0;
	int minPowDistance = pow(MAP_HEIGHT, 2) + pow(MAP_WIDTH, 2);
	int savedXY[2] = {_y, _x};
	int xPowDist = 0;
	int yPowDist = 0;
	for (size_t i = 0; i < 4; i++){
		_y = savedXY[0] + directions[i][1];
		_x = savedXY[1] + directions[i][2];
		modifyCoord();
		if (coordOnTheBorder(map, _x, _y) || isIntersection(objPool))
			continue ;
		yPowDist = pow(objPool[0]->getY() - abs(_y), 2);
		xPowDist = pow(objPool[0]->getX() - abs(_x), 2);
		powDistance = abs(yPowDist + xPowDist);
		if (powDistance < minPowDistance){
			minPowDistance = powDistance;
			_direction = directions[i][0];
		}
	}
	_y = savedXY[0];
	_x = savedXY[1];
}
bool	Enemy::isIntersection(vector<AGameObj *> & objPool){
	for (size_t i = 1; i < 3; i++){
		if (objPool.at(i)->getX() == _x && objPool.at(i)->getY() == _y && getDirection() && objPool.at(i) != this){
			setDirection(0);
			return true;
		}
	}
	return false;
}