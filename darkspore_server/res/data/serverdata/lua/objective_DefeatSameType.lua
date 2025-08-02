local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nObjective_DefeatSameType = L0_1
L0_1 = nObjective_DefeatSameType
L0_1.namespace = "nObjective_DefeatSameType"
L0_1 = nObjective_DefeatSameType
L1_1 = nUtil
L1_1 = L1_1.ToGUID
L2_1 = "0x09e6d288"
L1_1 = L1_1(L2_1)
L0_1.descriptionText = L1_1
L0_1 = nObjective_DefeatSameType
L1_1 = nUtil
L1_1 = L1_1.ToGUID
L2_1 = "0x09e6d289"
L1_1 = L1_1(L2_1)
L0_1.progressText = L1_1
L0_1 = nObjective_DefeatSameType
L0_1.timeObjectiveRequires = true
L0_1 = nObjective_DefeatSameType
L1_1 = nObjectiveEvents
L1_1 = L1_1.Death
L0_1.handledEvents = L1_1
L0_1 = nObjective_DefeatSameType
L0_1.goldDamageCount = 15
L0_1 = nObjective_DefeatSameType
L0_1.silverDamageCount = 10
L0_1 = nObjective_DefeatSameType
L0_1.bronzeDamageCount = 5
L0_1 = nObjective
L0_1 = L0_1.RegisterObjective
L1_1 = "DefeatSameType"
L2_1 = nObjective_DefeatSameType
L0_1(L1_1, L2_1)
L0_1 = nObjective_DefeatSameType
L1_1 = nObjectiveFns
L1_1 = L1_1.Init

function L2_1()
  local L0_2, L1_2, L2_2, L3_2, L4_2, L5_2, L6_2
  L0_2 = nThreadData
  L0_2 = L0_2.CreatePrivateTable
  L0_2 = L0_2()
  L1_2 = 0
  L2_2 = kMaxNumPlayers
  L2_2 = L2_2 - 1
  L3_2 = 1
  for L4_2 = L1_2, L2_2, L3_2 do
    L5_2 = {}
    L0_2[L4_2] = L5_2
    L5_2 = L0_2[L4_2]
    L5_2.numberDefeated = 0
    L5_2 = L0_2[L4_2]
    L5_2.mostDefeated = 0
    L5_2 = L0_2[L4_2]
    L6_2 = kObjIDNone
    L5_2.typeDefeating = L6_2
  end
  L1_2 = nObjective
  L1_2 = L1_2.SetObjectiveIntData
  L2_2 = kAllPlayers
  L3_2 = 0
  L4_2 = 0
  L5_2 = false
  L6_2 = false
  L1_2(L2_2, L3_2, L4_2, L5_2, L6_2)
  L1_2 = nObjective
  L1_2 = L1_2.SetObjectiveIntData
  L2_2 = kAllPlayers
  L3_2 = 1
  L4_2 = nObjective_DefeatSameType
  L4_2 = L4_2.goldDamageCount
  L5_2 = false
  L6_2 = false
  L1_2(L2_2, L3_2, L4_2, L5_2, L6_2)
end

L0_1[L1_1] = L2_1
L0_1 = nObjective_DefeatSameType
L1_1 = nObjectiveFns
L1_1 = L1_1.HandleEvent

