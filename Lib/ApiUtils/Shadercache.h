#pragma once

#include <d3d11.h>
#include <set>
#include <list>
#include <vector>
#include "..\Vektoria\ApiRender.h"

namespace Vektoria
{
	/*
	// Automatisches Shader-Rekompilieren
	enum EShaderAutoRecompilation
	{
		eShaderAutoRecompilation_Disabled, // Shader nur beim Programmstart kompilieren
		eShaderAutoRecompilation_Enabled   // Automatisches Rekompilieren von Shadern
	};
	*/

	class CShaderCache
	{
	public:
		static const bool bSupportLongFilenames = true;

		// String Konstanten
		static const int m_uCOMMAND_LINE_MAX_LENGTH = (bSupportLongFilenames) ? 2048 : 1024;
		static const int m_uTARGET_MAX_LENGTH = 16;
		static const int m_uENTRY_POINT_MAX_LENGTH = 128;
		static const int m_uFILENAME_MAX_LENGTH = 256;
		static const int m_uPATHNAME_MAX_LENGTH = 512;
		static const int m_uMACRO_MAX_LENGTH = 64;

		// Shadertypen
		enum EShaderType
		{
			eShaderTypeVertex,
			eShaderTypeHull,
			eShaderTypeDomain,
			eShaderTypeGeometry,
			eShaderTypePixel,
			eShaderTypeCompute,
			eShaderTypeUnkown
		};



		// Kompilierfehlerausgabe
		enum EErrorDisplayType
		{
			eDisplayInDebugOutput	// Schreibe Fehler in dubug text
		};

		// Anzahl der verwendeten CPU-Kerne zum Kompilieren
		enum EMaxCoresType
		{
			eMaxCoresNoLimit	    = -4,
			eMaxCores2xCPUCores     = -3,
			eMaxCoresUseAllCores    = -2,
			eMaxCoresUseAllButOne   = -1,
			eMaxCoresMultiThreaded  = 0,
			eMaxCoresSingleThreaded = 1
		};

		class CMacro
		{
		public:
			wchar_t m_wsName[m_uMACRO_MAX_LENGTH];
			int m_iValue;
		};

		class CShader
		{
		public:
			CShader();
			~CShader();

			EShaderType					m_eShaderType;
			ID3D11DeviceChild**			m_ppShader;
			ID3D11InputLayout**			m_ppInputLayout;
			D3D11_INPUT_ELEMENT_DESC*	m_pInputLayoutDesc;
			unsigned int				m_uiNumDescElements;
			wchar_t						m_wsTarget[m_uTARGET_MAX_LENGTH];
			wchar_t						m_wsEntryPoint[m_uENTRY_POINT_MAX_LENGTH];
			wchar_t						m_wsSourceFile[m_uFILENAME_MAX_LENGTH];
			unsigned int				m_uiNumMacros;
			CMacro*						m_pMacros;

			wchar_t                     m_wsRawFileName[m_uFILENAME_MAX_LENGTH];
			wchar_t                     m_wsHashedFileName[m_uFILENAME_MAX_LENGTH];
			wchar_t                     m_wsObjectFile[m_uFILENAME_MAX_LENGTH];
			wchar_t                     m_wsErrorFile[m_uFILENAME_MAX_LENGTH];
			wchar_t                     m_wsAssemblyFile[m_uFILENAME_MAX_LENGTH];
			wchar_t						m_wsAssemblyFileWithHashedFilename[m_uFILENAME_MAX_LENGTH];
			wchar_t                     m_wsPreprocessFile[m_uFILENAME_MAX_LENGTH];
			wchar_t                     m_wsHashFile[m_uFILENAME_MAX_LENGTH];
			wchar_t                     m_wsCommandLine[m_uCOMMAND_LINE_MAX_LENGTH];
			wchar_t                     m_wsPreprocessCommandLine[m_uCOMMAND_LINE_MAX_LENGTH];

			bool						m_bGPRsUpToDate;
			bool						m_bBeingProcessed;
			bool						m_bShaderUpToDate;
			BYTE*						m_pHash;
			long						m_uHashLength;

			BYTE*						m_pFilenameHash;
			long						m_uFilenameHashLength;

			const wchar_t*				m_pwsCompileStatus;
			int							m_iCompileWaitCount;
			HANDLE						m_hCompileProcessHandle;
			HANDLE						m_hCompileThreadHandle;

			void SetupHashedFilename();
		};

		CShaderCache(ID3D11Device* pDevice, ID3D11DeviceContext* pContext,
					const EShaderAutoRecompilation eShaderAutoRecompilation = eShaderAutoRecompilation_Disabled,
					 const EErrorDisplayType eErrorDisplayType = eDisplayInDebugOutput);
		~CShaderCache();

		// Füge Shader zum Cache hinzu
		bool AddShader(ID3D11DeviceChild** ppShader,
					   EShaderType eShaderType,
					   const wchar_t* pwsTarget,
					   const wchar_t* pwsEntryPoint,
					   const wchar_t* pwsSourceFile,
					   unsigned int uiNumMacros,
					   CMacro* pMacros,
					   ID3D11InputLayout** ppInputLayout,
					   const D3D11_INPUT_ELEMENT_DESC* pLayoutDesc,
					   unsigned int uiNumElements,
					   const bool i_bIsApplicationShader = true);

