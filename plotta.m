load('ostacoli.txt')
load('voronoi.txt')
load('percorso.txt')
load('incroci.txt')
plot(voronoi(:,1),voronoi(:,2),'r.','MarkerSize',10,'MarkerEdgeColor','g')
hold on
plot(ostacoli(:,1),ostacoli(:,2),'r.','MarkerSize',10)
plot(percorso(:,1),percorso(:,2),'MarkerEdgeColor','y','LineWidth',3)
plot(percorso(:,1),percorso(:,2),'r.','MarkerSize',15,'MarkerEdgeColor','y')
plot(incroci(:,1),incroci(:,2),'r.','MarkerSize',15,'MarkerEdgeColor','r')
hold off