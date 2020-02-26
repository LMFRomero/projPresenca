#ifndef BIXO_H
#define BIXO_H

#include <string>
#include "Screen.h"
#include "Keyboard.h"
#include "Database.h"

using namespace std;

class Bixo {
	public:
		Bixo (Keyboard, Screen, DataBase);

		~Bixo () {}

		bool adicionarPresenca (int);
		int getNUSP (void);
		string getName (void);
		string getEmail (void);
		bool criarBixo (void);
		void setName (string);
		void setNUSP (int);
		void setEmail (string);
		bool operator < (Bixo);

	private:
		Keyboard keyboard;
		Screen screen;
		DataBase database;
		string nome;
		int nUSP;
		string email;

		int verificaData (int);
		bool verificaBixo (void);
		bool userWants (void);
};

void sortFile(void);

#endif
