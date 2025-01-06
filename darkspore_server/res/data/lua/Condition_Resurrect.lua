local L0_1, L1_1, L2_1, L3_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_Resurrect = L0_1
L0_1 = nCondition_Resurrect
L0_1.namespace = "nCondition_Resurrect"
L0_1 = nCondition_Resurrect
L0_1.conditionType = 0
L0_1 = nCondition_Resurrect
L1_1 = {}
L2_1 = {}
L2_1.name = "Radius"
L3_1 = kReflectionType_float
L2_1.type = L3_1
L2_1.value = "20.0"
L1_1[1] = L2_1
L0_1.properties = L1_1
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "Resurrect"
L2_1 = nCondition_Resurrect
L0_1(L1_1, L2_1)
L0_1 = nCondition_Resurrect

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2
  L1_2 = nGameObject
  L1_2 = L1_2.GetPosition
  L2_2 = A0_2
  L1_2, L2_2, L3_2 = L1_2(L2_2)
  L4_2 = nObjectManager
  L4_2 = L4_2.GetObjectsInRadius
  L5_2 = L1_2
  L6_2 = L2_2
  L7_2 = L3_2
  L8_2 = 20
  L9_2 = kType_Creature
  L4_2 = L4_2(L5_2, L6_2, L7_2, L8_2, L9_2)
  L5_2 = ipairs
  L6_2 = L4_2
  L5_2, L6_2, L7_2 = L5_2(L6_2)
  for L8_2, L9_2 in L5_2, L6_2, L7_2 do
    L10_2 = nObjectManager
    L10_2 = L10_2.IsValidObject
    L11_2 = L9_2
    L10_2 = L10_2(L11_2)
    if L10_2 and L9_2 ~= A0_2 then
      L10_2 = nGameObject
      L10_2 = L10_2.GetTeam
      L11_2 = L9_2
      L10_2 = L10_2(L11_2)
      L11_2 = nGameObject
      L11_2 = L11_2.GetTeam
      L12_2 = A0_2
      L11_2 = L11_2(L12_2)
      if L10_2 == L11_2 then
        L10_2 = nGameObject
        L10_2 = L10_2.IsAlive
        L11_2 = L9_2
        L10_2 = L10_2(L11_2)
        if L10_2 == false then
          L10_2 = nGameObject
          L10_2 = L10_2.IsCorpseFadingAway
          L11_2 = L9_2
          L10_2 = L10_2(L11_2)
          if not L10_2 then
            L10_2 = nGameObject
            L10_2 = L10_2.GetHitDescriptors
            L11_2 = L9_2
            L10_2 = L10_2(L11_2)
            L11_2 = nBit
            L11_2 = L11_2.And
            L12_2 = L10_2
            L13_2 = nHitDescriptors
            L13_2 = L13_2.Critical
            L11_2 = L11_2(L12_2, L13_2)
            L11_2 = L11_2 ~= 0
            if not L11_2 then
              L12_2 = true
              L13_2 = 1
              L14_2 = 1
              L15_2 = 0
              L16_2 = L9_2
              return L12_2, L13_2, L14_2, L15_2, L16_2
            end
          end
        end
      end
    end
  end
  L5_2 = false
  return L5_2
end

L0_1[1] = L1_1
