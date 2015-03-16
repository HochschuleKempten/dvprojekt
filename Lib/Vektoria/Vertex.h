#pragma once
#include "../VektoriaMath/HVector.h"
#include "../VektoriaMath/HMat.h"

//--------------------------------------------------------------------------------------------
// CVertex: Klasse für Raumpunkte mit Zusatzinformationen (Normale, Binormale, Tangente, etc.)
//
// Autor: Prof. Dr. Tobias Breiner
// Letzte Änderung: 2011-08-07
//--------------------------------------------------------------------------------------------

namespace Vektoria
{

class CVertex
{
public:
	CVertex();
	CVertex(CHVector &  vPos, CHVector & vNormal, CHVector & vTangent, float fU, float fV);
	CVertex(CHVector &  vPos, CHVector & vNormal, CHVector & vTangent, CHVector & vBitangent, float fU, float fV);
	~CVertex();
	CVertex operator=(CVertex & vertex);
	CVertex operator*(CHMat & m);	// Matrixmultiplikation aller Werte mit der Matrix m => Verschieben, Rotieren, Skalieren etc. möglich 
	void Copy(CVertex & vertex);

	void Init(CHVector & vPos, CHVector & vNormal, CHVector & vTangent, float fU=0, float fV=0);
	void Init(CHVector & vPos, CHVector & vNormal, CHVector & vTangent, CHVector & vBitangent, float fU=0, float fV=0);
	void Fini();

	void UniteDirections(CVertex & vertex2); // Verschmilzt Normalen-, Tangenten- und Bitangenteninformationen der beiden Vertices this und vertex2


	void Transform(CHMat &m); // Matrixmultiplikation aller Werte mit der Matrix m => Verschieben, Rotieren, Skalieren etc. möglich 
	void TransformScaleless(CHMat &m); // Matrixmultiplikation aller Werte mit der Matrix m => Verschieben, Rotieren, Skalieren etc. möglich, schneller als Transform, aber bei Skalierungen und Spiegelungen werden Normalenvektoren falsch berechnet
	void TransformDirections(CHMat &m); // Matrixmultiplikation der Normalen-, der Tangenten- und der Bitangentenvektoren, Position und UV-Koordinaten werden belassen 

	CHVector m_vPos;
	CHVector m_vNormal;
	CHVector m_vTangent;
	CHVector m_vBitangent;
	float m_fU; // fuer das UV-Mapping
	float m_fV;
	bool m_bMarked;
};

}