#pragma once
#include "vertex.h"	
#include "../VektoriaMath/hvectors.h"
#include "math.h"
#include "DNATypes.h"
#include <fstream>


// FileBlender.h: : interface for the CFileBlender class for the import from .blend files
//
// Written and Developed by Matthias Sommer
// E-Mail:   8bitblip@googlemail.com
//
// Letzte Änderung: 2012-11-01
//
// blender_file_format: https://svn.blender.org/svnroot/bf-blender/trunk/blender/doc/blender_file_format/
// blender_svn: http://projects.blender.org/scm/viewvc.php/trunk/blender/source/blender/makesdna/?root=bf-blender
//////////////////////////////////////////////////////////////////////

#define SIZE_FILEHEADER 12

/*
The first 12 bytes of every blend-file is the file-header. The file-header has information on Blender (version-number) and the PC the blend-file was saved on (pointer-size and endianness). 
This is required as all data inside the blend-file is ordered in that way, because no translation or transformation is done during saving. 

File-header:
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
reference	    structure   type	                                                                                                                                    offset	size
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
identifier	    char[7]	    File identifier (always 'BLENDER')	                                                                                                        0	    7
pointer-size	char	    Size of a pointer; all pointers in the file are stored in this format. '_' means 4 bytes or 32 bit and '-' means 8 bytes or 64 bits.	    7	    1
endianness	    char	    Type of byte ordering used; 'v' means little endian and 'V' means big endian.	                                                            8	    1
version-number	char[3]	    Version of Blender the file was created in; '248' means version 2.48	                                                                    9	    3
*/
namespace Vektoria
{

typedef struct FILEHEADER {
	char id[8];
	int pointerSize;
	char endianness;
    char versionNumber[5];
} FILEHEADER;

/*
File-blocks contain a file-block-header and data. The start of a file-block is always aligned at 4 bytes. 
The file-block-header describes the total length of the data, the type of information stored in the file-block, 
the number of items of this information and the old memory pointer at the moment the data was written to disk. 
Depending on the pointer-size stored in the file-header, a file-block-header can be 20 or 24 bytes long. 
File-block-header:
-------------------------------------------------------------------------------------------------------------------------------------------------
reference	        structure   type	                                                                offset	            size
-------------------------------------------------------------------------------------------------------------------------------------------------
code	            char[4]	    Identifier of the file-block	                                        0	                4
size	            integer	    Total length of the data after the file-block-header	                4	                4
old memory address	void*	    Memory address the structure was located when written to disk	        8	                pointer-size (4/8)
SDNA index	        integer	    Index of the SDNA structure	                                            8+pointer-size	    4
count	            integer	    Number of structure located in this file-block	                        12+pointer-size	    4
*/
typedef struct FILEBLOCK {
    int offest;
    char code[5];
    int size;
    int oldMemoryAddress;
    int indexSDNA;
    int count;
    char* data;
} FILEBLOCK;

/*
Structure DNA is stored in a file-block with code 'DNA1'. It can be just before the 'ENDB' file-block. It contains all internal structures of the Blender release the file was created in. 
The data in this file-block must be interpreted as described in the this section. In a blend-file created with Blender 2.48a this section is 43468 bytes long and contains 309 structures. 
These structure can be described as C-structures. They can hold fields, arrays and pointers to other structures, just like a normal C-structure. 
structure Scene { 
    ID id;              // 52 bytes long (ID is different a structure) 
    Object *camera;     // 4 bytes long (pointer to an Object structure) 
    World *world;       // 4 bytes long (pointer to a World structure) ... 
    float cursor[3];    // 12 bytes long (array of 3 floats) ... 
} 
 
Structure of the DNA file-block-data:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
repeat condition	name	                type	    length	    description
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                    identifier	            char[4]	    4	        'SDNA'
                    name identifier	        char[4]	    4	        'NAME'
		            #names	                integer	    4	        Number of names follows
for(#names)		    name	                char[]	    ?	        Zero terminating string of name, also contains pointer and simple array definitions (e.g. '*vertex[3]\0')
		            type identifier	        char[4]	    4	        'TYPE' this field is aligned at 4 bytes
		            #types	                integer	    4	        Number of types follows
for(#types)		    type	                char[]	    ?	        Zero terminating string of type (e.g. 'int\0')
		            length identifier	    char[4]	    4	        'TLEN' this field is aligned at 4 bytes
for(#types)		    length	                short	    2	        Length in bytes of type (e.g. 4)
		            structure identifier	char[4]	    4	        'STRC' this field is aligned at 4 bytes
		            #structures	            integer	    4	        Number of structures follows
for(#structures)	structure type	        short	    2	        Index in types containing the name of the structure
..		            #fields	                short	    2	        Number of fields in this structure
..	for(#field)	    field type	            short	    2	        Index in type
for end	for end	    field name	            short	    2	        Index in name
*/
typedef struct DNA {
    char id[5];
    char nameId[5];
    int numNames;
    char** names;
    char typeId[5];
    int numTypes;
    char** types;
    char lengthId[5];
    short* length;
    char structureId[5];
    int numStructures;
    short* structureType;
    short* numFields;
    short** fieldType;
    short** fieldName;
} DNA;

class CRoot;
class CApiRender;
class CGeo;

class CFileBlender
{
public:
    CFileBlender(void);
    ~CFileBlender(void);

    CGeo* LoadGeo(char* acPath); // Lädt eine Geometrie aus einem .blend File
	bool LoadScene(char* acPath, CRoot* pRoot); // prototyp
private:
    char* m_acData; // Data returned from ReadFile
    int m_iFileLength; // Length returned from ReadFile
    int m_iNumFileBlocks; // Number of File-blocks stored in the read data
    FILEHEADER m_fileHeader; // File-header
	FILEBLOCK* m_fileBlocks; // Array of all File-blocks
    DNA m_dna; // DNA Structure: Contains all internal structures of the Blender release the file was created in

	Mesh* m_Meshes; // Array of Meshes

    /**
      * The function ReadFile() opens the .blend file, read the file and write the data into an array of bytes. 
      * The function allocates memory and copies into the array of bytes returend by the function. 
      * Important: It is the user's responsibility to free the allocated storage by calling free().
     **/
    char* ReadFile(char* acPath, int* iLength);
    bool Parse(void); // Parse the File-header, File-blocks and DNA Structure stored in the data returned from ReadFile.
    bool Parse(char* acData, int iFileLength, FILEHEADER* pFileHeader, FILEBLOCK** pFileBlocks, DNA* pDna, int* piNumFileBlocks); // untested!

    int ParseFileHeader(char* acData, FILEHEADER* fileHeader); // Parse the File-header and returns pos of the fist File-block
    int ParseFileBlock(char* acData, FILEBLOCK* fileBlock, int pointerSize, int offset); // Parse the File-block and returns position of the next File-block
    int ParseDNAStructure(char* acData, DNA* dna); // Parse the 'DNA1' file-block containing all internal structures of the Blender release the file was created in. Structure DNA is stored in a file-block with code 'DNA1'. It can be just before the 'ENDB' file-block.
    int ParseDNAStructure(FILEBLOCK* fileBlock, DNA* dna); // Parse the 'DNA1' file-block containing all internal structures of the Blender release the file was created in.
    
    int GetTypeIndexByType(DNA* dna, char* type);
    int GetLength(DNA* dna, int typeIndex);
    int GetStructureID(DNA* dna, int iTypeIndex); // Returns the strucutreID
    int GetNumFields(DNA* dna, int structureID);

	Mesh* GetMeshes(void); // untested prototype
};

}