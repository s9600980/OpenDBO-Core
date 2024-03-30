/******************************************************************************
* File			: QuestSearchGui.h
* Author		: Hong SungBock
* Copyright		: (��)NTL
* Date			: 2008. 5. 6
* Abstract		: 
*****************************************************************************
* Desc			: ��ī���� �޴����� �޴��� �����Ͽ� ������ ���� ����Ʈ
*				  ��ġ�� �Ѵ�
*****************************************************************************/

#pragma once

// presentation
#include "NtlPLGui.h"

// dbo
#include "SurfaceGui.h"

class CQuestSearchGui : public CNtlPLGui
{
public:
	struct sQuestInfo
	{
		std::wstring		wstrNPCName;
		std::list<std::wstring> listQuestTitle;
		RwReal				fXPos, fZPos;
		gui::CFlash*		pFlash;
	};

	typedef std::map<RwUInt32, sQuestInfo*>				MAP_QUEST_INFO;
	typedef std::map<RwUInt32, sQuestInfo*>::iterator	ITER_QUEST_INFO;

	CQuestSearchGui(const RwChar* pName);
	virtual ~CQuestSearchGui();

	RwBool		Create(RwReal fMapScale, gui::CComponent* parentComponent);
	VOID		Update(RwReal fElapsed);
	VOID		Destroy();
	
	VOID		SetArea(const CRectangle& rtWorldMap, RwReal fMapScale, const RwV2d& v2MapPos, RwInt32 iAvatarXPos_in_Map, RwInt32 iAvatarYPos_in_Map);
	VOID		ResetArea(const CRectangle& rtWorldMap, RwReal fMapScale, const RwV2d& v2MapPos);

protected:
	CQuestSearchGui() {}

	RwBool			IsSameZoneWithAvatar(RwUInt32 uiAvatarMapCode, RwReal fXPos, RwReal fZPos);

	RwBool			SetQuestInfo();

	VOID			OnMovieEnd(gui::CComponent* pComponent);
	VOID			OnMouseMove(RwInt32 nFlags, RwInt32 nX, RwInt32 nY);
	VOID			OnMouseLeave(gui::CComponent* pComponent);

protected:
	gui::CSlot			m_slotMovieEnd;
	gui::CSlot			m_slotMouseMove;
	gui::CSlot			m_slotMouseLeave;

	gui::CFlash*		m_pFlashSearch;

	RwV2d				m_v2MapPos;				///< �������� �Ǵ� ���� �»�� ��ġ
	RwInt32				m_iAvatarXPos, m_iAvatarYPos;
	MAP_QUEST_INFO		m_mapQuestInfo;
};