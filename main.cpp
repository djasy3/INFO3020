/*
	NOM: MUKEYA KASSINDYE
	NI : A00158681

	FICHIER MAIN: contient le corps du programme
	NB: Premier scenario implémenté
		Deuxième scenario en cours...
*/
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "nat.h"
#include "ordinateur.h"

using namespace std;

void sendMessage( Ordinateur&, Ordinateur&, Nat*, int );
bool continuer();

int main (int argc, char *argv[])
{
	Nat *serveurNat =  new Nat();//on crée notre objet NAT
    serveurNat->setNbreAdr(5);//on lui attribue un nombre d'adresse à generer
	serveurNat->genererAdrPub();//ensuite il génère les adresses
    //
	Ordinateur *ordiPub = new Ordinateur();	//objet ordinateur publique
	ordiPub->setNombreOrdisPub(3);			//nombre d'ordis publiques

	Ordinateur *ordiPr = new Ordinateur();	//objet ordinateur privé
	ordiPr->setNombreOrdisPr(5);			//nombre d'ordi privés
    
	//on affiche les ordinateurs locaux
	vector<Ordinateur> ordiL = ordiPr->getDetailsOrdisPrives();
	cout << "**************** ORDINATEURS LOCAUX ****************" << endl << endl;
	cout << "NOM\t\tIP\tPORT" << endl << endl;
	for(vector<Ordinateur>::iterator it = ordiL.begin(); it != ordiL.end(); ++it)
		cout << it->getNomOrdi() << "\t" << it->getIpOrdi() << "\t" << it->getPort() << endl;
	cout << endl;

	vector<Ordinateur> ordiP = ordiPub->getDetailsOrdisPubliques();
	//on affiche les ordinateurs publiques
	cout << "**************** ORDINATEURS PUBLIQUES ****************" << endl << endl;
	cout << "NOM\t\tIP\tPORT" << endl << endl;
	for(vector<Ordinateur>::iterator it = ordiP.begin(); it != ordiP.end(); ++it)
		cout << it->getNomOrdi() << "\t" << it->getIpOrdi() << "\t" << it->getPort() << endl;
	cout << endl;

	cout << "**************** IPs DU SERVEUR NAT ****************" << endl << endl;
	serveurNat->afficherAdressesPubliques();
//****************************************** interaction avec l'utilisateur ****************************************************
	bool encore = true;
	string choixOrdi1 = " ";//l'ordi pubique que l'utilisateur choisira pour recevoir le message
	string choixOrdi2 = " ";//l'ordi local que l'utilisateur choisira pour envoyer le message
	char directionMsg;	//choix de la direction du message
	int pos1 = -1, pos2 = -1;	//variables qui renvoi les positions des ordinateurs à partir de la table
	
	while(encore)
	{
		cout << "Choisir un Ordinateur local en entrant son numero: " << endl;
		cin >> choixOrdi1;
		cout << "Choisir un Ordinateur publique en entrant son numero: " << endl;
		cin >> choixOrdi2;
		cout << "Votre message doit être envoye de 1: " << choixOrdi1 << " -> " << choixOrdi2 << " ou de 2: " << choixOrdi1 << " <- " << choixOrdi2 << endl;
		cout << "Entrer 1 ou 2" << endl;
		cin >> directionMsg;
		//on renvoi les positions des ordi se trouvant dans le tableaux si ces varibles correspondent
		//ceci vérifie si les noms des ordinateurs que le user à donner existe
		for(unsigned int i(0); i < ordiL.size(); ++i )
		{
			if(ordiL.at(i).getNomOrdi() == choixOrdi1)
			{
				pos1 = i;
				break;
			}
		}
		//
		for(unsigned int i(0); i < ordiP.size(); ++i )
		{
			if(ordiP.at(i).getNomOrdi() == choixOrdi2)
			{
				pos2 = i;
				break;
			}
		}
		//
		if((pos1 >= 0) && (pos2 >= 0))
		{
			switch (directionMsg)
			{
			case '1':
				//traitement pour M>=N
				sendMessage(ordiL.at(pos1), ordiP.at(pos2), serveurNat, 1);
				encore = continuer();
				break;
			case '2':
				//traitement
				sendMessage(ordiL.at(pos1), ordiP.at(pos2), serveurNat, 2);
					encore = continuer();
				break;
			default:
				cout << "Mauvais choix, veuillez recommencer" << endl;
				encore = true;
				break;
			}
		}
		else
		{
			cout << "Les noms d'ordinateurs que vous avez insere, n'existent pas!" << endl;
			cout << "veuillez recommencer " << endl;
			encore = true;
		}
	}

	return 0;
}
//méthode qui nous simule l'envoi du message
void sendMessage( Ordinateur &from, Ordinateur &to, Nat *srv, int cas )
{
	//si c'est le premier cas, donc M>=N
	if(cas == 1)
	{
		//on affiche les détails de l'ordinateur qui envoi le message et les détails sur son destinataire
		cout << "Expediteur"  << endl;
		from.afficher();
		cout << "Destinataire"<< endl;
		to.afficher();
		cout << endl;
		//ensuite le traitement du Nat
		cout << "Attribution d'une adresse publique par le N.A.T" << endl;
		//on vérifie l'ordinateur privé avait déjà une adresse publique avant d'en lui attribuer
		if(!srv->hasAdrPub(from.getIpOrdi()))
			from.setIpOrdi(srv->attribAdrPub(from.getIpOrdi()));
		//on affiche la table de correspondance
		srv->afficherTableDeCorrespondance();
		cout << endl;
		//l'ordinateur local donne l'authorisation pour qu'il puisse accepter les communications de l'extérieur
		from.setAuth(true);
		//on réaffiche l'ordinateur locale avec la nouvelle adresse
		cout << "Expediteur(nouvelle adresse)"  << endl;
		from.afficher();
		cout << "Destinataire"<< endl;
		to.afficher();
		cout << endl;
		cout << "message envoyE..." << endl;
	}
	else if(cas == 2)
	{
		//on vérifie si l'ordinateur privé accepte les connection de l'extérieur
		//la communication sera établie si l'ordinateur publique à déjà communiqué une fois avec l'ordi local
		if(from.getAuth() == true)
		{
			//on affiche les détails de l'ordinateur qui envoi le message et les détails sur son destinataire
			cout << "Expediteur"  << endl;
			to.afficher();
			cout << "Destinataire"<< endl;
			from.afficher();
			cout << endl;
			//ensuite le traitement du Nat
			cout << "Reattribution d'une adresse privee par le N.A.T" << endl;
			//on vérifie l'ordinateur privé avait déjà une adresse publique avant d'en lui attribuer
			if(srv->hasAdrPub(from.getIpOrdi()))
				from.setIpOrdi(srv->rattribAdrPub(from.getIpOrdi()));
			//on affiche la table de correspondance
			srv->afficherTableDeCorrespondance();
			cout << endl;
			//on réaffiche l'ordinateur locale avec la nouvelle adresse
			cout << "Expediteur(nouvelle adresse)"  << endl;
			to.afficher();
			cout << "Destinataire"<< endl;
			from.afficher();
			cout << endl;
			cout << "message envoyé..." << endl;
		}
		else
		{
			cout << "vous devez avoir l'authorisation pour envoyer le message" << endl;
		}
	}
}
//fonction demandant à l'utilisateur veux continuer ou pas
bool continuer()
{
	char reponse = ' ';
	cout << "Voulez-vous envoyer d'autres messages?" << endl;
	cin >>reponse;
	//
	if(reponse == 'O' || reponse =='o')
		return true;
	else if(reponse == 'N' || reponse =='n')
		return false;
	else
		return false;
}