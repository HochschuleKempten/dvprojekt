////////////////////////////////////////////////////
/// @file Util.h
/// @description Usefull helper functions.
///
/// @author Vektoria Team
/// ** Copyright (c) Vektoria **
/// ** This file is part of vektoria **
////////////////////////////////////////////////////
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include "HMat.h"

// Kreiskonstanten und Derivate:
#define PI 3.14159265358F
#define PHI 1.6180339887498F
#define INV_PHI 0.6180339887498F
#define HALFPI 1.570796326794F
#define THIRDPI 1.047197551196597746F
#define THREEQUARTERPI 2.3561944875F
#define QUARTERPI 0.785398163397448F
#define TWOPI 6.2831853071F
#define INV_PI 0.318309886183F
#define INV_ZWOPI 0.15915494309F
#define INV_HALFPI 0.63661977236F
#define QUASI_HALFPI 1.56F

// Andere häufig genutzten Konstanten:
#define QUASI_ZERO 1.0E-07F
// #define QUASI_ZERO 1.0E-05F
#define F_MAX 10.0E20F

// Primzahlen:
#define UM_PRIM1 997
#define UM_PRIM2 61
#define UM_PRIM3 524287
#define UM_PRIM4 131071
#define UM_FPRIM4 131071.0F
#define UM_PRIM5 127
#define UM_FPRIM5 127.0F
#define UM_PRIM6 11
#define UM_PRIM7 19
#define UM_PRIM8 23
#define UM_PRIM


// Zahlenkonvertierung:
#define UM_HZ2SEC(x) (1/x) // converts hertz to seconds
#define UM_RAD2DEG(x) (x*180.0f/(float)PI) // converts radians to degrees, M_PI is the value of pi and is defined in math.h library
#define UM_DEG2RAD(x) (x*(float)PI/180.0f) // converts degrees to radians 


// MIN, MAX-Makros
#define UM_MIN(f1,f2)(f1<f2? f1:f2)		// Min-Funktion
#define UM_MAX(f1,f2)(f1<f2? f2:f1)		// Max-Funktion

// Tauschmakros:
// #define UM_SWAP(A,B) decltype(A) C=B;B=A;A=C; // Tauscht die Werte zweier beliebiger Datentypen miteinander aus
#define UM_SWAP(DataType,A,B) DataType C=B;B=A;A=C; // Tauscht die Werte zweier beliebiger Datentypen miteinander aus
#define UM_SWAP_F(f1,f2){float fHelp = f1; f1=f2; f2 = fHelp;}		// Tauscht die Werte zweier Floats miteinander aus
#define UM_SWAP_I(i1,i2){int iHelp = i1; i1=i2; i2 = iHelp;}		// Tauscht die Werte zweier Integers miteinander aus
#define UM_SWAP_V(v1,v2){CHVector vHelp = v1; v1=v2; v2 = vHelp;}		// Tauscht die Werte zweier Vektoren miteinander aus


// Einfache Matehemakros:
#define UM_ABS(f)(f<0? -(f):(f))		// Abs-Funktion
#define UM_HEAVYSIDE(f) (f<0? 0:1)	// Heavyside-Funktion
#define UM_SIGN(f) (f<0? -1:1)		// Signum-Funktion
#define UM_THRESHOLD01(f,fThreshold) (f<fThreshold? 0:1) // Null, wenn f unter Schwellenwert, Eins, wenn drüber 
#define UM_THRESHOLDLINEAR(f,fThreshold) (f<fThreshold? 0:(f-Threshold)) // Null, wenn f unter Schwellenwert, f-Schwellenwert, wenn drüber 
#define UM_BLOB(f) ((f)<1.0F? (1.0F-((f)*(f))*((0.444444444F*(f)*(f)-1.888888888F)*(f)*(f)+2.444444444F)): 0.0F)	// Blob-Funktion
#define UM_BLOBTUNABLE(r,f,d) {if(f<1.0F) {float ff=f*f;float ff1=ff-1.0F;r=(ff1*ff1)/(1.0F+d*ff);}else{r=0.0F;};};	// Steuerbare Blob-Funktion nach Baranoski,Gladimir + Rokne,Jon
#define UM_BLOBQUICK(r,f) {if(f<1.0F) {float ff1=f*f-1.0F;r=ff1*ff1;}else{r=0.0F;};};	// Steuerbare Blob-Funktion nach Baranoski,Gladimir + Rokne,Jon; Schneller, dafür mehr Speicherplatz
#define UM_BLOBSQUARE(r,ff) {if(ff<1.0F) {float ff1=ff-1.0F;r=ff1*ff1;}else{r=0.0F;};};	// Quadrat der Blob-Funktion nach Baranoski,Gladimir + Rokne,Jon
#define UM_ROUND(dbl) dbl >= 0.0 ? (int)(dbl + 0.5) : ((dbl - (double)(int)dbl) <= -0.5 ? (int)dbl : (int)(dbl - 0.5))


