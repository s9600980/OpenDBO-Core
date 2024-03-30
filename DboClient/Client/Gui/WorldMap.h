/******************************************************************************
* File			: CWorldMapGui.h
* Author		: Hong Sungbock
* Copyright		: (��)NTL
* Date			: 2007. 2. 1
* Update		: 2007. 12. 6 by Hong Sungbock(������ �߰�)
* Abstract		: 
*****************************************************************************
* Desc			: CWorldMapGui

*****************************************************************************/

#pragma once

// core
#include "ceventhandler.h"

// share
#include "WorldMapTable.h"

// presentation
#include "NtlPLGui.h"

// trigger
#include "DboTSCoreDefine.h"

// simulation
#include "NtlSharedType.h"
#include "NtlParty.h"
#include "NtlSlDef.h"
#include "NtlOtherParam.h"

// dbo
#include "SurfaceGui.h"
#include "Windowby3.h"

class CNtlSobAvatar;
struct sLAND_MARK_TBLDAT;
class CQuestSearchGui;


class CWorldMapGui : public CNtlPLGui, public RWS::CEventHandler
{
public:
	enum eWorldMapDefinedValue
	{
		MAX_LANDMARK_NAME				= 30,
	};

	enum eLandMarkType
	{
		LMS_TYPE_1,
		LMS_TYPE_2,
		LMS_TYPE_3,
		LMS_TYPE_4,

		NUM_LMT
	};

	// The bigger the terrain, the sooner the index is, the later the area check will be.
	enum eMainWorldFocusType
	{
		MWFT_YAHOI_WEST,
		MWFT_YAHOI_EAST,
		MWFT_KARIN,
		MWFT_PORUNGAROCKS,
		MWFT_FRANGFRANG,
		MWFT_MUSH_NORTH,
		MWFT_WESTLAND,
		MWFT_MUSH_SOUTH,
		MWFT_PORUNGAROCKS_SOUTH,
		MWFT_FRANGFRANG_SOUTH,
		MWFT_PAPAYA,

		NUM_MWFT,

		MWFT_NONE
	};	

	enum eMapDboRate // Not true scale
	{
		MAP_DBO_1,
		MAP_DBO_1_25,
		MAP_DBO_1_5,
		MAP_DBO_2,
		MAP_DBO_4,

		NUM_MAP_DBO
	};

	enum eBusMarkType
	{
		BUS_MARK_NORMAL,
		BUS_MARK_GET_ON,

		NUM_BUS_MARK
	};

	enum eBusDirectionType
	{
		BUS_DIRECTION_NORTH,
		BUS_DIRECTION_NORTH_EAST,
		BUS_DIRECTION_EAST,
		BUS_DIRECTION_SOUTH_EAST,
		BUS_DIRECTION_SOUTH,
		BUS_DIRECTION_SOUTH_WEST,
		BUS_DIRECTION_WEST,
		BUS_DIRECTION_NORTH_WEST,

		NUM_BUS_DIRECTION,
	};
	
	enum eCampPeopleType
	{
		CAMP_PEOPLE_MY_PARTY,
		CAMP_PEOPLE_MY_TEAM,
		CAMP_PEOPLE_EMENY_TEAM,

		NUM_CAMP_PEOPLE
	};

	struct LandMarkInfo
	{
		RwBool			bShowLandMark;
		RwUInt32		uiTableIndex;
		RwInt32			iPosX;
		RwInt32			iPosY;
		
		gui::CTexture*	pTexture;
		gui::CTexture*	pFocusingTexture;
		sLAND_MARK_TBLDAT* pLAND_MARK_TBLDAT;

		LandMarkInfo()
		:pTexture(NULL)
		,pFocusingTexture(NULL)
		,pLAND_MARK_TBLDAT(NULL)
		{

		}
	};

