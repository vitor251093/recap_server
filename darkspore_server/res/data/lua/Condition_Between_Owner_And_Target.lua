local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_Between_Owner_And_Target = L0_1
L0_1 = nCondition_Between_Owner_And_Target
L0_1.namespace = "nCondition_Between_Owner_And_Target"
L0_1 = nCondition_Between_Owner_And_Target
L0_1.conditionType = 0
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "BetweenOwnerAndTarget"
L2_1 = nCondition_Between_Owner_And_Target
L0_1(L1_1, L2_1)
L0_1 = nCondition_Between_Owner_And_Target

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2, L19_2, L20_2, L21_2
  L1_2 = nGameObject
  L1_2 = L1_2.GetOwnerID
  L2_2 = A0_2
  L1_2 = L1_2(L2_2)
  L2_2 = kObjIDNone
  if L1_2 ~= L2_2 then
    L2_2 = nAgent
    L2_2 = L2_2.GetBestTarget
    L3_2 = L1_2
    L2_2 = L2_2(L3_2)
    L3_2 = kObjIDNone
    if L2_2 ~= L3_2 then
      L3_2 = nGameObject
      L3_2 = L3_2.GetPosition
      L4_2 = A0_2
      L3_2, L4_2, L5_2 = L3_2(L4_2)
      L6_2 = nGameObject
      L6_2 = L6_2.GetPosition
      L7_2 = L1_2
      L6_2, L7_2, L8_2 = L6_2(L7_2)
      L9_2 = nGameObject
      L9_2 = L9_2.GetPosition
      L10_2 = L2_2
      L9_2, L10_2, L11_2 = L9_2(L10_2)
      L12_2 = nMathUtil
      L12_2 = L12_2.DistanceToLine
      L13_2 = L3_2
      L14_2 = L4_2
      L15_2 = L5_2
      L16_2 = L6_2
      L17_2 = L7_2
      L18_2 = L8_2
      L19_2 = L9_2
      L20_2 = L10_2
      L21_2 = L11_2
      L12_2 = L12_2(L13_2, L14_2, L15_2, L16_2, L17_2, L18_2, L19_2, L20_2, L21_2)
      L13_2 = nGameObject
      L13_2 = L13_2.GetFootprintRadius
      L14_2 = L1_2
      L13_2 = L13_2(L14_2)
      L14_2 = nGameObject
      L14_2 = L14_2.GetFootprintRadius
      L15_2 = A0_2
      L14_2 = L14_2(L15_2)
      L13_2 = L13_2 + L14_2
      if L12_2 < L13_2 then
        L13_2 = true
        return L13_2
      end
    end
  end
  L2_2 = false
  return L2_2
end

L0_1[1] = L1_1
