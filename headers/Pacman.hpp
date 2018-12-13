#ifndef PACMAN_HPP
#define PACMAN_HPP

#include "AGameObj.hpp"

class Pacman : public AGameObj{

	public:
		Pacman();
		Pacman(Pacman const & other);
		Pacman & operator = (Pacman const & other);
		~Pacman();
		void	scoreImproving();
		size_t	&getLives();
		size_t	&getScore();
		void	setLives(size_t const & lives);	
		void	setScore(size_t const & score);	
		void	showObj(WINDOW *wMap, WINDOW *wScore) const;
		void	specialMoving(vector<vPair> &map);

	private:
		size_t _lives;
		size_t _score;
	
};
#endif