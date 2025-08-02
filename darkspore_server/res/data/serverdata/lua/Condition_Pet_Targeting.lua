local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_Pet_Targeting = L0_1
L0_1 = nCondition_Pet_Targeting
L0_1.namespace = "nCondition_Pet_Targeting"
L0_1 = nCondition_Pet_Targeting
L0_1.conditionType = 0
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "PetTargeting"
L2_1 = nCondition_Pet_Targeting
L0_1(L1_1, L2_1)

function L0_1(A0_2, A1_2, A2_2, A3_2, A4_2)
  local L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2
  L5_2 = nGameObject
  L5_2 = L5_2.IsAlive
  L6_2 = A1_2
  L5_2 = L5_2(L6_2)
  if not L5_2 then
    L5_2 = false
    return L5_2
  end
  L5_2 = nAgent
  L5_2 = L5_2.HasTargetsOnAggroList
  L6_2 = A1_2
  L5_2 = L5_2(L6_2)
  if not L5_2 then
    L5_2 = false
    return L5_2
  end
  L5_2 = nGameObject
  L5_2 = L5_2.GetPosition
  L6_2 = A1_2
  L5_2, L6_2, L7_2 = L5_2(L6_2)
  L8_2 = nGameObject
  L8_2 = L8_2.GetFootprintRadius
  L9_2 = A1_2
  L8_2 = L8_2(L9_2)
  L9_2 = nAgent
  L9_2 = L9_2.InPerceptionCircle
  L10_2 = A0_2
  L11_2 = L5_2
  L12_2 = L6_2
  L13_2 = L7_2
  L14_2 = L8_2
  return L9_2(L10_2, L11_2, L12_2, L13_2, L14_2)
end

L1_1 = nCondition_Pet_Targeting

function L2_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2
  L1_2 = nAgent
  L1_2 = L1_2.GetBestTarget
  L2_2 = A0_2
  L1_2 = L1_2(L2_2)
  L2_2 = nGameObject
  L2_2 = L2_2.GetOwnerID
  L3_2 = A0_2
  L2_2 = L2_2(L3_2)
  L3_2 = nil
  L4_2 = nil
  L5_2 = nil
  L6_2 = nGameObject
  L6_2 = L6_2.IsAlive
  L7_2 = L2_2
  L6_2 = L6_2(L7_2)
  if L6_2 then
    L6_2 = nGameObject
    L6_2 = L6_2.GetPosition
    L7_2 = L2_2
    L6_2, L7_2, L8_2 = L6_2(L7_2)
    L5_2 = L8_2
    L4_2 = L7_2
    L3_2 = L6_2
  else
    L6_2 = nGameObject
    L6_2 = L6_2.GetPosition
    L7_2 = A0_2
    L6_2, L7_2, L8_2 = L6_2(L7_2)
    L5_2 = L8_2
    L4_2 = L7_2
    L3_2 = L6_2
  end
  L6_2 = L0_1
  L7_2 = A0_2
  L8_2 = L1_2
  L9_2 = L3_2
  L10_2 = L4_2
  L11_2 = L5_2
  L6_2 = L6_2(L7_2, L8_2, L9_2, L10_2, L11_2)
  if L6_2 then
    L6_2 = true
    L7_2 = 0
    L8_2 = 0
    L9_2 = 0
    L10_2 = L1_2
    return L6_2, L7_2, L8_2, L9_2, L10_2
  end
  L6_2 = nAgent
  L6_2 = L6_2.GetTargetsOnAggroList
  L7_2 = A0_2
  L6_2 = L6_2(L7_2)
  L7_2 = ipairs
  L8_2 = L6_2
  L7_2, L8_2, L9_2 = L7_2(L8_2)
  for L10_2, L11_2 in L7_2, L8_2, L9_2 do
    L12_2 = L0_1
    L13_2 = A0_2
    L14_2 = L11_2
    L15_2 = L3_2
    L16_2 = L4_2
    L17_2 = L5_2
    L12_2 = L12_2(L13_2, L14_2, L15_2, L16_2, L17_2)
    if L12_2 then
      L12_2 = true
      L13_2 = 0
      L14_2 = 0
      L15_2 = 0
      L16_2 = L11_2
      return L12_2, L13_2, L14_2, L15_2, L16_2
    end
  end
  L7_2 = false
  return L7_2
end

L1_1[1] = L2_1
