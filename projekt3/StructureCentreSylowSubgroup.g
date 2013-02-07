 StructureCentreSylowSubgroup := function(p,G)
 local S,s,C;                                 
 S:= SylowSubgroup(G,p);                      
 C := Centre(S);                              
 s := StructureDescription(C);                
 return s;                                    
 end;  
