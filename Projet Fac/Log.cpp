#include "Log.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

//initalisation du pointeur
Log* Log::_self = NULL;

Log::Log() //constructeur vide
{
 	ofstream _file;
	_file.open("rtype.log", ios::out|ios::trunc);
	_file<<"Debut du log :"<<endl;
	_file.close();
}

Log::~Log()
{
}

Log& Log::Get_instance()
{
	if( _self == NULL)
	{
		_self = new Log();
	}
	return *_self;
}

void Log::Kill()
{
	if( _self != NULL)
	{
		delete _self;
		_self = NULL;
	}
	
}

void Log::ecrire_construction(string chaine)
{
	ofstream _file;
	_file.open("rtype.log", ios::out|ios::app);

	if(_file)
	{
		_file<<"Construction "<<chaine<<endl;
	}
	_file.close();
}

void Log::ecrire_destruction(string chaine)
{
	ofstream _file;
		_file.open("rtype.log", ios::out|ios::app);
	if(_file)
	{
		_file<<"Destruction "<<chaine<<endl;
	}
	_file.close();
}