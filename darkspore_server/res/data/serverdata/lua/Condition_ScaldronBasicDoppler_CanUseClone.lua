local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = require
L1_1 = "Modifiers!modifier_ScaldronBasicDoppler_Passive.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_ScaldronBasicDoppler_CanUseClone = L0_1
L0_1 = nCondition_ScaldronBasicDoppler_CanUseClone
L0_1.namespace = "nCondition_ScaldronBasicDoppler_CanUseClone"
L0_1 = nCondition_ScaldronBasicDoppler_CanUseClone
L0_1.conditionType = 0
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "ScaldronBasicDoppler_CanUseClone"
L2_1 = nCondition_ScaldronBasicDoppler_CanUseClone
L0_1(L1_1, L2_1)
L0_1 = nCondition_ScaldronBasicDoppler_CanUseClone

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2
  L1_2 = nUtil
  L1_2 = L1_2.SPID
  L2_2 = "ScaldronBasicDoppler_Passive"
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
    L5_2 = nModifier_ScaldronBasicDoppler_Passive
    L5_2 = L5_2.GetFakeID
    L3_2 = L3_2(L4_2, L5_2)
    if L3_2 ~= nil then
      L4_2 = nObjectManager
      L4_2 = L4_2.IsValidObject
      L5_2 = L3_2
      L4_2 = L4_2(L5_2)
      if L4_2 ~= false then
        L4_2 = nGameObject
        L4_2 = L4_2.IsAlive
        L5_2 = L3_2
        L4_2 = L4_2(L5_2)
        if L4_2 ~= false then
          goto lbl_35
        end
      end
    end
    L4_2 = true
    return L4_2
  end
  ::lbl_35::
  L3_2 = false
  return L3_2
end

L0_1[1] = L1_1
