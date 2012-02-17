#ifndef UNCOPYABLE_H__
#define UNCOPYABLE_H__

class Uncopyable
{
protected:
	Uncopyable(){}
	~Uncopyable(){}

private:
	Uncopyable( const Uncopyable& );
	Uncopyable& operator=( const Uncopyable& );
};

#endif