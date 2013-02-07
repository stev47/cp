 StructureCentralizerSylowSubgroup := function(p,G)
 local S,s,C;                                      
 S:= SylowSubgroup(G,p);                           
 C := Centralizer(G,S);
 s := StructureDescription(C);                     
 return s;                                         
 end;  
