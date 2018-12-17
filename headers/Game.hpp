#ifndef GAME_HPP
#define GAME_HPP

#include "Pacman.hpp"
#include "Enemy.hpp"
class Game{
	public:
		Game();
		Game(char userMap[MAP_HEIGHT][MAP_WIDTH]);
		~Game();
		void	gameCycle();
		WINDOW	*wMap;
		WINDOW	*wScore;
	private:
		void	initMap(char c, size_t i, size_t j);
		void	initObjPool(char c, size_t i, size_t j);
		void	initView();
		bool	userController();
		void	moveObjects();
		void	showTheGame();
		void	showMap() const;
		void	gameIsOver();
		void	victory();

	protected:
		deque<AGameObj *> objPool;
		vector<vPair> map;
};

#endif