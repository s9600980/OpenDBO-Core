#include "stdafx.h"
#include "ug_opcodes.h"
#include "GameServer.h"
#include "NtlPacketGM.h"
#include "NtlResultCode.h"
#include "CPlayer.h"
#include "NtlPacketUtil.h"
#include "GameProcessor.h"
#include "PacketEventObj.h"


int CClientSession::OnAccept()
{
	CGameServer * app = (CGameServer*) NtlSfxGetApp();
	//NTL_PRINT(PRINT_APP, "CClientSession::OnAccept() \n");
	cPlayer = NULL;

	m_bSendLogMasterServer = true;
	m_eUserState = NTL_USER_STATE_NONE;
	m_bCashItemInfoLoaded = false;
	m_byChatServerAuthKey = NULL;

	//start handshake (with client)
	unsigned char buf[] = { 0x03, 0x00, 0xac, 0x86, 0xf5, 0x74 };
	CNtlPacket packet(buf, 0x06);
	app->Send(GetHandle(), &packet);
	
	return CNtlSession::OnAccept();
}

void CClientSession::OnClose()
{
	CGameServer * app = (CGameServer*)g_pApp;

	m_eUserState = NTL_USER_STATE_NONE;
	//NTL_PRINT(PRINT_APP, "CClientSession::OnClose() \n");
	if(cPlayer && cPlayer->IsLoggedOut() == false)
	{
		//send to master server that player logged out
		if (m_bSendLogMasterServer == true)
		{
			CNtlPacket packet(sizeof(sGM_LOGOUT_REQ));
			sGM_LOGOUT_REQ * res = (sGM_LOGOUT_REQ *)packet.GetPacketData();
			res->wOpCode = GM_LOGOUT_REQ;
			res->accountId = cPlayer->GetAccountID();
			res->serverChannelId = app->GetGsChannel();
			res->serverId = app->GetGsServerId();
			packet.SetPacketLen(sizeof(sGM_LOGOUT_REQ));
			if (app->SendTo(app->GetMasterServerSession(), &packet) != NTL_SUCCESS)
				ERR_LOG(LOG_GENERAL, "Failed sending logout packet to master server. Account ID %u", cPlayer->GetAccountID());
		}

		if(cPlayer->GetServerTeleportInfo().worldId == INVALID_WORLDID || cPlayer->IsLeaving() == false) //only send logout if we do not switch channel or teleport another one.
			cPlayer->Send_GtUserLeaveGame(CHARLEAVING_DISCONNECT, false, INVALID_SERVERCHANNELID, INVALID_SERVERINDEX);

		cPlayer->SetLoggedOut();
	}

	cPlayer = NULL;
}

int CClientSession::OnDispatch(CNtlPacket * pPacket)
{
	sNTLPACKETHEADER * pHeader = (sNTLPACKETHEADER *)pPacket->GetPacketData();
	if(pHeader->wOpCode == 4)
	{
		unsigned char buf[] = { 0x10, 0x00, 0x84, 0xfb, 0x48, 0xf4, 0x8e, 0x5a, 0xb6, 0x67, 0xe2, 0x3d,
			0x6e, 0x14, 0xb4, 0xa3, 0xc3, 0x24, 0x9e, 0x5f, 0xe3, 0xd1, 0xd5, 0x88, 0x10, 0x0d, 0x68,
			0x4f, 0x3b, 0xa5, 0xed, 0x37, 0xed, 0x4a };
		CNtlPacket packet(buf, 0x22);
		g_pApp->Send(GetHandle(), &packet);		
	}
	if (pHeader->wOpCode > 1 && cPlayer && cPlayer->IsGameMaster()) 
		NTL_PRINT(PRINT_APP, "%u | received opcode %u [%s]", GetHandle(), pHeader->wOpCode, NtlGetPacketName(pHeader->wOpCode));
	
	if (cPlayer)
	{
		if (pHeader->wOpCode == 1)
		{
			cPlayer->SessionPingCount += 1;			
		}
		if (pHeader->wOpCode == 4334)
		{
			if (cPlayer->SessionPingCount <= 17)
			{
				char* username = Ntl_WC2MB(cPlayer->GetCharName());
				NTL_PRINT(PRINT_APP, "Player %s Recived SessionCount %u And GET DISCONECTED BY SPEED HACK", username, cPlayer->SessionPingCount);
				this->Disconnect(false);
			}
			cPlayer->SessionPingCount = 0;
		}
	}
	if (cPlayer == NULL)
	{
		//Finish handshake
		if (m_eUserState == NTL_USER_STATE_NONE)
		{
			m_eUserState = NTL_USER_STATE_ENTERING_GAME;
		}
	}
	else
	{
		if (cPlayer->GetClientSessionID() != GetHandle())
		{
			ERR_LOG(LOG_USER, "Clientsesion ID does not match %u != %u", cPlayer->GetClientSessionID(), GetHandle());
			return NTL_FAIL;
		}
	}
	
	OpcodeHandler<CClientSession> const* opHandle = ug_opcodeTable->LookupOpcode(pHeader->wOpCode);
	if (opHandle)
	{
		if (opHandle->packetProcessing == PROCESS_INPLACE)
			(this->*opHandle->handler)(pPacket);
		else
			g_pGameProcessor->PostClientPacketEvent(new TPacketEventObj<CClientSession>(this, opHandle->handler, GetHandle(), pPacket, GetUniqueHandle()));

		return NTL_SUCCESS;
	}

	return CNtlSession::OnDispatch(pPacket);
}
