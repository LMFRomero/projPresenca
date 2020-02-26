#include "Computer.h"
#include "Keyboard.h"
#include "Screen.h"
#include "Aula.h"
#include "Bixo.h"
using namespace std;

void Computer::run (void) {
	bool userHasExited = false;
	mainMenuOption mainMenuChoice;
	int nusp;

	Aula *aula;
	Bixo *bixo;

	while (userHasExited == false) {
		mainMenuChoice = displayMainMenu();

		switch (mainMenuChoice) {
			case (NOVA_AULA):
				aula = new Aula(keyboard, screen, database);
				aula->criarNova();
				delete aula;
				break;

			case (NOVO_BIXO):
				bixo = new Bixo(keyboard, screen, database);
				bixo->criarBixo();
				delete bixo;
				break;

			case (ADC_BIXO):
				bixo = new Bixo(keyboard, screen, database);
				bixo->adicionarPresenca(0);
				delete bixo;
				break;

			case (RELATORIO):
				aula = new Aula(keyboard, screen, database);
				aula->gerarRelatorio();
				delete aula;
				break;

			case (RELATORIO_AULA):
				aula = new Aula (keyboard, screen, database);
				aula->gerarRelatorioxAula();
				delete aula;
				break;

			case (RESULTADO):
				aula = new Aula(keyboard, screen, database);
				aula->resultadoFinal();
				delete aula;
				break;
				
			case (EXIT):
				userHasExited = true;
				break;

			default:
				screen.displayLineMessage("Opcao Invalida. Tente novamnte");
				break;
		}
	}
}

mainMenuOption Computer::displayMainMenu (void) {
	screen.jumpLine();
	screen.displayLineMessage("MAIN MENU:");
	screen.displayLineMessage("1 - ADICIONAR NOVA AULA");
	screen.displayLineMessage("2 - ADICIONAR NOVO BIXO");
	screen.displayLineMessage("3 - ADICIONAR PRESENCA MANUALMENTE");
	screen.displayLineMessage("4 - GERAR RELATORIO DE PRESENCA DE UMA AULA");
	screen.displayLineMessage("5 - GERAR RELATORIOS X AULA");
	screen.displayLineMessage("6 - RESULTADO DO PING");
	screen.displayLineMessage("0 - SAIR");
	screen.displayMessage("Opcao: ");
	return static_cast <mainMenuOption> (keyboard.getMenuOption());
}
