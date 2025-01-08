local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_Zelem_Mark = L0_1
L0_1 = nCondition_Zelem_Mark
L0_1.namespace = "nCondition_Zelem_Mark"
L0_1 = nCondition_Zelem_Mark
L0_1.conditionType = 0
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "CheckZelemMark"
L2_1 = nCondition_Zelem_Mark
L0_1(L1_1, L2_1)
L0_1 = nCondition_Zelem_Mark
L1_1 = nUtil
L1_1 = L1_1.SPID
L2_1 = "MarkOfZelem"
L1_1 = L1_1(L2_1)
L0_1.debuff = L1_1

function L0_1(A0_2, A1_2, A2_2)
  local L3_2, L4_2, L5_2
  L3_2 = nModifier
  L3_2 = L3_2.GetFirstModifierByGUID
  L4_2 = A0_2
  L5_2 = A1_2
  L3_2 = L3_2(L4_2, L5_2)
  L4_2 = kObjIDNone
  if L3_2 == L4_2 then
    L4_2 = true
    return L4_2
  end
  L4_2 = nModifier
  L4_2 = L4_2.GetStackCount
  L5_2 = L3_2
  L4_2 = L4_2(L5_2)
  if A2_2 > L4_2 then
    L5_2 = true
    return L5_2
  end
end

L1_1 = nCondition_Zelem_Mark

function L2_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2
  L1_2 = nAgent
  L1_2 = L1_2.GetBestTarget
  L2_2 = A0_2
  L1_2 = L1_2(L2_2)
  L2_2 = nGameObject
  L2_2 = L2_2.IsPet
  L3_2 = L1_2
  L2_2 = L2_2(L3_2)
  if L2_2 then
    L2_2 = nGameObject
    L2_2 = L2_2.GetOwnerID
    L3_2 = L1_2
    L2_2 = L2_2(L3_2)
    L1_2 = L2_2
  end
  L2_2 = kObjIDNone
  if L1_2 ~= L2_2 then
    L2_2 = nModifier
    L2_2 = L2_2.AgentHasModifierMatchingGUID
    L3_2 = L1_2
    L4_2 = nCondition_Zelem_Mark
    L4_2 = L4_2.debuff
    L2_2 = L2_2(L3_2, L4_2)
    if not L2_2 then
      L2_2 = true
      L3_2 = 0
      L4_2 = 0
      L5_2 = 0
      L6_2 = L1_2
      return L2_2, L3_2, L4_2, L5_2, L6_2
    end
  end
  L2_2 = false
  return L2_2
end

L1_1[1] = L2_1
