local L0_1, L1_1, L2_1, L3_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nObjective_LootCrystals = L0_1
L0_1 = nObjective_LootCrystals
L0_1.namespace = "nObjective_LootCrystals"
L0_1 = nObjective_LootCrystals
L1_1 = nUtil
L1_1 = L1_1.ToGUID
L2_1 = "0x09e6e562"
L1_1 = L1_1(L2_1)
L0_1.descriptionText = L1_1
L0_1 = nObjective_LootCrystals
L1_1 = nUtil
L1_1 = L1_1.ToGUID
L2_1 = "0x09e6e563"
L1_1 = L1_1(L2_1)
L0_1.progressText = L1_1
L0_1 = nObjective_LootCrystals
L1_1 = nObjectiveEvents
L1_1 = L1_1.Death
L0_1.handledEvents = L1_1
L0_1 = nObjective_LootCrystals
L0_1.groupObjective = true
L0_1 = nObjective_LootCrystals
L0_1.timeObjectiveRequires = true
L0_1 = nObjective_LootCrystals
L1_1 = nUtil
L1_1 = L1_1.GetAsset
L2_1 = "loot_questCrystal.Noun"
L1_1 = L1_1(L2_1)
L0_1.dropObject = L1_1
L0_1 = nObjective_LootCrystals
L0_1.dropLevel = 0.135
L0_1 = nObjective_LootCrystals
L0_1.goldCrystals = 7
L0_1 = nObjective_LootCrystals
L0_1.silverCrystals = 5
L0_1 = nObjective_LootCrystals
L0_1.bronzeCrystals = 3
L0_1 = nObjective
L0_1 = L0_1.RegisterObjective
L1_1 = "LootCrystals"
L2_1 = nObjective_LootCrystals
L0_1(L1_1, L2_1)

function L0_1()
  local L0_2, L1_2
  L0_2 = nThreadData
  L0_2 = L0_2.GetPrivateTable
  L0_2 = L0_2()
  if L0_2 == nil then
    L1_2 = nThreadData
    L1_2 = L1_2.CreatePrivateTable
    L1_2 = L1_2()
    L0_2 = L1_2
    L0_2.foundCrystals = 0
  end
  return L0_2
end

L1_1 = nObjective_LootCrystals
L2_1 = nObjectiveFns
L2_1 = L2_1.Init

function L3_1()
  local L0_2, L1_2, L2_2, L3_2, L4_2, L5_2, L6_2
  L0_2 = L0_1
  L0_2 = L0_2()
  L0_2.foundCrystals = 0
  L1_2 = nObjective_LootCrystals
  L1_2 = L1_2.dropLevel
  L0_2.dropLevel = L1_2
  L1_2 = nObjective
  L1_2 = L1_2.SetObjectiveIntData
  L2_2 = kAllPlayers
  L3_2 = 0
  L4_2 = L0_2.foundCrystals
  L5_2 = false
  L6_2 = false
  L1_2(L2_2, L3_2, L4_2, L5_2, L6_2)
  L1_2 = nObjective
  L1_2 = L1_2.SetObjectiveIntData
  L2_2 = kAllPlayers
  L3_2 = 1
  L4_2 = nObjective_LootCrystals
  L4_2 = L4_2.goldCrystals
  L5_2 = false
  L6_2 = false
  L1_2(L2_2, L3_2, L4_2, L5_2, L6_2)
end

L1_1[L2_1] = L3_1
L1_1 = nObjective_LootCrystals

function L2_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2
  L1_2 = L0_1
  L1_2 = L1_2()
  L2_2 = L1_2.foundCrystals
  if L2_2 == nil then
    L1_2.foundCrystals = 1
  else
    L2_2 = L1_2.foundCrystals
    L2_2 = L2_2 + 1
    L1_2.foundCrystals = L2_2
  end
  L2_2 = nObjective
  L2_2 = L2_2.SetObjectiveIntDataFromSPID
  L3_2 = A0_2
  L4_2 = kAllPlayers
  L5_2 = 0
  L6_2 = L1_2.foundCrystals
  L7_2 = true
  L8_2 = true
  L2_2(L3_2, L4_2, L5_2, L6_2, L7_2, L8_2)
