StructureSylowSubgroup := function(p,G)
 local S,s;                             
 S := SylowSubgroup(G,p);                
 s := StructureDescription(S);          
 return s;
end;
