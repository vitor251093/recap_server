local L0_1, L1_1, L2_1, L3_1, L4_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_ShouldConsumeCorpse = L0_1
L0_1 = nCondition_ShouldConsumeCorpse
L0_1.namespace = "nCondition_ShouldConsumeCorpse"
L0_1 = nCondition_ShouldConsumeCorpse
L0_1.conditionType = 0
L0_1 = nCondition_ShouldConsumeCorpse
L1_1 = {}
L2_1 = {}
L2_1.name = "Radius"
L3_1 = kReflectionType_float
L2_1.type = L3_1
L2_1.value = "20.0"
L3_1 = {}
L3_1.name = "ConsumeChance"
L4_1 = kReflectionType_float
L3_1.type = L4_1
L3_1.value = "0.5"
L1_1[1] = L2_1
L1_1[2] = L3_1
L0_1.properties = L1_1
L0_1 = nCondition_ShouldConsumeCorpse
L1_1 = nUtil
L1_1 = L1_1.SPID
L2_1 = "BeingConsumedModifier"
L1_1 = L1_1(L2_1)
L0_1.beingConsumedModifier = L1_1
L0_1 = nCondition_ShouldConsumeCorpse
L0_1.maxEating = 2
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "ShouldConsumeCorpse"
L2_1 = nCondition_ShouldConsumeCorpse
L0_1(L1_1, L2_1)

function L0_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2
  L1_2 = 0
  L2_2 = nModifier
  L2_2 = L2_2.GetFirstModifierByGUID
  L3_2 = A0_2
  L4_2 = nCondition_ShouldConsumeCorpse
  L4_2 = L4_2.beingConsumedModifier
  L2_2 = L2_2(L3_2, L4_2)
  L3_2 = kObjIDNone
  if L2_2 ~= L3_2 then
    L3_2 = nModifier
    L3_2 = L3_2.GetStackCount
    L4_2 = L2_2
    L3_2 = L3_2(L4_2)
    L1_2 = L3_2
  end
  L3_2 = nCondition_ShouldConsumeCorpse
  L3_2 = L3_2.maxEating
  L3_2 = L1_2 > L3_2
  return L3_2
end

IsAlreadyBeingConsumed = L0_1
L0_1 = nCondition_ShouldConsumeCorpse

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2, L19_2, L20_2, L21_2
  L1_2 = nCondition
  L1_2 = L1_2.GetProperty
  L2_2 = A0_2
  L3_2 = "ConsumeChance"
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
        L12_2 = L12_2.IsAlive
        L13_2 = L11_2
        L12_2 = L12_2(L13_2)
        if not L12_2 then
          L12_2 = nGameObject
          L12_2 = L12_2.IsCorpseFadingAway
          L13_2 = L11_2
          L12_2 = L12_2(L13_2)
          if not L12_2 then
            L12_2 = nPlayer
            L12_2 = L12_2.IsPlayerControlledObject
            L13_2 = L11_2
            L12_2 = L12_2(L13_2)
            if not L12_2 then
              L12_2 = IsAlreadyBeingConsumed
              L13_2 = L11_2
              L12_2 = L12_2(L13_2)
              if not L12_2 then
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
  end
  L2_2 = false
  return L2_2
end

L0_1[1] = L1_1
