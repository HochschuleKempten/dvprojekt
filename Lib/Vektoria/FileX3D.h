#pragma once

namespace Vektoria
{

class CRoot;
class CApiRender;
class CVertex;
class CTriangleList;
class CGeo;

class CFileX3D
{
public:
	CFileX3D(void);
	~CFileX3D(void);

	int KillLeadingBlanks(char * pc);
	void MakeMeshByTriangles(char * acIndexes, char * acPoints, CTriangleList * ptrianglelist);
	void MakeMeshByFaces(char * acIndexes, char * acPoints, CTriangleList * ptrianglelist);
	float XZ2U(float fx, float fz);

	// bool GetNextFace(char * aacParamName[20], char * aacParamValue[20], CVertex * acvertexA, CVertex * acvertexB, CVertex * acvertexC);
	int GetNextTag(char * acTag, char * aacParamName[20], char * aacParamValue[20], char *  acTokenTag,int & iParams); 
	bool Load(char * acPath, CRoot * proot); 
	void Parse(char * acText, CRoot * proot);
	CGeo *  ParseGeo(char * acText, CRoot * proot);
	CGeo *  LoadGeo(char * acPath, CRoot * proot);




	char * m_pcBefore;
	char * m_pcText;
	char * m_pcPoints;
	char * m_pcIndexs;
};

}