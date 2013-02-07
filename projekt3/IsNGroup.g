IsNGroup := function(G)

 local a,i,j,L,L_2,l,l_2;
 a:=0;
 L:=PrimeDivisors(Order(G));
 l:=Length(L);

   for i in [1..l] do

   L_2 := AllSubgroups(SylowSubgroup(G,L[i]));
   l_2 := Length(L_2);

           for j in [1..l_2] do

               if IsSolvable(Normalizer(G,L_2[j]))=false
then
               a:=1;
               break;
               fi;
           od;

               if a = 1 then
               break;
               fi;
    od;

        if a = 1 then 
        return ("G ist keine N- Gruppe");
        else
        return ("G ist eine N- Gruppe");
        fi;
  
 end;
