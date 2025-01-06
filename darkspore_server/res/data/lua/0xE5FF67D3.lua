local L0_1, L1_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = require
L1_1 = "Modifiers!modifier_tree_root_passive.lua"
L0_1(L1_1)
L0_1 = {}
nLevelObject = L0_1
L0_1 = nLevelObject

function L1_1(A0_2, A1_2, A2_2)
  local L3_2, L4_2, L5_2, L6_2
  L3_2 = nGameObject
  L3_2 = L3_2.SetGraphicsState
  L4_2 = A1_2
  L5_2 = nUtil
  L5_2 = L5_2.SPID
  L6_2 = "dead"
  L5_2, L6_2 = L5_2(L6_2)
  L3_2(L4_2, L5_2, L6_2)
  L3_2 = nModifier
  L3_2 = L3_2.GetFirstModifierByGUID
  L4_2 = A1_2
  L5_2 = nUtil
  L5_2 = L5_2.SPID
  L6_2 = "TreeRootPassive"
  L5_2, L6_2 = L5_2(L6_2)
  L3_2 = L3_2(L4_2, L5_2, L6_2)
  L4_2 = kObjIDNone
  if L3_2 ~= L4_2 then
    L4_2 = nModifier
    L4_2 = L4_2.CallFunctionInContext
    L5_2 = L3_2
    L6_2 = nModifier_Tree_Root_Passive
    L6_2 = L6_2.OnTreeDeath
    L4_2(L5_2, L6_2)
  end
end

L0_1.OnTreeDeath = L1_1
