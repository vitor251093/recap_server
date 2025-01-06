local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_Nearest_Player = L0_1
L0_1 = nCondition_Nearest_Player
L0_1.namespace = "nCondition_Nearest_Player"
L0_1 = nCondition_Nearest_Player
L0_1.conditionType = 0
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "NearestPlayer"
L2_1 = nCondition_Nearest_Player
L0_1(L1_1, L2_1)
L0_1 = nCondition_Nearest_Player

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2
  L1_2 = nGameObject
  L1_2 = L1_2.GetTeam
  L2_2 = A0_2
  L1_2 = L1_2(L2_2)
  L2_2 = nPlayer
  L2_2 = L2_2.GetPlayerControlledObjects
  L2_2 = L2_2()
  L3_2 = 99999
  L4_2 = kObjIDNone
  L5_2 = ipairs
  L6_2 = L2_2
  L5_2, L6_2, L7_2 = L5_2(L6_2)
  for L8_2, L9_2 in L5_2, L6_2, L7_2 do
    L10_2 = nGameObject
    L10_2 = L10_2.ValidateHostileTarget
    L11_2 = L1_2
    L12_2 = L9_2
    L10_2 = L10_2(L11_2, L12_2)
    if L10_2 then
      L10_2 = nGameObject
      L10_2 = L10_2.GetObjectDistance
      L11_2 = A0_2
      L12_2 = L9_2
      L10_2 = L10_2(L11_2, L12_2)
      if L3_2 > L10_2 then
        L4_2 = L9_2
        L3_2 = L10_2
      end
    end
  end
  L5_2 = kObjIDNone
  if L4_2 ~= L5_2 then
    L5_2 = true
    L6_2 = 0
    L7_2 = 0
    L8_2 = 0
    L9_2 = L4_2
    return L5_2, L6_2, L7_2, L8_2, L9_2
  end
  L5_2 = false
  return L5_2
end

L0_1[1] = L1_1
