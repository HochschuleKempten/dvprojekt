#ifdef DNA_DEPRECATED_ALLOW
   /* allow use of deprecated items */
#  define DNA_DEPRECATED
#else
#  ifndef DNA_DEPRECATED
#      define DNA_DEPRECATED
#  endif
#endif

struct ID;

typedef struct ListBase 
{
	void *first, *last;
} ListBase;

//------------------------------------
//DNA_ID
//------------------------------------

typedef struct IDPropertyData {
	void *pointer;
	ListBase group;
	int val, val2; /*note, we actually fit a double into these two ints*/
} IDPropertyData;

typedef struct IDProperty {
	struct IDProperty *next, *prev;
	char type, subtype;
	short flag;
	char name[32];
	int saved; /*saved is used to indicate if this struct has been saved yet.
				seemed like a good idea as a pad var was needed anyway :)*/
	IDPropertyData data;	/* note, alignment for 64 bits */
	int len; /* array length, also (this is important!) string length + 1.
				the idea is to be able to reuse array realloc functions on strings.*/
	/* totallen is total length of allocated array/string, including a buffer.
	 * Note that the buffering is mild; the code comes from python's list implementation.*/
	int totallen; /*strings and arrays are both buffered, though the buffer isn't
					saved.*/
} IDProperty;

#define MAX_IDPROP_NAME	32
#define DEFAULT_ALLOC_FOR_NULL_STRINGS	64

/*->type*/
#define IDP_STRING		0
#define IDP_INT			1
#define IDP_FLOAT		2
#define IDP_ARRAY		5
#define IDP_GROUP		6
#define IDP_ID			7
#define IDP_DOUBLE		8
#define IDP_IDPARRAY	9
#define IDP_NUMTYPES	10
/*->subtype */
/* IDP_STRING */
#define IDP_STRING_SUB_UTF8  0 /* default */
#define IDP_STRING_SUB_BYTE  1 /* arbitrary byte array, _not_ null terminated */

#define MAX_ID_NAME	24

typedef struct ID {
	void *next, *prev;
	struct ID *newid;
	struct Library *lib;
	char name[24];
	short us;
	short flag;
	int icon_id;
	IDProperty *properties;
} ID;

#ifdef __BIG_ENDIAN__
   /* big endian */
#  define MAKE_ID2(c, d)		( (c)<<8 | (d) )
#  define MOST_SIG_BYTE			0
#  define BBIG_ENDIAN
#else
   /* little endian  */
#  define MAKE_ID2(c, d)		( (d)<<8 | (c) )
#  define MOST_SIG_BYTE			1
#  define BLITTLE_ENDIAN
#endif

/* ID from database */
#define ID_SCE		MAKE_ID2('S', 'C') /* Scene */
#define ID_LI		MAKE_ID2('L', 'I') /* Library */
#define ID_OB		MAKE_ID2('O', 'B') /* Object */
#define ID_ME		MAKE_ID2('M', 'E') /* Mesh */
#define ID_CU		MAKE_ID2('C', 'U') /* Curve */
#define ID_MB		MAKE_ID2('M', 'B') /* MetaBall */
#define ID_MA		MAKE_ID2('M', 'A') /* Material */
#define ID_TE		MAKE_ID2('T', 'E') /* Texture */
#define ID_IM		MAKE_ID2('I', 'M') /* Image */
#define ID_LT		MAKE_ID2('L', 'T') /* Lattice */
#define ID_LA		MAKE_ID2('L', 'A') /* Lamp */
#define ID_CA		MAKE_ID2('C', 'A') /* Camera */
#define ID_IP		MAKE_ID2('I', 'P') /* Ipo (depreciated, replaced by FCurves) */
#define ID_KE		MAKE_ID2('K', 'E') /* Key (shape key) */
#define ID_WO		MAKE_ID2('W', 'O') /* World */
#define ID_SCR		MAKE_ID2('S', 'R') /* Screen */
#define ID_SCRN		MAKE_ID2('S', 'N') /* (depreciated?) */
#define ID_VF		MAKE_ID2('V', 'F') /* VectorFont */
#define ID_TXT		MAKE_ID2('T', 'X') /* Text */
#define ID_SPK		MAKE_ID2('S', 'K') /* Speaker */
#define ID_SO		MAKE_ID2('S', 'O') /* Sound */
#define ID_GR		MAKE_ID2('G', 'R') /* Group */
#define ID_ID		MAKE_ID2('I', 'D') /* (internal use only) */
#define ID_AR		MAKE_ID2('A', 'R') /* Armature */
#define ID_AC		MAKE_ID2('A', 'C') /* Action */
#define ID_SCRIPT	MAKE_ID2('P', 'Y') /* Script (depreciated) */
#define ID_NT		MAKE_ID2('N', 'T') /* NodeTree */
#define ID_BR		MAKE_ID2('B', 'R') /* Brush */
#define ID_PA		MAKE_ID2('P', 'A') /* ParticleSettings */
#define ID_GD		MAKE_ID2('G', 'D') /* GreasePencil */
#define ID_WM		MAKE_ID2('W', 'M') /* WindowManager */
#define ID_MC		MAKE_ID2('M', 'C') /* MovieClip */

	/* NOTE! Fake IDs, needed for g.sipo->blocktype or outliner */
