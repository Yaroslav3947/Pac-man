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
		virtual void	specialMoving(vector<vPair> &map, deque<AGameObj *> & objPool) = 0;
		void			move(vector<vPair> & map, WINDOW *wMap, WINDOW *wScore, deque<AGameObj *> & objPool);
		int				&getX();
		int				&getY();
		int				&getDirection();
		void			setX(int const & x);
		void			setY(int const & y);
		void			setDirection(int const & direction);
		bool			isAlive();
		void			isKilled();
	protected:
		void			showShape(WINDOW *wMap) const;
		void			modifyCoord();
		void			moveCoord(int & x, int & y);
		bool			coordOnTheBorder(vector <vPair> &map, int x, int y) const;
		bool			coordTheSame(int x, int y) const;//no
	private:
		void			moveHorizontally(int & x);
		void			moveVertically(int & y);
		void			modifyHorizontally();
		void			modifyVertically();
		void			cleanPosition(WINDOW *wMap, vector<vPair> & map);
	protected:
		int		_x;
		int		_y;
		char	_shape;
		int		_direction;
		bool	_isAlive;
	
};
#endif