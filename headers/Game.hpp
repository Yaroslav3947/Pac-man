#ifndef GAME_HPP
#define GAME_HPP

#include "General.hpp"
#include "Pacman.hpp"

class Game{
	public:
		Game();
		Game(Game const & other);
		Game &	operator = (Game const & other);
		~Game();
		void	initView();
		void	initMap();
		void	initObjPool();
		void	gameCycle();
		bool	userController();
		void	showTheGame();
	protected:
		WINDOW	*wMap;
		WINDOW	*wScore;
		vector<AGameObj *> objPool;
		vector<vPair> map;
};

#endif