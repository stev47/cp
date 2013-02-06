Read("liste01.g");
Liste01 := Liste01();

Liste03 := [];
Print("Liste aller N-Gruppen davon: \n");
for G in Liste01 do
	if IsNGroup(G) then
		Print("Syl2G-isomorphietyp: \n", StructureSylowGroup(2, G), "\n");
		Print("Syl3G-isomorphietyp: \n", StructureSylowGroup(3, G), "\n");
		Print("Zentrum-isomorphietyp: \n", StructureCenterSylowGroup(2, G), "\n");
		Print("Zentralisator \n", StructureCentralizerSylowGroup(2, G));
		Print("Normalisator", StructureNormalizeralizerSylowGroup(2, G))
		Add(Liste03, G);
		Print(G, "\n");
	if;
od;
