#include "Enemy.hpp"
Enemy::Enemy(): AGameObj(17, 5, 'X'){

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
	int directions[4][3] = {{'s', 1, 0}, {'d', 0, 2}, {'w', -1, 0}, {'a', 0, -2}, };
	int powDistance = 0;
	int minPowDistance = pow(MAP_HEIGHT, 2) + pow(MAP_WIDTH, 2);
	int x = 0;
	int y = 0;
	for (size_t i = 0; i < 4; i++){
		y = pow((directions[i][1] + _y) - objPool[0]->getY(), 2);
		x = pow((directions[i][2] + _x) - objPool[0]->getX(), 2);
		powDistance = abs(y + x);
		if (powDistance < minPowDistance && coordOnTheBorder(map, _x + directions[i][2], _y + directions[i][1]) == false){
			minPowDistance = powDistance;
			_direction = directions[i][0];
		}
	}
}
