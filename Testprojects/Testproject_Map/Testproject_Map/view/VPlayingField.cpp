#include "VPlayingField.h"

NAMESPACE_VIEW_B


void VPlayingField::fieldClicked(const int i, const int j)
{
	//Todo (V) Check what you want to do with that click,
	// for now we just want to place a Object

	this->playingField->placeBuilding(i, j);

	//TODO (V) delete this line, VPlayingField should only call LPlayingField::placeBuilding, the objects should place themselves
	this->placeObject(i, j);
}

void VPlayingField::placeObject(int i, int j)
{

	//todo (V) place in VPowerPlant
	CGeoCone *cone = new CGeoCone();
	CMaterial * mat = new CMaterial();
	mat->MakeTextureDiffuse("textures\\_original.jpg");
	cone->Init(2.0, 2.0, mat, 24, true);
	cone->SetName("new TestCone");
	//How to rotate a geo???

	m_zpField[i][j].AddGeo(cone);
}

void VPlayingField::initPlayingField()
{
	m_zm.MakeTextureDiffuse("textures\\_original.jpg");
	CHVector size(2, 2, 0.5);
	std::stringstream stream;

	for (int i = 0; i < m_zgField.getRows(); i++) {
		for (int j = 0; j < m_zgField.getRows(); j++) {
			stream.clear();
			stream.str("");
			//TODO (JS) primary and secondary keys
			stream << "VPlayingField;" << i << ";" << j;

			m_zgField[i][j].Init(size, &m_zm);
			m_zgField[i][j].SetName(stream.str().c_str());
			m_zpField[i][j].AddGeo(&m_zgField[i][j]);
			m_zpField[i][j].SetName(stream.str().c_str());
			m_zp.AddPlacement(&m_zpField[i][j]);

			m_zpField[i][j].TranslateX(i * 4.1F);
			m_zpField[i][j].TranslateYDelta(j * 4.1F);
		}
	}

	//m_zp.RotateX(-40 * M_PI / 180);
	//m_zp.RotateXDelta(0.1);
	m_zp.TranslateDelta(-4, -4, -6);
	//TODO (JS) parse class name
	vMaster->addScenegraph("VPlayingField", this);
}


NAMESPACE_VIEW_E