end

L1_1.CrystalFound = L2_1
L1_1 = nObjective_LootCrystals
L2_1 = nObjectiveFns
L2_1 = L2_1.HandleEvent

function L3_1(A0_2, A1_2)
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
    L4_2 = nObjective
    L4_2 = L4_2.GetObjectiveEventIntData
    L5_2 = A1_2
    L6_2 = 3
    L4_2 = L4_2(L5_2, L6_2)
    L5_2 = nPlayer
    L5_2 = L5_2.IsPlayerControlledObject
    L6_2 = L2_2
    L5_2 = L5_2(L6_2)
    if not L5_2 then
      L5_2 = nGameObject
      L5_2 = L5_2.GetTeam
      L6_2 = L3_2
      L5_2 = L5_2(L6_2)
      L6_2 = nGameObject
      L6_2 = L6_2.GetTeam
      L7_2 = L2_2
      L6_2 = L6_2(L7_2)
      if L5_2 ~= L6_2 then
        L7_2 = nThreadData
        L7_2 = L7_2.GetPrivateTable
        L7_2 = L7_2()
        L8_2 = nGameDirector
        L8_2 = L8_2.GetKillPercent
        L8_2 = L8_2()
        if L7_2 ~= nil then
          L9_2 = L7_2.dropLevel
          if L8_2 > L9_2 then
            L9_2 = nAbility
            L9_2 = L9_2.IsNPC
            L10_2 = L2_2
            L9_2 = L9_2(L10_2)
            if L9_2 then
              L9_2 = nGameObject
              L9_2 = L9_2.DropObject
              L10_2 = nObjective_LootCrystals
              L10_2 = L10_2.dropObject
              L11_2 = L2_2
              L9_2(L10_2, L11_2)
              L9_2 = L7_2.dropLevel
              L10_2 = nObjective_LootCrystals
              L10_2 = L10_2.dropLevel
              L9_2 = L9_2 + L10_2
              L7_2.dropLevel = L9_2
              L9_2 = nDebug
              L9_2 = L9_2.LogToConsole
              L10_2 = "Dropping Crystal"
              L9_2(L10_2)
            end
          end
        end
      end
    end
  end
end

L1_1[L2_1] = L3_1
L1_1 = nObjective_LootCrystals
L2_1 = nObjectiveFns
L2_1 = L2_1.ObjectiveStatus

function L3_1(A0_2)
  local L1_2, L2_2, L3_2
  L1_2 = L0_1
  L1_2 = L1_2()
  if L1_2 ~= nil then
    L2_2 = L1_2.foundCrystals
    if L2_2 ~= nil then
      L2_2 = L1_2.foundCrystals
      L3_2 = nObjective_LootCrystals
      L3_2 = L3_2.goldCrystals
      if L2_2 >= L3_2 then
        L2_2 = nObjectiveStatus
        L2_2 = L2_2.Gold
        return L2_2
    end
  end
  else
    L2_2 = L1_2.foundCrystals
    if L2_2 ~= nil then
      L2_2 = L1_2.foundCrystals
      L3_2 = nObjective_LootCrystals
      L3_2 = L3_2.silverCrystals
      if L2_2 >= L3_2 then
        L2_2 = nObjectiveStatus
        L2_2 = L2_2.Silver
        return L2_2
    end
    else
      L2_2 = L1_2.foundCrystals
      if L2_2 ~= nil then
        L2_2 = L1_2.foundCrystals
        L3_2 = nObjective_LootCrystals
        L3_2 = L3_2.bronzeCrystals
        if L2_2 >= L3_2 then
          L2_2 = nObjectiveStatus
          L2_2 = L2_2.Bronze
          return L2_2
      end
      else
        L2_2 = nObjectiveStatus
        L2_2 = L2_2.Failed
        return L2_2
      end
    end
  end
end

L1_1[L2_1] = L3_1