#define ID_SEQ		MAKE_ID2('S', 'Q')
			/* constraint */
#define ID_CO		MAKE_ID2('C', 'O')
			/* pose (action channel, used to be ID_AC in code, so we keep code for backwards compat) */
#define ID_PO		MAKE_ID2('A', 'C')
			/* used in outliner... */
#define ID_NLA		MAKE_ID2('N', 'L')
			/* fluidsim Ipo */
#define ID_FLUIDSIM	MAKE_ID2('F', 'S')

#define ID_REAL_USERS(id) (((ID *)id)->us - ((((ID *)id)->flag & LIB_FAKEUSER) ? 1:0))

#define ID_CHECK_UNDO(id) ((GS((id)->name) != ID_SCR) && (GS((id)->name) != ID_WM))

#define ID_BLEND_PATH(_bmain, _id) ((_id)->lib ? (_id)->lib->filepath : (_bmain)->name)

#ifdef GS
#undef GS
#endif
#define GS(a)	(*((short *)(a)))

/* id->flag: set frist 8 bits always at zero while reading */
#define LIB_LOCAL		0
#define LIB_EXTERN		1
#define LIB_INDIRECT	2
#define LIB_TEST		8
#define LIB_TESTEXT		(LIB_TEST | LIB_EXTERN)
#define LIB_TESTIND		(LIB_TEST | LIB_INDIRECT)
#define LIB_READ		16
#define LIB_NEEDLINK	32

#define LIB_NEW			256
#define LIB_FAKEUSER	512
/* free test flag */
#define LIB_DOIT		1024
/* tag existing data before linking so we know what is new */
#define LIB_PRE_EXISTING	2048
/* runtime */
#define LIB_ID_RECALC		4096
#define LIB_ID_RECALC_DATA	8192

//------------------------------------
//DNA_customdata_types
//------------------------------------

typedef struct CustomDataLayer {
	int type;       /* type of data in layer */
	int offset;     /* in editmode, offset of layer in block */
	int flag;       /* general purpose flag */
	int active;     /* number of the active layer of this type */
	int active_rnd; /* number of the layer to render*/
	int active_clone; /* number of the layer to render*/
	int active_mask; /* number of the layer to render*/
	char pad[4];
	char name[32];  /* layer name */
	void *data;     /* layer data */
} CustomDataLayer;

typedef struct CustomDataExternal {
	char filename[240];
} CustomDataExternal;

/** structure which stores custom element data associated with mesh elements
 * (vertices, edges or faces). The custom data is organised into a series of
 * layers, each with a data type (e.g. MTFace, MDeformVert, etc.). */
