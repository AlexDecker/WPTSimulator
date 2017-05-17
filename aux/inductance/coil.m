tx=0.0;
ty=0.0;
tz=0.1;
R2=0.2;
R1=0.1;
N = 15;
pts = 1000;

delta = (R2-R1)/N;
tetaMin = R1*N*2*pi/(R2-R1);
tetaMax = R2*N*2*pi/(R2-R1);
teta = linspace(tetaMin,tetaMax,pts);
x1 = delta*teta.*cos(teta)/(2*pi);
y1 = delta*teta.*sin(teta)/(2*pi);
z1 = zeros(1,pts);


x2 = x1+tx;
y2 = y1+ty;
z2 = z1+tz;

L=inductance_neuman(x1,y1,z1,x2,y2,z2);