function L2_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2
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
    L5_2 = nThreadData
    L5_2 = L5_2.GetPrivateTable
    L5_2 = L5_2()
    L6_2 = nPlayer
    L6_2 = L6_2.IsPlayerControlledObject
    L7_2 = L3_2
    L6_2 = L6_2(L7_2)
    if L6_2 then
      L6_2 = kObjIDNone
      if L2_2 ~= L6_2 then
        L6_2 = nPlayer
        L6_2 = L6_2.GetPlayerIdForObject
        L7_2 = L3_2
        L6_2 = L6_2(L7_2)
        if L5_2 ~= nil and L4_2 == L6_2 then
          L7_2 = nAbility
          L7_2 = L7_2.IsNPC
          L8_2 = L2_2
          L7_2 = L7_2(L8_2)
          if L7_2 then
            L7_2 = nGameObject
            L7_2 = L7_2.GetTeam
            L8_2 = L3_2
            L7_2 = L7_2(L8_2)
            L8_2 = nGameObject
            L8_2 = L8_2.GetTeam
            L9_2 = L2_2
            L8_2 = L8_2(L9_2)
            if L7_2 ~= L8_2 then
              L9_2 = nGameObject
              L9_2 = L9_2.GetAssetNameWithType
              L10_2 = L2_2
              L9_2 = L9_2(L10_2)
              L10_2 = L5_2[L6_2]
              L10_2 = L10_2.typeDefeating
              if L9_2 == L10_2 then
                L10_2 = L5_2[L6_2]
                L11_2 = L5_2[L6_2]
                L11_2 = L11_2.numberDefeated
                L11_2 = L11_2 + 1
                L10_2.numberDefeated = L11_2
                L10_2 = L5_2[L6_2]
                L10_2 = L10_2.numberDefeated
                L11_2 = L5_2[L6_2]
                L11_2 = L11_2.mostDefeated
                if L10_2 > L11_2 then
                  L10_2 = L5_2[L6_2]
                  L11_2 = L5_2[L6_2]
                  L11_2 = L11_2.numberDefeated
                  L10_2.mostDefeated = L11_2
                  L10_2 = L5_2[L6_2]
                  L10_2 = L10_2.mostDefeated
                  L11_2 = nObjective_DefeatSameType
                  L11_2 = L11_2.goldDamageCount
                  if L10_2 <= L11_2 then
                    L10_2 = L5_2[L6_2]
                    L10_2 = L10_2.mostDefeated
                    L10_2 = L10_2 % 5
                    if L10_2 == 0 then
                      L10_2 = nObjective
                      L10_2 = L10_2.SetObjectiveIntData
                      L11_2 = L6_2
                      L12_2 = 0
                      L13_2 = L5_2[L6_2]
                      L13_2 = L13_2.mostDefeated
                      L14_2 = true
                      L15_2 = true
                      L10_2(L11_2, L12_2, L13_2, L14_2, L15_2)
                    else
                      L10_2 = nObjective
                      L10_2 = L10_2.SetObjectiveIntData
                      L11_2 = L6_2
                      L12_2 = 0
                      L13_2 = L5_2[L6_2]
                      L13_2 = L13_2.mostDefeated
                      L14_2 = true
                      L15_2 = false
                      L10_2(L11_2, L12_2, L13_2, L14_2, L15_2)
                    end
                  end
                end
              else
                L10_2 = L5_2[L6_2]
                L10_2.typeDefeating = L9_2
                L10_2 = L5_2[L6_2]
                L10_2.numberDefeated = 1
              end
            end
          end
        end
      end
    end
  end
end

L0_1[L1_1] = L2_1
L0_1 = nObjective_DefeatSameType
L1_1 = nObjectiveFns
L1_1 = L1_1.ObjectiveStatus

function L2_1(A0_2)
  local L1_2, L2_2, L3_2
  L1_2 = nThreadData
  L1_2 = L1_2.GetPrivateTable
  L1_2 = L1_2()
  L2_2 = 0
  if L1_2 ~= nil then
    L3_2 = L1_2[A0_2]
    L3_2 = L3_2.mostDefeated
    if L3_2 ~= nil then
      L3_2 = L1_2[A0_2]
      L2_2 = L3_2.mostDefeated
    end
  end
  L3_2 = nObjective_DefeatSameType
  L3_2 = L3_2.goldDamageCount
  if L2_2 >= L3_2 then
    L3_2 = nObjectiveStatus
    L3_2 = L3_2.Gold
    return L3_2
  else
    L3_2 = nObjective_DefeatSameType
    L3_2 = L3_2.silverDamageCount
    if L2_2 >= L3_2 then
      L3_2 = nObjectiveStatus
      L3_2 = L3_2.Silver
      return L3_2
    else
      L3_2 = nObjective_DefeatSameType
      L3_2 = L3_2.bronzeDamageCount
      if L2_2 >= L3_2 then
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
