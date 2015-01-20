/*
	NOM : MUKEYA KASSINDYE
	NI : A00158681
			FICHIER SOURCE : dans ce fichier on d�fini les prototypes de toutes les m�thodes relatives aux oridanteurs
*/

#ifndef ORDINATEUR_H
#define ORDINATEUR_H

#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>

//MIN et MAX nous servirons de g�n�rer des num�ros de port pour les ordinateurs priv�s ou en local
#define MIN 49153
#define MAX 65535

using namespace std;

class Ordinateur
{
public:
	Ordinateur(void);
	~Ordinateur(void);
	void setNombreOrdisPr(int);
	void setNombreOrdisPub(int);
	void setPort(string);
	void setIpOrdi(string);
	void setAdressePr(string);
	void setAdressePub(string);
	void setAuth(bool);
	bool getAuth();	//nous montrera si le pc � le droit de communiquer avec l'autre
	int getPort();
	string getAdressePr();
	string getAdressePub();
	string getNomOrdi();
	string getIpOrdi();
	vector<string> genererAdrPrive();//m�thode pour g�n�rer les adresses priv�es des ordinateur
	vector<string> genererAdrPublique();//m�thode pour g�n�rer les adresses priv�es des ordinateur
	vector<Ordinateur> getDetailsOrdisPrives();	//renvoi toutes les informations concernant un ordinateur(dns, ip, port)
	vector<Ordinateur> getDetailsOrdisPubliques();
	void afficher();//affiche les d�tails d'un ordinateur

private:
	int m_port;
	int m_nbreAdrPr;
	int m_nbreAdrPub;
	int intervalle;
	string m_plageAdresses;
	string m_nomOrdi;
	string m_ip;
	bool m_auth;//cette variable nous permettra de donner le droit � l'ordinateur publique de communiquer avec un ordinateur priv�
	vector<string> m_adressesPrivees;//pour les ordinateurs qui sont sur le r�seau priv�
	vector<string> m_adressesPubliques;//pour les ordinateurs qui sont sur le r�seau publique
	vector<Ordinateur> tempPr;
	vector<Ordinateur> tempPub;
};

#endif
