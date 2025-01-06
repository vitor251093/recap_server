local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nObjective_DoDamageOften = L0_1
L0_1 = nObjective_DoDamageOften
L0_1.namespace = "nObjective_DoDamageOften"
L0_1 = nObjective_DoDamageOften
L1_1 = nUtil
L1_1 = L1_1.ToGUID
L2_1 = "0x09e6d276"
L1_1 = L1_1(L2_1)
L0_1.descriptionText = L1_1
L0_1 = nObjective_DoDamageOften
L1_1 = nUtil
L1_1 = L1_1.ToGUID
L2_1 = "0x09e6d277"
L1_1 = L1_1(L2_1)
L0_1.progressText = L1_1
L0_1 = nObjective_DoDamageOften
L0_1.timeObjectiveRequires = true
L0_1 = nObjective_DoDamageOften
L1_1 = nObjectiveEvents
L1_1 = L1_1.Damage
L0_1.handledEvents = L1_1
L0_1 = nObjective_DoDamageOften
L0_1.difficultyScale = 7
L0_1 = nObjective_DoDamageOften
L0_1.goldDamageCountMin = 150
L0_1 = nObjective_DoDamageOften
L0_1.goldDamageCountMax = 500
L0_1 = nObjective_DoDamageOften
L0_1.silverDamageCountMin = 100
L0_1 = nObjective_DoDamageOften
L0_1.silverDamageCountMax = 350
L0_1 = nObjective_DoDamageOften
L0_1.bronzeDamageCountMin = 50
L0_1 = nObjective_DoDamageOften
L0_1.bronzeDamageCountMax = 200
L0_1 = nObjective
L0_1 = L0_1.RegisterObjective
L1_1 = "DoDamageOften"
L2_1 = nObjective_DoDamageOften
L0_1(L1_1, L2_1)
L0_1 = nObjective_DoDamageOften
L1_1 = nObjectiveFns
L1_1 = L1_1.Init

function L2_1()
  local L0_2, L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2
  L0_2 = nThreadData
  L0_2 = L0_2.CreatePrivateTable
  L0_2 = L0_2()
  L1_2 = nObjective_DoDamageOften
  L1_2 = L1_2.GetGoldCount
  L1_2 = L1_2()
  L2_2 = nObjective
  L2_2 = L2_2.SetObjectiveIntData
  L3_2 = kAllPlayers
  L4_2 = 1
  L5_2 = L1_2
  L6_2 = false
  L7_2 = false
  L2_2(L3_2, L4_2, L5_2, L6_2, L7_2)
end

L0_1[L1_1] = L2_1
L0_1 = nObjective_DoDamageOften

function L1_1()
  local L0_2, L1_2, L2_2, L3_2, L4_2
  L0_2 = nGameSimulator
  L0_2 = L0_2.GetMajorDifficulty
  L0_2 = L0_2()
  L1_2 = nObjective_DoDamageOften
  L1_2 = L1_2.difficultyScale
  if L0_2 > L1_2 then
    L1_2 = nObjective_DoDamageOften
    L0_2 = L1_2.difficultyScale
  end
  L1_2 = nObjective_DoDamageOften
  L1_2 = L1_2.goldDamageCountMax
  L2_2 = nObjective_DoDamageOften
  L2_2 = L2_2.goldDamageCountMin
  L1_2 = L1_2 - L2_2
  L2_2 = nObjective_DoDamageOften
  L2_2 = L2_2.goldDamageCountMin
  L3_2 = L1_2 * L0_2
  L4_2 = nObjective_DoDamageOften
  L4_2 = L4_2.difficultyScale
  L3_2 = L3_2 / L4_2
  L2_2 = L2_2 + L3_2
  return L2_2
end

L0_1.GetGoldCount = L1_1
L0_1 = nObjective_DoDamageOften
L1_1 = nObjectiveFns
L1_1 = L1_1.HandleEvent

