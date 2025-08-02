local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_Fire_Pet_Position = L0_1
L0_1 = nCondition_Fire_Pet_Position
L0_1.namespace = "nCondition_Fire_Pet_Position"
L0_1 = nCondition_Fire_Pet_Position
L0_1.conditionType = 0
L0_1 = nCondition_Fire_Pet_Position
L1_1 = nUtil
L1_1 = L1_1.SPID
L2_1 = "LightningCage"
L1_1 = L1_1(L2_1)
L0_1.lockdownModifier = L1_1
L0_1 = nCondition_Fire_Pet_Position
L0_1.minimumDistance = 0
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "Condition_FirePetPositioning"
L2_1 = nCondition_Fire_Pet_Position
L0_1(L1_1, L2_1)
L0_1 = nCondition_Fire_Pet_Position

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2, L19_2, L20_2
  L1_2 = nAgent
  L1_2 = L1_2.GetTargetsOnAggroList
  L2_2 = A0_2
  L1_2 = L1_2(L2_2)
  L2_2 = nGameObject
  L2_2 = L2_2.GetTeam
  L3_2 = A0_2
  L2_2 = L2_2(L3_2)
  L3_2 = ipairs
  L4_2 = L1_2
  L3_2, L4_2, L5_2 = L3_2(L4_2)
  for L6_2, L7_2 in L3_2, L4_2, L5_2 do
    L8_2 = nGameObject
    L8_2 = L8_2.ValidateHostileTarget
    L9_2 = L2_2
    L10_2 = L7_2
    L8_2 = L8_2(L9_2, L10_2)
    if L8_2 then
      L8_2 = nGameObject
      L8_2 = L8_2.IsModifierActive
      L9_2 = L7_2
      L10_2 = nCondition_Fire_Pet_Position
      L10_2 = L10_2.lockdownModifier
      L8_2 = L8_2(L9_2, L10_2)
      if L8_2 then
        L8_2 = nGameObject
        L8_2 = L8_2.GetPosition
        L9_2 = A0_2
        L8_2, L9_2, L10_2 = L8_2(L9_2)
        L11_2 = nGameObject
        L11_2 = L11_2.GetPosition
        L12_2 = L7_2
        L11_2, L12_2, L13_2 = L11_2(L12_2)
        L14_2 = nVector
        L14_2 = L14_2.distance
        L15_2 = L8_2
        L16_2 = L9_2
        L17_2 = L10_2
        L18_2 = L11_2
        L19_2 = L12_2
        L20_2 = L13_2
        L14_2 = L14_2(L15_2, L16_2, L17_2, L18_2, L19_2, L20_2)
        L15_2 = nCondition_Fire_Pet_Position
        L15_2 = L15_2.minimumDistance
        if L14_2 > L15_2 then
          L15_2 = true
          L16_2 = 0
          L17_2 = 0
          L18_2 = 0
          L19_2 = L7_2
          return L15_2, L16_2, L17_2, L18_2, L19_2
        end
        L15_2 = false
        return L15_2
      end
    end
  end
  L3_2 = false
  return L3_2
end

L0_1[1] = L1_1
