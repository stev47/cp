Vernetzung, Diskretisierung der Randbedingungen
===============================================

Einleseformat für Polygonzug und Randbedingungen
------------------------------------------------

Eine zusätzliche erste Zeile enthält zwei boolian Werte, die abfragen, ob eine Dirichlet- bzw. eine Neumannfunktion
vorliegt oder die Werte mit den daten übergeben werden.
Der erste Wert für die Dirichletfunktion.
Der zweite Wert für die Neumannfunktion.
"0" wenn die Werte in den Daten enthalten sind und "1" wenn eine Funktion implementiert ist, die die werte berechnet.

Die Daten sollen Zeilenweise vorliegen in folgendem Format:

    [dirichletf] [neumannf]
    [x1] [y1] [d1] [n1] [u1]
    [x2] [y2] [d2] [n2] [u2]
    ...
    [xn] [yn] [dn] [nn] [un]

Jede Zeile definiert einen Eckpunkt des Polygonzugs, wobei x,y die Koordinaten des Punktes angeben und d die Dirichlet-Daten.
Die Einzelnen Werte sind durch Leerzeichen oder Tabs voneinander getrennt.

Die Neumann-Daten n beziehen sich dabei auf den Mittelpunkt derjenigen Kante, welche durch den Punkt der aktuellen Zeile und den der darauf folgenden Zeile definiert wird.
Im Falle der letzten Zeile bezieht sich die Neumannbedingung auf den Mittelpunkt der Kante, die durch den letzten und den ersten Punkt definiert ist (der Polygonzug ist schließlich geschlossen).

u gibt an in wie viele Teile die Kante geteilt werden soll. u bezieht sich auf die Gleiche Kannte wie n. (u1 Unterteilung von Kante (x1,y1)->(x2,y2))
Wenn keine Unterteilung gewünscht ist ui = 0 (oder 1).
Die Knotenpunkte des Polygonzugs müssen /gegen/ den Uhrzeigersinn spezifiziert werden.

Ein Beispiel könnte folgendermaßen aussehen:

    0 0 4.5 1 1
    1 0 7 2.0 6
    1 1 6e-15 3 6
    0 1 8.7 9 2

TODO:

-Beispiel Funktion übergeben

