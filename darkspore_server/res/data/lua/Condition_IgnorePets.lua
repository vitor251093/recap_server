local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_IgnorePets = L0_1
L0_1 = nCondition_IgnorePets
L0_1.namespace = "nCondition_IgnorePets"
L0_1 = nCondition_IgnorePets
L0_1.conditionType = 0
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "IgnorePets"
L2_1 = nCondition_IgnorePets
L0_1(L1_1, L2_1)
L0_1 = nCondition_IgnorePets

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2
  L1_2 = nGameObject
  L1_2 = L1_2.GetTeam
  L2_2 = A0_2
  L1_2 = L1_2(L2_2)
  L2_2 = nAgent
  L2_2 = L2_2.GetTargetsOnAggroList
  L3_2 = A0_2
  L2_2 = L2_2(L3_2)
  L3_2 = nGameObject
  L3_2 = L3_2.GetTeam
  L4_2 = A0_2
  L3_2 = L3_2(L4_2)
  L4_2 = ipairs
  L5_2 = L2_2
  L4_2, L5_2, L6_2 = L4_2(L5_2)
  for L7_2, L8_2 in L4_2, L5_2, L6_2 do
    L9_2 = nGameObject
    L9_2 = L9_2.ValidateHostileTarget
    L10_2 = L3_2
    L11_2 = L8_2
    L9_2 = L9_2(L10_2, L11_2)
    if L9_2 then
      L9_2 = nGameObject
      L9_2 = L9_2.IsPet
      L10_2 = L8_2
      L9_2 = L9_2(L10_2)
      if not L9_2 then
        L9_2 = true
        L10_2 = 0
        L11_2 = 0
        L12_2 = 0
        L13_2 = L8_2
        return L9_2, L10_2, L11_2, L12_2, L13_2
      end
    end
  end
  L4_2 = false
  return L4_2
end

L0_1[1] = L1_1