typedef struct CustomData {
	CustomDataLayer *layers;      /* CustomDataLayers, ordered by type */
	int totlayer, maxlayer;       /* number of layers, size of layers array */
	int totsize, pad;             /* in editmode, total size of all data layers */
	void *pool;                   /* Bmesh: Memory pool for allocation of blocks */
	CustomDataExternal *external; /* external file storing customdata layers */
} CustomData;

/* CustomData.type */
#define CD_MVERT		0
#define CD_MSTICKY		1
#define CD_MDEFORMVERT	2
#define CD_MEDGE		3
#define CD_MFACE		4
#define CD_MTFACE		5
#define CD_MCOL			6
#define CD_ORIGINDEX	7
#define CD_NORMAL		8
#define CD_FLAGS		9
#define CD_PROP_FLT		10
#define CD_PROP_INT		11
#define CD_PROP_STR		12
#define CD_ORIGSPACE	13 /* for modifier stack face location mapping */
#define CD_ORCO			14
#define CD_MTEXPOLY		15
#define CD_MLOOPUV		16
#define CD_MLOOPCOL		17
#define CD_TANGENT		18
#define CD_MDISPS		19
#define CD_WEIGHT_MCOL	20 /* for displaying weightpaint colors */
#define CD_ID_MCOL		21
#define CD_TEXTURE_MCOL	22
#define CD_CLOTH_ORCO	23
#define CD_RECAST		24
#define CD_NUMTYPES		25

/* Bits for CustomDataMask */
#define CD_MASK_MVERT		(1 << CD_MVERT)
#define CD_MASK_MSTICKY		(1 << CD_MSTICKY)
#define CD_MASK_MDEFORMVERT	(1 << CD_MDEFORMVERT)
#define CD_MASK_MEDGE		(1 << CD_MEDGE)
#define CD_MASK_MFACE		(1 << CD_MFACE)
#define CD_MASK_MTFACE		(1 << CD_MTFACE)
#define CD_MASK_MCOL		(1 << CD_MCOL)
#define CD_MASK_ORIGINDEX	(1 << CD_ORIGINDEX)
#define CD_MASK_NORMAL		(1 << CD_NORMAL)
#define CD_MASK_FLAGS		(1 << CD_FLAGS)
#define CD_MASK_PROP_FLT	(1 << CD_PROP_FLT)
#define CD_MASK_PROP_INT	(1 << CD_PROP_INT)
#define CD_MASK_PROP_STR	(1 << CD_PROP_STR)
#define CD_MASK_ORIGSPACE	(1 << CD_ORIGSPACE)
#define CD_MASK_ORCO		(1 << CD_ORCO)
#define CD_MASK_MTEXPOLY	(1 << CD_MTEXPOLY)
#define CD_MASK_MLOOPUV		(1 << CD_MLOOPUV)
#define CD_MASK_MLOOPCOL	(1 << CD_MLOOPCOL)
#define CD_MASK_TANGENT		(1 << CD_TANGENT)
#define CD_MASK_MDISPS		(1 << CD_MDISPS)
#define CD_MASK_WEIGHT_MCOL	(1 << CD_WEIGHT_MCOL)
#define CD_MASK_CLOTH_ORCO	(1 << CD_CLOTH_ORCO)
#define CD_MASK_RECAST		(1 << CD_RECAST)

/* CustomData.flag */

/* indicates layer should not be copied by CustomData_from_template or
 * CustomData_copy_data */
#define CD_FLAG_NOCOPY    (1<<0)
/* indicates layer should not be freed (for layers backed by external data) */
#define CD_FLAG_NOFREE    (1<<1)
/* indicates the layer is only temporary, also implies no copy */
#define CD_FLAG_TEMPORARY ((1<<2)|CD_FLAG_NOCOPY)
/* indicates the layer is stored in an external file */
#define CD_FLAG_EXTERNAL  (1<<3)
/* indicates external data is read into memory */
#define CD_FLAG_IN_MEMORY (1<<4)

/* Limits */
#define MAX_MTFACE 8
#define MAX_MCOL   8

