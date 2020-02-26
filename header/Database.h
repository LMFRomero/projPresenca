#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <queue>
using namespace std;

class Bixo;

class DataBase{
	public:
		DataBase();

		void setPath (string);
		void resetPath (void);
		string getPath (void);
		bool searchBixo (int);
		bool searchClass (int);
		bool addBixo (Bixo*);
		void setFrequency (int, int);
		void addAula (int);
		vector <Bixo> getBixos (int);
		vector <Bixo> getAllBixos (void);

	private:
		string path;
};

#endif
