local L0_1, L1_1, L2_1, L3_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_LowAllyHealth = L0_1
L0_1 = nCondition_LowAllyHealth
L0_1.namespace = "nCondition_LowAllyHealth"
L0_1 = nCondition_LowAllyHealth
L0_1.conditionType = 0
L0_1 = nCondition_LowAllyHealth
L1_1 = {}
L2_1 = {}
L2_1.name = "Radius"
L3_1 = kReflectionType_float
L2_1.type = L3_1
L2_1.value = "20.0"
L1_1[1] = L2_1
L0_1.properties = L1_1
L0_1 = nCondition_LowAllyHealth
L1_1 = {}
L2_1 = {}
L2_1.name = "HealthPercent"
L3_1 = kReflectionType_float
L2_1.type = L3_1
L2_1.value = "50.0"
L1_1[1] = L2_1
L0_1.properties = L1_1
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "LowAllyHealth"
L2_1 = nCondition_LowAllyHealth
L0_1(L1_1, L2_1)
L0_1 = nCondition_LowAllyHealth

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
  L5_2 = nObjectManager
  L5_2 = L5_2.GetObjectsInRadius
  L6_2 = L1_2
  L7_2 = L2_2
  L8_2 = L3_2
  L9_2 = L4_2
  L10_2 = kType_Creature
  L5_2 = L5_2(L6_2, L7_2, L8_2, L9_2, L10_2)
  L6_2 = ipairs
  L7_2 = L5_2
  L6_2, L7_2, L8_2 = L6_2(L7_2)
  for L9_2, L10_2 in L6_2, L7_2, L8_2 do
    L11_2 = nObjectManager
    L11_2 = L11_2.IsValidObject
    L12_2 = L10_2
    L11_2 = L11_2(L12_2)
    if L11_2 then
      L11_2 = nGameObject
      L11_2 = L11_2.GetTeam
      L12_2 = L10_2
      L11_2 = L11_2(L12_2)
      L12_2 = nGameObject
      L12_2 = L12_2.GetTeam
      L13_2 = A0_2
      L12_2 = L12_2(L13_2)
      if L11_2 == L12_2 then
        L11_2 = nGameObject
        L11_2 = L11_2.IsAlive
        L12_2 = L10_2
        L11_2 = L11_2(L12_2)
        if L11_2 then
          L11_2 = nGameObject
          L11_2 = L11_2.GetHitPoints
          L12_2 = L10_2
          L11_2 = L11_2(L12_2)
          L12_2 = nGameObject
          L12_2 = L12_2.GetMaxHitPoints
          L13_2 = L10_2
          L12_2 = L12_2(L13_2)
          L11_2 = L11_2 / L12_2
          L12_2 = nCondition
          L12_2 = L12_2.GetProperty
          L13_2 = A0_2
          L14_2 = "HealthPercent"
          L12_2 = L12_2(L13_2, L14_2)
          L12_2 = L12_2 / 100
          if L11_2 < L12_2 then
            L13_2 = true
            L14_2 = 1
            L15_2 = 1
            L16_2 = 0
            L17_2 = L10_2
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
