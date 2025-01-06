local L0_1, L1_1, L2_1, L3_1, L4_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_AllyHasDebuff = L0_1
L0_1 = nCondition_AllyHasDebuff
L0_1.namespace = "nCondition_AllyHasDebuff"
L0_1 = nCondition_AllyHasDebuff
L0_1.conditionType = 0
L0_1 = nCondition_AllyHasDebuff
L1_1 = {}
L2_1 = {}
L2_1.name = "Radius"
L3_1 = kReflectionType_float
L2_1.type = L3_1
L2_1.value = "20.0"
L3_1 = {}
L3_1.name = "Randomness"
L4_1 = kReflectionType_float
L3_1.type = L4_1
L3_1.value = "0.0075"
L1_1[1] = L2_1
L1_1[2] = L3_1
L0_1.properties = L1_1
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "AllyHasDebuff"
L2_1 = nCondition_AllyHasDebuff
L0_1(L1_1, L2_1)
L0_1 = nCondition_AllyHasDebuff

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2
  L1_2 = nGameObject
  L1_2 = L1_2.GetPosition
  L2_2 = A0_2
  L1_2, L2_2, L3_2 = L1_2(L2_2)
  L4_2 = nCondition
  L4_2 = L4_2.GetProperty
  L5_2 = A0_2
  L6_2 = "Radius"
  L4_2 = L4_2(L5_2, L6_2)
  L5_2 = nCondition
  L5_2 = L5_2.GetProperty
  L6_2 = A0_2
  L7_2 = "Randomness"
  L5_2 = L5_2(L6_2, L7_2)
  L6_2 = math
  L6_2 = L6_2.random
  L6_2 = L6_2()
  if L5_2 > L6_2 then
    L6_2 = nObjectManager
    L6_2 = L6_2.GetObjectsInRadius
    L7_2 = L1_2
    L8_2 = L2_2
    L9_2 = L3_2
    L10_2 = L4_2
    L11_2 = kType_Creature
    L6_2 = L6_2(L7_2, L8_2, L9_2, L10_2, L11_2)
    L7_2 = ipairs
    L8_2 = L6_2
    L7_2, L8_2, L9_2 = L7_2(L8_2)
    for L10_2, L11_2 in L7_2, L8_2, L9_2 do
      L12_2 = nGameObject
      L12_2 = L12_2.IsAlive
      L13_2 = L11_2
      L12_2 = L12_2(L13_2)
      if L12_2 then
        L12_2 = nGameObject
        L12_2 = L12_2.GetTeam
        L13_2 = L11_2
        L12_2 = L12_2(L13_2)
        L13_2 = nGameObject
        L13_2 = L13_2.GetTeam
        L14_2 = A0_2
        L13_2 = L13_2(L14_2)
        if L12_2 == L13_2 then
          L12_2 = nModifier
          L12_2 = L12_2.GetModifiersMatchingDescriptor
          L13_2 = L11_2
          L14_2 = nDescriptors
          L14_2 = L14_2.IsDebuff
          L12_2 = L12_2(L13_2, L14_2)
          L13_2 = #L12_2
          if 0 < L13_2 then
            L13_2 = true
            L14_2 = 0
            L15_2 = 0
            L16_2 = 0
            L17_2 = L11_2
            return L13_2, L14_2, L15_2, L16_2, L17_2
          end
        end
      end
    end
  end
  L6_2 = false
  return L6_2
end

L0_1[1] = L1_1
