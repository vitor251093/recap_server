local L0_1, L1_1, L2_1, L3_1, L4_1, L5_1, L6_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_AllyNeedsBuff = L0_1
L0_1 = nCondition_AllyNeedsBuff
L0_1.namespace = "nCondition_AllyNeedsBuff"
L0_1 = nCondition_AllyNeedsBuff
L0_1.conditionType = 0
L0_1 = nCondition_AllyNeedsBuff
L1_1 = {}
L2_1 = {}
L2_1.name = "Buff"
L3_1 = kReflectionType_string
L2_1.type = L3_1
L2_1.value = ""
L3_1 = {}
L3_1.name = "Radius"
L4_1 = kReflectionType_float
L3_1.type = L4_1
L3_1.value = "20.0"
L4_1 = {}
L4_1.name = "Stacks"
L5_1 = kReflectionType_int
L4_1.type = L5_1
L4_1.value = "0"
L5_1 = {}
L5_1.name = "CheckSelf"
L6_1 = kReflectionType_bool
L5_1.type = L6_1
L5_1.value = "false"
L1_1[1] = L2_1
L1_1[2] = L3_1
L1_1[3] = L4_1
L1_1[4] = L5_1
L0_1.properties = L1_1
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "AllyNeedsBuff"
L2_1 = nCondition_AllyNeedsBuff
L0_1(L1_1, L2_1)

function L0_1(A0_2, A1_2, A2_2)
  local L3_2, L4_2, L5_2
  L3_2 = nModifier
  L3_2 = L3_2.GetFirstModifierByGUID
  L4_2 = A0_2
  L5_2 = A1_2
  L3_2 = L3_2(L4_2, L5_2)
  L4_2 = kObjIDNone
  if L3_2 == L4_2 then
    L4_2 = true
    return L4_2
  end
  L4_2 = nModifier
  L4_2 = L4_2.GetStackCount
  L5_2 = L3_2
  L4_2 = L4_2(L5_2)
  if A2_2 > L4_2 then
    L5_2 = true
    return L5_2
  end
end

L1_1 = nCondition_AllyNeedsBuff

function L2_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2
  L1_2 = nUtil
  L1_2 = L1_2.SPID
  L2_2 = nCondition
  L2_2 = L2_2.GetProperty
  L3_2 = A0_2
  L4_2 = "Buff"
  L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2 = L2_2(L3_2, L4_2)
  L1_2 = L1_2(L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2)
  L2_2 = nGameObject
  L2_2 = L2_2.GetPosition
  L3_2 = A0_2
  L2_2, L3_2, L4_2 = L2_2(L3_2)
  L5_2 = nCondition
  L5_2 = L5_2.GetProperty
  L6_2 = A0_2
  L7_2 = "Radius"
  L5_2 = L5_2(L6_2, L7_2)
  L6_2 = nCondition
  L6_2 = L6_2.GetProperty
  L7_2 = A0_2
  L8_2 = "Stacks"
  L6_2 = L6_2(L7_2, L8_2)
  L7_2 = nCondition
  L7_2 = L7_2.GetProperty
  L8_2 = A0_2
  L9_2 = "CheckSelf"
  L7_2 = L7_2(L8_2, L9_2)
  if L5_2 == 0 and L7_2 == true then
    L8_2 = L0_1
    L9_2 = A0_2
    L10_2 = L1_2
    L11_2 = L6_2
    L8_2 = L8_2(L9_2, L10_2, L11_2)
    if L8_2 then
      L8_2 = true
      L9_2 = 0
      L10_2 = 0
      L11_2 = 0
      L12_2 = A0_2
      return L8_2, L9_2, L10_2, L11_2, L12_2
    else
      L8_2 = false
      return L8_2
    end
  end
  L8_2 = nObjectManager
  L8_2 = L8_2.GetObjectsInRadius
  L9_2 = L2_2
  L10_2 = L3_2
  L11_2 = L4_2
  L12_2 = L5_2
  L13_2 = kType_Creature
  L8_2 = L8_2(L9_2, L10_2, L11_2, L12_2, L13_2)
  L9_2 = ipairs
  L10_2 = L8_2
  L9_2, L10_2, L11_2 = L9_2(L10_2)
  for L12_2, L13_2 in L9_2, L10_2, L11_2 do
    L14_2 = nGameObject
    L14_2 = L14_2.IsAlive
    L15_2 = L13_2
    L14_2 = L14_2(L15_2)
    if L14_2 then
      L14_2 = nGameObject
      L14_2 = L14_2.GetTeam
      L15_2 = L13_2
      L14_2 = L14_2(L15_2)
      L15_2 = nGameObject
      L15_2 = L15_2.GetTeam
      L16_2 = A0_2
      L15_2 = L15_2(L16_2)
      if L14_2 == L15_2 and (L13_2 ~= A0_2 or L7_2) then
        L14_2 = L0_1
        L15_2 = L13_2
        L16_2 = L1_2
        L17_2 = L6_2
        L14_2 = L14_2(L15_2, L16_2, L17_2)
        if L14_2 then
          L14_2 = true
          L15_2 = 0
          L16_2 = 0
          L17_2 = 0
          L18_2 = L13_2
          return L14_2, L15_2, L16_2, L17_2, L18_2
        end
      end
    end
  end
  L9_2 = false
  return L9_2
end

L1_1[1] = L2_1
