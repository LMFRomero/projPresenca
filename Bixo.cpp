#include "Bixo.h"
#include "Keyboard.h"
#include "Screen.h"
#include "Database.h"
#include <iostream>

using namespace std;

Bixo::Bixo (Keyboard keyboard1, Screen screen1, DataBase database1) : keyboard (keyboard1), screen (screen1), database (database1), nUSP(0) {}

bool Bixo::adicionarPresenca (int data) {
	char resp;
	bool bixoOK;
	int dataOK;

	dataOK = verificaData(data);

	if (dataOK == 0) {
		return false;
	}

	data = dataOK;

	screen.displayMessage("Numero USP do bixo: ");
	nUSP = keyboard.getNumber();
	
	if (nUSP < 0) return false;

	bixoOK = verificaBixo();

	if (bixoOK == false) {
		return false;
	}
	
	database.setFrequency(nUSP, data);	

	return true;
}

int Bixo::verificaData(int data) {
	if (data == 0) {
		screen.displayMessage("Qual a data da aula para adicionar presenca? ");
		data = keyboard.getNumber();

		if (database.searchClass(data) == false) {
			screen.displayLineMessage("Aula nao encontrada.");
			return 0;
		}
	}

	return data;
}

bool Bixo::verificaBixo() {
	bool allGood;
	bool bixoFound;

	bixoFound = database.searchBixo(nUSP);

	if (bixoFound == false) {
		if (userWants() == true) {
			allGood = criarBixo();
			return allGood;
		}
		else {
			return false;
		}
	}

	return true;
}

bool Bixo::userWants (void) {
	screen.displayMessage("Bixo nao encontrado. Deseja adicionar um novo? [y/n] ");
	char resp = keyboard.getCharAnswer();

	if (resp == 'n' or resp == 'N') {
		return false;
	}

	else if (resp == 'y' or resp == 'Y') {
		return true;
	}
		
	else {
		screen.displayLineMessage("Opcao Invalida.");
		return false;
	}
}

bool Bixo::criarBixo () {
	screen.displayMessage("Qual o nome do bixo? ");
	nome = keyboard.getLine();
	
	if (nUSP == 0) {
		screen.displayMessage("Qual o nUSP do bixo? ");
		nUSP = keyboard.getNumber();
	}

	if (nome.empty() == true) {
		return false;
	}

	screen.displayMessage("Qual o email do bixo? ");
	email = keyboard.getLine();

	if (email.empty() == true) {
		return false;
	}

	bool a = database.addBixo(this);
	return a;
}

int Bixo::getNUSP (void) {
	return this->nUSP;
}

string Bixo::getName (void) {
	return this->nome;
}

string Bixo::getEmail (void) {
	return this->email;
}

void Bixo::setName (string name1) {
	nome = name1;
}

void Bixo::setNUSP (int nusp) {
	nUSP = nusp;
}

void Bixo::setEmail (string email1) {
	email = email1;
}

bool Bixo::operator < (Bixo bixo1) {
	return !(this->nome.compare(bixo1.getName()) < 0);
}
