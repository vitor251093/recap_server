local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_PulsarPull = L0_1
L0_1 = nCondition_PulsarPull
L0_1.namespace = "nCondition_PulsarPull"
L0_1 = nCondition_PulsarPull
L0_1.conditionType = 0
L0_1 = nCondition_PulsarPull
L1_1 = {}
L0_1.properties = L1_1
L0_1 = nCondition_PulsarPull
L1_1 = nUtil
L1_1 = L1_1.SPID
L2_1 = "PullModifier"
L1_1 = L1_1(L2_1)
L0_1.EnergyDefenseDebuffModifier = L1_1
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "Condition_PulsarPull"
L2_1 = nCondition_PulsarPull
L0_1(L1_1, L2_1)
L0_1 = nCondition_PulsarPull

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2
  L1_2 = nAgent
  L1_2 = L1_2.GetBestTarget
  L2_2 = A0_2
  L1_2 = L1_2(L2_2)
  L2_2 = nGameObject
  L2_2 = L2_2.IsAlive
  L3_2 = L1_2
  L2_2 = L2_2(L3_2)
  if L2_2 then
    L2_2 = nGameObject
    L2_2 = L2_2.IsModifierActive
    L3_2 = L1_2
    L4_2 = nCondition_PulsarPull
    L4_2 = L4_2.EnergyDefenseDebuffModifier
    L2_2 = L2_2(L3_2, L4_2)
    if L2_2 then
      L2_2 = true
      return L2_2
    end
  end
  L2_2 = false
  return L2_2
end

L0_1[1] = L1_1
