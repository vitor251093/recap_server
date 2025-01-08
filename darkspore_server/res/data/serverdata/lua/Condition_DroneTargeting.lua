local L0_1, L1_1, L2_1, L3_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = require
L1_1 = "Lua!Vector.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_DroneTargeting = L0_1
L0_1 = nCondition_DroneTargeting
L0_1.namespace = "nCondition_DroneTargeting"
L0_1 = nCondition_DroneTargeting
L0_1.conditionType = 0
L0_1 = nCondition_DroneTargeting
L1_1 = {}
L2_1 = {}
L2_1.name = "Radius"
L3_1 = kReflectionType_float
L2_1.type = L3_1
L2_1.value = "15.0"
L1_1[1] = L2_1
L0_1.properties = L1_1
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "DroneTargeting"
L2_1 = nCondition_DroneTargeting
L0_1(L1_1, L2_1)
L0_1 = nCondition_DroneTargeting

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2, L19_2, L20_2, L21_2, L22_2, L23_2, L24_2, L25_2, L26_2, L27_2, L28_2, L29_2, L30_2, L31_2
  L1_2 = nGameObject
  L1_2 = L1_2.GetIsStealthed
  L2_2 = A0_2
  L1_2 = L1_2(L2_2)
  if L1_2 then
    L1_2 = false
    return L1_2
  end
  L1_2 = nGameObject
  L1_2 = L1_2.GetOwnerID
  L2_2 = A0_2
  L1_2 = L1_2(L2_2)
  L2_2 = nObjectManager
  L2_2 = L2_2.IsValidObject
  L3_2 = L1_2
  L2_2 = L2_2(L3_2)
  if L2_2 then
    L2_2 = nGameObject
    L2_2 = L2_2.GetTeam
    L3_2 = A0_2
    L2_2 = L2_2(L3_2)
    L3_2 = nGameObject
    L3_2 = L3_2.GetPosition
    L4_2 = A0_2
    L3_2, L4_2, L5_2 = L3_2(L4_2)
    L6_2 = nGameObject
    L6_2 = L6_2.GetPosition
    L7_2 = L1_2
    L6_2, L7_2, L8_2 = L6_2(L7_2)
    L9_2 = L6_2 - L3_2
    L10_2 = L7_2 - L4_2
    L11_2 = 0
    L12_2 = nVector
    L12_2 = L12_2.normalize
    L13_2 = L9_2
    L14_2 = L10_2
    L15_2 = L11_2
    L12_2, L13_2, L14_2 = L12_2(L13_2, L14_2, L15_2)
    L11_2 = L14_2
    L10_2 = L13_2
    L9_2 = L12_2
    L12_2 = nCondition
    L12_2 = L12_2.GetProperty
    L13_2 = A0_2
    L14_2 = "Radius"
    L12_2 = L12_2(L13_2, L14_2)
    L13_2 = nObjectManager
    L13_2 = L13_2.GetObjectsInRadius_SortedByDistance
    L14_2 = L3_2
    L15_2 = L4_2
    L16_2 = L5_2
    L17_2 = L12_2
    L18_2 = kType_Creature
    L13_2 = L13_2(L14_2, L15_2, L16_2, L17_2, L18_2)
    L14_2 = ipairs
    L15_2 = L13_2
    L14_2, L15_2, L16_2 = L14_2(L15_2)
    for L17_2, L18_2 in L14_2, L15_2, L16_2 do
      L19_2 = nGameObject
      L19_2 = L19_2.ValidateHostileTarget
      L20_2 = L2_2
      L21_2 = L18_2
      L19_2 = L19_2(L20_2, L21_2)
      if L19_2 then
        L19_2 = nGameObject
        L19_2 = L19_2.GetPosition
        L20_2 = L18_2
        L19_2, L20_2, L21_2 = L19_2(L20_2)
        L22_2 = L19_2 - L3_2
        L23_2 = L20_2 - L4_2
        L24_2 = 0
        L25_2 = nVector
        L25_2 = L25_2.normalize
        L26_2 = L22_2
        L27_2 = L23_2
        L28_2 = L24_2
        L25_2, L26_2, L27_2 = L25_2(L26_2, L27_2, L28_2)
        L24_2 = L27_2
        L23_2 = L26_2
        L22_2 = L25_2
        L25_2 = nVector
        L25_2 = L25_2.dot
        L26_2 = L9_2
        L27_2 = L10_2
        L28_2 = L11_2
        L29_2 = L22_2
        L30_2 = L23_2
        L31_2 = L24_2
        L25_2 = L25_2(L26_2, L27_2, L28_2, L29_2, L30_2, L31_2)
        if L25_2 < 0.5 then
          L25_2 = true
          L26_2 = L19_2
          L27_2 = L20_2
          L28_2 = L21_2
          L29_2 = L18_2
          return L25_2, L26_2, L27_2, L28_2, L29_2
        end
      end
    end
  end
  L2_2 = false
  return L2_2
end

L0_1[1] = L1_1
