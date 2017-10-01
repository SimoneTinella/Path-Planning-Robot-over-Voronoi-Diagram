# Path-Planning-Robot-over-Voronoi-Diagram
Path Planning Algorithm- Generalized Voronoi Diagram

Two algorithms are implemented in this project.
1) Create a Generalized Voronoi Diagram path over a map with obstacles.
2) Return a list of Points to reach a point B starting from a point A.

To create an obstacle you have to insert the vertices clockwise. Example

std::vector<Punto*> obj;
obj.push_back(new Punto(20,80)); 
obj.push_back(new Punto(20,90)); 
obj.push_back(new Punto(30,90)); 
obj.push_back(new Punto(30,80)); 
Ostacolo *o=new Ostacolo(&obj);	

After this you have to create a vector with your created obstacles

std::vector<Ostacolo*> ostacoli;
ostacoli.push_back(o);

After this you have to inizialize the map with your specs (Width, Height, vector of obstacles)

Voronoi *mappa=new Voronoi(200,200,ostacoli);

This three lines returns points of map, obstacles and crossings (Used to create a plot)

std::vector<Punto*> *voronoi= mappa->getPuntiVoronoi();
ostacoli= *mappa->getOstacoli();
std::vector<Punto*> *incroci= mappa->getIncroci();

After this you have to create starting point(partenza) and end point(arrivo)

Punto *partenza= new Punto(20,140);
Punto *arrivo= new Punto(160,70);

This line returns a points vector that connects the starting point to the end point.

std::vector<Punto> percorso=mappa->getPercorso(*partenza,*arrivo);
	
