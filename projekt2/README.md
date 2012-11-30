Vernetzung, Diskretisierung der Randbedingungen
===============================================

Einleseformat für Polygonzug und Randbedingungen
------------------------------------------------

Die Daten sollen Zeilenweise vorliegen in folgendem Format:

    [x1] [y1] [d1] [n1]
    [x2] [y2] [d2] [n2]
    ...
    [xn] [yn] [dn] [nn]

Jede Zeile definiert einen Eckpunkt des Polygonzugs, wobei x,y die Koordinaten des Punktes angeben und d die Dirichlet-Daten.
Die Einzelnen Werte sind durch Leerzeichen oder Tabs voneinander getrennt.

Die Neumann-Daten n beziehen sich dabei auf den Mittelpunkt derjenigen Kante, welche durch den Punkt der aktuellen Zeile und den der darauf folgenden Zeile definiert wird.
Im Falle der letzten Zeile bezieht sich die Neumannbedingung auf den Mittelpunkt der Kante, die durch den letzten und den ersten Punkt definiert ist (der Polygonzug ist schließlich geschlossen).

Die Knotenpunkte des Polygonzugs müssen /gegen/ den Uhrzeigersinn spezifiziert werden.

Ein Beispiel könnte folgendermaßen aussehen:

    0 0 4.5 1
    1 0 7 2.0
    1 1 6e-15 3
    0 1 8.7 9





