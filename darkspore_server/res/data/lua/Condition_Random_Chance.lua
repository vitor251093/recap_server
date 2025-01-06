local L0_1, L1_1, L2_1, L3_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_RandomChance = L0_1
L0_1 = nCondition_RandomChance
L0_1.namespace = "nCondition_RandomChance"
L0_1 = nCondition_RandomChance
L0_1.conditionType = 0
L0_1 = nCondition_RandomChance
L1_1 = {}
L2_1 = {}
L2_1.name = "Chance"
L3_1 = kReflectionType_float
L2_1.type = L3_1
L2_1.value = "0.5"
L1_1[1] = L2_1
L0_1.properties = L1_1
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "RandomChance"
L2_1 = nCondition_RandomChance
L0_1(L1_1, L2_1)
L0_1 = nCondition_RandomChance

function L1_1(A0_2)
  local L1_2, L2_2, L3_2
  L1_2 = nCondition
  L1_2 = L1_2.GetProperty
  L2_2 = A0_2
  L3_2 = "Chance"
  L1_2 = L1_2(L2_2, L3_2)
  L2_2 = math
  L2_2 = L2_2.random
  L2_2 = L2_2()
  if L1_2 > L2_2 then
    L2_2 = true
    return L2_2
  end
  L2_2 = false
  return L2_2
end

L0_1[1] = L1_1
