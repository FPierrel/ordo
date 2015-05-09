min: c1+c2+c3+c4+c5+c6+c7+c8+c9; /* Somme des Ci */

/* Borne max = Somme des durées opératoires */
M = 6 + 2 + 1 + 5 + 3 + 4 + 7 + 1 + 8;

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
C0 + M * (x01 - 1) <= C1 - p1;
C1 + M * (x10 - 1) <= C0 - p0;
x23 + x32 = 1;
C2 + M * (x23 - 1) <= C3 - p3;
C3 + M * (x32 - 1) <= C2 - p2;
x34 + x43 = 1;
C3 + M * (x34 - 1) <= C4 - p4;
C4 + M * (x43 - 1) <= C3 - p3;
x24 + x42 = 1;
C2 + M * (x24 - 1) <= C4 - p4;
C4 + M * (x42 - 1) <= C2 - p2;
x67 + x76 = 1;
C6 + M * (x67 - 1) <= C7 - p7;
C7 + M * (x76 - 1) <= C6 - p6;
x68 + x86 = 1;
C6 + M * (x68 - 1) <= C8 - p8;
C8 + M * (x86 - 1) <= C6 - p6;
x78 + x87 = 1;
C7 + M * (x78 - 1) <= C8 - p8;
C8 + M * (x87 - 1) <= C7 - p7;

/* Contraintes de précédence sur les taches d'une même machine */

x04 + x40 = 1;
C0 + M * (x04 - 1) <= C4 - p4;
C4 + M * (x40 - 1) <= C0 - p0;
x05 + x50 = 1;
C0 + M * (x05 - 1) <= C5 - p5;
C5 + M * (x50 - 1) <= C0 - p0;
x06 + x60 = 1;
C0 + M * (x06 - 1) <= C6 - p6;
C6 + M * (x60 - 1) <= C0 - p0;
x45 + x54 = 1;
C4 + M * (x45 - 1) <= C5 - p5;
C5 + M * (x54 - 1) <= C4 - p4;
x46 + x64 = 1;
C4 + M * (x46 - 1) <= C6 - p6;
C6 + M * (x64 - 1) <= C4 - p4;
x56 + x65 = 1;
C5 + M * (x56 - 1) <= C6 - p6;
C6 + M * (x65 - 1) <= C5 - p5;
x27 + x72 = 1;
C2 + M * (x27 - 1) <= C7 - p7;
C7 + M * (x72 - 1) <= C2 - p2;
x31 + x13 = 1;
C3 + M * (x31 - 1) <= C1 - p1;
C1 + M * (x13 - 1) <= C3 - p3;
x38 + x83 = 1;
C3 + M * (x38 - 1) <= C8 - p8;
C8 + M * (x83 - 1) <= C3 - p3;
x18 + x81 = 1;
C1 + M * (x18 - 1) <= C8 - p8;
C8 + M * (x81 - 1) <= C1 - p1;

/* Contraintes temporelles */

M >= C0 >= p0;
M >= C1 >= p1;
M >= C2 >= p2;
M >= C3 >= p3;
M >= C4 >= p4;
M >= C5 >= p5;
M >= C6 >= p6;
M >= C7 >= p7;
M >= C8 >= p8;

binary x01, x10, x23, x32, x34, x43, x24, x42, x67, x76, x68, x86, x78, x87, x04, x40, x05, x50, x06, x60, x45, x54, x46, x64, x56, x65, x27, x72, x31, x13, x38, x83, x18, x81;