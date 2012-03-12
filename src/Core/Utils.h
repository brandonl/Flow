#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <vector>
#include <queue>
#include <cassert>
#include <sstream>

#define BLT_TOUCH(x) ((void)(x))
#define bltAssert(A) assert(A)

class Uncopyable
{
	protected:
		Uncopyable() {}
		~Uncopyable() {}

	private:
		Uncopyable(const Uncopyable&);
		const Uncopyable& operator=(const Uncopyable&);
};

template <class Tar, class Src>
Tar lexicalCast( Src arg )
{
	std::stringstream interpreter;
	Tar res;
	if( !(interpreter << arg) || !(interpreter >> res) || !(interpreter >> std::ws).eof() )
		printf( "Throw Bad Cast Exception\n" );
	return res;
}

template<typename T>
void eraseUnordered( std::vector<T>& v, size_t index)
{
    v[index] = std::move( v.back() );
    v.pop_back();
}
//------------------------------------------------------Containter Poppers----------
template <class T>
inline typename T::value_type popFrom( T& container ) 
{
	T::value_type val = container.top();
	container.pop();
	return val;
}

// Queue overload
template <class T>
inline typename std::queue<T>::value_type popFrom( std::queue<T>& container ) 
{
	queue<T>::value_type val = container.front();
	container.pop();
	return val;
}

// Vector overload
template <class T>
inline typename std::vector<T>::value_type popFrom( std::vector<T>& container ) 
{
	queue<T>::value_type val = container.back();
	container.pop_back();
	return val;
}

struct deleteMapFunctor
{
	template<typename A, typename B>
    void operator()( std::pair<A,B> x ) const
    {
        delete x.second;
    }
};

struct deleteFunctor
{
	template <typename T>
	void operator()( const T* ptr ) const
	{
		if( ptr )
			delete ptr;
	}
};

struct printFunctor
{
	template <typename T>
	void operator()( const T* ptr ) const
	{
		std::cout << T << std::endl;
	}
};
#endif
