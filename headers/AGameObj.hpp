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
		//need?virtual bool	isAlive() = 0;
		virtual void	showObj(WINDOW *wMap, WINDOW *wScore) const = 0;
		void			showShape(WINDOW *wMap) const;
		void			move(vector<vPair> & map, WINDOW *wMap, WINDOW *wScore, vector<AGameObj *> objPool);
		void			moveCoord(int & x, int & y);
		void			moveHorizontally(int & x);
		void			moveVertically(int & y);
		void			modifyCoord();
		void			modifyHorizontally();
		void			modifyVertically();
		virtual void	specialMoving(vector<vPair> &map, vector<AGameObj *> objPool) = 0;
		bool			coordOnTheBorder(vector <vPair> &map, int x, int y) const;
		bool			coordTheSame(int x, int y) const;//no
		void			cleanPosition(WINDOW *wMap, vector<vPair> & map);
		int		&getX();
		int		&getY();
		int		&getDirection();
		void	setX(int const & x);
		void	setY(int const & y);
		void	setDirection(int const & direction);
	protected: // private
		int		_x;
		int		_y;
		char	_shape;
		int		_direction;
	
};
#endif