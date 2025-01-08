local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = require
L1_1 = "Modifiers!modifier_shadow_boss_passive.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_Shadow_Boss_Duplicate = L0_1
L0_1 = nCondition_Shadow_Boss_Duplicate
L0_1.namespace = "nCondition_Shadow_Boss_Duplicate"
L0_1 = nCondition_Shadow_Boss_Duplicate
L0_1.conditionType = 0
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "ShadowBossDuplicateCheck"
L2_1 = nCondition_Shadow_Boss_Duplicate
L0_1(L1_1, L2_1)
L0_1 = nCondition_Shadow_Boss_Duplicate

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2
  L1_2 = nModifier
  L1_2 = L1_2.GetFirstModifierByGUID
  L2_2 = A0_2
  L3_2 = nUtil
  L3_2 = L3_2.SPID
  L4_2 = "ShadowBossPassive"
  L3_2, L4_2, L5_2 = L3_2(L4_2)
  L1_2 = L1_2(L2_2, L3_2, L4_2, L5_2)
  L2_2 = false
  L3_2 = kObjIDNone
  if L1_2 ~= L3_2 then
    L3_2 = nModifier
    L3_2 = L3_2.CallFunctionInContext
    L4_2 = L1_2
    L5_2 = nModifier_Shadow_Boss_Passive
    L5_2 = L5_2.CanDuplicate
    L3_2 = L3_2(L4_2, L5_2)
    L2_2 = L3_2
  end
  return L2_2
end

L0_1[1] = L1_1
