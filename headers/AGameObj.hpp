#ifndef AGAMEOBJ_HPP
#define AGAMEOBJ_HPP

#include "General.hpp"
class AGameObj {

	public:
		AGameObj();
		AGameObj(size_t const & x, size_t const & y, wchar_t const & shape);
		AGameObj(AGameObj const & other);
		AGameObj & operator = (AGameObj const & other);
		virtual ~AGameObj() = 0;
		virtual void	showObj(WINDOW *wMap, WINDOW *wScore) const = 0;
		void			showShape(WINDOW *wMap) const;
		void			move(vector<vPair> & map, WINDOW *wMap, WINDOW *wScore, vector<AGameObj *> objPool);
		virtual void	specialMoving(vector<vPair> &map, vector<AGameObj *> objPool) = 0;
		bool			coordOnTheBorder(vector <vPair> &map, size_t x, size_t y) const;
		bool			coordTheSame(size_t x, size_t y) const;
		size_t	&getX();
		size_t	&getY();
		int		&getDirection();
		void	setX(size_t const & x);
		void	setY(size_t const & y);
		void	setDirection(int const & direction);
	protected: // private
		size_t	_x;
		size_t	_y;
		wchar_t	_shape;
		int		_direction;
	
};
#endif