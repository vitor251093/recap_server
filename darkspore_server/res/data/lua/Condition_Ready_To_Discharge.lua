local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_Ready_To_Discharge = L0_1
L0_1 = nCondition_Ready_To_Discharge
L0_1.namespace = "nCondition_Ready_To_Discharge"
L0_1 = nCondition_Ready_To_Discharge
L0_1.conditionType = 0
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "ReadyToDischarge"
L2_1 = nCondition_Ready_To_Discharge
L0_1(L1_1, L2_1)

function L0_1(A0_2, A1_2, A2_2)
  local L3_2, L4_2, L5_2
  L3_2 = nModifier
  L3_2 = L3_2.GetFirstModifierByGUID
  L4_2 = A0_2
  L5_2 = A1_2
  L3_2 = L3_2(L4_2, L5_2)
  L4_2 = kObjIDNone
  if L3_2 == L4_2 then
    L4_2 = true
    return L4_2
  end
  L4_2 = nModifier
  L4_2 = L4_2.GetStackCount
  L5_2 = L3_2
  L4_2 = L4_2(L5_2)
  if A2_2 > L4_2 then
    L5_2 = true
    return L5_2
  end
  L5_2 = false
  return L5_2
end

L1_1 = nCondition_Ready_To_Discharge

function L2_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2
  L1_2 = nUtil
  L1_2 = L1_2.SPID
  L2_2 = "CitadelChargeCounter"
  L1_2 = L1_2(L2_2)
  L2_2 = nGameObject
  L2_2 = L2_2.GetPosition
  L3_2 = A0_2
  L2_2, L3_2, L4_2 = L2_2(L3_2)
  L5_2 = 16
  L6_2 = 5
  L7_2 = L0_1
  L8_2 = A0_2
  L9_2 = L1_2
  L10_2 = 5
  L7_2 = L7_2(L8_2, L9_2, L10_2)
  if not L7_2 then
    L7_2 = true
    return L7_2
  end
  L7_2 = nObjectManager
  L7_2 = L7_2.GetObjectsInRadius
  L8_2 = L2_2
  L9_2 = L3_2
  L10_2 = L4_2
  L11_2 = L5_2
  L12_2 = kType_Creature
  L7_2 = L7_2(L8_2, L9_2, L10_2, L11_2, L12_2)
  L8_2 = ipairs
  L9_2 = L7_2
  L8_2, L9_2, L10_2 = L8_2(L9_2)
  for L11_2, L12_2 in L8_2, L9_2, L10_2 do
    L13_2 = nGameObject
    L13_2 = L13_2.IsAlive
    L14_2 = L12_2
    L13_2 = L13_2(L14_2)
    if L13_2 then
      L13_2 = nGameObject
      L13_2 = L13_2.GetTeam
      L14_2 = L12_2
      L13_2 = L13_2(L14_2)
      L14_2 = nGameObject
      L14_2 = L14_2.GetTeam
      L15_2 = A0_2
      L14_2 = L14_2(L15_2)
      if L13_2 == L14_2 and L12_2 ~= A0_2 then
        L13_2 = nGameObject
        L13_2 = L13_2.IsSameSpecies
        L14_2 = L12_2
        L15_2 = A0_2
        L13_2 = L13_2(L14_2, L15_2)
        if L13_2 then
          L13_2 = false
          return L13_2
        end
      end
    end
  end
  L8_2 = true
  return L8_2
end

L1_1[1] = L2_1