	struct sWorldMapFocusRect
	{
		CSurfaceGui		surface;
		CRectangle		rtClick;
		TBLIDX			mapID;
		ZONEID			zoneID;
	};

	struct sPARTYMEMBER
	{
		RwV2d				v2Pos;
		RwBool				bShow;
		WCHAR*				pwcName;
	};

	struct sCAMP_PEOPLE				///< ������ ������ ����鳢�� �ο�� �Ǵ� ���
	{
		CPos				v2Pos;
		eCampPeopleType		ePeopleType;
		const WCHAR*		pwcName;
	};

	struct sNEXT_QUEST
	{
		CPos				position;
		RwBool				bShow;
		eQMI_TARGET_TYPE	eTargetType;
		WORLDID				WorldID;
		const WCHAR*		pwcText;
	};

	struct sBindMarkInfo
	{
		RwBool				bShow;
		RwV3d				v3Pos;
		RwUInt8				byBindType;
		WORLDID				WorldID;
	};

	struct sWarFog
	{
		RwBool				bShow;
		RwUInt32			uiWarfogIndex;
		CSurfaceGui			srfWarFog;
	};

	struct sWarFogDisappearEvent
	{
		RwBool				bActiveEffect;
		RwUInt32			uiWarfogIndex;
		RwReal				fRemainTime;
		RwReal				fElapsed;
	};

	struct sBusPosition
	{
		CPos				position;
		SERIAL_HANDLE		hBus;
		eBUS_SHAPE_TYPE		eBusShapeType;
		eBusDirectionType	eBusDirection;
	};

	struct sSCRAMBLE_SEAL_MARK
	{
		eDBO_TEAM			eTeamState;
		RwBool				bShow;
		RwV3d				v3Pos;
		CPos				position;
		std::wstring		wstrName;
	};

	struct sSCRAMBLE_VISIBLE
	{
		RwBool				bScramble;
		RwBool				bShowOurTeam;
		RwBool				bShowOurTeamMiniMap;
		RwBool				bShowOtherTeam;
		RwBool				bShowOtherTeamMiniMap;
	};

	typedef std::list<sCAMP_PEOPLE>					LIST_CAMP;

	typedef std::list<sNEXT_QUEST>					NEXTQUEST_LIST;
	typedef std::list<sNEXT_QUEST>::iterator		NEXTQUEST_ITER;

	typedef std::list<LandMarkInfo>					LANDMARK_LIST;
	typedef std::list<LandMarkInfo>::iterator		LANDMARK_ITER;

	typedef std::map<SERIAL_HANDLE, sBusPosition>				BUS_POS_MAP;
	typedef std::map<SERIAL_HANDLE, sBusPosition>::iterator		BUS_POS_ITER;

	typedef std::map<RwUInt32, sSCRAMBLE_SEAL_MARK*>			MAP_SCRAMBLE_SEAL_MARK;


	CWorldMapGui(const RwChar* pName);
	virtual ~CWorldMapGui();

	RwBool		Create();
	VOID		Update(RwReal fElapsed);
	VOID		Destroy();
	
	RwInt32		SwitchDialog(bool bOpen);		///< DialogManager������ Open/Close

protected:
	CWorldMapGui() {};
	virtual VOID	HandleEvents( RWS::CMsg &msg );

	VOID			SetAlpha(RwUInt8 byAlpha);
	RwUInt8			GetAlpha();

	RwBool			AnalysisAreaInfo();
	RwBool			LoadingMapSurface(RwUInt8 byMapMode);
	VOID			LoadingWorldFocus();
	VOID			LoadingLandMark();
	VOID			LoadSearchQuest();

	RwBool			UpdateChangeZoneMap(RwReal fElapsed);
	VOID			UpdateWarfogEffect(RwReal fElapsed);
	VOID			UpdateAvatarMark(CNtlSobAvatar* pAvatar);
	VOID			UpdatePartyMemberMark(CNtlSobAvatar* pAvatar);
	VOID			UpdateCampPeople(CNtlSobAvatar* pAvatar);
	VOID			UpdateBusPosition();
	VOID			UpdateNextQuestMark();	
	VOID			UpdateBindInfo();	
	VOID			UpdateWarFog();

