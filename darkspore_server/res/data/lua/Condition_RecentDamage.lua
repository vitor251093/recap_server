local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_RecentDamage = L0_1
L0_1 = nCondition_RecentDamage
L0_1.namespace = "nCondition_RecentDamage"
L0_1 = nCondition_RecentDamage
L0_1.conditionType = 0
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "RecentDamageCheck"
L2_1 = nCondition_RecentDamage
L0_1(L1_1, L2_1)
L0_1 = nCondition_RecentDamage

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2
  L1_2 = false
  L2_2 = nGameObject
  L2_2 = L2_2.GetRecentDamage
  L3_2 = A0_2
  L4_2 = 999999
  L5_2 = 3
  L6_2 = false
  L2_2 = L2_2(L3_2, L4_2, L5_2, L6_2)
  if 10 < L2_2 then
    L1_2 = true
  end
  return L1_2
end

L0_1[1] = L1_1
