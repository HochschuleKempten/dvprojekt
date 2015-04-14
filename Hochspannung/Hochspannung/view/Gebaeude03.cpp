#include "Gebaeude03.h"

NAMESPACE_VIEW_B


Gebaeude03::Gebaeude03()
{
	m_zpGebaeude03.AddPlacement(&m_zpStufe0);
	m_zpGebaeude03.AddPlacement(&m_zpStufe1);
	m_zpGebaeude03.AddPlacement(&m_zpStufe2);
	m_zpGebaeude03.AddPlacement(&m_zpStufe3);
	m_zpGebaeude03.AddPlacement(&m_zpStufe4);
	m_zpGebaeude03.AddPlacement(&m_zpStufe5);
	m_zpGebaeude03.AddPlacement(&m_zpStufe6);
	m_zpGebaeude03.AddPlacement(&m_zpStufe7);
	m_zpGebaeude03.AddPlacement(&m_zpStufe8);
	m_zpGebaeude03.AddPlacement(&m_zpStufe9);
	m_zpGebaeude03.AddPlacement(&m_zpStufe10);
	m_zpGebaeude03.AddPlacement(&m_zpStufe11);
	m_zpGebaeude03.AddPlacement(&m_zpStufe12);
	m_zpGebaeude03.AddPlacement(&m_zpStufe13);
	m_zpGebaeude03.AddPlacement(&m_zpPodeststufe0);
	m_zpGebaeude03.AddPlacement(&m_zpPodeststufe1);

	m_zpGebaeude03.AddPlacement(&m_zpTube0);
	m_zpGebaeude03.AddPlacement(&m_zpTube1);
	m_zpGebaeude03.AddPlacement(&m_zpTube2);
	m_zpGebaeude03.AddPlacement(&m_zpTube3);
	m_zpGebaeude03.AddPlacement(&m_zpTube4);
	m_zpGebaeude03.AddPlacement(&m_zpTube5);
	m_zpGebaeude03.AddPlacement(&m_zpTube6);
	m_zpGebaeude03.AddPlacement(&m_zpTube7);
	m_zpGebaeude03.AddPlacement(&m_zpTube8);
	m_zpGebaeude03.AddPlacement(&m_zpTube9);
	m_zpGebaeude03.AddPlacement(&m_zpTube10);
	m_zpGebaeude03.AddPlacement(&m_zpTube11);
	m_zpGebaeude03.AddPlacement(&m_zpTube12);
	m_zpGebaeude03.AddPlacement(&m_zpTube14);
	m_zpGebaeude03.AddPlacement(&m_zpTube15);
	m_zpGebaeude03.AddPlacement(&m_zpTube16);
	m_zpGebaeude03.AddPlacement(&m_zpTube17);
	m_zpGebaeude03.AddPlacement(&m_zpTube18);
	m_zpGebaeude03.AddPlacement(&m_zpTube19);
	m_zpGebaeude03.AddPlacement(&m_zpTube20);
	m_zpGebaeude03.AddPlacement(&m_zpTube21);
	m_zpGebaeude03.AddPlacement(&m_zpTube22);
	m_zpGebaeude03.AddPlacement(&m_zpTube23);
	m_zpGebaeude03.AddPlacement(&m_zpTube24);
	m_zpGebaeude03.AddPlacement(&m_zpTube25);
	m_zpGebaeude03.AddPlacement(&m_zpTube26);
	m_zpGebaeude03.AddPlacement(&m_zpTube27);
	m_zpGebaeude03.AddPlacement(&m_zpTube28);
	m_zpGebaeude03.AddPlacement(&m_zpTube29);
	m_zpGebaeude03.AddPlacement(&m_zpTube30);
	m_zpGebaeude03.AddPlacement(&m_zpTube31);
	m_zpGebaeude03.AddPlacement(&m_zpTube32);
	m_zpGebaeude03.AddPlacement(&m_zpTube33);
	m_zpGebaeude03.AddPlacement(&m_zpTube34);
	m_zpGebaeude03.AddPlacement(&m_zpTube35);

	m_zpGebaeude03.AddPlacement(&m_zpCylinder0);
	m_zpGebaeude03.AddPlacement(&m_zpCylinder1);
	m_zpGebaeude03.AddPlacement(&m_zpCylinder2);
	m_zpGebaeude03.AddPlacement(&m_zpCylinder3);
	m_zpGebaeude03.AddPlacement(&m_zpCylinder4);
	m_zpGebaeude03.AddPlacement(&m_zpCylinder5);
	m_zpGebaeude03.AddPlacement(&m_zpCylinder6);
	m_zpGebaeude03.AddPlacement(&m_zpCylinder7);
	m_zpGebaeude03.AddPlacement(&m_zpCylinder8);


	//Geäubde scenePlacement
	m_zpGebaeude03.AddPlacement(&m_zpWallNorth);
	m_zpGebaeude03.AddPlacement(&m_zpWallWest);
	m_zpGebaeude03.AddPlacement(&m_zpWallEast);
	m_zpGebaeude03.AddPlacement(&m_zpWallSouth);
	m_zpGebaeude03.AddPlacement(&m_zpDach);

	

	//PlacementsGeo
	m_zpStufe0.AddGeo(&m_zgStufe0);
	m_zpStufe1.AddGeo(&m_zgStufe0);
	m_zpStufe2.AddGeo(&m_zgStufe0);
	m_zpStufe3.AddGeo(&m_zgStufe0);
	m_zpStufe4.AddGeo(&m_zgStufe0);
	m_zpStufe5.AddGeo(&m_zgStufe0);
	m_zpStufe6.AddGeo(&m_zgStufe0);
	m_zpStufe7.AddGeo(&m_zgStufe0);
	m_zpStufe8.AddGeo(&m_zgStufe0);
	m_zpStufe9.AddGeo(&m_zgStufe0);
	m_zpStufe10.AddGeo(&m_zgStufe0);
	m_zpStufe11.AddGeo(&m_zgStufe0);
	m_zpStufe12.AddGeo(&m_zgStufe0);
	m_zpStufe13.AddGeo(&m_zgStufe0);

	m_zpPodeststufe0.AddGeo(&m_zgPodeststufe0);
	m_zpPodeststufe1.AddGeo(&m_zgPodeststufe0);

	m_zpTube0.AddGeo(&m_zgTube0);
	m_zpTube1.AddGeo(&m_zgTube1);
	m_zpTube2.AddGeo(&m_zgTube2);
	m_zpTube3.AddGeo(&m_zgTube3);
	m_zpTube4.AddGeo(&m_zgTube4);
	m_zpTube5.AddGeo(&m_zgTube5);
	m_zpTube6.AddGeo(&m_zgTube6);
	m_zpTube7.AddGeo(&m_zgTube7);
	m_zpTube8.AddGeo(&m_zgTube8);
	m_zpTube9.AddGeo(&m_zgTube9);
	m_zpTube10.AddGeo(&m_zgTube10);
	m_zpTube11.AddGeo(&m_zgTube11);
	m_zpTube12.AddGeo(&m_zgTube12);
	m_zpTube13.AddGeo(&m_zgTube13);
	m_zpTube14.AddGeo(&m_zgTube14);
	m_zpTube15.AddGeo(&m_zgTube15);
	m_zpTube16.AddGeo(&m_zgTube16);
	m_zpTube17.AddGeo(&m_zgTube17);
	m_zpTube18.AddGeo(&m_zgTube18);
	m_zpTube19.AddGeo(&m_zgTube19);
	m_zpTube20.AddGeo(&m_zgTube20);
	m_zpTube21.AddGeo(&m_zgTube21);
	m_zpTube22.AddGeo(&m_zgTube22);
	m_zpTube23.AddGeo(&m_zgTube23);
	m_zpTube24.AddGeo(&m_zgTube24);
	m_zpTube25.AddGeo(&m_zgTube25);
	m_zpTube26.AddGeo(&m_zgTube26);
	m_zpTube27.AddGeo(&m_zgTube27);
	m_zpTube28.AddGeo(&m_zgTube28);
	m_zpTube29.AddGeo(&m_zgTube29);
	m_zpTube30.AddGeo(&m_zgTube30);
	m_zpTube31.AddGeo(&m_zgTube31);
	m_zpTube32.AddGeo(&m_zgTube32);
	m_zpTube33.AddGeo(&m_zgTube33);
	m_zpTube34.AddGeo(&m_zgTube34);
	m_zpTube35.AddGeo(&m_zgTube35);

	m_zpCylinder0.AddGeo(&m_zgCylinder0);
	m_zpCylinder1.AddGeo(&m_zgCylinder0);
	m_zpCylinder2.AddGeo(&m_zgCylinder0);
	m_zpCylinder3.AddGeo(&m_zgCylinder0);
	m_zpCylinder4.AddGeo(&m_zgCylinderGelaender);
	m_zpCylinder5.AddGeo(&m_zgCylinderGelaender);

	m_zpCylinder6.AddGeo(&m_zgCylinderGelaender);
	m_zpCylinder7.AddGeo(&m_zgCylinderGelaender);
	m_zpCylinder8.AddGeo(&m_zgCylinder8);

	//Gebäude PlacementsGEo

	pm_zWallNSWE = &m_zWallNorth;
	m_zpWallNorth.AddGeo(&m_zWallNorth);
	m_zpWallWest.AddGeo(pm_zWallNSWE);
	m_zpWallEast.AddGeo(pm_zWallNSWE);
	m_zpWallSouth.AddGeo(pm_zWallNSWE);
	m_zpDach.AddGeo(&m_zgDach);

	//Walls&Windows
	m_zgWindow.InitRect(CFloatRect(0.2, 0.9, 0.1, 0.1), false);
	m_zgWindow.AddGeoWall(&m_zgWallFrame);
	m_zWallNorth.AddGeoWindows(&m_zgWindow, CFloatRect(0, 0.1, 1, 0.8), 7, 3);

	m_zgWindowInlay.InitRect(CFloatRect(0.1, 0.1, 0.8, 0.8), false);
	m_zgWallFrame.AddGeoWindow(&m_zgWindowInlay);

	m_zgWindowInlay.InitRect(CFloatRect(0.1, 0.1, 0.8, 0.8), false);
	m_zgWindowInlay.AddGeoWall(&m_zgWallGlass);

	//GeoKörper
	m_zgWallFrame.Init(1, 1, 0.5, &m_zmWallFrame);
	m_zgWallGlass.Init(1, 1, 0.5, &m_zmWallGlass);
	m_zWallNorth.Init(100, 50, 1, &m_zmWallNorth);
	m_zgDach.Init(CHVector(51, 1, 51, 0), &m_zmDach);
	//Ops
	m_zgStufe0.Init(CHVector(10, 0.5, 1.5), &m_zmStufe0);
	m_zgPodeststufe0.Init(CHVector(10, 0.5, 10), &m_zmPodeststufe0);
	m_zgTube0.InitStraight(0.25, 0.5, 20, &m_zmTube0, 24, false);
	m_zgTube1.InitStraight(0.25, 0.5, 20, &m_zmTube0, 24, false);
	m_zgTube2.InitStraight(0.25, 0.5, 22.5, &m_zmTube0, 24, false);
	m_zgTube3.InitStraight(0.25, 0.5, 22.5, &m_zmTube0, 24, false);
	m_zgTube4.InitStraight(0.25, 0.5, 25, &m_zmTube0, 24, false);
	m_zgTube5.InitStraight(0.25, 0.5, 25, &m_zmTube0, 24, false);
	m_zgTube6.InitStraight(0.25, 0.5, 27.5, &m_zmTube0, 24, false);
	m_zgTube7.InitStraight(0.25, 0.5, 27.5, &m_zmTube0, 24, false);
	m_zgTube8.InitStraight(0.25, 0.5, 30, &m_zmTube0, 24, false);
	m_zgTube9.InitStraight(0.25, 0.5, 30, &m_zmTube0, 24, false);
	m_zgTube10.InitStraight(0.25, 0.5, 32.5, &m_zmTube0, 24, false);
	m_zgTube11.InitStraight(0.25, 0.5, 32.5, &m_zmTube0, 24, false);
	m_zgTube12.InitStraight(0.25, 0.5, 35, &m_zmTube0, 24, false);
	m_zgTube13.InitStraight(0.25, 0.5, 35, &m_zmTube0, 24, false);
	m_zgTube14.InitStraight(0.25, 0.5, 37.5, &m_zmTube0, 24, false);
	m_zgTube15.InitStraight(0.25, 0.5, 37.5, &m_zmTube0, 24, false);
	m_zgTube16.InitStraight(0.25, 0.5, 37.5, &m_zmTube0, 24, false);
	m_zgTube17.InitStraight(0.25, 0.5, 37.5, &m_zmTube0, 24, false);

	m_zgTube18.InitStraight(0.25, 0.5, 40, &m_zmTube0, 24, false);
	m_zgTube19.InitStraight(0.25, 0.5, 40, &m_zmTube0, 24, false);
	m_zgTube20.InitStraight(0.25, 0.5, 42.5, &m_zmTube0, 24, false);
	m_zgTube21.InitStraight(0.25, 0.5, 42.5, &m_zmTube0, 24, false);
	m_zgTube22.InitStraight(0.25, 0.5, 45, &m_zmTube0, 24, false);
	m_zgTube23.InitStraight(0.25, 0.5, 45, &m_zmTube0, 24, false);
	m_zgTube24.InitStraight(0.25, 0.5, 47.5, &m_zmTube0, 24, false);
	m_zgTube25.InitStraight(0.25, 0.5, 47.5, &m_zmTube0, 24, false);
	m_zgTube26.InitStraight(0.25, 0.5, 50, &m_zmTube0, 24, false);
	m_zgTube27.InitStraight(0.25, 0.5, 50, &m_zmTube0, 24, false);
	m_zgTube28.InitStraight(0.25, 0.5, 52.5, &m_zmTube0, 24, false);
	m_zgTube29.InitStraight(0.25, 0.5, 52.5, &m_zmTube0, 24, false);
	m_zgTube30.InitStraight(0.25, 0.5, 55, &m_zmTube0, 24, false);
	m_zgTube31.InitStraight(0.25, 0.5, 55, &m_zmTube0, 24, false);

	m_zgTube32.InitStraight(0.25, 0.5, 57.5, &m_zmTube0, 24, false);
	m_zgTube33.InitStraight(0.25, 0.5, 57.5, &m_zmTube0, 24, false);
	m_zgTube34.InitStraight(0.25, 0.5, 57.5, &m_zmTube0, 24, false);
	m_zgTube35.InitStraight(0.25, 0.5, 57.5, &m_zmTube0, 24, false);

	m_zgCylinder0.Init(0.7, 0.7, 33.5, &m_zmCylinder0);
	m_zgCylinderGelaender.Init(0.7, 0.7, 17.5, &m_zmCylinder0);
	m_zgCylinder8.Init(0.9, 0.9, 19.25, &m_zmCylinder0);


	m_zpStufe0.Translate(0, 0, 0);
	m_zpStufe1.Translate(0, 2.5, 3);
	m_zpStufe2.Translate(0, 5, 6);
	m_zpStufe3.Translate(0, 7.5, 9);
	m_zpStufe4.Translate(0, 10, 12);
	m_zpStufe5.Translate(0, 12.5, 15);
	m_zpStufe6.Translate(0, 15, 18);

	m_zpPodeststufe0.Translate(0, 17.5, 29.5);

	m_zpStufe7.Translate(0, 20, 41);
	m_zpStufe8.Translate(0, 22.5, 44);
	m_zpStufe9.Translate(0, 25, 47);
	m_zpStufe10.Translate(0, 27.5, 50);
	m_zpStufe11.Translate(0, 30, 53);
	m_zpStufe12.Translate(0, 32.5, 56);
	m_zpStufe13.Translate(0, 35, 59);

	m_zpPodeststufe1.Translate(0, 37.5, 70.5);



	m_zpTube0.Translate(9, 0, 0);
	m_zpTube1.Translate(-9, 0, 0);
	m_zpTube2.Translate(9, 1.25, 3);
	m_zpTube3.Translate(-9, 1.25, 3);
	m_zpTube4.Translate(9, 2.5, 6);
	m_zpTube5.Translate(-9, 2.5, 6);
	m_zpTube6.Translate(9, 3.75, 9);
	m_zpTube7.Translate(-9, 3.75, 9);
	m_zpTube8.Translate(9, 5, 12);
	m_zpTube9.Translate(-9, 5, 12);
	m_zpTube10.Translate(9, 6.25, 15);
	m_zpTube11.Translate(-9, 6.25, 15);
	m_zpTube12.Translate(9, 7.5, 18);
	m_zpTube13.Translate(-9, 7.5, 18);

	m_zpTube14.Translate(9, 8.75, 21);
	m_zpTube15.Translate(-9, 8.75, 21);
	m_zpTube16.Translate(9, 8.75, 39);
	m_zpTube17.Translate(-9, 8.75, 39);

	m_zpTube18.Translate(-9, 10, 42);
	m_zpTube19.Translate(9, 10, 42);
	m_zpTube20.Translate(-9, 11.25, 45);
	m_zpTube21.Translate(9, 11.25, 45);
	m_zpTube22.Translate(-9, 12.5, 48);
	m_zpTube23.Translate(9, 12.5, 48);
	m_zpTube24.Translate(-9, 13.75, 51);
	m_zpTube25.Translate(9, 13.75, 51);
	m_zpTube26.Translate(-9, 15, 54);
	m_zpTube27.Translate(9, 15, 54);
	m_zpTube28.Translate(-9, 16.25, 57);
	m_zpTube29.Translate(9, 16.25, 57);
	m_zpTube30.Translate(-9, 17.5, 60);
	m_zpTube31.Translate(9, 17.5, 60);

	m_zpTube32.Translate(-9, 18.75, 63);
	m_zpTube33.Translate(9, 18.75, 63);
	m_zpTube34.Translate(-9, 18.75, 81);
	m_zpTube35.Translate(9, 18.75, 81);

	m_zpCylinder0.RotateX(PI / 3.6);
	m_zpCylinder0.TranslateDelta(9, 5.8, -4.2);

	m_zpCylinder1.RotateX(PI / 3.6);
	m_zpCylinder1.TranslateDelta(-9, 5.8, -4.2);

	m_zpCylinder2.RotateX(PI / 3.6);
	m_zpCylinder2.TranslateDelta(9, 27, 38);

	m_zpCylinder3.RotateX(PI / 3.6);
	m_zpCylinder3.TranslateDelta(-9, 27, 38);

	m_zpCylinder4.RotateX(PI / 2);
	m_zpCylinder4.TranslateDelta(-9, 27.2, 21);

	m_zpCylinder5.RotateX(PI / 2);
	m_zpCylinder5.TranslateDelta(9, 27.2, 21);

	m_zpCylinder6.RotateX(PI / 2);
	m_zpCylinder6.TranslateDelta(9, 48.25, 63.4);

	m_zpCylinder7.RotateX(PI / 2);
	m_zpCylinder7.TranslateDelta(-9, 48.25, 63.4);

	m_zpCylinder8.RotateZ(PI / 2);
	m_zpCylinder8.TranslateDelta(9.5, 48, 80.8);

	//GebäudeOps

	m_zpWallNorth.Translate(10, 0, 80);


	m_zpWallWest.RotateY(PI / 2);
	m_zpWallWest.TranslateDelta(109, 0, 80);

	m_zpWallEast.RotateY(PI / 2);
	m_zpWallEast.TranslateDelta(10, 0, 80);



	m_zpWallSouth.RotateY(PI);
	m_zpWallSouth.TranslateDelta(109, 0, -19);

	m_zpDach.Translate(60, 51, 30.5);
}


Gebaeude03::~Gebaeude03()
{
}


CPlacement* Gebaeude03::getPlacement(){

	return &m_zpGebaeude03;
}


NAMESPACE_VIEW_E