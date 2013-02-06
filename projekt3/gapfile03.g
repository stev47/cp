Read("liste01.g");
Liste01 := Liste01();

Liste03 := [];
Print("Liste aller endlichen, einfachen, nicht-abelschen Gruppen bis Ordnung 10000 mit allen Partitionen: \n");
for G in Liste01 do
	if not HasNoTrivialPartition(G) then
		Add(Liste03, G);
		Print(G, " ", FindAllPartitions(G), "\n");
	fi;
od;
