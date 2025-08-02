local L0_1, L1_1, L2_1, L3_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_Closest = L0_1
L0_1 = nCondition_Closest
L0_1.namespace = "nCondition_Closest"
L0_1 = nCondition_Closest
L0_1.conditionType = 0
L0_1 = nCondition_Closest
L1_1 = {}
L2_1 = {}
L2_1.name = "Radius"
L3_1 = kReflectionType_float
L2_1.type = L3_1
L2_1.value = "30.0"
L1_1[1] = L2_1
L0_1.properties = L1_1
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "Closest"
L2_1 = nCondition_Closest
L0_1(L1_1, L2_1)
L0_1 = nCondition_Closest

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2, L19_2
  L1_2 = nGameObject
  L1_2 = L1_2.GetTeam
  L2_2 = A0_2
  L1_2 = L1_2(L2_2)
  L2_2 = nGameObject
  L2_2 = L2_2.GetPosition
  L3_2 = A0_2
  L2_2, L3_2, L4_2 = L2_2(L3_2)
  L5_2 = nCondition
  L5_2 = L5_2.GetProperty
  L6_2 = A0_2
  L7_2 = "Radius"
  L5_2 = L5_2(L6_2, L7_2)
  L6_2 = nObjectManager
  L6_2 = L6_2.GetObjectsInRadius_SortedByDistance
  L7_2 = L2_2
  L8_2 = L3_2
  L9_2 = L4_2
  L10_2 = L5_2
  L11_2 = kType_Creature
  L6_2 = L6_2(L7_2, L8_2, L9_2, L10_2, L11_2)
  L7_2 = ipairs
  L8_2 = L6_2
  L7_2, L8_2, L9_2 = L7_2(L8_2)
  for L10_2, L11_2 in L7_2, L8_2, L9_2 do
    if L11_2 ~= A0_2 then
      L12_2 = nGameObject
      L12_2 = L12_2.ValidateHostileTarget
      L13_2 = L1_2
      L14_2 = L11_2
      L12_2 = L12_2(L13_2, L14_2)
      if L12_2 then
        L12_2 = nGameObject
        L12_2 = L12_2.GetPosition
        L13_2 = L11_2
        L12_2, L13_2, L14_2 = L12_2(L13_2)
        L15_2 = true
        L16_2 = L12_2
        L17_2 = L13_2
        L18_2 = L14_2
        L19_2 = L11_2
        return L15_2, L16_2, L17_2, L18_2, L19_2
      end
    end
  end
  L7_2 = false
  return L7_2
end

L0_1[1] = L1_1