function L2_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2
  L2_2 = nObjectiveEvents
  L2_2 = L2_2.Damage
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
    L5_2 = nObjective
    L5_2 = L5_2.GetObjectiveEventIntData
    L6_2 = A1_2
    L7_2 = 4
    L5_2 = L5_2(L6_2, L7_2)
    L6_2 = nPlayer
    L6_2 = L6_2.IsPlayerControlledObject
    L7_2 = L3_2
    L6_2 = L6_2(L7_2)
    if L6_2 then
      L6_2 = kObjIDNone
      if L2_2 ~= L6_2 then
        L6_2 = nAbility
        L6_2 = L6_2.IsNPC
        L7_2 = L2_2
        L6_2 = L6_2(L7_2)
        if L6_2 then
          L6_2 = nGameObject
          L6_2 = L6_2.GetTeam
          L7_2 = L3_2
          L6_2 = L6_2(L7_2)
          L7_2 = nGameObject
          L7_2 = L7_2.GetTeam
          L8_2 = L2_2
          L7_2 = L7_2(L8_2)
          L8_2 = nThreadData
          L8_2 = L8_2.GetPrivateTable
          L8_2 = L8_2()
          if L8_2 ~= nil and L6_2 ~= L7_2 then
            L9_2 = nPlayer
            L9_2 = L9_2.GetPlayerIdForObject
            L10_2 = L3_2
            L9_2 = L9_2(L10_2)
            L10_2 = nObjective_DoDamageOften
            L10_2 = L10_2.GetGoldCount
            L10_2 = L10_2()
            L11_2 = L8_2[L9_2]
            if L11_2 ~= nil then
              L11_2 = L8_2[L9_2]
              if not (L10_2 > L11_2) then
                goto lbl_97
              end
            end
            L11_2 = L8_2[L9_2]
            if L11_2 == nil then
              L8_2[L9_2] = 1
            else
              L11_2 = L8_2[L9_2]
              L11_2 = L11_2 + 1
              L8_2[L9_2] = L11_2
            end
            L11_2 = L8_2[L9_2]
            L11_2 = L11_2 % 100
            if L11_2 == 0 then
              L11_2 = nObjective
              L11_2 = L11_2.SetObjectiveIntData
              L12_2 = L9_2
              L13_2 = 0
              L14_2 = L8_2[L9_2]
              L15_2 = true
              L16_2 = true
              L11_2(L12_2, L13_2, L14_2, L15_2, L16_2)
            else
              L11_2 = nObjective
              L11_2 = L11_2.SetObjectiveIntData
              L12_2 = L9_2
              L13_2 = 0
              L14_2 = L8_2[L9_2]
              L15_2 = true
              L16_2 = false
              L11_2(L12_2, L13_2, L14_2, L15_2, L16_2)
            end
          end
        end
      end
    end
  end
  ::lbl_97::
end

L0_1[L1_1] = L2_1
L0_1 = nObjective_DoDamageOften
L1_1 = nObjectiveFns
L1_1 = L1_1.ObjectiveStatus

function L2_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2
  L1_2 = nThreadData
  L1_2 = L1_2.GetPrivateTable
  L1_2 = L1_2()
  L2_2 = 0
  if L1_2 ~= nil then
    L3_2 = L1_2[A0_2]
    if L3_2 ~= nil then
      L2_2 = L1_2[A0_2]
    end
  end
  L3_2 = nGameSimulator
  L3_2 = L3_2.GetMajorDifficulty
  L3_2 = L3_2()
  L4_2 = nObjective_DoDamageOften
  L4_2 = L4_2.difficultyScale
  if L3_2 > L4_2 then
    L4_2 = nObjective_DoDamageOften
    L3_2 = L4_2.difficultyScale
  end
  L4_2 = nObjective_DoDamageOften
  L4_2 = L4_2.goldDamageCountMax
  L5_2 = nObjective_DoDamageOften
  L5_2 = L5_2.goldDamageCountMin
  L4_2 = L4_2 - L5_2
  L5_2 = nObjective_DoDamageOften
  L5_2 = L5_2.silverDamageCountMax
  L6_2 = nObjective_DoDamageOften
  L6_2 = L6_2.silverDamageCountMin
  L5_2 = L5_2 - L6_2
  L6_2 = nObjective_DoDamageOften
  L6_2 = L6_2.bronzeDamageCountMax
  L7_2 = nObjective_DoDamageOften
  L7_2 = L7_2.bronzeDamageCountMin
  L6_2 = L6_2 - L7_2
  L7_2 = nObjective_DoDamageOften
  L7_2 = L7_2.goldDamageCountMin
  L8_2 = L4_2 * L3_2
  L9_2 = nObjective_DoDamageOften
  L9_2 = L9_2.difficultyScale
  L8_2 = L8_2 / L9_2
  L7_2 = L7_2 + L8_2
  if L2_2 >= L7_2 then
    L7_2 = nObjectiveStatus
    L7_2 = L7_2.Gold
    return L7_2
  else
    L7_2 = nObjective_DoDamageOften
    L7_2 = L7_2.silverDamageCountMin
    L8_2 = L5_2 * L3_2
    L9_2 = nObjective_DoDamageOften
    L9_2 = L9_2.difficultyScale
    L8_2 = L8_2 / L9_2
    L7_2 = L7_2 + L8_2
    if L2_2 >= L7_2 then
      L7_2 = nObjectiveStatus
      L7_2 = L7_2.Silver
      return L7_2
    else
      L7_2 = nObjective_DoDamageOften
      L7_2 = L7_2.bronzeDamageCountMin
      L8_2 = L6_2 * L3_2
      L9_2 = nObjective_DoDamageOften
      L9_2 = L9_2.difficultyScale
      L8_2 = L8_2 / L9_2
      L7_2 = L7_2 + L8_2
      if L2_2 >= L7_2 then
        L7_2 = nObjectiveStatus
        L7_2 = L7_2.Bronze
        return L7_2
      else
        L7_2 = nObjectiveStatus
        L7_2 = L7_2.Failed
        return L7_2
      end
    end
  end
end

L0_1[L1_1] = L2_1
