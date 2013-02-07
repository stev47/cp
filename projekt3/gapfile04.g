Read("liste01.g");
Read("IsNGroup.g");
Read("StructureCentralizerSylowSubgroup.g");
Read("StructureCentreSylowSubgroup.g");
Read("StructureNormalizerSylowSubgroup.g");
Read("StructureSylowSubgroup.g");
Liste01 := Liste01();
Liste03 := [];
Print("Liste aller N-Gruppen davon: \n");
for G in Liste01 do
	if IsNGroup(G) then
		Print("==== ", StructureDescription(G), " ====\n");
		Print("Syl2G-isomorphietyp: ", StructureSylowSubgroup(2, G), "\n");
		Print("Syl3G-isomorphietyp: ", StructureSylowSubgroup(3, G), "\n");
		Print("Zentrum: ", StructureCentreSylowSubgroup(2, G), "\n");
		Print("Zentralisator ", StructureCentralizerSylowSubgroup(2, G), "\n");
		Print("Normalisator ", StructureNormalizerSylowSubgroup(2, G), "\n\n");
		Add(Liste03, G);
	fi;
od;
Liste04 := List(Liste03, l -> StructureDescription(l));
Print(Liste04, "\n");