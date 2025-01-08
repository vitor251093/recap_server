local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nObjective_NoSlowing = L0_1
L0_1 = nObjective_NoSlowing
L0_1.namespace = "nObjective_NoSlowing"
L0_1 = nObjective_NoSlowing
L1_1 = nUtil
L1_1 = L1_1.ToGUID
L2_1 = "0x09e6d038"
L1_1 = L1_1(L2_1)
L0_1.descriptionText = L1_1
L0_1 = nObjective_NoSlowing
L1_1 = nObjectiveEvents
L1_1 = L1_1.ModifierCreated
L0_1.handledEvents = L1_1
L0_1 = nObjective_NoSlowing
L0_1.gold = 0
L0_1 = nObjective_NoSlowing
L0_1.silver = 10
L0_1 = nObjective_NoSlowing
L0_1.bronze = 20
L0_1 = nObjective
L0_1 = L0_1.RegisterObjective
L1_1 = "NoSlowing"
L2_1 = nObjective_NoSlowing
L0_1(L1_1, L2_1)
L0_1 = nObjective_NoSlowing
L1_1 = nObjectiveFns
L1_1 = L1_1.Init

function L2_1()
  local L0_2, L1_2
  L0_2 = nThreadData
  L0_2 = L0_2.CreatePrivateTable
  L0_2()
end

L0_1[L1_1] = L2_1
L0_1 = nObjective_NoSlowing
L1_1 = nObjectiveFns
L1_1 = L1_1.HandleEvent

function L2_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2
  L2_2 = nObjectiveEvents
  L2_2 = L2_2.ModifierCreated
  if A0_2 == L2_2 then
    L2_2 = nObjective
    L2_2 = L2_2.GetObjectiveEventGUIDData
    L3_2 = A1_2
    L4_2 = 0
    L2_2 = L2_2(L3_2, L4_2)
    L3_2 = nObjective
    L3_2 = L3_2.GetObjectiveEventGUIDData
    L4_2 = A1_2
    L5_2 = 1
    L3_2 = L3_2(L4_2, L5_2)
    if L2_2 ~= L3_2 then
      L4_2 = nPlayer
      L4_2 = L4_2.IsPlayerControlledObject
      L5_2 = L3_2
      L4_2 = L4_2(L5_2)
      if L4_2 then
        L4_2 = nObjective
        L4_2 = L4_2.GetObjectiveEventIntData
        L5_2 = A1_2
        L6_2 = 3
        L4_2 = L4_2(L5_2, L6_2)
        L5_2 = nBit
        L5_2 = L5_2.And
        L6_2 = L4_2
        L7_2 = nBit
        L7_2 = L7_2.Or
        L8_2 = nDebuffDescriptors
        L8_2 = L8_2.IsRoot
        L9_2 = nDebuffDescriptors
        L9_2 = L9_2.IsSlow
        L7_2, L8_2, L9_2 = L7_2(L8_2, L9_2)
        L5_2 = L5_2(L6_2, L7_2, L8_2, L9_2)
        if L5_2 ~= 0 then
          L5_2 = nPlayer
          L5_2 = L5_2.GetPlayerIdForObject
          L6_2 = L3_2
          L5_2 = L5_2(L6_2)
          L6_2 = nThreadData
          L6_2 = L6_2.GetPrivateTable
          L6_2 = L6_2()
          L7_2 = L6_2[L5_2]
          if L7_2 == nil then
            L6_2[L5_2] = 1
          else
            L7_2 = L6_2[L5_2]
            L7_2 = L7_2 + 1
            L6_2[L5_2] = L7_2
          end
        end
      end
    end
  end
end

L0_1[L1_1] = L2_1
L0_1 = nObjective_NoSlowing
L1_1 = nObjectiveFns
L1_1 = L1_1.ObjectiveStatus

function L2_1(A0_2)
  local L1_2, L2_2, L3_2
  L1_2 = nThreadData
  L1_2 = L1_2.GetPrivateTable
  L1_2 = L1_2()
  L2_2 = 0
  L3_2 = L1_2[A0_2]
  if L3_2 ~= nil then
    L2_2 = L1_2[A0_2]
  end
  L3_2 = nObjective_NoSlowing
  L3_2 = L3_2.gold
  if L2_2 <= L3_2 then
    L3_2 = nObjectiveStatus
    L3_2 = L3_2.Gold
    return L3_2
  else
    L3_2 = nObjective_NoSlowing
    L3_2 = L3_2.silver
    if L2_2 <= L3_2 then
      L3_2 = nObjectiveStatus
      L3_2 = L3_2.Silver
      return L3_2
    else
      L3_2 = nObjective_NoSlowing
      L3_2 = L3_2.bronze
      if L2_2 <= L3_2 then
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
