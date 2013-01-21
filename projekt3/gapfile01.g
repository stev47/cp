LogTo("text.txt");
Liste := [];
Print("Alternierende Gruppen \n");
#Schleife ueber die Ordnung
for n in [1..10] do
	#Alternierende Gruppe erstellen
	G := AlternatingGroup(n);
	#wenn Gruppe einfach dann ausgeben
	if IsSimpleGroup(G) and Order(G)<=10000 and IsAbelian(G) = false then
		Print(G, " ", Order(G), " ", " Alt(", n, ") \n");
		Add(Liste, G);
	fi;
od;
Print("\n");
Print("Projektive spezielle lineare Gruppen  PSL(2,q) \n");
for n in [2..30] do
	if IsPrimePowerInt(n) then
		H := PSL(2,n);
		if IsSimpleGroup(H) and Order(H)<=10000 and IsAbelian(H) = false then
			Print(H, " ", Order(H), " PSL(2,", n, ") \n");
			Add(Liste, H);
		fi;
	fi;
od;
Print("\n");
Print("Projektive spezielle lineare Gruppe  PSL(3,3) \n");
K := PSL(3,3);
if IsSimpleGroup(K) and Order(K)<=10000 and IsAbelian(K) = false then
	Print(K, " ", Order(K), " PSL(3,3) \n");
	Add(Liste, K);
fi;
Print("\n");
Print("Projektive spezielle unitaere Gruppe  PSU(3,3) \n");
L := PSU(3,3);
if IsSimpleGroup(L) and Order(L)<=10000 and IsAbelian(L) = false then
	Print(L, " ", Order(L), " PSU(3,3) \n");
	Add(Liste, L);
fi;
Print("\n");
Print("Mathieu-Gruppe \n");
M := MathieuGroup(11);
if IsSimpleGroup(M) and Order(M)<=10000 and IsAbelian(M) = false then
	Print(M, " ", Order(M), " Mathieu-Gruppe \n");
	Add(Liste, M);
fi;
Print("\n");
k := Size(Liste);
u := IsomorphismGroups(AlternatingGroup(3),AlternatingGroup(4));
Liste01 := [];
for i in [1..k] do
	p := 0;
	for j in [i+1..k] do
		if not u = IsomorphismGroups(Liste[i], Liste[j]) then
			p := 1;
		fi;
	od;
	if p = 0 then
		Add(Liste01, Liste[i]);
	fi;
od;
Liste02 := List(Liste01, l -> StructureDescription(l));
Print(Liste02, "\n");

#Print(ConjugacyClassesSubgroups(Liste01[1]), "\n");
#Print(List(ConjugacyClassesSubgroups(Liste01[1]), Representative), "\n");

Liste03:=[];
#minimal einfach? (alle untergruppen auflösbar):
for G in Liste01 do
	minimal:=1;
	for U in List(ConjugacyClassesSubgroups(G), Representative) do
		#Print(U);
		if not IsSolvableGroup(U)  then  #IsSolvableGroup(U) klappt nicht IsPolycyclicGroup(U)
			if not U=G then
				minimal:=0;
				Print("fail");
				break;
			fi;
		fi;
	od;
	if minimal=1 then
		Add(Liste03, G);
	fi;
od;
Print("\n Minimale eifache Gruppen \n");
#Print (Liste03, "\n");
Liste04 := List(Liste03, l -> StructureDescription(l));
Print(Liste04, "\n");


LogTo();