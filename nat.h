/*
	NOM : MUKEYA KASSINDYE
	NI : A00158681
			FICHIER SOURCE : dans ce fichier on défini les prototypes de toutes les méthodes relatives au nat
*/
#ifndef NAT_H
#define NAT_H

#include <cassert>
#include <vector>
#include <list>
#include <string>
#include <ctime>
#include <iostream>

#define MIN 49153
#define MAX 65535

using namespace std;

//on va créer une structure de table de distribution d'adresses ip publique aux ordinateurs privés
typedef struct TableDeDistributionIp TableDeDistributionIp;
struct TableDeDistributionIp
{
	string natIpPub;
	string ordiIpPr;
};

class Nat
{
	public:
		Nat();
		virtual ~Nat();
		void setNbreAdr(int);	//prend en paramètre le nombre d'adresses qui seront générées
		void genererAdrPub();//prend en paramètre le nombre d'ordi privé pour leur attribuer une adresse chacun
		string attribAdrPub(string);	//méthode qui nous servira d'attribuer les adresses publiques aux ordinateur privés
		string rattribAdrPub(string);//on remet dans la table d'adresse publique l'adresse utilisée par l'ordinateur privé
		bool hasAdrPub(string);//méthode qui nous permet de savoir si une adresse privée à déjà une adresse publique attribuée
		void afficherTableDeCorrespondance();//va nous afficher les attributions des adresse publiques au adresses privées
		void afficherAdressesPubliques();
		void genererPorts();//va générer les port si les ordianteurs locaux sont plus nombreux que les ip prévu du nat

	private:
		int m_port;				//numero de port à attribuer à l'ordinateur privé
		vector<string> m_adressesPubliques;//adresse publique à attribuer l'ordinateur privé
		list<TableDeDistributionIp> m_temp;//contiendra temporairement la table des adresses privés aux quelles on a déjà attribué un ip public
		int m_nbreAdresses;		//nombre d'adresse à reserver
		string m_plageAdresses;
		int intervalle;
};

#endif
