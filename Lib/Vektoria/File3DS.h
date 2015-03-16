#pragma once
#include "root.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>
#include <vector>

// #pragma once
// #include "root.h"
// #include <Util.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <conio.h>
// #include <io.h>
// #include <vector>
// #include <map>

namespace Vektoria
{

#define PRIMARY				0x4D4D		//0x4D4D // Main Chunk
#define EDITOR				0x3d3d		//	├─ 0x3D3D // 3D Editor Chunk
#define O_OBJECT			0x4000		//	│  ├─ 0x4000 // Object Block
#define O_MESH				0x4100		//	│  │  ├─ 0x4100 // Triangular Mesh
#define O_VERTICES			0x4110		//	│  │  │  ├─ 0x4110 // Vertices List
#define O_FACEDESC			0x4120		//	│  │  │  ├─ 0x4120 // Faces Description
#define O_FACEMAT			0x4130		//	│  │  │  │  └─ 0x4130 // Faces Material
#define O_MAPPINGCOORS		0x4140		//	│  │  │  ├─ 0x4140 // Mapping Coordinates List
#define O_SMOOTHINGGROUP	0x4150		//	│  │  │  │  └─ 0x4150 // Smoothing Group List
#define O_LOCALCOORDSYS		0x4160		//	│  │  │  └─ 0x4160 // Local Coordinates System
#define O_LIGHT				0x4600		//	│  │  ├─ 0x4600 // Light
#define O_SPOTLIGHT			0x4610		//	│  │  │  └─ 0x4610 // Spotlight
#define O_CAMERA			0x4700		//	│  │  └─ 0x4700 // Camera
#define M_MATERIAL			0xAFFF		//	│  └─ 0xAFFF // Material Block
#define M_MATNAME			0xA000		//	│     ├─ 0xA000 // Material Name
#define M_AMBIENTCOL		0xA010		//	│     ├─ 0xA010 // Ambient Color
#define M_DIFFUSECOL		0xA020		//	│     ├─ 0xA020 // Diffuse Color
#define M_SPECCOLOR			0xA030		//	│     ├─ 0xA030 // Specular Color
#define M_TEXTUREMAP		0xA200		//	│     ├─ 0xA200 // Texture Map 1
#define M_BUMPMAP			0xA230		//	│     ├─ 0xA230 // Bump Map
#define M_REFLECTIONMAP		0xA220		//	│     └─ 0xA220 // Reflection Map
#define M_MAPPINGFILENAME	0xA300		//	│        ├─ 0xA300 // Mapping Filename
#define M_MAPPINGPARAMS		0xA351		//	│        └─ 0xA351 // Mapping Parameters
#define K_KEYFRAME			0xB000		//	└─ 0xB000 // Keyframer Chunk
#define K_MESHINFORMATION	0xB002		//	   ├─ 0xB002 // Mesh Information Block
#define K_SPOTLIGHT			0xB007		//	   ├─ 0xB007 // Spot Light Information Block
#define K_FRAMES			0xB008		//	   └─ 0xB008 // Frames (Start and End)
#define K_OBJNAME			0xB010		//	      ├─ 0xB010 // Object Name
#define K_OBJPIVOTPOINT		0xB013		//	      ├─ 0xB013 // Object Pivot Point
#define K_POSITIONTRACK		0xB020		//	      ├─ 0xB020 // Position Track
#define K_ROTATIONTRACK		0xB021		//	      ├─ 0xB021 // Rotation Track
#define K_SCALETRACK		0xB022		//	      ├─ 0xB022 // Scale Track
#define K_HIRARCHYPOS		0xB030		//	      └─ 0xB030 // Hierarchy Position


	struct SVertex {
		CHVector vPos;
		CHVector vNormal;
		CHVector vTangent;
		float fU;
		float fV;
	};

	struct STriangle {
		int a;
		int b;
		int c;
	};

	struct SMesh {
		char* cpName;
		std::vector<SVertex> vVertices;
		std::vector<STriangle> vTriangles;

		int iHirachyPosition;
		int iPositionKeyFrames;
		int iRoationKeyFrames;
		int iScaleKeyFrames;

		CHVector vPivotPoint;
		std::vector<CHVector> vPosition;
		std::vector<CHVector> vRotation;
		std::vector<CHVector> vScale;
		std::vector<float> vRotRadians;

	};

	struct SObject {
		int iNumberOfFrames;
		std::vector<SMesh> vMeshes;
	};



	class CFile3DS
	{

		SObject st3DObject;
		std::map<char*, CPlacement*> m_zpPlacements;
		std::vector<SMesh>::iterator pActiveMesh;
		CMaterial * m_ObjectMaterial;
		CPlacement *m_zpObject;
		bool m_bProcessed;


		void SetActiveMeshPointer(FILE *pFile, unsigned int uiChunkLenght);
		char * ReadString(FILE * pFile);
		void ReadMeshName(FILE *pFile, unsigned int uiChunkLenght);
		void ReadKeyFrames(FILE *pFile);
		void ReadVerticies(FILE *pFile);
		void ReadTriangles(FILE *pFile);
		void ReadUVCoordinates(FILE *pFile);
		void ReadPivotPoint(FILE *pFile);
		void ReadPositionTrack(FILE *pFile);
		void ReadRotationTrack(FILE *pFile);
		void ReadScaleTrack(FILE *pFile);
		void ReadHirachyTrack(FILE *pFile);
		void AddVerticies();
		void CalculateVertexNormals();
		void CalculateVertexTangents();
		void ProcessModel();
		void TranslateMeshAndItsChildren(SMesh* mMesh, int iPosFrame);
		bool Delay(int milliseconds);

	public:
		CFile3DS(void);
		~CFile3DS(void);
		CPlacement* GetObject(int iFramePos = 0);
		void Load3DS (char *pFilename);
		void SetMaterial(CMaterial *m_zm);
		void Animate(int iFPS = 24, int iStartFrame = 0, int iEndFrame = 999999);
		void SetAnimFrameTo(int iPosFrame);
	};
}