/* Created by Simone Tinella, University of Catania*/

#include "Punto.h"
#include <math.h>
#include <vector>

class Ostacolo{
	private:
		std::vector<Punto*> vertici;
		std::vector<Punto*> ingombro;
	public:
		Ostacolo(std::vector<Punto*> *vert);
		std::vector<Punto*> *getIngombro();
		static double Distanza(Punto p1,Punto p2);		
};

Ostacolo::Ostacolo(std::vector<Punto*> *vert){
	vertici=*vert;
	
	if(vertici.size()>1){
		for(int i=0;i<vertici.size();i++){
			Punto *p1= vertici.at(i);
            Punto *p2= vertici.at((i+1)%vertici.size());
            
            double p1x= p1->getX();
            double p2x=p2->getX();
            double p1y=p1->getY();
            double p2y= p2->getY();
			
			Punto *tmp=p1;
			double tmp_x= tmp->getX();
			double tmp_y= tmp->getY();
			
			do{
				
				ingombro.push_back(tmp);
				
				if(p1x==p2x && p1y!=p2y){ //retta verticale
                    if(p1y<p2y)
                        tmp_y++;
                    else if(p1y>p2y)
                        tmp_y--;                   
                }else if(p1x!=p2x && p1y==p2y){ //retta orizzontale
                    if(p1x<p2x)
                        tmp_x++;
                    else if(p1x>p2x)
                        tmp_x--;
                }else{ //retta obbligua
                   if(p1x<p2x)
                        tmp_x++;
                    else if(p1x>p2x)
                        tmp_x--;
                   
                    tmp_y= ((tmp_x-p1x)/(p2x-p1x))*(p2y-p1y) +p1y ;
                }
				
				tmp= new Punto(tmp_x,tmp_y);
				
			}while(!(tmp->getX()==p2->getX() && tmp->getY()==p2->getY()));
			
		}
	}else ingombro.push_back(vertici.at(0));
	
}


std::vector<Punto*> *Ostacolo::getIngombro(){
	return &ingombro;
}

double Ostacolo::Distanza(Punto p1,Punto p2){
	return sqrt((p1.getX()-p2.getX())*(p1.getX()-p2.getX()) + (p1.getY()-p2.getY())*(p1.getY()-p2.getY()));
}

