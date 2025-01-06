local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_ManaOverload = L0_1
L0_1 = nCondition_ManaOverload
L0_1.namespace = "nCondition_ManaOverload"
L0_1 = nCondition_ManaOverload
L0_1.conditionType = 0
L0_1 = nCondition_ManaOverload
L0_1.maxMana = 5
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "ManaOverload"
L2_1 = nCondition_ManaOverload
L0_1(L1_1, L2_1)
L0_1 = nCondition_ManaOverload

function L1_1(A0_2)
  local L1_2, L2_2
  L1_2 = nGameObject
  L1_2 = L1_2.GetManaPoints
  L2_2 = A0_2
  L1_2 = L1_2(L2_2)
  L2_2 = nCondition_ManaOverload
  L2_2 = L2_2.maxMana
  if L1_2 >= L2_2 then
    L2_2 = true
    return L2_2
  end
  L2_2 = false
  return L2_2
end

L0_1[1] = L1_1
