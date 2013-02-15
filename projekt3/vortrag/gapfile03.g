Read("liste01.g");
Read("HasNonTrivialPartition.txt");
Read("FindAllPartitions.txt");
Liste01 := Liste01();

Liste03 := [];
Print("Liste aller endlichen, einfachen, nicht-abelschen Gruppen bis
 Ordnung 10000 mit nicht trivialen Partitionen");
for i in [1..Length(Liste01)] do
	G:=Liste01[i];
	if  HasNonTrivialPartition(G) then
		Add(Liste03, G);
		Print(StructureDescription(G), " hat nicht triviale Partitionen \n");
	fi;
od;

