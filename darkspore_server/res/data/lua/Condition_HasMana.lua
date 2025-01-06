local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_HasMana = L0_1
L0_1 = nCondition_HasMana
L0_1.namespace = "nCondition_HasMana"
L0_1 = nCondition_HasMana
L0_1.conditionType = 0
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "HasMana"
L2_1 = nCondition_HasMana
L0_1(L1_1, L2_1)
L0_1 = nCondition_HasMana

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2
  L1_2 = nAgent
  L1_2 = L1_2.GetBestTarget
  L2_2 = A0_2
  L1_2 = L1_2(L2_2)
  L2_2 = kObjIDNone
  if L1_2 ~= L2_2 then
    L2_2 = nObjectManager
    L2_2 = L2_2.IsValidObject
    L3_2 = L1_2
    L2_2 = L2_2(L3_2)
    if L2_2 then
      L2_2 = nGameObject
      L2_2 = L2_2.GetManaPoints
      L3_2 = L1_2
      L2_2 = L2_2(L3_2)
      if 0 < L2_2 then
        L2_2 = nGameObject
        L2_2 = L2_2.GetPosition
        L3_2 = L1_2
        L2_2, L3_2, L4_2 = L2_2(L3_2)
        L5_2 = true
        L6_2 = L2_2
        L7_2 = L3_2
        L8_2 = L4_2
        L9_2 = L1_2
        return L5_2, L6_2, L7_2, L8_2, L9_2
      end
    end
  end
  L2_2 = false
  return L2_2
end

L0_1[1] = L1_1
