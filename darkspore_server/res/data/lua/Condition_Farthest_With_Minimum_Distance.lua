local L0_1, L1_1, L2_1, L3_1, L4_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_FarthestWithMinimumDistance = L0_1
L0_1 = nCondition_FarthestWithMinimumDistance
L0_1.namespace = "nCondition_FarthestWithMinimumDistance"
L0_1 = nCondition_FarthestWithMinimumDistance
L0_1.conditionType = 0
L0_1 = nCondition_FarthestWithMinimumDistance
L1_1 = {}
L2_1 = {}
L2_1.name = "Distance"
L3_1 = kReflectionType_float
L2_1.type = L3_1
L2_1.value = "10.0"
L3_1 = {}
L3_1.name = "Radius"
L4_1 = kReflectionType_float
L3_1.type = L4_1
L3_1.value = "30.0"
L1_1[1] = L2_1
L1_1[2] = L3_1
L0_1.properties = L1_1
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "FarthestWithMinimumDistance"
L2_1 = nCondition_FarthestWithMinimumDistance
L0_1(L1_1, L2_1)
L0_1 = nCondition_FarthestWithMinimumDistance

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2
  L1_2 = nCondition
  L1_2 = L1_2.GetProperty
  L2_2 = A0_2
  L3_2 = "Radius"
  L1_2 = L1_2(L2_2, L3_2)
  L2_2 = nGameObject
  L2_2 = L2_2.GetPosition
  L3_2 = A0_2
  L2_2, L3_2, L4_2 = L2_2(L3_2)
  L5_2 = nGameObject
  L5_2 = L5_2.GetTeam
  L6_2 = A0_2
  L5_2 = L5_2(L6_2)
  L6_2 = nObjectManager
  L6_2 = L6_2.GetObjectsInRadius_SortedByFurthestDistance
  L7_2 = L2_2
  L8_2 = L3_2
  L9_2 = L4_2
  L10_2 = L1_2
  L11_2 = nSporeLabs
  L11_2 = L11_2.damageableObjectTypes
  L6_2 = L6_2(L7_2, L8_2, L9_2, L10_2, L11_2)
  L7_2 = nCondition
  L7_2 = L7_2.GetProperty
  L8_2 = A0_2
  L9_2 = "Distance"
  L7_2 = L7_2(L8_2, L9_2)
  L8_2 = ipairs
  L9_2 = L6_2
  L8_2, L9_2, L10_2 = L8_2(L9_2)
  for L11_2, L12_2 in L8_2, L9_2, L10_2 do
    L13_2 = nGameObject
    L13_2 = L13_2.ValidateHostileTarget
    L14_2 = L5_2
    L15_2 = L12_2
    L13_2 = L13_2(L14_2, L15_2)
    if L13_2 then
      L13_2 = nGameObject
      L13_2 = L13_2.GetObjectDistance
      L14_2 = A0_2
      L15_2 = L12_2
      L13_2 = L13_2(L14_2, L15_2)
      if L7_2 > L13_2 then
        L14_2 = false
        return L14_2
      else
        L14_2 = true
        L15_2 = 0
        L16_2 = 0
        L17_2 = 0
        L18_2 = L12_2
        return L14_2, L15_2, L16_2, L17_2, L18_2
      end
    end
  end
  L8_2 = false
  return L8_2
end

L0_1[1] = L1_1
