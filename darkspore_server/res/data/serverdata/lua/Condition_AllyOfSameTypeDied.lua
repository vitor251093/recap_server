local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_AllyOfSameTypeDied = L0_1
L0_1 = nCondition_AllyOfSameTypeDied
L0_1.namespace = "nCondition_AllyOfSameTypeDied"
L0_1 = nCondition_AllyOfSameTypeDied
L0_1.conditionType = 0
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "AllyOfSameTypeDied"
L2_1 = nCondition_AllyOfSameTypeDied
L0_1(L1_1, L2_1)
L0_1 = nCondition_AllyOfSameTypeDied

function L1_1(A0_2)
  local L1_2, L2_2, L3_2
  L1_2 = nGameObject
  L1_2 = L1_2.IsStimulusActive
  L2_2 = A0_2
  L3_2 = nStimulusFlags
  L3_2 = L3_2.AllyOfSameTypeDied
  L1_2 = L1_2(L2_2, L3_2)
  if L1_2 then
    L1_2 = true
    return L1_2
  end
  L1_2 = false
  return L1_2
end

L0_1[1] = L1_1
