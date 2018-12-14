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
	mvwprintw(wScore, 2, 15, "Enemy x = %d, y = %d", _x, _y);
}
void	Enemy::specialMoving(vector<vPair> &map, vector<AGameObj *> objPool){

	chooseDirection(map, objPool);
	(void)map;
	(void)objPool;
}

void	Enemy::chooseDirection(vector<vPair> &map, vector<AGameObj *> objPool){
	int directions[4][3] = {{'w', -1, 0}, {'s', 1, 0}, {'a', 0, -1}, {'d', 0, 1}};
	int powDistance = 0;
	int minPowDistance = pow(MAP_HEIGHT, 2) + pow(MAP_WIDTH, 2);
	for (size_t i = 0; i < 4; i++){
		powDistance = pow(objPool[0]->getY() - (_y + directions[i][1]), 2) + pow(objPool[0]->getX() - (_x + directions[i][2]), 2);
		if (labs(powDistance) < labs (minPowDistance) && coordOnTheBorder(map, _x + directions[i][2], _y + directions[i][1]) == false){
			minPowDistance = labs (powDistance);
			_direction = directions[i][0];
		}
	}
}
