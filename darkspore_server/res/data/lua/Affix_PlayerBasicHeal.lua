local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nAffix_PlayerBasicHeal = L0_1
L0_1 = nAffix_PlayerBasicHeal
L0_1.namespace = "nAffix_PlayerBasicHeal"
L0_1 = nAffix_PlayerBasicHeal
L1_1 = nUtil
L1_1 = L1_1.ToGUID
L2_1 = "0x098d3ebe"
L1_1 = L1_1(L2_1)
L0_1.localizedText = L1_1
L0_1 = nAffix_PlayerBasicHeal
L1_1 = kInvalidGUID
L0_1.objective = L1_1
L0_1 = nAffix_PlayerBasicHeal
L1_1 = nObjectiveEvents
L1_1 = L1_1.Damage
L0_1.handledEvents = L1_1
L0_1 = nAffix_PlayerBasicHeal
L0_1.healPercent = 0.02
L0_1 = nAffix_PlayerBasicHeal
L0_1.healCoefficent = 0
L0_1 = nAffix
L0_1 = L0_1.RegisterAffix
L1_1 = "PlayerBasicHeal"
L2_1 = nAffix_PlayerBasicHeal
L0_1(L1_1, L2_1)
L0_1 = nAffix_PlayerBasicHeal
L1_1 = nAffixFns
L1_1 = L1_1.Tick

function L2_1()
  local L0_2, L1_2
end

L0_1[L1_1] = L2_1
L0_1 = nAffix_PlayerBasicHeal
L1_1 = nAffixFns
L1_1 = L1_1.HandleEvent

function L2_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2
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
      L6_2 = nBit
      L6_2 = L6_2.And
      L7_2 = L5_2
      L8_2 = nDescriptors
      L8_2 = L8_2.IsBasic
      L6_2 = L6_2(L7_2, L8_2)
      if L6_2 ~= 0 then
        L6_2 = nGameObject
        L6_2 = L6_2.IsAlive
        L7_2 = L3_2
        L6_2 = L6_2(L7_2)
        if L6_2 then
          L6_2 = nGameObject
          L6_2 = L6_2.GetMaxHitPoints
          L7_2 = L3_2
          L6_2 = L6_2(L7_2)
          L7_2 = nAffix_PlayerBasicHeal
          L7_2 = L7_2.healPercent
          L7_2 = L6_2 * L7_2
          L8_2 = nGameObject
          L8_2 = L8_2.HealDamage
          L9_2 = kObjIDNone
          L10_2 = L3_2
          L11_2 = {}
          L12_2 = L7_2
          L13_2 = L7_2
          L11_2[1] = L12_2
          L11_2[2] = L13_2
          L12_2 = nAffix_PlayerBasicHeal
          L12_2 = L12_2.healCoefficient
          L8_2(L9_2, L10_2, L11_2, L12_2)
        end
      end
    end
  end
end

L0_1[L1_1] = L2_1
