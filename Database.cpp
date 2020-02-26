#include <bits/stdc++.h>
#include <stdlib.h>
#include "Database.h"
#include "Bixo.h"

using namespace std;

DataBase::DataBase() {
	path = "./database/";
}

void DataBase::setPath (string addPath) {
	path.append(addPath);
}

void DataBase::resetPath (void) {
	path = "./database/";
}

string DataBase::getPath (void) {
	return path;
}

bool DataBase::searchBixo (int NUSP) {
	int tmpNUSP;
	string tmpPath = getPath();
	string bixosFilePath = tmpPath.append("bixos/bixos");
	FILE *bixosFile = fopen(bixosFilePath.c_str(), "r+");
	resetPath();
	
	if (bixosFile == NULL) return false;

	while (fscanf(bixosFile, "%d", &tmpNUSP) != EOF) {
		if (tmpNUSP == NUSP) {
			fclose (bixosFile);
			return true;
		}
	}

	fclose(bixosFile);

	return false;
}

bool DataBase::searchClass (int data) {
	int tmpAula;
	string tmpPath = getPath();
	string aulasFilePath = tmpPath.append("aulas/aulas");
	FILE *aulasFile = fopen(aulasFilePath.c_str(), "r+");
	resetPath();

	if (aulasFile == NULL) return false;

	while (fscanf(aulasFile, "%d", &tmpAula) != EOF) {
		if (tmpAula == data) {
			fclose (aulasFile);
			return true;
		}
	}

	fclose(aulasFile);

	return false;
}

bool DataBase::addBixo(Bixo *bixo) {
	int nusp = bixo->getNUSP();
	string name = bixo->getName();
	string email = bixo->getEmail();

	string bixosPath = getPath().append("bixos/");
	string bixosFilePath = bixosPath;
	string newBixoFilePath = bixosPath;
	
	bixosFilePath.append("bixos");
	newBixoFilePath.append(to_string(nusp));

	FILE *bixosFile = fopen (bixosFilePath.c_str(), "a+");
	FILE *newBixoFile = fopen (newBixoFilePath.c_str(), "w+");

	fprintf(bixosFile, "%d\n", nusp);

	fprintf(newBixoFile, "%d\n", nusp);
	fprintf(newBixoFile, "%s\n", name.c_str());
	fprintf(newBixoFile, "%s\n", email.c_str());
	
	fclose(bixosFile);
	fclose(newBixoFile);

	return true;
}

void DataBase::setFrequency (int NUSP, int data) {
	string path = getPath();
	string aulasPath = path;
	string bixoPath = path;

	bixoPath.append("bixos/").append(to_string(NUSP));
	aulasPath.append("aulas/").append(to_string(data));

	FILE *aulaFile = fopen(aulasPath.c_str(), "a+");
	FILE *bixoFile = fopen(bixoPath.c_str(), "a+");

	fprintf(aulaFile, "%d\n", NUSP);
	fprintf(bixoFile, "%d\n", data);

	fclose(aulaFile);
	fclose(bixoFile);

	return;
}

void DataBase::addAula (int data) {
	string path = getPath();
	string aulasDir = path.append("aulas/");
	string aulasPathFile, newAulaPathFile;

	aulasPathFile = newAulaPathFile = aulasDir;
	aulasPathFile.append("aulas");
	newAulaPathFile.append(to_string(data));

	FILE *aulasFile = fopen(aulasPathFile.c_str(), "a+");
	FILE *newAulaFile = fopen(newAulaPathFile.c_str(), "w+");

	fprintf(aulasFile, "%d\n", data);

	fclose(aulasFile);
	fclose(newAulaFile);
}

vector <Bixo> DataBase::getBixos(int data) {
	string pathFile = getPath();
	string pathBixos = getPath().append("bixos/");
	string tmpPathBixo;

	Keyboard keyboard; Screen screen; DataBase database;

	FILE *aulaFile;
	FILE *bixoFile;

	char *tmpName;
	int tmpNUSP;

	vector <Bixo> myVector;
	Bixo tmpBixo(keyboard, screen, database);

	pathFile.append("aulas/").append(to_string(data));
	aulaFile = fopen (pathFile.c_str(), "r");
	
	while (fscanf(aulaFile, "%d", &tmpNUSP) != EOF) {
		tmpPathBixo = pathBixos;
		tmpPathBixo.append(to_string(tmpNUSP));
		bixoFile = fopen(tmpPathBixo.c_str(), "r");

		fscanf(bixoFile, "%*d %m[^\r\n]", &tmpName);

		tmpBixo.setName(string(tmpName));
		tmpBixo.setNUSP(tmpNUSP);

		myVector.push_back(tmpBixo);

		free(tmpName);
		fclose(bixoFile);
	}

	sort(myVector.begin(), myVector.end());
	
	return myVector;
}

vector <Bixo> DataBase::getAllBixos(void) {
	string pathFile = getPath();
	string pathBixos = getPath().append("bixos/");
	string tmpPathBixo;

	Keyboard keyboard; Screen screen; DataBase database;

	FILE *aulaFile;
	FILE *bixoFile;

	char *tmpName;
	int tmpNUSP;

	vector <Bixo> myVector;
	Bixo tmpBixo(keyboard, screen, database);

	pathFile.append("bixos/bixos");
	aulaFile = fopen (pathFile.c_str(), "r");
	
	while (fscanf(aulaFile, "%d", &tmpNUSP) != EOF) {
		tmpPathBixo = pathBixos;
		tmpPathBixo.append(to_string(tmpNUSP));
		bixoFile = fopen(tmpPathBixo.c_str(), "r");

		fscanf(bixoFile, "%*d %m[^\r\n]", &tmpName);

		tmpBixo.setName(string(tmpName));
		tmpBixo.setNUSP(tmpNUSP);

		myVector.push_back(tmpBixo);

		free(tmpName);
		fclose(bixoFile);
	}

	sort(myVector.begin(), myVector.end());
	
	return myVector;
}
