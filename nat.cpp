/*
	NOM : MUKEYA KASSINDYE
	NI : A00158681
			FICHIER SOURCE : dans ce fichier on implémente toute les méthodes relatives au serveur nat
*/
#include "nat.h"

Nat::Nat()
{
    this->m_port = 0;
    this->m_nbreAdresses = 0;
    this->m_plageAdresses = " ";
}
Nat::~Nat()
{
	cout << "Arret du serveur NAT..." << endl;
}
//
void Nat::setNbreAdr(int m)//m représente le nombre d'adresse à être générées
{
    assert(m > 0);//évalue si le nombre entré est correcte!
    this->m_nbreAdresses = m;
}
//cette méthode va nous permettre de générer une plage des adresses ip en fonction du nombre des ordis privés
void Nat::genererAdrPub()
{
	for(int i(0); i < this->m_nbreAdresses; ++i)
	{
		 this->m_plageAdresses = "134.139.0.";//6ème case reservée pour la partie hôte
		 this->m_adressesPubliques.push_back(this->m_plageAdresses.append(to_string(i+1)));
	}
}
//méthode qui génère les ports//2 ème scénario
void Nat::genererPorts()
{
	this->m_port = MIN + (rand() % intervalle);
}
//méthode qui vérifie si l'adresse privée à déjà une adresse publique lui étant attribué par le serveur
bool Nat::hasAdrPub(string adrsPrive)
{
	if(!this->m_temp.empty())
	{
		for(list<TableDeDistributionIp>::iterator it = this->m_temp.begin(); it != this->m_temp.end(); ++it)
			return adrsPrive == it->natIpPub;
	}
	else
		return false;
}
//cette méthode va nous permettre d'attribuer une adresse ip à l'ordinateur privé qui veux faire un msg à un ordi publique
string Nat::attribAdrPub(string adrsPrive)
{
	TableDeDistributionIp *tab =  new TableDeDistributionIp;
    //on utilisera la table des adresses privées générée par la méthode genererAdrPub
	if(this->m_adressesPubliques.size() != 0)
	{
		tab->ordiIpPr = adrsPrive;
		tab->natIpPub = m_adressesPubliques.back();//on lui attribue une addresse publique
		this->m_temp.push_back(*tab);//on sauvegarde la paire (iprivée et publique)
		this->m_adressesPubliques.pop_back();//ensuite on enlève cette addresse de la table d'adresses publique pour éviter rédondance
		//ensuite on retourne l'adresse publique
		return this->m_temp.back().natIpPub;//on peut simplement retourner tab->natIpPub
	}
	else
	{
		cout << "Pas d'adresse publiques disponibles" << endl;
		return(0);
	}
}
//on remet dans la table d'adresse publique l'adresse utilisée par l'ordinateur privé et on retourne vrai si tout s'est bien passé
string Nat::rattribAdrPub(string adrsPub)
{
	for(list<TableDeDistributionIp>::iterator it = this->m_temp.begin(); it != this->m_temp.end(); ++it)
	{
		if(adrsPub == it->natIpPub)
		{
			//m_adressesPubliques.push_back(adrsPub);//on remet l'adresse publique emprunté dans la plage d'adresse
			adrsPub = it->ordiIpPr;
			break;
		}
	}
	return adrsPub;
}
//méthode pour afficher la table de correspondance
void Nat::afficherTableDeCorrespondance()
{
	if(this->m_temp.empty())
			cout << "La table est vide !" << endl;
	else
	{
		for(list<TableDeDistributionIp>::iterator it = this->m_temp.begin(); it != this->m_temp.end(); ++it)
			cout << it->ordiIpPr << " ---> " << it->natIpPub << endl;
	}
}
//
void Nat::afficherAdressesPubliques()
{
	if(this->m_adressesPubliques.empty())
		cout << "Aucune adresse Publique" << endl;
	else
	{
		for(vector<string>::iterator it = this->m_adressesPubliques.begin(); it != this->m_adressesPubliques.end(); ++it)
			cout << *it << endl;
	}
}