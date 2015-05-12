min: j1+j2+j3+j4; /* Somme des Ci des jobs */

/* Borne max = Somme des durées opératoires */
// M = 37;

/* Durée opératoires */
p0 = 6;
p1 = 2;
p2 = 1;
p3 = 5;
p4 = 3;
p5 = 4;
p6 = 7;
p7 = 1;
p8 = 8;

/* Contraintes de précédence sur les taches d'un même job */

x01 + x10 = 1;
C0 + 37 * x01 - 37 <= C1 - p1;
C1 + 37 * x10 - 37 <= C0 - p0;
x23 + x32 = 1;
C2 + 37 * x23 - 37 <= C3 - p3;
C3 + 37 * x32 - 37 <= C2 - p2;
x34 + x43 = 1;
C3 + 37 * x34 - 37 <= C4 - p4;
C4 + 37 * x43 - 37 <= C3 - p3;
x24 + x42 = 1;
C2 + 37 * x24 - 37 <= C4 - p4;
C4 + 37 * x42 - 37 <= C2 - p2;
x67 + x76 = 1;
C6 + 37 * x67 - 37 <= C7 - p7;
C7 + 37 * x76 - 37 <= C6 - p6;
x68 + x86 = 1;
C6 + 37 * x68 - 37 <= C8 - p8;
C8 + 37 * x86 - 37 <= C6 - p6;
x78 + x87 = 1;
C7 + 37 * x78 - 37 <= C8 - p8;
C8 + 37 * x87 - 37 <= C7 - p7;

/* Contraintes de précédence sur les taches d'une même machine */

x04 + x40 = 1;
C0 + 37 * x04 - 37 <= C4 - p4;
C4 + 37 * x40 - 37 <= C0 - p0;
x05 + x50 = 1;
C0 + 37 * x05 - 37 <= C5 - p5;
C5 + 37 * x50 - 37 <= C0 - p0;
x06 + x60 = 1;
C0 + 37 * x06 - 37 <= C6 - p6;
C6 + 37 * x60 - 37 <= C0 - p0;
x45 + x54 = 1;
C4 + 37 * x45 - 37 <= C5 - p5;
C5 + 37 * x54 - 37 <= C4 - p4;
x46 + x64 = 1;
C4 + 37 * x46 - 37 <= C6 - p6;
C6 + 37 * x64 - 37 <= C4 - p4;
x56 + x65 = 1;
C5 + 37 * x56 - 37 <= C6 - p6;
C6 + 37 * x65 - 37 <= C5 - p5;
x27 + x72 = 1;
C2 + 37 * x27 - 37 <= C7 - p7;
C7 + 37 * x72 - 37 <= C2 - p2;
x31 + x13 = 1;
C3 + 37 * x31 - 37 <= C1 - p1;
C1 + 37 * x13 - 37 <= C3 - p3;
x38 + x83 = 1;
C3 + 37 * x38 - 37 <= C8 - p8;
C8 + 37 * x83 - 37 <= C3 - p3;
x18 + x81 = 1;
C1 + 37 * x18 - 37 <= C8 - p8;
C8 + 37 * x81 - 37 <= C1 - p1;

/* Contraintes temporelles */

C0 >= p0;
C1 >= p1;
C2 >= p2;
C3 >= p3;
C4 >= p4;
C5 >= p5;
C6 >= p6;
C7 >= p7;
C8 >= p8;

C0 <= j1;
C1 <= j1;
C2 <= j2;
C3 <= j2;
C4 <= j2;
C5 <= j3;
C6 <= j4;
C7 <= j4;
C8 <= j4;

j1 >= 0;
j2 >= 0;
j3 >= 0;
j4 >= 0;

bin x01, x10, x23, x32, x34, x43, x24, x42, x67, x76, x68, x86, x78, x87, x04, x40, x05, x50, x06, x60, x45, x54, x46, x64, x56, x65, x27, x72, x31, x13, x38, x83, x18, x81;