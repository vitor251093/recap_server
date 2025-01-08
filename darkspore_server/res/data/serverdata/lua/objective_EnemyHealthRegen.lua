local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nObjective_EnemyHealthRegen = L0_1
L0_1 = nObjective_EnemyHealthRegen
L0_1.namespace = "nObjective_EnemyHealthRegen"
L0_1 = nObjective_EnemyHealthRegen
L1_1 = nUtil
L1_1 = L1_1.ToGUID
L2_1 = "0x098cd815"
L1_1 = L1_1(L2_1)
L0_1.descriptionText = L1_1
L0_1 = nObjective_EnemyHealthRegen
L1_1 = nObjectiveEvents
L1_1 = L1_1.Heal
L0_1.handledEvents = L1_1
L0_1 = nObjective_EnemyHealthRegen
L0_1.goldRegens = 50
L0_1 = nObjective_EnemyHealthRegen
L0_1.silverRegens = 100
L0_1 = nObjective_EnemyHealthRegen
L0_1.bronzeRegens = 150
L0_1 = nObjective
L0_1 = L0_1.RegisterObjective
L1_1 = "EnemyHealthRegen"
L2_1 = nObjective_EnemyHealthRegen
L0_1(L1_1, L2_1)
L0_1 = nObjective_EnemyHealthRegen
L1_1 = nObjectiveFns
L1_1 = L1_1.Init

function L2_1()
  local L0_2, L1_2
  L0_2 = nThreadData
  L0_2 = L0_2.CreatePrivateTable
  L0_2 = L0_2()
  L0_2.numRegens = 0
  L0_2.healthRegen = 0
end

L0_1[L1_1] = L2_1
L0_1 = nObjective_EnemyHealthRegen
L1_1 = nObjectiveFns
L1_1 = L1_1.HandleEvent

function L2_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2
  L2_2 = nObjectiveEvents
  L2_2 = L2_2.Heal
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
    L4_2 = L4_2.GetObjectiveEventFloatData
    L5_2 = A1_2
    L6_2 = 3
    L4_2 = L4_2(L5_2, L6_2)
    L5_2 = nPlayer
    L5_2 = L5_2.IsPlayerControlledObject
    L6_2 = L2_2
    L5_2 = L5_2(L6_2)
    if L5_2 == false then
      L5_2 = kObjIDNone
      if L3_2 == L5_2 then
        L5_2 = nThreadData
        L5_2 = L5_2.GetPrivateTable
        L5_2 = L5_2()
        L6_2 = L5_2.numRegens
        L6_2 = L6_2 + 1
        L5_2.numRegens = L6_2
        L6_2 = L5_2.healthRegen
        L6_2 = L6_2 + L4_2
        L5_2.healthRegen = L6_2
        L6_2 = nObjective
        L6_2 = L6_2.SetObjectiveIntData
        L7_2 = kAllPlayers
        L8_2 = 0
        L9_2 = L5_2.numRegens
        L10_2 = true
        L11_2 = false
        L6_2(L7_2, L8_2, L9_2, L10_2, L11_2)
        L6_2 = nObjective
        L6_2 = L6_2.SetObjectiveIntData
        L7_2 = kAllPlayers
        L8_2 = 1
        L9_2 = L5_2.healthRegen
        L10_2 = true
        L11_2 = false
        L6_2(L7_2, L8_2, L9_2, L10_2, L11_2)
      end
    end
  end
end

L0_1[L1_1] = L2_1
L0_1 = nObjective_EnemyHealthRegen
L1_1 = nObjectiveFns
L1_1 = L1_1.ObjectiveStatus

function L2_1(A0_2)
  local L1_2, L2_2, L3_2
  L1_2 = nThreadData
  L1_2 = L1_2.GetPrivateTable
  L1_2 = L1_2()
  L2_2 = L1_2.numRegens
  if L2_2 ~= nil then
    L2_2 = L1_2.numRegens
    L3_2 = nObjective_EnemyHealthRegen
    L3_2 = L3_2.goldRegens
    if L2_2 < L3_2 then
      L2_2 = nObjectiveStatus
      L2_2 = L2_2.Gold
      return L2_2
  end
  else
    L2_2 = L1_2.numRegens
    if L2_2 ~= nil then
      L2_2 = L1_2.numRegens
      L3_2 = nObjective_EnemyHealthRegen
      L3_2 = L3_2.silverRegens
      if L2_2 < L3_2 then
        L2_2 = nObjectiveStatus
        L2_2 = L2_2.Silver
        return L2_2
    end
    else
      L2_2 = L1_2.numRegens
      if L2_2 ~= nil then
        L2_2 = L1_2.numRegens
        L3_2 = nObjective_EnemyHealthRegen
        L3_2 = L3_2.bronzeRegens
        if L2_2 < L3_2 then
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

L0_1[L1_1] = L2_1
