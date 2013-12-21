#ifndef _Log
#define _Log

#include <fstream>

using namespace std;

class Log
{
private:
	static Log* _self;
	Log(); //constructeur vide
	~Log();
public:
	static Log& Get_instance();
	static void Kill();
	void ecrire_construction(string);
	void ecrire_destruction(string);
};

#endif _Log