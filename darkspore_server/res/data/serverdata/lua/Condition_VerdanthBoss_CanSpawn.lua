local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = require
L1_1 = "Abilities!ability_spawn.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_VerdanthBoss_CanSpawn = L0_1
L0_1 = nCondition_VerdanthBoss_CanSpawn
L0_1.namespace = "nCondition_VerdanthBoss_CanSpawn"
L0_1 = nCondition_VerdanthBoss_CanSpawn
L0_1.conditionType = 0
L0_1 = nCondition_VerdanthBoss_CanSpawn
L1_1 = {}
L0_1.properties = L1_1
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "VerdanthBoss_CanSpawn"
L2_1 = nCondition_VerdanthBoss_CanSpawn
L0_1(L1_1, L2_1)
L0_1 = nCondition_VerdanthBoss_CanSpawn

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2
  L1_2 = nGameObject
  L1_2 = L1_2.GetNPCRank
  L2_2 = A0_2
  L1_2 = L1_2(L2_2)
  L2_2 = nObjectManager
  L2_2 = L2_2.GetObjectsOfOwner
  L3_2 = A0_2
  L2_2 = L2_2(L3_2)
  L3_2 = #L2_2
  L4_2 = nAbility
  L4_2 = L4_2.GetRankedValueWithRank
  L5_2 = nAbility_Spawn
  L5_2 = L5_2.maxNumberCreatureSpawns
  L6_2 = L1_2
  L4_2 = L4_2(L5_2, L6_2)
  if L3_2 < L4_2 then
    L3_2 = true
    return L3_2
  end
  L3_2 = false
  return L3_2
end

L0_1[1] = L1_1
