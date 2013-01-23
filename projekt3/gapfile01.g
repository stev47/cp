Liste := [];
#Schleife ueber die Ordnung
for n in [1..10] do
	#Alternierende Gruppe erstellen
	Add(Liste, AlternatingGroup(n));
od;
for n in [2..30] do
	# ist q primzahlpotenz? (Körpergrade sind Primzahlpotenzen)
	if IsPrimePowerInt(n) then
		Add(Liste, PSL(2,n));
	fi;
od;
Add(Liste, PSL(3,3));
Add(Liste, PSU(3,3));
Add(Liste, MathieuGroup(11));

Liste := Filtered(Liste, g -> (IsSimpleGroup(g) and (not IsAbelian(g)) and Order(g) <= 10000));

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
Print("Liste aller endlichen, einfachen, nicht-abelschen Gruppen bis Ordnung 10000: \n");
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
				#Print("fail");
				break;
			fi;
		fi;
	od;
	if minimal=1 then
		Add(Liste03, G);
	fi;
od;
Print("\nMinimale einfache Gruppen \n");
#Print (Liste03, "\n");
Liste04 := List(Liste03, l -> StructureDescription(l));
Print(Liste04, "\n");
