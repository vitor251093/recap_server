local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_DogDistracted = L0_1
L0_1 = nCondition_DogDistracted
L0_1.namespace = "nCondition_DogDistracted"
L0_1 = nCondition_DogDistracted
L0_1.conditionType = 0
L0_1 = nCondition_DogDistracted
L0_1.chanceOfDistraction = 0.01
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "NoctDogIsDistracted"
L2_1 = nCondition_DogDistracted
L0_1(L1_1, L2_1)
L0_1 = nCondition_DogDistracted

function L1_1(A0_2)
  local L1_2, L2_2
  L1_2 = math
  L1_2 = L1_2.random
  L1_2 = L1_2()
  L2_2 = nCondition_DogDistracted
  L2_2 = L2_2.chanceOfDistraction
  if L1_2 < L2_2 then
    L1_2 = true
    return L1_2
  end
  L1_2 = false
  return L1_2
end

L0_1[1] = L1_1
