#ifndef _ID_GENERATOR_H_
#define _ID_GENERATOR_H_

class IDGenerator
{
public:
	static int generateID()
	{
		static int id = 0;

		return id++;
	}
};

#endif //_ID_GENERATOR_H_