	VOID			UpdateScrambleSeal();

	VOID			SetLandMarkNamePosition(gui::CStaticBox* pStatic, RwInt32 iX, RwInt32 iY, RwInt32 iLandMarkSize);	
	sWORLD_MAP_TBLDAT*	GetWorldMapTable(RwUInt32 uiWorldID, RwUInt32 uiZoneID);
	VOID			GetAvatarMarkPosition(RwInt32& iOutputX, RwInt32& iOutputY, CNtlSobAvatar* pAvatar);

	// ����� ��ǥ�� �Է��Ͽ� ����� ��忡 ���� 2D��ǥ�� �����ش�
	VOID			GetMapPos_from_RealPos(RwReal fX, RwReal fZ, RwInt32& iX, RwInt32& iY);

	VOID			LocateComponent();
	VOID			CheckInfoWindow();
	RwReal			GetAngle(RwV3d v3Dir);			///< 12�� ������ �������� �ð���� ����

	VOID			UnLoadWorldFocus();
	VOID			UnloadLandMark();
	VOID			UnloadWarFogTexture();
	VOID			UnloadQuestSearch();

	VOID			ClearSeal();
	RwBool			IsinMap(RwInt32 iPosX, RwInt32 iPosY);	
	RwBool			CanRenderBus();
	RwBool			CanRenderBusRoute();
	VOID			ShowBusRouteComponent(bool bShow);
	VOID			ShowScrambleCampComponent(bool bShow);
	eBusDirectionType	GetBusDirectionType(RwReal fAngle);

	BOOL			IsWarfogActive(WORD wWarfogIndex);


	VOID			OnClicked_CloseButton(gui::CComponent* pComponent);

	VOID			OnToggle_QuestInfoButton(gui::CComponent* pComponent, bool bToggled);
	VOID			OnToggle_PopoStoneButton(gui::CComponent* pComponent, bool bToggled);
	VOID			OnToggle_PortalButton(gui::CComponent* pComponent, bool bToggled);

	VOID			OnToggle_BusRouteButton(gui::CComponent* pComponent, bool bToggled);
	VOID			OnToggle_VisibleOurGuildMemberButton(gui::CComponent* pComponent, bool bToggled);
	VOID			OnToggle_VisibleOurGuildMemberMiniMapButton(gui::CComponent* pComponent, bool bToggled);
	VOID			OnToggle_VisibleOtherGuildMemberButton(gui::CComponent* pComponent, bool bToggled);
	VOID			OnToggle_VisibleOtherGuildMemberMiniMapButton(gui::CComponent* pComponent, bool bToggled);

	VOID			OnScrollChanged(RwInt32 iOffset);
	VOID			OnPaint();
	VOID			OnPostPaint();
	VOID			OnMouseDown(const CKey& key);
	VOID			OnMouseUp(const CKey& key);
	VOID			OnMove(RwInt32 iOldX, RwInt32 iOldY );
	VOID			OnResize(RwInt32 iOldW, RwInt32 iOldH );
	VOID			OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY);
	VOID			OnMouseLeave(gui::CComponent* pComponent);

