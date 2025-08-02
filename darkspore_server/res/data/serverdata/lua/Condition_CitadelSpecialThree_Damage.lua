local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = require
L1_1 = "Modifiers!modifier_CitadelSpecialThree_LaserZoneController.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_CitadelSpecialThree_Damage = L0_1
L0_1 = nCondition_CitadelSpecialThree_Damage
L0_1.namespace = "nCondition_CitadelSpecialThree_Damage"
L0_1 = nCondition_CitadelSpecialThree_Damage
L0_1.conditionType = 0
L0_1 = nCondition_CitadelSpecialThree_Damage
L1_1 = {}
L0_1.properties = L1_1
L0_1 = nCondition_CitadelSpecialThree_Damage
L0_1.distance = 20
L0_1 = nCondition_CitadelSpecialThree_Damage
L0_1.damageDelay = 2
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "CitadelSpecialThree_Damage"
L2_1 = nCondition_CitadelSpecialThree_Damage
L0_1(L1_1, L2_1)
L0_1 = nCondition_CitadelSpecialThree_Damage

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2
  L1_2 = nAgent
  L1_2 = L1_2.GetBestTarget
  L2_2 = A0_2
  L1_2 = L1_2(L2_2)
  L2_2 = nUtil
  L2_2 = L2_2.SPID
  L3_2 = "CitadelSpecialThree_LaserZoneControllerModifier"
  L2_2 = L2_2(L3_2)
  L3_2 = nModifier
  L3_2 = L3_2.GetFirstModifierByGUID
  L4_2 = A0_2
  L5_2 = L2_2
  L3_2 = L3_2(L4_2, L5_2)
  if L1_2 == nil or L3_2 == nil then
    L4_2 = true
    return L4_2
  end
  L4_2 = nGameObject
  L4_2 = L4_2.GetObjectDistance
  L5_2 = A0_2
  L6_2 = L1_2
  L4_2 = L4_2(L5_2, L6_2)
  L5_2 = nCondition_CitadelSpecialThree_Damage
  L5_2 = L5_2.distance
  if L4_2 <= L5_2 then
    L5_2 = true
    return L5_2
  else
    L5_2 = nGameSimulator
    L5_2 = L5_2.GetGameTime
    L5_2 = L5_2()
    L6_2 = nAbility
    L6_2 = L6_2.CallFunctionInContext
    L7_2 = L3_2
    L8_2 = nModifier_CitadelSpecialThree_LaserZoneController
    L8_2 = L8_2.GetLastDamageTime
    L9_2 = L2_2
    L6_2 = L6_2(L7_2, L8_2, L9_2)
    L7_2 = nCondition_CitadelSpecialThree_Damage
    L7_2 = L7_2.damageDelay
    L7_2 = L6_2 + L7_2
    if L5_2 < L7_2 then
      L7_2 = false
      return L7_2
    end
  end
  L5_2 = true
  return L5_2
end

L0_1[1] = L1_1
