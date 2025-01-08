local L0_1, L1_1, L2_1, L3_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_Most_Isolated_Enemy = L0_1
L0_1 = nCondition_Most_Isolated_Enemy
L0_1.namespace = "nCondition_Most_Isolated_Enemy"
L0_1 = nCondition_Most_Isolated_Enemy
L0_1.conditionType = 0
L0_1 = nCondition_Most_Isolated_Enemy
L1_1 = {}
L2_1 = {}
L2_1.name = "Radius"
L3_1 = kReflectionType_float
L2_1.type = L3_1
L2_1.value = "50.0"
L1_1[1] = L2_1
L0_1.properties = L1_1
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "MostIsolatedEnemy"
L2_1 = nCondition_Most_Isolated_Enemy
L0_1(L1_1, L2_1)

function L0_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2
  L2_2 = 0
  L3_2 = nCondition
  L3_2 = L3_2.GetProperty
  L4_2 = A0_2
  L5_2 = "Radius"
  L3_2 = L3_2(L4_2, L5_2)
  L4_2 = nGameObject
  L4_2 = L4_2.GetTeam
  L5_2 = A1_2
  L4_2 = L4_2(L5_2)
  L5_2 = nGameObject
  L5_2 = L5_2.GetPosition
  L6_2 = A1_2
  L5_2, L6_2, L7_2 = L5_2(L6_2)
  L8_2 = nObjectManager
  L8_2 = L8_2.GetObjectsInRadius
  L9_2 = L5_2
  L10_2 = L6_2
  L11_2 = L7_2
  L12_2 = L3_2
  L13_2 = kType_Creature
  L8_2 = L8_2(L9_2, L10_2, L11_2, L12_2, L13_2)
  L9_2 = ipairs
  L10_2 = L8_2
  L9_2, L10_2, L11_2 = L9_2(L10_2)
  for L12_2, L13_2 in L9_2, L10_2, L11_2 do
    if L13_2 ~= A1_2 then
      L14_2 = nGameObject
      L14_2 = L14_2.GetTeam
      L15_2 = L13_2
      L14_2 = L14_2(L15_2)
      if L14_2 == L4_2 then
        L14_2 = nGameObject
        L14_2 = L14_2.GetObjectDistance
        L15_2 = L13_2
        L16_2 = A1_2
        L14_2 = L14_2(L15_2, L16_2)
        L2_2 = L2_2 + L14_2
      end
    end
  end
  return L2_2
end

GetTotalDistanceFromAllies = L0_1
L0_1 = nCondition_Most_Isolated_Enemy

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2
  L1_2 = nGameObject
  L1_2 = L1_2.GetIsStealthed
  L2_2 = A0_2
  L1_2 = L1_2(L2_2)
  if not L1_2 then
    L2_2 = false
    return L2_2
  end
  L2_2 = nCondition
  L2_2 = L2_2.GetProperty
  L3_2 = A0_2
  L4_2 = "Radius"
  L2_2 = L2_2(L3_2, L4_2)
  L3_2 = nGameObject
  L3_2 = L3_2.GetTeam
  L4_2 = A0_2
  L3_2 = L3_2(L4_2)
  L4_2 = nGameObject
  L4_2 = L4_2.GetPosition
  L5_2 = A0_2
  L4_2, L5_2, L6_2 = L4_2(L5_2)
  L7_2 = nObjectManager
  L7_2 = L7_2.GetObjectsInRadius
  L8_2 = L4_2
  L9_2 = L5_2
  L10_2 = L6_2
  L11_2 = L2_2
  L12_2 = kType_Creature
  L7_2 = L7_2(L8_2, L9_2, L10_2, L11_2, L12_2)
  L8_2 = {}
  L9_2 = ipairs
  L10_2 = L7_2
  L9_2, L10_2, L11_2 = L9_2(L10_2)
  for L12_2, L13_2 in L9_2, L10_2, L11_2 do
    if L13_2 ~= A0_2 then
      L14_2 = nGameObject
      L14_2 = L14_2.ValidateHostileTarget
      L15_2 = L3_2
      L16_2 = L13_2
      L14_2 = L14_2(L15_2, L16_2)
      if L14_2 then
        L14_2 = GetTotalDistanceFromAllies
        L15_2 = A0_2
        L16_2 = L13_2
        L14_2 = L14_2(L15_2, L16_2)
        L8_2[L13_2] = L14_2
      end
    end
  end
  L9_2 = kObjIDNone
  L10_2 = 0
  L11_2 = pairs
  L12_2 = L8_2
  L11_2, L12_2, L13_2 = L11_2(L12_2)
  for L14_2, L15_2 in L11_2, L12_2, L13_2 do
    if L15_2 >= L10_2 then
      L9_2 = L14_2
      L10_2 = L15_2
    end
  end
  L11_2 = kObjIDNone
  if L9_2 ~= L11_2 then
    L11_2 = true
    L12_2 = 0
    L13_2 = 0
    L14_2 = 0
    L15_2 = L9_2
    return L11_2, L12_2, L13_2, L14_2, L15_2
  end
  L11_2 = false
  return L11_2
end

L0_1[1] = L1_1
