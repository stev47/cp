LogTo("text.txt");
#Schleife ueber die Ordnung
for n in [1..10] do
	#Alternierende Gruppe erstellen
	G := AlternatingGroup(n);
	#wenn Gruppe einfach dann ausgeben
	if IsSimpleGroup(G) and Order(G)<=10000 and IsAbelian(G) = false then
		Print(G, " ", Order(G), "\n");
	fi;
od;
Print("\n");
for n in [2..7] do
	H := PSL(2,n);
	if IsSimpleGroup(H) and Order(H)<=10000 and IsAbelian(H) = false then
		Print(H, " ", Order(H), "\n");
	fi;
od;
LogTo();