#liste01.g
Liste01 := function ()
local Liste, Liste01, Liste02;
Liste := [];
#Schleife ueber die Ordnung
for n in [1..10] do
	#Alternierende Gruppe erstellen
	Add(Liste, AlternatingGroup(n));
od;
for n in [2..30] do
	# ist q primzahlpotenz? (Koerpergrade sind Primzahlpotenzen)
	if IsPrimePowerInt(n) then
		Add(Liste, PSL(2,n));
	fi;
od;
Add(Liste, PSL(3,3));
Add(Liste, PSU(3,3));
Add(Liste, MathieuGroup(11));

#Eigenschaften fuer einfache Gruppen ueberpruefen.
Liste := Filtered(Liste, g -> (IsSimpleGroup(g) and (not IsAbelian(g)) and Order(g)<= 10000));