		// Erstelle Shader, die zum Cache hinzugefügt wurden
		HRESULT GenerateShaders(EShaderCreation eShaderCreation, const bool bRecreateShaders = false);
		const bool RecompileTouchedShaders(void) const;
		void SetMaximumCoresForShaderCompiler(const int iMaxCores = eMaxCoresNoLimit);
		void SetRecompileTouchesShadersFlag(const bool bRecompileWhenTouched);
	
		bool ShadersReady();
		void OnDestroyDevice();
		void Abort();

		void GenerateShadersThreadProc();

		private:
			
			void PreprocessShaders();
			void CompileShaders();
			void InvalidateShaders();

			HRESULT CreateShaders();
			BOOL PreprocessShader(CShader* pShader);
			BOOL CompileShader(CShader* pShader);
			HRESULT CreateShader(CShader* pShader);

			void StripPathInformationFromPreprocessFile(CShader* pShader, FILE* pFile, char* pFileBufDst, int iFileSize);
			BOOL CreateHashFromPreprocessFile(CShader* pShader);
			static void CreateHash(const char* pData, int iFileSize, BYTE** hash, long* plLen);
			void WriteHashFile(CShader* pShader);
			BOOL CompareHash(CShader* pShader);

			bool WatchDirectoryForChanges();
			static void __stdcall OnDirectoryChangeEventTriggered(void* args, BOOLEAN);

			BOOL CheckFXC();
			BOOL CheckShaderFile(CShader* pShader);
			BOOL CheckObjectFile(CShader* pShader);

			void PrintShaderErrors(FILE* pFile);

			void DeleteFileByFilename(const wchar_t* pwsFile) const;
			void DeleteErrorFiles();
			void DeleteErrorFile(CShader* pShader);
			void DeleteAssemblyFiles();
			void DeleteAssemblyFile(CShader* pShader);
			void DeleteObjectFiles();
			void DeleteObjectFile(CShader* pShader);
			void DeletePreprocessFiles();
			void DeletePreprocessFile(CShader* pShader);
			void DeleteHashFiles();
			void DeleteHashFile(CShader* pShader);

			void InsertFilenameIntoCommandLine(wchar_t* pwsCommandLine, const wchar_t* pwsFilename) const;

			template<size_t N>
			void CreateFullPathFromFilename(wchar_t(&pwsPath)[N], const wchar_t* pwsFileName) const
			{
				swprintf_s(pwsPath, L"%s\\%s", (bSupportLongFilenames) ? m_wsUniCodeWorkingDir : m_wsWorkingDir, pwsFileName);
			}

			EShaderCreation			m_eShaderCreation;
			EMaxCoresType			m_MaxCoresType;
			unsigned int			m_uiNumCPUCoresToUse;
			unsigned int			m_uiNumCPUCores;
			bool					m_bShadersCreated;
			bool					m_bAbort;
			bool					m_bPrintedProgress;
			std::list<CShader*>		m_ShaderSourceList;
			std::list<CShader*>		m_ShaderList;
			std::list<CShader*>     m_PreprocessList;
			std::list<CShader*>		m_HashList;
			std::list<CShader*>		m_CompileList;
			std::list<CShader*>		m_CompileCheckList;
			std::list<CShader*>		m_CreateList;
			std::set<CShader*>		m_ErrorList;
			ID3D11Device*			m_pDevice;
			ID3D11DeviceContext*	m_pContext;

			struct SProgressInfo
			{
				SProgressInfo()
				: m_pwsFilename(L"No Progress Info Structure: filename unknown"),
			      m_pwsStatus(L"No Status"),
				  m_pShader(NULL)
				{}
				
				SProgressInfo(CShader* pShader, const wchar_t* wsStatus = L"Initializing...")
					: m_pwsFilename((pShader) ? pShader->m_wsRawFileName : L"Invalid Progress Info Structure: Unknown Filename"),
					  m_pwsStatus(wsStatus),
					  m_pShader(pShader)
				{}

				wchar_t*		m_pwsFilename;
				const wchar_t*	m_pwsStatus;
				CShader*		m_pShader;
			};

			SProgressInfo*			m_pProgressInfo;

			unsigned int			m_uiProgressCounter;
			wchar_t					m_wsFcxExePath[m_uPATHNAME_MAX_LENGTH];
			wchar_t					m_wsDevExepath[m_uPATHNAME_MAX_LENGTH];
			wchar_t					m_wsWorkingDir[m_uPATHNAME_MAX_LENGTH];
			wchar_t					m_wsUniCodeWorkingDir[m_uPATHNAME_MAX_LENGTH];
			wchar_t					m_wsBatchWorkingDir[m_uPATHNAME_MAX_LENGTH];
			wchar_t					m_wsLastShaderError[m_uCOMMAND_LINE_MAX_LENGTH * 4];
			CRITICAL_SECTION		m_CompileShaders_CriticalSection;
			HANDLE					m_watchHandle;
			HANDLE					m_waitPoolHandle;
			unsigned int			m_uiShaderErrorRenderedCount;
			bool					m_bRecompileTouchedShaders;
			bool					m_bShowShaderErrors;
			bool					m_bHasShaderErrorsToDisplay;
			bool					m_bForceDebugShaders;
			bool					m_bCreateHashDigest;
			EErrorDisplayType		m_ErrorDisplayType;
	};
}

