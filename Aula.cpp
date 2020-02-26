#include <bits/stdc++.h>
#include "Keyboard.h"
#include "Screen.h"
#include "Database.h"
#include "Aula.h"
#include "Bixo.h"

using namespace std;

Aula::Aula(Keyboard keyboard1, Screen screen1, DataBase database1) : keyboard (keyboard1), screen(screen1), database(database1) {}

void Aula::criarNova (void) {
	int data;
	int userHasExited = false;
	Bixo *bixo;

	screen.displayMessage("Qual a data da nova aula? [DDMM] ");
	data = keyboard.getNumber();

	if (database.searchClass(data) == false) database.addAula(data);
	
	while (userHasExited == false) {
		screen.displayLineMessage("Entre -1 para parar.");
		bixo = new Bixo(keyboard, screen, database);
		userHasExited = !(bixo->adicionarPresenca(data));
		delete bixo;
	}
}

void Aula::gerarRelatorio (void) {
	int data;
	Bixo bixoTmp(keyboard, screen, database);
	vector <Bixo> bixoVector;
	FILE *relatFile;
	string relatName;

	string tmpName;
	int tmpNUSP;

	screen.displayMessage("Qual a data da aula? [DDMM] ");
	data = keyboard.getNumber();

	if (database.searchClass(data) == false) {
		screen.displayLineMessage("Aula nao encontrada.");
		return;
	}
	
	relatName.append("relat").append(to_string(data)).append(".csv");

	relatFile = fopen (relatName.c_str(), "w");

	bixoVector = database.getBixos(data);

	while (bixoVector.empty() == false) {
		bixoTmp = bixoVector.back();
		bixoVector.pop_back();

		tmpName = bixoTmp.getName();
		tmpNUSP = bixoTmp.getNUSP();

		fprintf(relatFile, "%s,%d\n", tmpName.c_str(), tmpNUSP);
	}

	fclose(relatFile);
}

void sortFile(void) {
	Keyboard keyboard; DataBase database; Screen screen;
	FILE *csv = fopen("finalResult.csv", "r");

	vector <Bixo> bixoVector;
	Bixo tmpBixo(keyboard, screen, database);
	char *tmpNome, *tmpEmail;
	int tmpNUSP;

	while (fscanf(csv, " %m[^,],%d,%ms", &tmpNome, &tmpNUSP, &tmpEmail) != EOF) {
		tmpBixo.setName(string(tmpNome));
		tmpBixo.setNUSP(tmpNUSP);
		tmpBixo.setEmail(string(tmpEmail));
		bixoVector.push_back(tmpBixo);

		free(tmpNome);
		free(tmpEmail);
	}

	sort(bixoVector.begin(), bixoVector.end());

	fclose(csv);
	csv = fopen("finalResult.csv", "w");

	while (bixoVector.empty() == false) {
		tmpBixo = bixoVector.back();
		bixoVector.pop_back();
		fprintf(csv, "%s %d %s\n", (tmpBixo.getName()).c_str(), tmpBixo.getNUSP(), (tmpBixo.getEmail()).c_str());
	}
	
	fclose(csv);
}

void Aula::resultadoFinal (void) {
	string aulasPath = database.getPath().append("aulas/aulas");
	string bixosDir = database.getPath().append("bixos/");
	string bixosFilePath, tmpBixoFilePath;

	char *tmpNome, *tmpEmail;

	int counterAulas = 0, counterPresencaBixo = 0;
	int tmpNUSP;
	float frequency;

	bixosFilePath = tmpBixoFilePath = bixosDir;
	bixosFilePath.append("bixos");

	FILE *aulasFile = fopen(aulasPath.c_str(), "r");
	FILE *bixosFile = fopen(bixosFilePath.c_str(), "r");
	FILE *bixoFile;
	FILE *finalResult = fopen("finalResult.csv", "w+");

	while (fscanf(aulasFile, "%*d") != EOF) {
		counterAulas++;
	}

	counterAulas /= 2;

	fclose(aulasFile);

	while (fscanf(bixosFile, "%d", &tmpNUSP) != EOF) {
		tmpBixoFilePath.append(to_string(tmpNUSP));
		bixoFile = fopen (tmpBixoFilePath.c_str(), "r");

		fscanf(bixoFile, "%*d %m[^\n\r] %ms", &tmpNome, &tmpEmail);

		while (fscanf(bixoFile, "%*d") != EOF) {
			counterPresencaBixo++;
		}

		frequency = counterPresencaBixo/static_cast<float> (counterAulas);

		if (frequency > 0.5) {
			fprintf(finalResult, "%s,%d,%s\n", tmpNome, tmpNUSP, tmpEmail);
		}

		counterPresencaBixo = 0;
		free(tmpNome);
		free(tmpEmail);
		fclose(bixoFile);
		tmpBixoFilePath = bixosDir;
	}


	fclose(bixosFile);
	fclose(finalResult);
	sortFile();
}

void Aula::gerarRelatorioxAula (void) {
	string path = database.getPath();
	string bixoFilePath, aulasFilePath;
	FILE *bixoFile, *aulasFile, *report;

	vector <int> aulasVector;
	vector <Bixo> bixosVector;

	int tmpAula, tmpNUSP;
	string tmpName;
	int fscanfResult;
	int aulasSize;

	Bixo tmpBixo(keyboard, screen, database);

	aulasFilePath = path;
	aulasFilePath.append("aulas/aulas");
	aulasFile = fopen (aulasFilePath.c_str(), "r");

	while (fscanf(aulasFile, "%d", &tmpAula) != EOF) {
		aulasVector.push_back(tmpAula);
	}

	fclose(aulasFile);
	
	report = fopen ("relatBixosVSAulas.csv", "w");

	for (int i = 0; i < aulasVector.size(); i += 2) {
		fprintf(report, ",%d Week", (i/2)+1);
	}
	fprintf(report, "\n");

	bixosVector = database.getAllBixos();

	aulasSize = aulasVector.size();

	while (bixosVector.empty() == false) {
		//pega um bixor, remove ele do vector, e printa o nome no .csv
		tmpBixo = bixosVector.back();
		bixosVector.pop_back();
		tmpName = tmpBixo.getName();
		fprintf(report, "%s,", tmpName.c_str());

		//abre o arquivo do bixo e pega as aulas que o bixo participou
		bixoFilePath = path;
		tmpNUSP = tmpBixo.getNUSP();
		bixoFilePath.append("bixos/").append(to_string(tmpNUSP));
		bixoFile = fopen(bixoFilePath.c_str(), "r");
		fscanf(bixoFile, "%*d %*[^\r\n] %*s");

		fscanfResult = fscanf(bixoFile, "%d", &tmpNUSP);

		for (int i = 0; i < aulasSize; i += 2) {
			if (fscanfResult != EOF) {
				if(aulasVector[i] == tmpNUSP) {
					fscanfResult = fscanf(bixoFile, "%d", &tmpNUSP);
					fprintf(report, "x");
				}

				else if (i+1 != aulasSize and aulasVector[i+1] == tmpNUSP) {
					fscanfResult = fscanf(bixoFile, "%d", &tmpNUSP);
					fprintf(report, "x");
					
				}
			}

			if (i == aulasSize-1 or i == aulasSize-2) {
				fprintf(report, "\n");
			}
			else {
				fprintf(report, ",");
			}
		}

		fclose(bixoFile);
	}

	fclose(report);
}
