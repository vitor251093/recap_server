local L0_1, L1_1, L2_1, L3_1, L4_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_HasStacks = L0_1
L0_1 = nCondition_HasStacks
L0_1.namespace = "nCondition_HasStacks"
L0_1 = nCondition_HasStacks
L0_1.conditionType = 0
L0_1 = nCondition_HasStacks
L1_1 = {}
L2_1 = {}
L2_1.name = "Buff"
L3_1 = kReflectionType_string
L2_1.type = L3_1
L2_1.value = ""
L3_1 = {}
L3_1.name = "Stacks"
L4_1 = kReflectionType_int
L3_1.type = L4_1
L3_1.value = "1"
L1_1[1] = L2_1
L1_1[2] = L3_1
L0_1.properties = L1_1
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "HasStacks"
L2_1 = nCondition_HasStacks
L0_1(L1_1, L2_1)
L0_1 = nCondition_HasStacks

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2
  L1_2 = nUtil
  L1_2 = L1_2.SPID
  L2_2 = nCondition
  L2_2 = L2_2.GetProperty
  L3_2 = A0_2
  L4_2 = "Buff"
  L2_2, L3_2, L4_2, L5_2 = L2_2(L3_2, L4_2)
  L1_2 = L1_2(L2_2, L3_2, L4_2, L5_2)
  L2_2 = nCondition
  L2_2 = L2_2.GetProperty
  L3_2 = A0_2
  L4_2 = "Stacks"
  L2_2 = L2_2(L3_2, L4_2)
  L3_2 = nModifier
  L3_2 = L3_2.GetFirstModifierByGUID
  L4_2 = A0_2
  L5_2 = L1_2
  L3_2 = L3_2(L4_2, L5_2)
  L4_2 = kObjIDNone
  if L3_2 ~= L4_2 then
    L4_2 = nModifier
    L4_2 = L4_2.GetStackCount
    L5_2 = L3_2
    L4_2 = L4_2(L5_2)
    if L2_2 <= L4_2 then
      L5_2 = true
      return L5_2
    end
  end
  L4_2 = false
  return L4_2
end

L0_1[1] = L1_1
