#ifndef COMPUTER_H
#define COMPUTER_H
#include "Screen.h"
#include "Keyboard.h"
#include "Database.h"

enum mainMenuOption {EXIT = 0, NOVA_AULA, NOVO_BIXO, ADC_BIXO, RELATORIO, RELATORIO_AULA, RESULTADO};

class Computer {
	public:
		void run(void);

	private:
		Keyboard keyboard;
		Screen screen;
		DataBase database;
		mainMenuOption displayMainMenu(void);
};


#endif
