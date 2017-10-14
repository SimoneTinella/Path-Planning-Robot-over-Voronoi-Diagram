/* Created by Simone Tinella, University of Catania*/

#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>
#include "Ostacolo.h"

const double unit= 1;
const double raggio_ricerca= 5*unit*sqrt(2); //raggio ricerca vicini
const double dist_tolleranza= unit*sqrt(2);

const double distanza= 5*unit;//*sqrt(2); //filtro
const int scarto=1; //filtro

class Voronoi{
	private:
		double lunghezza;
		double larghezza;
		std::vector<Ostacolo*> ostacoli;
		std::vector<Punto*> punti_voronoi;
		std::vector<Punto*> incroci;
		void CreaVoronoi();
		std::vector<Punto*> getPercorsoVoronoi(Punto partenza,Punto arrivo,std::vector<Punto*> *incroci_s);
		std::vector<Punto*> getPercorsoVoronoi2(Punto partenza,Punto arrivo);
				
	public:
		Voronoi(double larghezza,double lunghezza,std::vector<Ostacolo*> ostacoli);
		std::vector<Ostacolo*> *getOstacoli();
		std::vector<Punto*> *getPuntiVoronoi();
		std::vector<Punto> getPercorso(Punto partenza,Punto arrivo);
		Punto getPuntoDistanzaMinima(Punto p);	
		std::vector<Punto*> *getIncroci();
		
};

Voronoi::Voronoi(double larghezza,double lunghezza,std::vector<Ostacolo*> ostacoli){
	this->ostacoli=ostacoli;
	
	//Usare questo se non si vogliono i collegamenti degli spiegoli dell'ambiente
	std::vector<Punto*> ambiente;
	ambiente.push_back(new Punto(0,0));
	ambiente.push_back(new Punto(larghezza-1,0));
	ambiente.push_back(new Punto(larghezza-1,lunghezza-1));
	ambiente.push_back(new Punto(0,lunghezza-1));
	this->ostacoli.push_back(new Ostacolo(&ambiente));
	
	//usare questo se si vogliono gli spigoli dell'ambiente
	/*std::vector<Punto*> ambiente;
	ambiente.push_back(new Punto(0,0));
	ambiente.push_back(new Punto(larghezza-1,0));
	this->ostacoli.push_back(new Ostacolo(&ambiente));
	std::vector<Punto*> ambiente2;
	ambiente2.push_back(new Punto(larghezza-1,1));
	ambiente2.push_back(new Punto(larghezza-1,lunghezza-1));
	this->ostacoli.push_back(new Ostacolo(&ambiente2));
	std::vector<Punto*> ambiente3;
	ambiente3.push_back(new Punto(larghezza-2,lunghezza-1));
	ambiente3.push_back(new Punto(0,lunghezza-1));
	this->ostacoli.push_back(new Ostacolo(&ambiente3));
	std::vector<Punto*> ambiente4;
	ambiente4.push_back(new Punto(0,lunghezza-2));
	ambiente4.push_back(new Punto(0,1));
	this->ostacoli.push_back(new Ostacolo(&ambiente4));*/
	
	this->lunghezza=lunghezza;
	this->larghezza=larghezza;
	
	std::cout<<"Sto cercando i punti di voronoi"<<std::endl;
	CreaVoronoi();
	std::cout<<"Mappa di voronoi creata"<<std::endl;
}

std::vector<Ostacolo*> *Voronoi::getOstacoli(){
	return &ostacoli;
}

std::vector<Punto*> *Voronoi::getPuntiVoronoi(){
	return &punti_voronoi;
}

std::vector<Punto*> *Voronoi::getIncroci(){
	return &incroci;
}

