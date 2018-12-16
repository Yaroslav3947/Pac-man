#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "AGameObj.hpp"
#include <cmath>
class Enemy : public AGameObj{
	public:
		Enemy();
		Enemy(Enemy const & other);
		Enemy & operator = (Enemy const & other);
		~Enemy();
	private:
		void	showObj(WINDOW *wMap, WINDOW *wScore) const;
		void	specialMoving(vector<vPair> &map, vector<AGameObj *> & objPool);
		void	chooseDirection(vector<vPair> &map, vector<AGameObj *> objPool);

};

#endif