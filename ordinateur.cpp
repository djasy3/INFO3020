/*
	NOM : MUKEYA KASSINDYE

			FICHIER SOURCE : dans ce fichier on implémente toute les méthodes relatives aux ordinateurs
*/
#include "ordinateur.h"

Ordinateur::Ordinateur(void)
{
	srand(time(NULL));
	this->intervalle = 0;
	this->m_port = 0;
	this->m_nbreAdrPr = 0;
	this->m_nbreAdrPub = 0;
	this->m_plageAdresses = " ";
	this->m_nomOrdi = " ";
	this->m_ip = " ";
	this->m_auth = false;
}


Ordinateur::~Ordinateur(void)
{
}
//accesseur nous permettant d'avoir un nombre d'ordinateur auxquels attribuer des adresses privée et numero de port
void Ordinateur::setNombreOrdisPr(int nbre) { this->m_nbreAdrPr = nbre; }
void Ordinateur::setNombreOrdisPub(int nbre ){ this->m_nbreAdrPub = nbre; }
//méthode qui renvoi génère les adresse publique en fonction du nombre d'ordinateur privés
vector<string>Ordinateur::genererAdrPrive()
{
	if(this->m_nbreAdrPr == 0)
	{
		cout << "nombre d'addresses inconnue" << endl;
		exit (EXIT_FAILURE);
	}
	else
	{
		for(int i(0); i < this->m_nbreAdrPr; ++i)
		{
			this->m_plageAdresses = "192.168.0.";//6ème case reservée pour la partie hôte
			this->m_adressesPrivees.push_back(this->m_plageAdresses.append(to_string(i+1)));
		}
		return this->m_adressesPrivees;
	}
}
//méthode pour générer les ip des ordi qui sont publique
vector<string>Ordinateur::genererAdrPublique()
{
	if(this->m_nbreAdrPub == 0)
	{
		cout << "nombre d'addresses inconnue" << endl;
		exit (EXIT_FAILURE);
	}
	else
	{
		for(int i(0); i < this->m_nbreAdrPub; ++i)
		{
			this->m_plageAdresses = "133.168.0.";//6ème case reservée pour la partie hôte
			this->m_adressesPubliques.push_back(this->m_plageAdresses.append(to_string(i+1)));
		}
		return this->m_adressesPubliques;
	}
}
//méthode pour obtenir une adresse privé et l'attribuer à un ordinateur
string Ordinateur::getAdressePr() 
{ 
	string temp = this->m_adressesPrivees.back();
	this->m_adressesPrivees.pop_back();
	return temp ; 
}
//on renvoi le nom du pc
string Ordinateur::getAdressePub() 
{ 
	string temp = this->m_adressesPubliques.back();
	this->m_adressesPubliques.pop_back();
	return  temp;
}
////fonction qui libère l'adresse après utilisation
//void Ordinateur::setAdressePub(string adrs)
//{
//	this->m_adressesPubliques.push_back(adrs);
//}
////
//void Ordinateur::setAdressePr(string adrs)
//{
//	this->m_adressesPrivees.push_back(adrs);
//}
//méthode pour générer les ports publique est privés
void Ordinateur::setPort(string adrs)
{
	intervalle = MAX - MIN;
	//on vérifie si l'adresse est publique ou privé pour générer un port approprié
	if(adrs.substr(0,7) == "192.168" || adrs.substr(0,6) == "172.16" || adrs.substr(0,2) == "10")
		this->m_port  = MIN + (rand() % intervalle);
	else
		this->m_port = (rand() % 1023) + 1;
}
//méthode qui renvoi un port
int Ordinateur::getPort(){ return this->m_port; }
//donner l'authorisation à un ordi publique de communiquer avec un ordinateur privé
void Ordinateur::setAuth(bool ok){ this->m_auth = ok; }
//
bool Ordinateur::getAuth(){ return this->m_auth; }
//
string Ordinateur::getNomOrdi() { return this->m_nomOrdi;}
//
string Ordinateur::getIpOrdi() { return this->m_ip; }
//
void Ordinateur::setIpOrdi(string ip) { this->m_ip = ip; }
//cette méthode va nous permettre de construire un vecteur d'ordinateurs privés(local)
vector<Ordinateur> Ordinateur::getDetailsOrdisPrives()	//renvoi toutes les informations concernant un ordinateur(dns, ip, port)
{
	this->genererAdrPrive();
	//
	for(int i(0); i < this->m_nbreAdrPr; ++i)
	{
		this->m_ip = this->getAdressePr();	//on donne un adresse à notre objet
		this->setPort(m_ip);
		this->m_nomOrdi = "X";				//tout les ordi locaux commenceront avec un X
		this->m_nomOrdi.append(to_string(i+1));
		this->setAuth(false);
		//on place notre objet actuel dans le vecteur ordinateur
		tempPr.push_back(*this);
	}
	//on retourne nos ordi
	return tempPr;
}
//on génère les ordis publiques
vector<Ordinateur> Ordinateur::getDetailsOrdisPubliques()	//renvoi toutes les informations concernant un ordinateur(dns, ip, port)
{
	this->genererAdrPublique();
	//
	for(int i(0); i < this->m_nbreAdrPub; ++i)
	{
		this->m_ip = this->getAdressePub();	//on donne un adresse à notre objet
		this->setPort(m_ip);
		this->m_nomOrdi = "Y";				//tout les ordi locaux commenceront avec un X
		this->m_nomOrdi.append(to_string(i+1));
		this->setAuth(true);
		//on place notre objet actuel dans le vecteur ordinateur
		tempPub.push_back(*this);
	}
	//on retourne nos ordi
	return tempPub;
}
//méthode afficher
void Ordinateur::afficher()
{
	cout<< "Nom:\t" << this->getNomOrdi()<< endl
		<< "Ip:\t"  << this->getIpOrdi() << endl
		<< "Port:\t"<< this->getPort()    << endl;
	if(this->getAuth() == true)
		cout<< "In:\tTrue" << endl;//le champ in permet de spécifier si l'ordinateur accepte de communiquer avec lui ou pas
	else
		cout<< "In:\tFalse"<< endl;
}
