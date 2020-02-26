#ifndef AULA_H
#define AULA_H

#include "Keyboard.h"
#include "Screen.h"
#include "Database.h"

using namespace std;

class Aula {
	public:
		Aula (Keyboard, Screen, DataBase);

		~Aula () {}

		void criarNova(void);
		void gerarRelatorio(void);
		void resultadoFinal(void);
		void gerarRelatorioxAula(void);

	private:
		Keyboard keyboard;
		Screen screen;
		DataBase database;
};

#endif
