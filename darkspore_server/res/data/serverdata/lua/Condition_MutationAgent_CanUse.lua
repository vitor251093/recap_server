local L0_1, L1_1, L2_1, L3_1, L4_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = require
L1_1 = "Modifiers!modifier_mutation_agent_passive.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_MutationAgent_CanUse = L0_1
L0_1 = nCondition_MutationAgent_CanUse
L0_1.namespace = "nCondition_MutationAgent_CanUse"
L0_1 = nCondition_MutationAgent_CanUse
L0_1.conditionType = 0
L0_1 = nCondition_MutationAgent_CanUse
L0_1.playerDistance = 25
L0_1 = nCondition_MutationAgent_CanUse
L1_1 = {}
L2_1 = {}
L2_1.name = "Radius"
L3_1 = kReflectionType_float
L2_1.type = L3_1
L2_1.value = "20.0"
L3_1 = {}
L3_1.name = "IgnoreMySpecies"
L4_1 = kReflectionType_bool
L3_1.type = L4_1
L3_1.value = "false"
L1_1[1] = L2_1
L1_1[2] = L3_1
L0_1.properties = L1_1
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "MutationAgent_CanUse"
L2_1 = nCondition_MutationAgent_CanUse
L0_1(L1_1, L2_1)
L0_1 = nCondition_MutationAgent_CanUse

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2, L19_2, L20_2, L21_2, L22_2, L23_2
  L1_2 = nUtil
  L1_2 = L1_2.SPID
  L2_2 = "MutationAgentPassive"
  L1_2 = L1_2(L2_2)
  L2_2 = nUtil
  L2_2 = L2_2.SPID
  L3_2 = "EliteModifier"
  L2_2 = L2_2(L3_2)
  L3_2 = nModifier
  L3_2 = L3_2.GetFirstModifierByGUID
  L4_2 = A0_2
  L5_2 = L1_2
  L3_2 = L3_2(L4_2, L5_2)
  L4_2 = nGameObject
  L4_2 = L4_2.GetPosition
  L5_2 = A0_2
  L4_2, L5_2, L6_2 = L4_2(L5_2)
  L7_2 = nCondition
  L7_2 = L7_2.GetProperty
  L8_2 = A0_2
  L9_2 = "Radius"
  L7_2 = L7_2(L8_2, L9_2)
  L8_2 = nCondition
  L8_2 = L8_2.GetProperty
  L9_2 = A0_2
  L10_2 = "IgnoreMySpecies"
  L8_2 = L8_2(L9_2, L10_2)
  if L3_2 ~= nil then
    L9_2 = nAgent
    L9_2 = L9_2.GetBestTarget
    L10_2 = A0_2
    L9_2 = L9_2(L10_2)
    L10_2 = nGameObject
    L10_2 = L10_2.GetObjectDistance
    L11_2 = A0_2
    L12_2 = L9_2
    L10_2 = L10_2(L11_2, L12_2)
    L11_2 = nCondition_MutationAgent_CanUse
    L11_2 = L11_2.playerDistance
    if L10_2 < L11_2 then
      L11_2 = nObjectManager
      L11_2 = L11_2.GetObjectsInRadius_SortedByDistance
      L12_2 = L4_2
      L13_2 = L5_2
      L14_2 = L6_2
      L15_2 = L7_2
      L16_2 = kType_Creature
      L11_2 = L11_2(L12_2, L13_2, L14_2, L15_2, L16_2)
      L12_2 = ipairs
      L13_2 = L11_2
      L12_2, L13_2, L14_2 = L12_2(L13_2)
      for L15_2, L16_2 in L12_2, L13_2, L14_2 do
        if L16_2 ~= A0_2 then
          L17_2 = nGameObject
          L17_2 = L17_2.IsAlive
          L18_2 = L16_2
          L17_2 = L17_2(L18_2)
          if L17_2 then
            L17_2 = nGameObject
            L17_2 = L17_2.GetTeam
            L18_2 = L16_2
            L17_2 = L17_2(L18_2)
            L18_2 = nGameObject
            L18_2 = L18_2.GetTeam
            L19_2 = A0_2
            L18_2 = L18_2(L19_2)
            if L17_2 == L18_2 then
              if L8_2 then
                L17_2 = nGameObject
                L17_2 = L17_2.IsSameSpecies
                L18_2 = A0_2
                L19_2 = L16_2
                L17_2 = L17_2(L18_2, L19_2)
                if L17_2 then
                  goto lbl_119
                end
              end
              L17_2 = nAttribute
              L17_2 = L17_2.GetAttributeValue
              L18_2 = L16_2
              L19_2 = nAttributeType
              L19_2 = L19_2.Intangible
              L17_2 = L17_2(L18_2, L19_2)
              if L17_2 == 0 then
                L17_2 = nModifier
                L17_2 = L17_2.GetFirstModifierByGUID
                L18_2 = L16_2
                L19_2 = L2_2
                L17_2 = L17_2(L18_2, L19_2)
                L18_2 = kObjIDNone
                if L17_2 == L18_2 then
                  L18_2 = nGameObject
                  L18_2 = L18_2.GetObjectDistance
                  L19_2 = A0_2
                  L20_2 = L16_2
                  L18_2 = L18_2(L19_2, L20_2)
                  if 5 < L18_2 then
                    L19_2 = nAbility
                    L19_2 = L19_2.CallFunctionInContext
                    L20_2 = L3_2
                    L21_2 = nModifier_Mutation_Agent_Passive
                    L21_2 = L21_2.CanUseAbility
                    L19_2 = L19_2(L20_2, L21_2)
                    if L19_2 then
                      L19_2 = true
                      L20_2 = 0
                      L21_2 = 0
                      L22_2 = 0
                      L23_2 = L16_2
                      return L19_2, L20_2, L21_2, L22_2, L23_2
                    end
                  end
                end
              end
            end
          end
        end
        ::lbl_119::
      end
    end
  end
  L9_2 = false
  return L9_2
end

L0_1[1] = L1_1
