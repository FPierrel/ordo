min: j1+j2+j3; /* Somme des Ci des jobs*/

/* Borne max = Somme des durées opératoires */
// M = 35;

/* Durée opératoires */
p0 = 2;
p1 = 5;
p2 = 4;
p3 = 3;
p4 = 9;
p5 = 2;
p6 = 10;

/* Contraintes de précédence sur les taches d'un même job */

x01 + x10 = 1;
C0 + 35 * x01 - 35 <= C1 - p1;
C1 + 35 * x10 - 35 <= C0 - p0;
x02 + x20 = 1;
C0 + 35 * x02 - 35 <= C2 - p2;
C2 + 35 * x20 - 35 <= C0 - p0;
x12 + x21 = 1;
C1 + 35 * x12 - 35 <= C2 - p2;
C2 + 35 * x21 - 35 <= C1 - p1;
x34 + x43 = 1;
C3 + 35 * x34 - 35 <= C4 - p4;
C4 + 35 * x43 - 35 <= C3 - p3;
x35 + x53 = 1;
C3 + 35 * x35 - 35 <= C5 - p5;
C5 + 35 * x53 - 35 <= C3 - p3;
x45 + x54 = 1;
C4 + 35 * x45 - 35 <= C5 - p5;
C5 + 35 * x54 - 35 <= C4 - p4;

/* Contraintes de précédence sur les taches d'une même machine */

x03 + x30 = 1;
C0 + 35 * x03 - 35 <= C3 - p3;
C3 + 35 * x30 - 35 <= C0 - p0;
x06 + x60 = 1;
C0 + 35 * x06 - 35 <= C6 - p6;
C6 + 35 * x60 - 35 <= C0 - p0;
x36 + x63 = 1;
C3 + 35 * x36 - 35 <= C6 - p6;
C6 + 35 * x63 - 35 <= C3 - p3;
x14 + x41 = 1;
C1 + 35 * x14 - 35 <= C4 - p4;
C4 + 35 * x41 - 35 <= C1 - p1;
x25 + x52 = 1;
C2 + 35 * x25 - 35 <= C5 - p5;
C5 + 35 * x52 - 35 <= C2 - p2;

/* Contraintes temporelles */

C0 >= p0;
C1 >= p1;
C2 >= p2;
C3 >= p3;
C4 >= p4;
C5 >= p5;
C6 >= p6;

C0 <= j1;
C1 <= j1;
C2 <= j1;
C3 <= j2;
C4 <= j2;
C5 <= j2;
C6 <= j3;

j1 >=0 ;
j2 >=0 ;
j3 >=0 ;

bin x01, x10, x02, x20, x12, x21, x34, x43, x35, x53, x45, x54, x03, x30, x06, x60, x36, x63, x14, x41, x25, x52;