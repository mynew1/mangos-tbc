/*
* See AUTHORS file for Copyright information
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "CPlusMgr.h"
#include "CPlayer.h"
#include "ObjectGuid.h"

/* CreatureScript */

CreatureAI* CPlusMgr::GetCreatureAI(Creature* pCreature)
{
    if (CreatureScript* script = m_CreatureScripts.GetScript(pCreature->GetEntry()))
        return script->GetCreatureAI(pCreature);

    return nullptr;
}

bool CPlusMgr::OnGossipHello(Player* pPlayer, Creature* pCreature)
{
    pPlayer->PlayerTalkClass->ClearMenus();

    if (CreatureScript* script = m_CreatureScripts.GetScript(pCreature->GetEntry()))
        return script->OnGossipHello(pPlayer, pCreature);

    return false;
}

bool CPlusMgr::OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action, std::string code)
{
    pPlayer->PlayerTalkClass->ClearMenus();

    if (CreatureScript* script = m_CreatureScripts.GetScript(pCreature->GetEntry()))
        return script->OnGossipSelect(pPlayer, pCreature, sender, action, code);

    return false;
}

bool CPlusMgr::OnQuestAccept(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
{
    if (CreatureScript* script = m_CreatureScripts.GetScript(pCreature->GetEntry()))
        return script->OnQuestAccept(pPlayer, pCreature, pQuest);

    return false;
}

bool CPlusMgr::OnQuestRewarded(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
{
    if (CreatureScript* script = m_CreatureScripts.GetScript(pCreature->GetEntry()))
        return script->OnQuestRewarded(pPlayer, pCreature, pQuest);

    return false;
}

uint32 CPlusMgr::GetDialogStatus(Player* pPlayer, Creature* pCreature)
{
    if (CreatureScript* script = m_CreatureScripts.GetScript(pCreature->GetEntry()))
        return script->GetDialogStatus(pPlayer, pCreature);

    return 0;
}

/* GameObjectScript */

bool CPlusMgr::OnGameObjectUse(Player* pPlayer, GameObject* pGameObject)
{
    if (GameObjectScript* script = m_GameObjectScripts.GetScript(pGameObject->GetEntry()))
        return script->OnGameObjectUse(pPlayer, pGameObject);

    return false;
}

bool CPlusMgr::OnGossipHello(Player* pPlayer, GameObject* pGameObject)
{
    if (GameObjectScript* script = m_GameObjectScripts.GetScript(pGameObject->GetEntry()))
        return script->OnGossipHello(pPlayer, pGameObject);

    return false;
}

bool CPlusMgr::OnGossipSelect(Player* pPlayer, GameObject* pGameObject, uint32 sender, uint32 action, std::string code)
{
    if (GameObjectScript* script = m_GameObjectScripts.GetScript(pGameObject->GetEntry()))
        return script->OnGossipSelect(pPlayer, pGameObject, sender, action, code);

    return false;
}

bool CPlusMgr::OnQuestAccept(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest)
{
    if (GameObjectScript* script = m_GameObjectScripts.GetScript(pGameObject->GetEntry()))
        return script->OnQuestAccept(pPlayer, pGameObject, pQuest);

    return false;
}

bool CPlusMgr::OnQuestRewarded(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest)
{
    if (GameObjectScript* script = m_GameObjectScripts.GetScript(pGameObject->GetEntry()))
        return script->OnQuestRewarded(pPlayer, pGameObject, pQuest);

    return false;
}

uint32 CPlusMgr::GetDialogStatus(Player* pPlayer, GameObject* pGameObject)
{
    if (GameObjectScript* script = m_GameObjectScripts.GetScript(pGameObject->GetEntry()))
        return script->GetDialogStatus(pPlayer, pGameObject);

    return false;
}

/* ItemScript */

bool CPlusMgr::OnGossipSelect(Player* pPlayer, Item* pItem, uint32 sender, uint32 action, std::string code)
{
    // PlayerScript
    if (uint32 scriptid = pPlayer->GetCPlayer()->GetScriptID())
    {
        if (PlayerScript* script = m_PlayerScripts.GetScript(scriptid))
        {
            pPlayer->GetCPlayer()->SetScriptID(0);
            return script->OnGossipSelect(pPlayer, sender, action, code);
        }
    }
    // ItemScript
    if (ItemScript* script = m_ItemScripts.GetScript(pItem->GetEntry()))
        return script->OnGossipSelect(pPlayer, pItem, sender, action, code);

    return false;
}

bool CPlusMgr::OnQuestAccept(Player* pPlayer, Item* pItem, Quest const* pQuest)
{
    if (ItemScript* script = m_ItemScripts.GetScript(pItem->GetEntry()))
        return script->OnQuestAccept(pPlayer, pItem, pQuest);

    return false;
}

bool CPlusMgr::OnItemUse(Player* pPlayer, Item* pItem, SpellCastTargets const& targets)
{
    if (ItemScript* script = m_ItemScripts.GetScript(pItem->GetEntry()))
        return script->OnItemUse(pPlayer, pItem, targets);

    return false;
}

/* PlayerScript */

ObjectGuid PlayerScript::GetHearthStoneOrPlayerGuid(Player* pPlayer)
{
    for (uint8 i = INVENTORY_SLOT_ITEM_START; i < INVENTORY_SLOT_ITEM_END; ++i)
    if (Item* pItem = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
    if (pItem->GetEntry() == 6948)
        return pItem->GetObjectGuid();

    return pPlayer->GetObjectGuid();
}

bool CPlusMgr::OnGossipHello(Player* pPlayer)
{
    if (uint32 scriptid = pPlayer->GetCPlayer()->GetScriptID())
    {
        if (PlayerScript* script = m_PlayerScripts.GetScript(scriptid))
        {
            pPlayer->GetCPlayer()->SetScriptID(0);
            return script->OnGossipHello(pPlayer);
        }
    }

    return false;
}

bool CPlusMgr::OnGossipSelect(Player* pPlayer, uint32 sender, uint32 action, std::string code)
{
    if (uint32 scriptid = pPlayer->GetCPlayer()->GetScriptID())
    {
        if (PlayerScript* script = m_PlayerScripts.GetScript(scriptid))
        {
            pPlayer->GetCPlayer()->SetScriptID(0);
            return script->OnGossipSelect(pPlayer, sender, action, code);
        }
    }

    return false;
}