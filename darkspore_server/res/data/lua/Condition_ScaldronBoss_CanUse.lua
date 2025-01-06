local L0_1, L1_1, L2_1, L3_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = require
L1_1 = "Modifiers!modifier_ScaldronBoss_AIPassive.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_ScaldronBoss_CanUse = L0_1
L0_1 = nCondition_ScaldronBoss_CanUse
L0_1.namespace = "nCondition_ScaldronBoss_CanUse"
L0_1 = nCondition_ScaldronBoss_CanUse
L0_1.conditionType = 0
L0_1 = nCondition_ScaldronBoss_CanUse
L1_1 = {}
L2_1 = {}
L2_1.name = "Ability"
L3_1 = kReflectionType_string
L2_1.type = L3_1
L2_1.value = ""
L1_1[1] = L2_1
L0_1.properties = L1_1
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "ScaldronBoss_CanUse"
L2_1 = nCondition_ScaldronBoss_CanUse
L0_1(L1_1, L2_1)
L0_1 = nCondition_ScaldronBoss_CanUse

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2
  L1_2 = nUtil
  L1_2 = L1_2.SPID
  L2_2 = nCondition
  L2_2 = L2_2.GetProperty
  L3_2 = A0_2
  L4_2 = "Ability"
  L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2 = L2_2(L3_2, L4_2)
  L1_2 = L1_2(L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2)
  L2_2 = nUtil
  L2_2 = L2_2.SPID
  L3_2 = "ScaldronBoss_AIPassive"
  L2_2 = L2_2(L3_2)
  L3_2 = nUtil
  L3_2 = L3_2.SPID
  L4_2 = "ScaldronBoss_AIPassiveStage2"
  L3_2 = L3_2(L4_2)
  L4_2 = nModifier
  L4_2 = L4_2.GetFirstModifierByGUID
  L5_2 = A0_2
  L6_2 = L2_2
  L4_2 = L4_2(L5_2, L6_2)
  L5_2 = kObjIDNone
  if L4_2 == L5_2 then
    L5_2 = nModifier
    L5_2 = L5_2.GetFirstModifierByGUID
    L6_2 = A0_2
    L7_2 = L3_2
    L5_2 = L5_2(L6_2, L7_2)
    L4_2 = L5_2
  end
  L5_2 = kObjIDNone
  if L4_2 ~= L5_2 then
    L5_2 = nAbility
    L5_2 = L5_2.CallFunctionInContext
    L6_2 = L4_2
    L7_2 = nModifier_ScaldronBoss_AIPassive
    L7_2 = L7_2.CanUseAbility
    L8_2 = L1_2
    L5_2 = L5_2(L6_2, L7_2, L8_2)
    if L5_2 then
      L6_2 = true
      return L6_2
    end
  end
  L5_2 = false
  return L5_2
end

L0_1[1] = L1_1