protected:
	gui::CSlot			m_slotMouseDown;
	gui::CSlot			m_slotMouseUp;
	gui::CSlot			m_slotMove;
	gui::CSlot			m_slotResize;
	gui::CSlot			m_slotMouseMove;
	gui::CSlot			m_slotMouseLeave;
	gui::CSlot			m_slotPaint;
	gui::CSlot			m_slotPostPaint;
	gui::CSlot			m_slotCloseButton;

	gui::CSlot			m_slotQuestInfoToggle;
	gui::CSlot			m_slotPopoStoneToggle;
	gui::CSlot			m_slotPortalToggle;
	gui::CSlot			m_slotBusRouteToggle;


	gui::CSlot			m_slotVisibleOurGuildMemberButton;
	gui::CSlot			m_slotVisibleOurGuildMemberMiniMapButton;
	gui::CSlot			m_slotVisibleOtherGuildMemberButton;
	gui::CSlot			m_slotVisibleOtherGuildMemberMiniMapButton;
	gui::CSlot			m_slotTab;
	gui::CSlot			m_slotAlphaScrollChanged;
	gui::CSlot			m_slotAlphaScrollSliderMoved;

	gui::CStaticBox*	m_pDialogName;
	gui::CStaticBox*	m_pRegionName;
	gui::CStaticBox*	m_pstbRecommendedLevel;
	gui::CStaticBox*	m_pLandMarkName[MAX_LANDMARK_NAME];

	gui::CComboBox*		m_pcbbSearchWorld;

	gui::CComboBox*		m_pcbbSearchZone;

	gui::CComboBox*		m_pcbbSearchCity;

	gui::CComboBox*		m_pcbbSearchNpc;

	gui::CStaticBox*	m_pBusRoute;			/// "���� �뼱��"
	gui::CStaticBox*	m_pOurGuild;			/// "�츮 ����"
	gui::CStaticBox*	m_pOtherGuild;			/// "��� ����"
	gui::CStaticBox*	m_pTransparency;		/// "����"

	gui::CScrollBar*	m_pAlphaScrollbar;

	gui::CButton*		m_pExitButton;			///< â�ݱ� ��ư
	gui::CButton*		m_pBusRouteButton;
	gui::CButton*		m_pVisibleOurGuildMemberButton;
	gui::CButton*		m_pVisibleOurGuildMemberMiniMapButton;
	gui::CButton*		m_pVisibleOtherGuildMemberButton;	
	gui::CButton*		m_pVisibleOtherGuildMemberMiniMapButton;

	CWindowby3			m_MapFrameUp;			///< ������� Ʋ ���
	CSurfaceGui			m_MapFrameLC;			///< ������� Ʋ ���ߴ�
	CSurfaceGui			m_MapFrameRC;			///< ������� Ʋ ���ߴ�
	CWindowby3			m_MapFrameDown;			///< ������� Ʋ �ϴ�

	CSurfaceGui			m_surBack;				///< ��� �����̽�
	CSurfaceGui			m_srfMap;				///< �� �����̽�
	CSurfaceGui			m_srfBusRoute;			///< ���� �뼱 �����̽�
	CSurfaceGui			m_surMarkBus[NUM_BUS_SHAPE_TYPE][NUM_BUS_MARK][NUM_BUS_DIRECTION];	///< ���� ��ũ
	CSurfaceGui			m_surMarkAvatar;		///< �ƹ�Ÿ ��ũ
	CSurfaceGui			m_surMarkPartryMember;	///< ��Ƽ�� ��ũ
	CSurfaceGui			m_surLandMark[NUM_LMT];	///< ���� ��ũ
	CSurfaceGui			m_surNextQuestMark[NUM_eQMI_TARGET_TYPE];///< ���� ���� ����Ʈ ��ũ
	CSurfaceGui			m_surBindMark;			///< ���ε� ��ũ
	CSurfaceGui			m_surDboRate[NUM_MAP_DBO];	///< DBO ������ ����
	CSurfaceGui			m_surCamp[NUM_CAMP_PEOPLE];///< (�ǾƱ���)���� ����� �ο�� ����� �����
	CSurfaceGui			m_surScrambleSeal[NUM_DBO_TEAM];	///< ������ ����

	CSurfaceGui			m_srfQTSlotIcon[10];
	CSurfaceGui			m_srfQTSlotIconWorld;

	CSurfaceGui			m_srfPortal_Man;
	CSurfaceGui			m_srfPortalUnRegMark;

	gui::CFlash*		m_pflaScanQuest;
	gui::CFlash*		m_pflaScanNpc;
	gui::CFlash*		m_pflaScanRader;
	gui::CFlash*		m_pflaScanRaderRange;

	gui::CStaticBox*	m_pstbQuestInfo;
	gui::CButton*		m_pbtnQuestInfoOnOff;

	gui::CStaticBox*	m_pstbPopoStone;
	gui::CButton*		m_pbtnPopoStone;

	gui::CStaticBox*	m_pstbPortal;
	gui::CButton*		m_pbtnPortal;

	gui::CComponent*	m_pDummy;				///< for Post render

	RwUInt8				m_byFocusArea;			///< ��Ŀ�� �ǰ� �ִ� ����� ��Ŀ�� �̹��� �ε���(���� �� �ε����� �������)
	ZONEID				m_FocusZoneID;			///< Zone index being focused
	TBLIDX				m_FocusMapID;			///< World map index being focused
	sWorldMapFocusRect	m_aMainWorldFocus[NUM_MWFT];///< ���ο����� ��Ŀ��

	RwUInt8				m_byMapMode;			///< �� ���
	RwReal				m_fElapsedTime;			///< ������Ʈ Ÿ��
	RwReal				m_fElapsedTestChangeZone;///< ���� �ٲ���� �˻��ϴ� �ð�
	RwReal				m_fMapScale;			///< �� ������
	RwUInt8				m_byDboRateType;		///< �� ��ô�� �ƴ� ������ ����

	RwUInt32			m_uiFocusLandMarkIndex;	///< ��Ŀ�̵ǰ� �ִ� ���帶ũ �ε���
	ZONEID				m_uiPressedZoneIndex;	///< ZONE Index of mouse down zone
	TBLIDX				m_uiPressedMapIndex;	///< World Index of mouse down zone
	RwBool				m_bRightMouse;			///< ���콺 ������
	RwBool				m_bChangedMap_by_User;	///< ������ ó���� ���� �ʿ��� �ٸ� ������ �ٲپ� ����
	
	RwInt32				m_iMapStartX, m_iMapStartY; ///< ���� �� ����

	TBLIDX				m_uiRenderingWorldID;	///< The world ID of the area being drawn on the screen
	ZONEID				m_uiRenderingZoneID;	///< ȭ�鿡 �׷����� �ִ� ������ �� ���̵�

	TBLIDX				m_uiActiveWorldID;		///< World ID where the avatar is located
	ZONEID				m_uiActiveZoneID;		///< �ƹ�Ÿ�� ��ġ�� �� ID

	RwV2d				m_v2MapPos;				///< �������� �Ǵ� ���� �»�� ��ġ
	sPARTYMEMBER		m_aPartyMember[NTL_MAX_MEMBER_IN_PARTY - 1]; ///< ��Ƽ�� ��ġ

	sWarFogDisappearEvent m_WarFogDisappearEvent;	///< ������ �����͸� �޾Ƽ� ������� �̺�Ʈ ������
	sSCRAMBLE_VISIBLE	m_tScrambleVisible;


	BUS_POS_MAP			m_mapBusPos;
	LIST_CAMP			m_listCamp;				///< (�ǾƱ���)���� ����� �ο�� ����� �����
	NEXTQUEST_LIST		m_listNextQuest;
	LANDMARK_LIST		m_listLandMark;			///< ���帶ũ ��ġ
	sBindMarkInfo		m_BindInfo;				///< ���ε� ��ġ ����
	sWarFog				m_WarFog[DBO_WORLD_MAP_TABLE_COUNT_WORLD_WARFOG];///< �� ���� ����
	CQuestSearchGui*	m_pQuestSearch;			///< ����Ʈ ��ġ gui
	MAP_SCRAMBLE_SEAL_MARK	m_mapScrambleSealMark;
};