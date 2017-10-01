/* Created by Simone Tinella, University of Catania*/

#include<iostream>
#include<vector>
#include <fstream>
#include "Voronoi.h"

int main(){
	
	std::vector<Punto*> quadrato;
	quadrato.push_back(new Punto(20,80));
	quadrato.push_back(new Punto(20,90));
	quadrato.push_back(new Punto(30,90));
	quadrato.push_back(new Punto(30,80));
	Ostacolo *o=new Ostacolo(&quadrato);		
	
	std::vector<Punto*> rettangolo;
	rettangolo.push_back(new Punto(80,50));
	rettangolo.push_back(new Punto(90,50));
	rettangolo.push_back(new Punto(90,45));
	rettangolo.push_back(new Punto(80,45));
	Ostacolo *o1=new Ostacolo(&rettangolo);	
	
	std::vector<Punto*> triangolo;
	triangolo.push_back(new Punto(30,50));
	triangolo.push_back(new Punto(35,60));
	triangolo.push_back(new Punto(40,50));
	Ostacolo *o2=new Ostacolo(&triangolo);
	
	std::vector<Punto*> rettangolo2;
	rettangolo2.push_back(new Punto(150,50));
	rettangolo2.push_back(new Punto(170,50));
	rettangolo2.push_back(new Punto(170,35));
	rettangolo2.push_back(new Punto(150,35));
	Ostacolo *o3=new Ostacolo(&rettangolo2);	
	
	std::vector<Punto*> figura;
	figura.push_back(new Punto(70,160));
	figura.push_back(new Punto(100,160));
	figura.push_back(new Punto(90,140));
	figura.push_back(new Punto(85,150));
	figura.push_back(new Punto(80,140));
	Ostacolo *o4=new Ostacolo(&figura);
	
	std::vector<Punto*> punto;
	punto.push_back(new Punto(90,95));
	Ostacolo *o5=new Ostacolo(&punto);
	
	std::vector<Ostacolo*> ostacoli;
	ostacoli.push_back(o);
	ostacoli.push_back(o1);
	ostacoli.push_back(o2);
	ostacoli.push_back(o3);
	ostacoli.push_back(o4);
	ostacoli.push_back(o5);

	Voronoi *mappa=new Voronoi(200,200,ostacoli);
	std::vector<Punto*> *voronoi= mappa->getPuntiVoronoi();
	ostacoli= *mappa->getOstacoli();
	std::vector<Punto*> *incroci= mappa->getIncroci();
	
	Punto *partenza= new Punto(20,140);
	Punto *arrivo= new Punto(160,70);
	std::vector<Punto> percorso=mappa->getPercorso(*partenza,*arrivo);
	
	std::ofstream fostacoli("ostacoli.txt");
	for(int i=0;i<ostacoli.size();i++){
		for(int j=0;j<ostacoli.at(i)->getIngombro()->size();j++){
		fostacoli<< ostacoli.at(i)->getIngombro()->at(j)->getX() << " " << ostacoli.at(i)->getIngombro()->at(j)->getY() << std::endl;
		}
	}
	fostacoli.close();
	
	std::ofstream fvoronoi("voronoi.txt");
	for(int i=0;i<voronoi->size();i++){
		fvoronoi<< voronoi->at(i)->getX() << " " << voronoi->at(i)->getY() << std::endl;		
	}
	fvoronoi.close();
	
	std::ofstream fpercorso("percorso.txt");
	for(int i=0;i<percorso.size();i++){
		fpercorso<< percorso.at(i).getX() << " " << percorso.at(i).getY() << std::endl;		
	}
	fpercorso.close();
	
	std::ofstream fincroci("incroci.txt");
	for(int i=0;i<incroci->size();i++){
		fincroci<< incroci->at(i)->getX() << " " << incroci->at(i)->getY() << std::endl;		
	}
	fincroci.close();
}
