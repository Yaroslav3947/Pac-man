#ifndef PACMAN_HPP
#define PACMAN_HPP

#include "AGameObj.hpp"

class Pacman : public AGameObj{

	public:
		Pacman();
		Pacman(int const x, int const y);
		Pacman(Pacman const & other);
		Pacman & operator = (Pacman const & other);
		~Pacman();
		size_t	&getScore();
		void	setScore(size_t const & score);
		void	livesReduction();

	private:
		void	scoreImproving(wchar_t & food);
		void	showObj(WINDOW *wMap, WINDOW *wScore) const;
		void	specialMoving(vector<vPair> &map, vector<AGameObj *> & objPool);
		size_t _score;
	
};
#endif