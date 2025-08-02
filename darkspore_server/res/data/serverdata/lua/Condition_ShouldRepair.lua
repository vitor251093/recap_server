local L0_1, L1_1, L2_1, L3_1, L4_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_ShouldRepair = L0_1
L0_1 = nCondition_ShouldRepair
L0_1.namespace = "nCondition_ShouldRepair"
L0_1 = nCondition_ShouldRepair
L0_1.conditionType = 0
L0_1 = nCondition_ShouldRepair
L1_1 = {}
L2_1 = {}
L2_1.name = "Radius"
L3_1 = kReflectionType_float
L2_1.type = L3_1
L2_1.value = "20.0"
L3_1 = {}
L3_1.name = "RepairChance"
L4_1 = kReflectionType_float
L3_1.type = L4_1
L3_1.value = "0.5"
L1_1[1] = L2_1
L1_1[2] = L3_1
L0_1.properties = L1_1
L0_1 = nCondition_ShouldRepair
L1_1 = nUtil
L1_1 = L1_1.SPID
L2_1 = "DontRepairModifier"
L1_1 = L1_1(L2_1)
L0_1.dontRepairModifier = L1_1
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "ShouldRepair"
L2_1 = nCondition_ShouldRepair
L0_1(L1_1, L2_1)
L0_1 = nCondition_ShouldRepair

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2, L19_2, L20_2, L21_2
  L1_2 = nGameObject
  L1_2 = L1_2.IsModifierActive
  L2_2 = A0_2
  L3_2 = nCondition_ShouldRepair
  L3_2 = L3_2.dontRepairModifier
  L1_2 = L1_2(L2_2, L3_2)
  if not L1_2 then
    L1_2 = nCondition
    L1_2 = L1_2.GetProperty
    L2_2 = A0_2
    L3_2 = "RepairChance"
    L1_2 = L1_2(L2_2, L3_2)
    L2_2 = math
    L2_2 = L2_2.random
    L2_2 = L2_2()
    if L1_2 > L2_2 then
      L2_2 = nGameObject
      L2_2 = L2_2.GetPosition
      L3_2 = A0_2
      L2_2, L3_2, L4_2 = L2_2(L3_2)
      L5_2 = nCondition
      L5_2 = L5_2.GetProperty
      L6_2 = A0_2
      L7_2 = "Radius"
      L5_2 = L5_2(L6_2, L7_2)
      L6_2 = nObjectManager
      L6_2 = L6_2.GetObjectsInRadius
      L7_2 = L2_2
      L8_2 = L3_2
      L9_2 = L4_2
      L10_2 = L5_2
      L11_2 = kType_Creature
      L6_2 = L6_2(L7_2, L8_2, L9_2, L10_2, L11_2)
      L7_2 = ipairs
      L8_2 = L6_2
      L7_2, L8_2, L9_2 = L7_2(L8_2)
      for L10_2, L11_2 in L7_2, L8_2, L9_2 do
        L12_2 = nObjectManager
        L12_2 = L12_2.IsValidObject
        L13_2 = L11_2
        L12_2 = L12_2(L13_2)
        if L12_2 and L11_2 ~= A0_2 then
          L12_2 = nGameObject
          L12_2 = L12_2.GetTeam
          L13_2 = L11_2
          L12_2 = L12_2(L13_2)
          L13_2 = nGameObject
          L13_2 = L13_2.GetTeam
          L14_2 = A0_2
          L13_2 = L13_2(L14_2)
          if L12_2 == L13_2 then
            L12_2 = nGameObject
            L12_2 = L12_2.IsAlive
            L13_2 = L11_2
            L12_2 = L12_2(L13_2)
            if not L12_2 then
              L12_2 = nGameObject
              L12_2 = L12_2.IsCorpseFadingAway
              L13_2 = L11_2
              L12_2 = L12_2(L13_2)
              if not L12_2 then
                L12_2 = nGameObject
                L12_2 = L12_2.GetCreatureType
                L13_2 = L11_2
                L12_2 = L12_2(L13_2)
                L13_2 = nDamageTypes
                L13_2 = L13_2.Technology
                if L12_2 == L13_2 then
                  L12_2 = nGameObject
                  L12_2 = L12_2.GetHitDescriptors
                  L13_2 = L11_2
                  L12_2 = L12_2(L13_2)
                  L13_2 = nBit
                  L13_2 = L13_2.And
                  L14_2 = L12_2
                  L15_2 = nHitDescriptors
                  L15_2 = L15_2.Critical
                  L13_2 = L13_2(L14_2, L15_2)
                  L13_2 = L13_2 ~= 0
                  if not L13_2 then
                    L14_2 = nGameObject
                    L14_2 = L14_2.GetPosition
                    L15_2 = L11_2
                    L14_2, L15_2, L16_2 = L14_2(L15_2)
                    L17_2 = true
                    L18_2 = L14_2
                    L19_2 = L15_2
                    L20_2 = L16_2
                    L21_2 = L11_2
                    return L17_2, L18_2, L19_2, L20_2, L21_2
                  end
                end
              end
            end
          end
        end
      end
    else
      L2_2 = nGameObject
      L2_2 = L2_2.GetNPCRank
      L3_2 = A0_2
      L2_2 = L2_2(L3_2)
      L3_2 = nModifier
      L3_2 = L3_2.RequestModifier
      L4_2 = A0_2
      L5_2 = A0_2
      L6_2 = nCondition_ShouldRepair
      L6_2 = L6_2.dontRepairModifier
      L7_2 = kObjIDNone
      L8_2 = L2_2
      L3_2(L4_2, L5_2, L6_2, L7_2, L8_2)
    end
  end
  L1_2 = false
  return L1_2
end

L0_1[1] = L1_1
