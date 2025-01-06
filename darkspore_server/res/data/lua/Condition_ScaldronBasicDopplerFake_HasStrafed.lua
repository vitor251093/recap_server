local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = require
L1_1 = "Modifiers!modifier_ScaldronBasicDopplerFake_Passive.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_ScaldronBasicDopplerFake_HasStrafed = L0_1
L0_1 = nCondition_ScaldronBasicDopplerFake_HasStrafed
L0_1.namespace = "nCondition_ScaldronBasicDopplerFake_HasStrafed"
L0_1 = nCondition_ScaldronBasicDopplerFake_HasStrafed
L0_1.conditionType = 0
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "ScaldronBasicDopplerFake_HasStrafed"
L2_1 = nCondition_ScaldronBasicDopplerFake_HasStrafed
L0_1(L1_1, L2_1)
L0_1 = nCondition_ScaldronBasicDopplerFake_HasStrafed

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2
  L1_2 = nUtil
  L1_2 = L1_2.SPID
  L2_2 = "ScaldronBasicDopplerFake_Passive"
  L1_2 = L1_2(L2_2)
  L2_2 = nModifier
  L2_2 = L2_2.GetFirstModifierByGUID
  L3_2 = A0_2
  L4_2 = L1_2
  L2_2 = L2_2(L3_2, L4_2)
  L3_2 = kObjIDNone
  if L2_2 ~= L3_2 then
    L3_2 = nAbility
    L3_2 = L3_2.CallFunctionInContext
    L4_2 = L2_2
    L5_2 = nModifier_ScaldronBasicDopplerFake_Passive
    L5_2 = L5_2.HasStrafed
    L3_2 = L3_2(L4_2, L5_2)
    if L3_2 then
      L3_2 = true
      return L3_2
    end
  end
  L3_2 = false
  return L3_2
end

L0_1[1] = L1_1