//------------------------------------
//DNA_meshdata_types
//------------------------------------
typedef struct MFace {
	unsigned int v1, v2, v3, v4;
	short mat_nr;
	char edcode, flag;
} MFace;

typedef struct MEdge {
	unsigned int v1, v2;
	char crease, bweight;
	short flag;
} MEdge;

typedef struct MDeformWeight {
	int				def_nr;
	float			weight;
} MDeformWeight;

typedef struct MDeformVert {
	struct MDeformWeight *dw;
	int totweight;
	int flag;
} MDeformVert;

typedef struct MVert {
	float	co[3];
	short	no[3];
	char flag, bweight;
} MVert;

/* at the moment alpha is abused for vertex painting and not used for transperency */
typedef struct MCol {
	char a, r, g, b;	
} MCol;

typedef struct MTexPoly{
	struct Image *tpage;
	char flag, transp;
	short mode,tile,unwrap;
}MTexPoly;

typedef struct MLoopUV{
	float uv[2];
}MLoopUV;

typedef struct MLoopCol{
	char a, r, g, b;
	int pad;
}MLoopCol;

typedef struct MSticky {
	float co[2];
} MSticky;

typedef struct MSelect {
	int index;
	int type;
} MSelect;

typedef struct MTFace {
	float uv[4][2];
	struct Image *tpage;
	char flag, transp;
	short mode, tile, unwrap;
} MTFace;

/*Custom Data Properties*/
typedef struct MFloatProperty{
	float	f;
} MFloatProperty;
typedef struct MIntProperty{
	int		i;
} MIntProperty;
typedef struct MStringProperty{
	char	s[256];
} MStringProperty;

typedef struct OrigSpaceFace {
	float uv[4][2];
} OrigSpaceFace;

typedef struct MDisps {
	int totdisp;
	char pad[4];
	float (*disps)[3];
} MDisps;

/* Multires structs for compatibility with old files */
typedef struct MultiresCol {
	float a, r, g, b;
} MultiresCol;

typedef struct MultiresColFace {
	/* vertex colors */
	MultiresCol col[4];
} MultiresColFace;

typedef struct MultiresFace {
	unsigned int v[4];
	unsigned int mid;
	char flag, mat_nr, pad[2];
} MultiresFace;

typedef struct MultiresEdge {
	unsigned int v[2];
	unsigned int mid;
} MultiresEdge;

struct MultiresMapNode;
typedef struct MultiresLevel {
	struct MultiresLevel *next, *prev;

	MultiresFace *faces;
	MultiresColFace *colfaces;
	MultiresEdge *edges;

	unsigned int totvert, totface, totedge, pad;

	MVert *verts;
} MultiresLevel;

typedef struct Multires {
	ListBase levels;
	MVert *verts;

	unsigned char level_count, current, newlvl, edgelvl, pinlvl, renderlvl;
	unsigned char use_col, flag;

	/* Special level 1 data that cannot be modified from other levels */
	CustomData vdata;
	CustomData fdata;
	short *edge_flags;
	char *edge_creases;
} Multires;


typedef struct MRecast{
	int		i;
} MRecast;

/* mvert->flag (1=SELECT) */
#define ME_SPHERETEST		2
#define ME_VERT_TMP_TAG		4
#define ME_HIDE				16
#define ME_VERT_MERGED		(1<<6)
#define ME_VERT_PBVH_UPDATE	(1<<7)

/* medge->flag (1=SELECT)*/
#define ME_EDGEDRAW			(1<<1)
#define ME_SEAM				(1<<2)
#define ME_FGON				(1<<3)
						/* reserve 16 for ME_HIDE */
#define ME_EDGERENDER		(1<<5)
#define ME_LOOSEEDGE		(1<<7)
#define ME_SHARP			(1<<9)    /* only reason this flag remains a 'short' */

/* puno = vertexnormal (mface) */
/* render assumes flips to be ordered like this */
#define ME_FLIPV1		1
#define ME_FLIPV2		2
#define ME_FLIPV3		4
#define ME_FLIPV4		8
#define ME_PROJXY		16
#define ME_PROJXZ		32
#define ME_PROJYZ		64

