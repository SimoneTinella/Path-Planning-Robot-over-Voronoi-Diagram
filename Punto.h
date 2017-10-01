/* Created by Simone Tinella, University of Catania*/

class Punto{
	private:
		double x,y;
	public:
		Punto(double x,double y);
		double getX();
		double getY();
};

Punto::Punto(double x,double y){
	this->x=x;
	this->y=y;
}

double Punto::getX(){
	return x;
}

double Punto::getY(){
	return y;
}
