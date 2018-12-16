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
		void	gameCycle();
		WINDOW	*wMap;
		WINDOW	*wScore;
	private:
		void	initView();
		void	initMap();
		bool	userController();
		void	initObjPool();
		void	moveObjects();
		void	showTheGame();
		void	showMap() const;
		void	gameIsOver();

	protected:
		vector<AGameObj *> objPool;
		vector<vPair> map;
};

#endif