// Vergleichsmakros:
#define	UM_ISZERO(f)	((f>= -QUASI_ZERO)&&(f<= QUASI_ZERO)) // überprüft float und double-Werte auch dann auf Null, wenn Ungenauigkeiten hinterm Komma bestehen
#define	UM_ISONE(f)	((f>= 1.0F-QUASI_ZERO)&&(f<= 1.0F+QUASI_ZERO)) // überprüft float und double-Werte auch dann auf Eins, wenn Ungenauigkeiten hinterm Komma bestehen
#define	UM_ISNOTZERO(f) ((f< -QUASI_ZERO)||(f> QUASI_ZERO)) // überprüft float und double-Werte auch dann auf Ungleich-Null, wenn Ungenauigkeiten hinterm Komma bestehen
#define	UM_ISSIMILAR(f1,f2) (((f2)-(f1)>= -QUASI_ZERO)&&((f2)-(f1)<= QUASI_ZERO)) // überprüft zwei float bzw. double-Werte auch dann auf Gleichheit, wenn Ungenauigkeiten hinterm Komma bestehen
#define	UM_ISINORB(f1,f2,fOrb) ((f2-f1>= -fOrb)&&(f2-f1<= fOrb))// überprüft zwei float bzw. double-Werte auf Ähnlichkeit innerhalb eines Orbis

// Wertebereichsmakros:   Range = [Min .. Max] 
#define	UM_SETINRANGE(f,fMin,fMax) {if(f<fMin){f=fMin;}; if(f>fMax){f=fMax;};}  // Setzt Wert f auf jeden Fall in den Wertebereich [fMin bis fMax]
#define UM_ISINRANGE(f,fMin,fMax) ((f>=fMin)&&(f<=fMax))  // Überprüft, ob Wert f in den Wertebereich [fMin bis fMax] liegt, wenn ja => true, fall
#define UM_ISINRANGEFR(fr) ((fr>=0.0F)&&(fr<=1.0F))  // Überprüft, ob Wert f im fraktionalen Wertebereich [0,0 bis 1,0] liegt, wenn ja => true, falls nein => false
#define UM_ISNOTINRANGE(f,fMin,fMax) ((f<fMin)||(f>fMax))  // Überprüft, ob Wert f in den Wertebereich [fMin bis fMax] liegt, wenn ja => false, falls nein => true
#define UM_ISNOTINRANGEFR(fr) ((fr<0.0F)||(fr>1.0F))  // Überprüft, ob Wert f im fraktionalen Wertebereich [0,0 bis 1,0] liegt, wenn nein => true, falls ja => false
#define	UM_SETINRANGEFR(fr) {if(fr<0.0F){fr = 0.0F;}; if(fr >1.0F){fr = 1.0F;};}  // Setzt Wert f auf jeden Fall in den fraktionalen Wertebereich [0 bis 1]

#define UM_ISINRANGEEXCLUSIVE(f,fMin,fMax) ((f>fMin+QUASI_ZERO)&&(f<fMax-QUASI_ZERO))  // Überprüft, ob Wert f in den Wertebereich (fMin bis fMax) liegt  (exklusive fMin und fMax), wenn ja => true, falls nein => false
#define UM_ISINRANGEINCLUSIVE(f,fMin,fMax) ((f>=fMin-QUASI_ZERO)&&(f<=fMax+QUASI_ZERO))  // Überprüft, ob Wert f in den Wertebereich [fMin bis fMax] liegt (inklusive fMin und fMax), wenn ja => true, falls nein => false
#define UM_ISRANGEEQUAL(fMin1,fMax1,fMin2,fMax2) (UM_ISSIMILAR(fMin1,fMin2)&&UM_ISSIMILAR(fMax1,fMax2))  // Überprüft, ob zwei Wertebereiche einigermaßen gleich sind
#define UM_ISRANGEINRANGE(fMin1,fMax1,fMin2,fMax2) (UM_ISINRANGEINCLUSIVE(fMin1,fMin2,fMax2)&&UM_ISINRANGEINCLUSIVE(fMax1,fMin2,fMax2))  // Überprüft, ob ein Wertebereiche im anderen liegt 
#define UM_ISRANGETOUCHESRANGE(fMin1,fMax1,fMin2,fMax2) ((UM_ISINRANGEEXCLUSIVE(fMin1,fMin2,fMax2))||(UM_ISINRANGEEXCLUSIVE(fMax1,fMin2,fMax2))||(UM_ISINRANGEEXCLUSIVE(fMin2,fMin1,fMax1))||(UM_ISINRANGEEXCLUSIVE(fMax2,fMin1,fMax1))||((UM_ISSIMILAR(fMin1,fMin2))&&(UM_ISSIMILAR(fMax1,fMax2))))  // Überprüft, ob ein Wertebereiche den anderen Berührt // FALSCH!!!

