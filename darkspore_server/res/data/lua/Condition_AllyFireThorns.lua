local L0_1, L1_1, L2_1, L3_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_AllyFireThorns = L0_1
L0_1 = nCondition_AllyFireThorns
L0_1.namespace = "nCondition_AllyFireThorns"
L0_1 = nCondition_AllyFireThorns
L0_1.conditionType = 0
L0_1 = nCondition_AllyFireThorns
L1_1 = {}
L2_1 = {}
L2_1.name = "Radius"
L3_1 = kReflectionType_float
L2_1.type = L3_1
L2_1.value = "20.0"
L1_1[1] = L2_1
L0_1.properties = L1_1
L0_1 = nCondition_AllyFireThorns
L1_1 = nUtil
L1_1 = L1_1.SPID
L2_1 = "Modifier_FireThorns"
L1_1 = L1_1(L2_1)
L0_1.FireThornsModifier = L1_1
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "condition_AllyFireThorns"
L2_1 = nCondition_AllyFireThorns
L0_1(L1_1, L2_1)
L0_1 = nCondition_AllyFireThorns

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2
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
    L11_2 = nGameObject
    L11_2 = L11_2.IsAlive
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
        L11_2 = L11_2.IsModifierActive
        L12_2 = L10_2
        L13_2 = nCondition_AllyFireThorns
        L13_2 = L13_2.FireThornsModifier
        L11_2 = L11_2(L12_2, L13_2)
        if not L11_2 then
          L11_2 = true
          L12_2 = 0
          L13_2 = 0
          L14_2 = 0
          L15_2 = L10_2
          return L11_2, L12_2, L13_2, L14_2, L15_2
        end
      end
    end
  end
  L6_2 = false
  return L6_2
end

L0_1[1] = L1_1