/* edcode (mface) */
#define ME_V1V2			1
#define ME_V2V3			2
#define ME_V3V1			4
#define ME_V3V4			4
#define ME_V4V1			8

/* flag (mface) */
#define ME_SMOOTH			1
#define ME_FACE_SEL			2
						/* flag ME_HIDE==16 is used here too */ 
/* mselect->type */
#define ME_VSEl	0
#define ME_ESEl 1
#define ME_FSEL 2

/* mtface->flag */
#define TF_SELECT	1 /* use MFace hide flag (after 2.43), should be able to reuse after 2.44 */
#define TF_ACTIVE	2 /* deprecated! */
#define TF_SEL1		4
#define TF_SEL2		8
#define TF_SEL3		16
#define TF_SEL4		32
#define TF_HIDE		64 /* unused, same as TF_SELECT */

/* mtface->mode */
#define TF_DYNAMIC		1
#define TF_ALPHASORT	2
#define TF_TEX			4
#define TF_SHAREDVERT	8
#define TF_LIGHT		16

#define TF_CONVERTED 32 /* tface converted to material */

#define TF_SHAREDCOL	64
#define TF_TILES		128		/* deprecated */
#define TF_BILLBOARD	256
#define TF_TWOSIDE		512
#define TF_INVISIBLE	1024

#define TF_OBCOL		2048
#define TF_BILLBOARD2	4096	/* with Z axis constraint */
#define TF_SHADOW		8192
#define TF_BMFONT		16384

/* mtface->transp, values 1-4 are used as flags in the GL, WARNING, TF_SUB cant work with this */
#define TF_SOLID	0
#define TF_ADD		1
#define TF_ALPHA	2
#define TF_CLIP		4 /* clipmap alpha/binary alpha all or nothing! */

/* sub is not available in the user interface anymore */
#define TF_SUB		3


/* mtface->unwrap */
#define TF_DEPRECATED1	1
#define TF_DEPRECATED2	2
#define TF_DEPRECATED3	4
#define TF_DEPRECATED4	8
#define TF_PIN1		    16
#define TF_PIN2		    32
#define TF_PIN3	   		64
#define TF_PIN4	    	128

typedef struct Mesh {
	ID id;
	struct AnimData *adt;		/* animation data (must be immediately after id for utilities to use it) */

	struct BoundBox *bb;
	
	struct Ipo *ipo  DNA_DEPRECATED;  /* old animation system, deprecated for 2.5 */
	struct Key *key;
	struct Material **mat;

	struct MFace *mface;	/* array of mesh object mode faces */
	struct MTFace *mtface;	/* store face UV's and texture here */
	struct TFace *tface;	/* depecrated, use mtface */
	struct MVert *mvert;	/* array of verts */
	struct MEdge *medge;	/* array of edges */
	struct MDeformVert *dvert;	/* deformgroup vertices */
	struct MCol *mcol;		/* array of colors, this must be the number of faces * 4 */
	struct MSticky *msticky;
	struct Mesh *texcomesh;
	struct MSelect *mselect;
	
	struct EditMesh *edit_mesh;	/* not saved in file! */

	struct CustomData vdata, edata, fdata;

	int totvert, totedge, totface, totselect;
	
	/* the last selected vertex/edge/face are used for the active face however
	 * this means the active face must always be selected, this is to keep track
	 * of the last selected face and is similar to the old active face flag where
	 * the face does not need to be selected, -1 is inactive */
	int act_face; 

	/* texture space, copied as one block in editobject.c */
	float loc[3];
	float size[3];
	float rot[3];

	short texflag, drawflag;
	short smoothresh, flag;

	short subdiv  DNA_DEPRECATED, subdivr  DNA_DEPRECATED;
	char subsurftype  DNA_DEPRECATED; /* only kept for backwards compat, not used anymore */
	char editflag;

	short totcol;

	struct Multires *mr DNA_DEPRECATED; /* deprecated multiresolution modeling data, only keep for loading old files */
} Mesh;