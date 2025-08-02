local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nObjective_PlayerHealthDrain = L0_1
L0_1 = nObjective_PlayerHealthDrain
L0_1.namespace = "nObjective_PlayerHealthDrain"
L0_1 = nObjective_PlayerHealthDrain
L1_1 = nUtil
L1_1 = L1_1.ToGUID
L2_1 = "0x098cd816"
L1_1 = L1_1(L2_1)
L0_1.descriptionText = L1_1
L0_1 = nObjective_PlayerHealthDrain
L1_1 = nObjectiveEvents
L1_1 = L1_1.Damage
L0_1.handledEvents = L1_1
L0_1 = nObjective_PlayerHealthDrain
L0_1.goldDeaths = 0
L0_1 = nObjective_PlayerHealthDrain
L0_1.silverDeaths = 1
L0_1 = nObjective_PlayerHealthDrain
L0_1.bronzeDeaths = 2
L0_1 = nObjective
L0_1 = L0_1.RegisterObjective
L1_1 = "PlayerHealthDrain"
L2_1 = nObjective_PlayerHealthDrain
L0_1(L1_1, L2_1)
L0_1 = nObjective_PlayerHealthDrain
L1_1 = nObjectiveFns
L1_1 = L1_1.Init

function L2_1()
  local L0_2, L1_2
  L0_2 = nThreadData
  L0_2 = L0_2.CreatePrivateTable
  L0_2()
end

L0_1[L1_1] = L2_1
L0_1 = nObjective_PlayerHealthDrain
L1_1 = nObjectiveFns
L1_1 = L1_1.HandleEvent

function L2_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2
  L2_2 = nObjectiveEvents
  L2_2 = L2_2.Death
  if A0_2 == L2_2 then
    L2_2 = nObjective
    L2_2 = L2_2.GetObjectiveEventGUIDData
    L3_2 = A1_2
    L4_2 = 1
    L2_2 = L2_2(L3_2, L4_2)
    L3_2 = nObjective
    L3_2 = L3_2.GetObjectiveEventGUIDData
    L4_2 = A1_2
    L5_2 = 2
    L3_2 = L3_2(L4_2, L5_2)
    L4_2 = nPlayer
    L4_2 = L4_2.IsPlayerControlledObject
    L5_2 = L2_2
    L4_2 = L4_2(L5_2)
    if L4_2 then
      L4_2 = kObjIDNone
      if L3_2 == L4_2 then
        L4_2 = nPlayer
        L4_2 = L4_2.GetPlayerIdForObject
        L5_2 = L2_2
        L4_2 = L4_2(L5_2)
        L5_2 = nThreadData
        L5_2 = L5_2.GetPrivateTable
        L5_2 = L5_2()
        L6_2 = L5_2[L4_2]
        if L6_2 == nil then
          L5_2[L4_2] = 1
        else
          L6_2 = L5_2[L4_2]
          L6_2 = L6_2 + 1
          L5_2[L4_2] = L6_2
        end
        L6_2 = nObjective
        L6_2 = L6_2.SetObjectiveIntData
        L7_2 = L4_2
        L8_2 = 0
        L9_2 = L5_2[L4_2]
        L10_2 = true
        L11_2 = false
        L6_2(L7_2, L8_2, L9_2, L10_2, L11_2)
      end
    end
  end
end

L0_1[L1_1] = L2_1
L0_1 = nObjective_PlayerHealthDrain
L1_1 = nObjectiveFns
L1_1 = L1_1.ObjectiveStatus

function L2_1(A0_2)
  local L1_2, L2_2, L3_2
  L1_2 = nThreadData
  L1_2 = L1_2.GetPrivateTable
  L1_2 = L1_2()
  L2_2 = 0
  L3_2 = L1_2[A0_2]
  if L3_2 ~= nil then
    L2_2 = L1_2[A0_2]
  end
  L3_2 = nObjective_PlayerHealthDrain
  L3_2 = L3_2.goldDeaths
  if L2_2 <= L3_2 then
    L3_2 = nObjectiveStatus
    L3_2 = L3_2.Gold
    return L3_2
  else
    L3_2 = nObjective_PlayerHealthDrain
    L3_2 = L3_2.silverDeaths
    if L2_2 <= L3_2 then
      L3_2 = nObjectiveStatus
      L3_2 = L3_2.Silver
      return L3_2
    else
      L3_2 = nObjective_PlayerHealthDrain
      L3_2 = L3_2.bronzeDeaths
      if L2_2 <= L3_2 then
        L3_2 = nObjectiveStatus
        L3_2 = L3_2.Bronze
        return L3_2
      else
        L3_2 = nObjectiveStatus
        L3_2 = L3_2.Failed
        return L3_2
      end
    end
  end
end

L0_1[L1_1] = L2_1