void Voronoi::CreaVoronoi(){
	
	for(double tmpY=unit;tmpY<lunghezza-unit;tmpY+=unit){
		
		float percento= ((float)tmpY/(float)(lunghezza-unit))*100;
		std::cout<<"Elaborazione: "<<percento<<"% \r";
		
		for(double tmpX=unit;tmpX<larghezza-unit;tmpX+=unit){
		
			
			Punto *tmp_punto= new Punto(tmpX,tmpY);
			
			std::vector<double> distanze;
			for(int i=0;i<ostacoli.size();i++){
				double minDist=10000;
				for(int j=0;j<ostacoli.at(i)->getIngombro()->size();j++){
					double tmp_dist= Ostacolo::Distanza(*tmp_punto,*ostacoli.at(i)->getIngombro()->at(j));
					//double tmp_dist= fabs(tmp_punto->getX()-ostacoli.at(i)->getIngombro()->at(j)->getX())+fabs(tmp_punto->getY()-ostacoli.at(i)->getIngombro()->at(j)->getY());
					if(tmp_dist<minDist) 
						minDist=tmp_dist;
				}
				distanze.push_back(minDist);
			}
			
			//Mi servono le distanze dagli ostacoli + vicini
			std::sort(distanze.begin(),distanze.begin()+distanze.size());
			
			double min1= distanze.at(0);
			double min2= distanze.at(1);	
			
			if(fabs(min2-min1)<=dist_tolleranza){
				punti_voronoi.push_back(tmp_punto);
				
				if(ostacoli.size()>2){
					double min3= distanze.at(2);
					if(fabs(min2-min3)<=dist_tolleranza && fabs(min3-min1)<=dist_tolleranza) incroci.push_back(tmp_punto);	
				}
				
			}else delete tmp_punto;
		
			
		}
	}
}



std::vector<Punto> Voronoi::getPercorso(Punto partenza,Punto arrivo){
	std::cout<<"Calcolo il percorso"<<std::endl;
	
	std::vector<Punto> percorso;
	percorso.push_back(partenza); //solo temporaneo
	double dist=10000;
	double dist2=10000;
	Punto *minimo_arrivo=NULL;
	Punto *minimo=NULL;
	
	for(int i=0;i<punti_voronoi.size();i++){
		Punto *p= punti_voronoi.at(i);
		double val= sqrt((partenza.getX()-p->getX())*(partenza.getX()-p->getX()) + (partenza.getY()-p->getY())*(partenza.getY()-p->getY()));
        double val2= sqrt((arrivo.getX()-p->getX())*(arrivo.getX()-p->getX()) + (arrivo.getY()-p->getY())*(arrivo.getY()-p->getY()));
		if(val<dist){
			minimo=p;
			dist=val;
		}
		if(val2<dist2){
			minimo_arrivo=p;
			dist2=val2;
		}
	}
	
	if(minimo==NULL) return percorso;
	if(minimo_arrivo==NULL) return percorso;
	
	percorso.push_back(*minimo);
	
	if(minimo->getX()== arrivo.getX() && minimo->getY()==arrivo.getY()) return percorso;
	
	std::vector<Punto*> perc_voro= getPercorsoVoronoi(*minimo,*minimo_arrivo,NULL);
	//std::vector<Punto*> perc_voro= getPercorsoVoronoi2(*minimo,*minimo_arrivo);
	
	if(perc_voro.size()>0){
		Punto *tmp=perc_voro.at(0);
		percorso.push_back(*tmp);
		for(int i=1;i<perc_voro.size();i++){
			if(Ostacolo::Distanza(*tmp,*perc_voro.at(i))>=distanza){
				percorso.push_back(*perc_voro.at(i));
				tmp=perc_voro.at(i);
			}
		}
		
		std::vector<Punto> temp;
		for(int i=0;i<percorso.size();i+=scarto){
			temp.push_back(percorso.at(i));
		}
		percorso=temp;
			
	}
	
	percorso.push_back(*minimo_arrivo);
	percorso.push_back(arrivo);
	
	return percorso;	
}



