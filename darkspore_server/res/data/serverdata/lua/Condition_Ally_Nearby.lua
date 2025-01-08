local L0_1, L1_1, L2_1, L3_1, L4_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_AllyNearby = L0_1
L0_1 = nCondition_AllyNearby
L0_1.namespace = "nCondition_AllyNearby"
L0_1 = nCondition_AllyNearby
L0_1.conditionType = 0
L0_1 = nCondition_AllyNearby
L1_1 = {}
L2_1 = {}
L2_1.name = "Radius"
L3_1 = kReflectionType_float
L2_1.type = L3_1
L2_1.value = "20.0"
L3_1 = {}
L3_1.name = "IgnoreMySpecies"
L4_1 = kReflectionType_bool
L3_1.type = L4_1
L3_1.value = "false"
L1_1[1] = L2_1
L1_1[2] = L3_1
L0_1.properties = L1_1
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "AllyNearby"
L2_1 = nCondition_AllyNearby
L0_1(L1_1, L2_1)
L0_1 = nCondition_AllyNearby

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2
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
  L7_2 = "IgnoreMySpecies"
  L5_2 = L5_2(L6_2, L7_2)
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
    if L11_2 ~= A0_2 then
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
          if L5_2 then
            L12_2 = nGameObject
            L12_2 = L12_2.IsSameSpecies
            L13_2 = A0_2
            L14_2 = L11_2
            L12_2 = L12_2(L13_2, L14_2)
            if L12_2 then
              goto lbl_60
            end
          end
          L12_2 = true
          L13_2 = 0
          L14_2 = 0
          L15_2 = 0
          L16_2 = L11_2
          return L12_2, L13_2, L14_2, L15_2, L16_2
        end
      end
    end
    ::lbl_60::
  end
  L7_2 = false
  return L7_2
end

L0_1[1] = L1_1
L0_1 = {}
nCondition_AllyNotNearby = L0_1
L0_1 = nCondition_AllyNotNearby
L0_1.namespace = "nCondition_AllyNotNearby"
L0_1 = nCondition_AllyNotNearby
L0_1.conditionType = 0
L0_1 = nCondition_AllyNotNearby
L1_1 = {}
L2_1 = {}
L2_1.name = "Radius"
L3_1 = kReflectionType_float
L2_1.type = L3_1
L2_1.value = "20.0"
L1_1[1] = L2_1
L0_1.properties = L1_1
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "AllyNotNearby"
L2_1 = nCondition_AllyNotNearby
L0_1(L1_1, L2_1)
L0_1 = nCondition_AllyNotNearby

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2
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
    if L10_2 ~= A0_2 then
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
          L11_2 = false
          return L11_2
        end
      end
    end
  end
  L6_2 = true
  return L6_2
end

L0_1[1] = L1_1
