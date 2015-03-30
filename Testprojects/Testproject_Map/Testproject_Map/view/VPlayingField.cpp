#include "VPlayingField.h"

NAMESPACE_VIEW_B

void VPlayingField::init()
{
	m_zm.MakeTextureDiffuse("textures\\_original.jpg");
	CHVector size(2, 2, 0.5);
	std::stringstream stream;
	for (int i = 0; i < arrLength; i++) {
		for (int j = 0; j < arrLength; j++) {
			stream.clear();
			stream.str("");
			stream << "i = " << i << ", j = " << j;

			//todo ugly indexing, improve
			m_zg[i][j].Init(size, &m_zm);
			m_zg[i][j].SetName(stream.str().c_str());
			m_zp[i][j].AddGeo(&m_zg[i][j]);
			m_zp[i][j].SetName(stream.str().c_str());
			m_zpCentral.AddPlacement(&m_zp[i][j]);

			m_zp[i][j].TranslateX(i * 4.1F);
			m_zp[i][j].TranslateYDelta(j * 4.1F);
		}
	}

	//m_zpCentral.RotateX(-40 * M_PI / 180);
	//m_zpCentral.RotateXDelta(0.1);
	m_zpCentral.TranslateDelta(-4, -4, -6);

	//TODO make this nice
	AddPlacement(&m_zpCentral);
	master->addScenegraph(this);
}

NAMESPACE_VIEW_E
