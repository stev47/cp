G := AlternatingGroup(8);
H := PSL(3,4);
Print("G = ", G, " ", Order(G), "\nH = ", H, " ", Order(G), "\n");
Print("Sind G und H isomorph? \n", IsomorphismGroups(G, H), "\n");
Liste01 := []; Liste02 := [];
for x in G do
	if not Order(x) in Liste01 then
		Add(Liste01, Order(x));
	fi;
od;
for x in H do
	if not Order(x) in Liste02 then
		Add(Liste02, Order(x));
	fi;
od;
Sort(Liste01); Sort(Liste02);
Print("In G gibt es Elemente der Ordnung: ", Liste01, "\n","In H gibt es Elemente der Ordnung
: ", Liste02,  "\n");
