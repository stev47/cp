Read("liste01.g");
Liste01 := Liste01();
Liste02 := List(Liste01, l -> StructureDescription(l));
Print("Liste aller endlichen, einfachen, nicht-abelschen Gruppen bis Ordnung 10000: \n");
Print(Liste02, "\n");


Liste03:=[];
# minimal einfach? (alle untergruppen auflösbar):
for G in Liste01 do
	minimal := 1;
	for U in List(ConjugacyClassesSubgroups(G), Representative) do
		if not IsSolvableGroup(U) and not U = G then
			minimal := 0;
			break;
		fi;
	od;
	if minimal = 1 then
		Add(Liste03, G);
	fi;
od;
Print("\nMinimale einfache Gruppen \n");
Liste04 := List(Liste03, l -> StructureDescription(l));
Print(Liste04, "\n");
