#liste01.g
#Isomorphe Gruppen ausschliessen
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

return Liste01;

end;