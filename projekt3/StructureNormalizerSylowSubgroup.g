 StructureNormalizerSylowSubgroup := function(p,G) 
 local S,s,N;                                     
 S:= SylowSubgroup(G,p);                          
 N := Normalizer(G,S);                            
 s := StructureDescription(N);                    
 return s;                                        
 end;         

