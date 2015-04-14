#pragma once

#include "VGeneral.h"

NAMESPACE_VIEW_B


class Gebaeude03
{
private:
	//Stufen
	CGeoCube m_zgStufe0;
	CPlacement m_zpStufe0;
	CMaterial m_zmStufe0;



	CPlacement m_zpStufe1;
	CPlacement m_zpStufe2;
	CPlacement m_zpStufe3;
	CPlacement m_zpStufe4;
	CPlacement m_zpStufe5;
	CPlacement m_zpStufe6;
	CPlacement m_zpStufe7;
	CPlacement m_zpStufe8;
	CPlacement m_zpStufe9;
	CPlacement m_zpStufe10;
	CPlacement m_zpStufe11;
	CPlacement m_zpStufe12;
	CPlacement m_zpStufe13;


	//Podest
	CGeoCube m_zgPodeststufe0;
	CPlacement m_zpPodeststufe0;
	CMaterial m_zmPodeststufe0;


	//Geländer
	CPlacement m_zpPodeststufe1;

	CGeoTube m_zgTube0;
	CPlacement m_zpTube0;
	CMaterial m_zmTube0;
	CGeoTube m_zgTube1;
	CPlacement m_zpTube1;
	CGeoTube m_zgTube2;
	CPlacement m_zpTube2;
	CGeoTube m_zgTube3;
	CPlacement m_zpTube3;
	CGeoTube m_zgTube4;
	CPlacement m_zpTube4;
	CGeoTube m_zgTube5;
	CPlacement m_zpTube5;
	CGeoTube m_zgTube6;
	CPlacement m_zpTube6;
	CGeoTube m_zgTube7;
	CPlacement m_zpTube7;
	CGeoTube m_zgTube8;
	CPlacement m_zpTube8;
	CGeoTube m_zgTube9;
	CPlacement m_zpTube9;
	CGeoTube m_zgTube10;
	CPlacement m_zpTube10;
	CGeoTube m_zgTube11;
	CPlacement m_zpTube11;
	CGeoTube m_zgTube12;
	CPlacement m_zpTube12;
	CGeoTube m_zgTube13;
	CPlacement m_zpTube13;

	CGeoTube m_zgTube14;
	CPlacement m_zpTube14;
	CGeoTube m_zgTube15;
	CPlacement m_zpTube15;
	CGeoTube m_zgTube16;
	CPlacement m_zpTube16;
	CGeoTube m_zgTube17;
	CPlacement m_zpTube17;

	CGeoTube m_zgTube18;
	CPlacement m_zpTube18;
	CGeoTube m_zgTube19;
	CPlacement m_zpTube19;
	CGeoTube m_zgTube20;
	CPlacement m_zpTube20;
	CGeoTube m_zgTube21;
	CPlacement m_zpTube21;
	CGeoTube m_zgTube22;
	CPlacement m_zpTube22;
	CGeoTube m_zgTube23;
	CPlacement m_zpTube23;
	CGeoTube m_zgTube24;
	CPlacement m_zpTube24;
	CGeoTube m_zgTube25;
	CPlacement m_zpTube25;
	CGeoTube m_zgTube26;
	CPlacement m_zpTube26;
	CGeoTube m_zgTube27;
	CPlacement m_zpTube27;
	CGeoTube m_zgTube28;
	CPlacement m_zpTube28;
	CGeoTube m_zgTube29;
	CPlacement m_zpTube29;
	CGeoTube m_zgTube30;
	CPlacement m_zpTube30;
	CGeoTube m_zgTube31;
	CPlacement m_zpTube31;

	CGeoTube m_zgTube32;
	CPlacement m_zpTube32;
	CGeoTube m_zgTube33;
	CPlacement m_zpTube33;
	CGeoTube m_zgTube34;
	CPlacement m_zpTube34;
	CGeoTube m_zgTube35;
	CPlacement m_zpTube35;

	CGeoCylinder m_zgCylinder0;
	CPlacement m_zpCylinder0;
	CMaterial m_zmCylinder0;

	CPlacement m_zpCylinder1;
	CPlacement m_zpCylinder2;
	CPlacement m_zpCylinder3;

	CGeoCylinder m_zgCylinderGelaender;
	CPlacement m_zpCylinder4;
	CPlacement m_zpCylinder5;

	CPlacement m_zpCylinder6;
	CPlacement m_zpCylinder7;

	CPlacement m_zpCylinder8;
	CGeoCylinder m_zgCylinder8;

	//Gebäude03
	CGeoWall m_zWallNorth;
	CPlacement m_zpWallNorth;
	CMaterial m_zmWallNorth;

	CPlacement m_zpWallWest;
	CPlacement m_zpWallEast;
	CPlacement m_zpWallSouth;

	CGeoWall *pm_zWallNSWE;

	CGeoCube m_zgDach;
	CPlacement m_zpDach;
	CMaterial m_zmDach;

	CGeoWindow m_zgWindow;
	CGeoWindow m_zgWindowInlay;

	CGeoWall m_zgWallFrame;
	CMaterial m_zmWallFrame;

	CGeoWall m_zgWallGlass;
	CMaterial m_zmWallGlass;


	//Boden

	CGeoCube m_zgBoden;
	CPlacement m_zpBoden;
	CMaterial m_zmBoden;

	CPlacement m_zpGebaeude03;

public:

	Gebaeude03();
	~Gebaeude03();

	CPlacement* getPlacement();
};


NAMESPACE_VIEW_E
