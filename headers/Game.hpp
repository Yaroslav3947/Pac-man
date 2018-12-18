#ifndef GAME_HPP
#define GAME_HPP

#include "Pacman.hpp"
#include "Enemy.hpp"
class Game{
	public:
		Game(string userMap[MAP_HEIGHT]);
		~Game();
		void	gameCycle();
		WINDOW	*wMap;
		WINDOW	*wScore;
	private:
		bool	mapIsValid(string userMap[MAP_HEIGHT]);
		void	initMap(char c, size_t i, size_t j);
		void	initObjPool(char c, size_t i, size_t j);
		void	initView();
		bool	userController();
		void	moveObjects();
		void	showTheGame();
		void	showMap() const;
		void	gameIsOver() const;
		void	victory() const;

	protected:
		deque<AGameObj *> objPool;
		vector<vPair> map;
};

#endif