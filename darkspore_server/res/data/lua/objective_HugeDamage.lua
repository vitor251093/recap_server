local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nObjective_HugeDamage = L0_1
L0_1 = nObjective_HugeDamage
L0_1.namespace = "nObjective_HugeDamage"
L0_1 = nObjective_HugeDamage
L1_1 = nUtil
L1_1 = L1_1.ToGUID
L2_1 = "0x09e6d259"
L1_1 = L1_1(L2_1)
L0_1.descriptionText = L1_1
L0_1 = nObjective_HugeDamage
L1_1 = nUtil
L1_1 = L1_1.ToGUID
L2_1 = "0x09e6d260"
L1_1 = L1_1(L2_1)
L0_1.progressText = L1_1
L0_1 = nObjective_HugeDamage
L0_1.timeObjectiveRequires = true
L0_1 = nObjective_HugeDamage
L1_1 = nObjectiveEvents
L1_1 = L1_1.Damage
L0_1.handledEvents = L1_1
L0_1 = nObjective_HugeDamage
L0_1.goldDamageCount = 30
L0_1 = nObjective_HugeDamage
L0_1.silverDamageCount = 15
L0_1 = nObjective_HugeDamage
L0_1.bronzeDamageCount = 5
L0_1 = nObjective_HugeDamage
L0_1.damageThresholdMultiplayer = 35
L0_1 = nObjective
L0_1 = L0_1.RegisterObjective
L1_1 = "HugeDamage"
L2_1 = nObjective_HugeDamage
L0_1(L1_1, L2_1)
L0_1 = nObjective_HugeDamage
L1_1 = nObjectiveFns
L1_1 = L1_1.Init

function L2_1()
  local L0_2, L1_2, L2_2, L3_2, L4_2, L5_2, L6_2
  L0_2 = nThreadData
  L0_2 = L0_2.CreatePrivateTable
  L0_2 = L0_2()
  L1_2 = nAttribute
  L1_2 = L1_2.GetHealthMultiplierForDifficulty
  L1_2 = L1_2()
  L0_2.damageThreshold = L1_2
  L1_2 = L0_2.damageThreshold
  L2_2 = nObjective_HugeDamage
  L2_2 = L2_2.damageThresholdMultiplayer
  L1_2 = L1_2 * L2_2
  L0_2.damageThreshold = L1_2
  L1_2 = nObjective
  L1_2 = L1_2.SetObjectiveIntData
  L2_2 = kAllPlayers
  L3_2 = 1
  L4_2 = L0_2.damageThreshold
  L5_2 = false
  L6_2 = false
  L1_2(L2_2, L3_2, L4_2, L5_2, L6_2)
  L1_2 = nObjective
  L1_2 = L1_2.SetObjectiveIntData
  L2_2 = kAllPlayers
  L3_2 = 2
  L4_2 = nObjective_HugeDamage
  L4_2 = L4_2.goldDamageCount
  L5_2 = false
  L6_2 = false
  L1_2(L2_2, L3_2, L4_2, L5_2, L6_2)
end

L0_1[L1_1] = L2_1
L0_1 = nObjective_HugeDamage
L1_1 = nObjectiveFns
L1_1 = L1_1.HandleEvent

function L2_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2
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
          if L6_2 ~= L7_2 then
            L8_2 = nThreadData
            L8_2 = L8_2.GetPrivateTable
            L8_2 = L8_2()
            if L8_2 ~= nil then
              L9_2 = L8_2.damageThreshold
              if L4_2 > L9_2 then
                L9_2 = nPlayer
                L9_2 = L9_2.GetPlayerIdForObject
                L10_2 = L3_2
                L9_2 = L9_2(L10_2)
                L10_2 = L8_2[L9_2]
                if L10_2 ~= nil then
                  L10_2 = L8_2[L9_2]
                  L11_2 = nObjective_HugeDamage
                  L11_2 = L11_2.goldDamageCount
                  if not (L10_2 < L11_2) then
                    goto lbl_99
                  end
                end
                L10_2 = L8_2[L9_2]
                if L10_2 == nil then
                  L8_2[L9_2] = 1
                else
                  L10_2 = L8_2[L9_2]
                  L10_2 = L10_2 + 1
                  L8_2[L9_2] = L10_2
                end
                L10_2 = L8_2[L9_2]
                L10_2 = L10_2 % 10
                if L10_2 == 0 then
                  L10_2 = nObjective
                  L10_2 = L10_2.SetObjectiveIntData
                  L11_2 = L9_2
                  L12_2 = 0
                  L13_2 = L8_2[L9_2]
                  L14_2 = true
                  L15_2 = true
                  L10_2(L11_2, L12_2, L13_2, L14_2, L15_2)
                else
                  L10_2 = nObjective
                  L10_2 = L10_2.SetObjectiveIntData
                  L11_2 = L9_2
                  L12_2 = 0
                  L13_2 = L8_2[L9_2]
                  L14_2 = true
                  L15_2 = false
                  L10_2(L11_2, L12_2, L13_2, L14_2, L15_2)
                end
              end
            end
          end
        end
      end
    end
  end
  ::lbl_99::
end

L0_1[L1_1] = L2_1
L0_1 = nObjective_HugeDamage
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
    if L3_2 ~= nil then
      L2_2 = L1_2[A0_2]
    end
  end
  L3_2 = nObjective_HugeDamage
  L3_2 = L3_2.goldDamageCount
  if L2_2 >= L3_2 then
    L3_2 = nObjectiveStatus
    L3_2 = L3_2.Gold
    return L3_2
  else
    L3_2 = nObjective_HugeDamage
    L3_2 = L3_2.silverDamageCount
    if L2_2 >= L3_2 then
      L3_2 = nObjectiveStatus
      L3_2 = L3_2.Silver
      return L3_2
    else
      L3_2 = nObjective_HugeDamage
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
