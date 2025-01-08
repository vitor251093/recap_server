local L0_1, L1_1, L2_1, L3_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_LowHealth = L0_1
L0_1 = nCondition_LowHealth
L0_1.namespace = "nCondition_LowHealth"
L0_1 = nCondition_LowHealth
L0_1.conditionType = 0
L0_1 = nCondition_LowHealth
L1_1 = {}
L2_1 = {}
L2_1.name = "HealthPercent"
L3_1 = kReflectionType_float
L2_1.type = L3_1
L2_1.value = "30.0"
L1_1[1] = L2_1
L0_1.properties = L1_1
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "LowHealth"
L2_1 = nCondition_LowHealth
L0_1(L1_1, L2_1)
L0_1 = nCondition_LowHealth

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2
  L1_2 = nGameObject
  L1_2 = L1_2.GetHitPoints
  L2_2 = A0_2
  L1_2 = L1_2(L2_2)
  L2_2 = nGameObject
  L2_2 = L2_2.GetMaxHitPoints
  L3_2 = A0_2
  L2_2 = L2_2(L3_2)
  L1_2 = L1_2 / L2_2
  L2_2 = nCondition
  L2_2 = L2_2.GetProperty
  L3_2 = A0_2
  L4_2 = "HealthPercent"
  L2_2 = L2_2(L3_2, L4_2)
  L2_2 = L2_2 / 100
  if L1_2 <= L2_2 then
    L3_2 = true
    return L3_2
  end
  L3_2 = false
  return L3_2
end

L0_1[1] = L1_1