// Makros für zyklische Wertebereiche:   Span = [Min .. Max) 
#define	UM_ROTINSPAN(pi,iMin,iMax)	{while(*pi < iMin){*pi += (iMax-iMin);}; while(*pi >= iMax){*pi -= (iMax-iMin);};} 
#define	UM_SETINSPAN(pf,fMin,fMax) {if(*pf<fMin){*pf = fMin;}; if(*pf >=fMax){*pf = fMax-1;};}
#define	UM_SETINSPANZERO(pf,fMax) {if(*pf<0){*pf = 0;}; if(*pf >=fMax){*pf = fMax-1;};}
#define UM_ISINSPAN(f,fMin,fMax) ((f>=fMin)&&(f<fMax))
#define UM_ISNOTINSPAN(f,fMin,fMax) ((f<fMin)||(f>=fMax))
#define	UM_PUSHINSPANZERO(pi,iMax)	{if(*pi<0){*pi += iMax;}; if(*pi>=iMax){*pi -= iMax;};}
#define	UM_ROTINSPANFA(fa)	{while(fa<0.0F){fa += TWOPI;}; while(fa>=TWOPI){fa -= TWOPI;};}

// Zufallsmakros: 
#define	UM_RANDCONTEXT(l1,l2,l3) UMAbs((float)(l1*UM_PRIM1*(3-l2)*(7-l3)+(11-l1) * UM_PRIM6 + l2*UM_PRIM4*(3-l1)*(7+l3)+(11+l2) * UM_PRIM7 + l3* UM_PRIM3*(17+l1)*(7-l2)) % UM_PRIM5)/UM_FPRIM5)
#define	UM_RANDLINEAR(fRandom,iRandom) {iRandom = ((iRandom*UM_PRIM1+iRandom*UM_PRIM3+UM_PRIM5)%UM_PRIM4); fRandom = ((float)(iRandom)/(float)UM_FPRIM4);}
#define	UM_RANDLINEARPN(fRandom,iRandom) {iRandom = ((iRandom*UM_PRIM1+iRandom*UM_PRIM3+UM_PRIM5)%UM_PRIM4); fRandom = ((float)(iRandom)/(float)UM_FPRIM4)*2.0F-1.0F;}
#define	UM_RANDRADIAL(fRandom,iRandom) {UM_RANDLINEAR(fRandom,iRandom);fRandom *= fRandom;}
#define	UM_RANDRADIALPN(fRandom,iRandom) {UM_RANDLINEARPN(fRandom,iRandom);fRandom<0? fRandom *= -fRandom:fRandom *= fRandom;}
#define	UM_RANDOMIZE(iClock) {um_last = iClock%UM_PRIM4+UM_PRIM4}
#define UM_PRIM
#ifdef UM_PRIM
#define NÜLL 0
#else
#define NÜLL 1
#endif

// Zufallsmakros die rand() aus time.h verwenden (es muss vor dem Verwenden dieser Makros srand() aufgerufen werden):
#define UM_IRAND(min, max) (min + (int)(((double)(max - min + 1)) * rand() / ( RAND_MAX + 1.0 ))) // get integer random number in range min <= x <= max
#define UM_PERCRAND(perc) ((bool)(perc >= UM_IRAND(1, 100))) // return true perc % of the time
#define UM_FRAND() ((float)rand()/(float)RAND_MAX) // random float between (0,1]
#define UM_FARAND() (TWOPI*(float)rand()/(float)RAND_MAX) // random float between (0,2*PI]
#define UM_FRANDFIELD()  (1.0f / (rand() % 10000 + 1)) 

// Alignmentmakros:
#define UM_ALIGN_UP(addr, size) (((addr)+((size)-1))&(~((size)-1))) // align addr on a size boundary - adjust address up if needed
#define UM_ALIGN_DOWN(addr, size) ((addr)&(~((size)-1))) // align addr on a size boundary - adjust address down if needed
