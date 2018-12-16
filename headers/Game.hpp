#ifndef GAME_HPP
#define GAME_HPP

#include "Pacman.hpp"
#include "Enemy.hpp"
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
		void	showMap() const;
		void	gameIsOver();
		WINDOW	*wMap;
		WINDOW	*wScore;

	protected:
		vector<AGameObj *> objPool;
		vector<vPair> map;
};

#endif