std::vector<Punto*> Voronoi::getPercorsoVoronoi(Punto partenza,Punto arrivo,std::vector<Punto*> *incroci_s){
	std::vector<Punto*> percorso;
	std::vector<Punto*> punti_passati;
	punti_passati.push_back(&partenza);
	
	Punto *tmp=&partenza;
	
	do{
		std::vector<Punto*> vicini;
		
		for(int i=0;i<punti_voronoi.size();i++){
			Punto *p=punti_voronoi.at(i);
			double val= sqrt((tmp->getX()-p->getX())*(tmp->getX()-p->getX()) + (tmp->getY()-p->getY())*(tmp->getY()-p->getY()));
			
			bool passato=false;
			for(int i=0;i<punti_passati.size();i++){
				if(p==punti_passati.at(i))
					passato=true;
			}
			
			if(val<=raggio_ricerca && !passato)
				vicini.push_back(p);
		}
		
		if(vicini.size()>0){
			double dist=10000;
			Punto *temp;
			for(int i=0;i<vicini.size();i++){
				Punto *vicino= vicini.at(i);
				double val= sqrt((vicino->getX()-arrivo.getX())*(vicino->getX()-arrivo.getX()) + (vicino->getY()-arrivo.getY())*(vicino->getY()-arrivo.getY()));
				if(val<dist){
					temp=vicino;
					dist=val;
				}
			}
			
			if(dist<Ostacolo::Distanza(*tmp,arrivo)) //controllo per evitare l'allontamento
				tmp=temp;
				else goto alternativo;
				
			//	tmp=temp; //oppure questa senza il controllo di sopra
			percorso.push_back(tmp);
			punti_passati.push_back(tmp);
		}else{
			alternativo:
			std::cout<<"Non ci sono riuscito, ritento"<<std::endl;
		
			percorso.clear();
			punti_passati.clear();
			Punto *incrocio_vicino=NULL;
			
			double dist=10000;
			for(int i=0;i<incroci.size();i++){
				Punto *inc= incroci.at(i);
				double val=Ostacolo::Distanza(*inc,arrivo);				
				bool presente=false;
				if(incroci_s!=NULL)
				for(int j=0;j<incroci_s->size();j++){
					if(inc==incroci_s->at(j)){
						presente=true;
						break;
					}						
				}				
				if(val<dist && !presente){
					incrocio_vicino=inc;
					dist=val;
				} 				
			}
			
			if(incrocio_vicino==NULL) {
				std::cout<<"Impossibile trovare un percorso"<<std::endl;
				exit(-1);
			}
			
 			std::cout<<"incrocio vicino scelto: "<<incrocio_vicino->getX()<<" "<<incrocio_vicino->getY();
			
			if(incroci_s==NULL){
				std::vector<Punto*> incroci_scelti;
				incroci_s=&incroci_scelti;				
			}
			
			incroci_s->push_back(incrocio_vicino);
			percorso= getPercorsoVoronoi(partenza,*incrocio_vicino,incroci_s);
			
			std::vector<Punto*> restante= getPercorsoVoronoi(*incrocio_vicino,arrivo,incroci_s); 
			
			percorso.insert(percorso.end(),restante.begin(),restante.end());
			return percorso;
		}
		
	}while(!(tmp->getX()==arrivo.getX() && tmp->getY()==arrivo.getY()));
	
	
	return percorso;
}

std::vector<Punto*> Voronoi::getPercorsoVoronoi2(Punto partenza,Punto arrivo){
	std::vector<Punto*> percorso;
	
	Punto *incrocio_partenza;
	Punto *incrocio_arrivo;
	
	double dist1=10000;
	double dist2=10000;
	for(int i=0;i<incroci.size();i++){
		Punto *inc= incroci.at(i);
		double val= Ostacolo::Distanza(*inc,partenza);
		double val2= Ostacolo::Distanza(*inc,arrivo);		
		if(val<dist1){
			dist1=val;
			incrocio_partenza=inc;
		}
		if(val2<dist2){
			dist2=val2;
			incrocio_arrivo=inc;
		}		
	}
	
	dist1=10000;
	Punto *incrocio_obiettivo;
	for(int i=0;i<incroci.size();i++){
		Punto *inc= incroci.at(i);
		double val= Ostacolo::Distanza(*inc,*incrocio_partenza);
		double val2= Ostacolo::Distanza(*inc,*incrocio_arrivo);
		if(fabs(val-val2)<dist1){
			incrocio_obiettivo=inc;
			dist1=fabs(val-val2);
		}	
	}
	
	percorso= getPercorsoVoronoi(partenza,*incrocio_arrivo,NULL);
	
	std::vector<Punto*> temp;/*= getPercorsoVoronoi(*incrocio_partenza,*incrocio_obiettivo,NULL);
	percorso.insert(percorso.end(),temp.begin(),temp.end());
	
	temp= getPercorsoVoronoi(*incrocio_obiettivo,*incrocio_arrivo,NULL);
	percorso.insert(percorso.end(),temp.begin(),temp.end());*/
	
	temp= getPercorsoVoronoi(*incrocio_arrivo,arrivo,NULL);
	percorso.insert(percorso.end(),temp.begin(),temp.end());
	
	return percorso;
}




