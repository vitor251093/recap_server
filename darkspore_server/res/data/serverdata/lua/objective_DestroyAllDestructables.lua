local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nObjective_DestroyAllDestructables = L0_1
L0_1 = nObjective_DestroyAllDestructables
L0_1.namespace = "nObjective_DestroyAllDestructables"
L0_1 = nObjective_DestroyAllDestructables
L1_1 = nUtil
L1_1 = L1_1.ToGUID
L2_1 = "0x09e6d558"
L1_1 = L1_1(L2_1)
L0_1.descriptionText = L1_1
L0_1 = nObjective_DestroyAllDestructables
L1_1 = nUtil
L1_1 = L1_1.ToGUID
L2_1 = "0x09e6d559"
L1_1 = L1_1(L2_1)
L0_1.progressText = L1_1
L0_1 = nObjective_DestroyAllDestructables
L0_1.groupObjective = true
L0_1 = nObjective_DestroyAllDestructables
L0_1.timeObjectiveRequires = true
L0_1 = nObjective_DestroyAllDestructables
L1_1 = nObjectiveEvents
L1_1 = L1_1.Death
L0_1.handledEvents = L1_1
L0_1 = nObjective_DestroyAllDestructables
L1_1 = kInvalidGUID
L0_1.completedVoiceOver = L1_1
L0_1 = nObjective_DestroyAllDestructables
L0_1.goldPercentage = 0.9
L0_1 = nObjective_DestroyAllDestructables
L0_1.silverPercentage = 0.7
L0_1 = nObjective_DestroyAllDestructables
L0_1.bronzePercentage = 0.5
L0_1 = nObjective_DestroyAllDestructables
L0_1.reportFrequencyPercent = 25
L0_1 = nObjective
L0_1 = L0_1.RegisterObjective
L1_1 = "DestroyAllDestructables"
L2_1 = nObjective_DestroyAllDestructables
L0_1(L1_1, L2_1)
L0_1 = nObjective_DestroyAllDestructables
L1_1 = nObjectiveFns
L1_1 = L1_1.Init

function L2_1()
  local L0_2, L1_2, L2_2, L3_2, L4_2, L5_2, L6_2
  L0_2 = nThreadData
  L0_2 = L0_2.CreatePrivateTable
  L0_2 = L0_2()
  L1_2 = nObjective
  L1_2 = L1_2.GetRegisteredDestructibles
  L1_2 = L1_2()
  L0_2.startingDestructables = L1_2
  L0_2.destroyedDestructables = 0
  L1_2 = nObjective_DestroyAllDestructables
  L1_2 = L1_2.reportFrequencyPercent
  L0_2.reportPercentage = L1_2
  L1_2 = nObjective
  L1_2 = L1_2.SetObjectiveIntData
  L2_2 = kAllPlayers
  L3_2 = 1
  L4_2 = nObjective_DestroyAllDestructables
  L4_2 = L4_2.goldPercentage
  L4_2 = L4_2 * 100
  L5_2 = false
  L6_2 = false
  L1_2(L2_2, L3_2, L4_2, L5_2, L6_2)
end

L0_1[L1_1] = L2_1
L0_1 = nObjective_DestroyAllDestructables
L1_1 = nObjectiveFns
L1_1 = L1_1.HandleEvent

function L2_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2
  L2_2 = nObjectiveEvents
  L2_2 = L2_2.Death
  if A0_2 == L2_2 then
    L2_2 = nObjective
    L2_2 = L2_2.GetObjectiveEventGUIDData
    L3_2 = A1_2
    L4_2 = 1
    L2_2 = L2_2(L3_2, L4_2)
    L3_2 = nThreadData
    L3_2 = L3_2.GetPrivateTable
    L3_2 = L3_2()
    L4_2 = nGameObject
    L4_2 = L4_2.GetNPCType
    L5_2 = L2_2
    L4_2 = L4_2(L5_2)
    L5_2 = nNPCType
    L5_2 = L5_2.Destructible
    if L4_2 == L5_2 then
      L4_2 = nGameObject
      L4_2 = L4_2.GetMarkerID
      L5_2 = L2_2
      L4_2 = L4_2(L5_2)
      if L4_2 ~= 0 then
        L5_2 = L3_2.destroyedDestructables
        L5_2 = L5_2 + 1
        L3_2.destroyedDestructables = L5_2
        L5_2 = L3_2.destroyedDestructables
        L6_2 = L3_2.startingDestructables
        L5_2 = L5_2 / L6_2
        L5_2 = L5_2 * 100
        if L5_2 <= 100 then
          L6_2 = L3_2.reportPercentage
          if L5_2 >= L6_2 then
            L6_2 = nObjective
            L6_2 = L6_2.SetObjectiveIntData
            L7_2 = kAllPlayers
            L8_2 = 0
            L9_2 = L3_2.reportPercentage
            L10_2 = true
            L11_2 = true
            L6_2(L7_2, L8_2, L9_2, L10_2, L11_2)
            L6_2 = L3_2.reportPercentage
            L7_2 = nObjective_DestroyAllDestructables
            L7_2 = L7_2.reportFrequencyPercent
            L6_2 = L6_2 + L7_2
            L3_2.reportPercentage = L6_2
          else
            L6_2 = nObjective
            L6_2 = L6_2.SetObjectiveIntData
            L7_2 = kAllPlayers
            L8_2 = 0
            L9_2 = L5_2
            L10_2 = true
            L11_2 = false
            L6_2(L7_2, L8_2, L9_2, L10_2, L11_2)
          end
        end
      end
    end
  end
end

L0_1[L1_1] = L2_1
L0_1 = nObjective_DestroyAllDestructables
L1_1 = nObjectiveFns
L1_1 = L1_1.ObjectiveStatus

function L2_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2
  L1_2 = nThreadData
  L1_2 = L1_2.GetPrivateTable
  L1_2 = L1_2()
  L2_2 = 1
  if L1_2 ~= nil then
    L3_2 = L1_2.startingDestructables
    if L3_2 ~= nil then
      L3_2 = L1_2.startingDestructables
      if L3_2 ~= 1 then
        L3_2 = L1_2.destroyedDestructables
        L4_2 = L1_2.startingDestructables
        L2_2 = L3_2 / L4_2
      end
    end
  end
  L3_2 = nObjective_DestroyAllDestructables
  L3_2 = L3_2.goldPercentage
  if L2_2 >= L3_2 then
    L3_2 = nObjectiveStatus
    L3_2 = L3_2.Gold
    return L3_2
  else
    L3_2 = nObjective_DestroyAllDestructables
    L3_2 = L3_2.silverPercentage
    if L2_2 >= L3_2 then
      L3_2 = nObjectiveStatus
      L3_2 = L3_2.Silver
      return L3_2
    else
      L3_2 = nObjective_DestroyAllDestructables
      L3_2 = L3_2.bronzePercentage
      if L2_2 >= L3_2 then
        L3_2 = nObjectiveStatus
        L3_2 = L3_2.Bronze
        return L3_2
      else
        L3_2 = nObjectiveStatus
        L3_2 = L3_2.Failed
        return L3_2
      end
    end
  end
end

L0_1[L1_1] = L2_1
