#ifndef AGAMEOBJ_HPP
#define AGAMEOBJ_HPP

#include "General.hpp"
class AGameObj {

	public:
		AGameObj();
		AGameObj(size_t const & x, size_t const & y, char const & shape);
		AGameObj(AGameObj const & other);
		AGameObj & operator = (AGameObj const & other);
		virtual ~AGameObj() = 0;
		virtual void	showObj(WINDOW *wMap, WINDOW *wScore) const = 0;
		virtual void	specialMoving(vector<vPair> &map, deque<AGameObj *> & objPool) = 0;
		void			move(vector<vPair> & map, WINDOW *wMap, deque<AGameObj *> & objPool);
		int				&getX();
		int				&getY();
		int				&getDirection();
		short			&getStatus();
		void			setX(int const & x);
		void			setY(int const & y);
		void			setDirection(int const & direction);
		void			setStatus(short const & status);
	protected:
		void			showShape(WINDOW *wMap) const;
		void			moveCoord(int & x, int & y);
		bool			coordOnTheBorder(vector <vPair> &map, int x, int y) const;
		void			modifyCoord();
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
		short	_status;
	
};
#endif