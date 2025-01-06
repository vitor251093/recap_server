local L0_1, L1_1, L2_1, L3_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nObjective_DefeatAllMonsters = L0_1
L0_1 = nObjective_DefeatAllMonsters
L0_1.namespace = "nObjective_DefeatAllMonsters"
L0_1 = nObjective_DefeatAllMonsters
L1_1 = nUtil
L1_1 = L1_1.ToGUID
L2_1 = "0x097562ef"
L1_1 = L1_1(L2_1)
L0_1.descriptionText = L1_1
L0_1 = nObjective_DefeatAllMonsters
L1_1 = nUtil
L1_1 = L1_1.ToGUID
L2_1 = "0x098cd6b9"
L1_1 = L1_1(L2_1)
L0_1.progressText = L1_1
L0_1 = nObjective_DefeatAllMonsters
L0_1.groupObjective = true
L0_1 = nObjective_DefeatAllMonsters
L0_1.timeObjectiveRequires = true
L0_1 = nObjective_DefeatAllMonsters
L1_1 = nBit
L1_1 = L1_1.Or
L2_1 = nObjectiveEvents
L2_1 = L2_1.FullClear
L3_1 = nObjectiveEvents
L3_1 = L3_1.Death
L1_1 = L1_1(L2_1, L3_1)
L0_1.handledEvents = L1_1
L0_1 = nObjective_DefeatAllMonsters
L1_1 = kInvalidGUID
L0_1.completedVoiceOver = L1_1
L0_1 = nObjective_DefeatAllMonsters
L0_1.goldPercentage = 0.95
L0_1 = nObjective_DefeatAllMonsters
L0_1.silverPercentage = 0.75
L0_1 = nObjective_DefeatAllMonsters
L0_1.bronzePercentage = 0.5
L0_1 = nObjective_DefeatAllMonsters
L0_1.reportFrequencyPercent = 25
L0_1 = nObjective
L0_1 = L0_1.RegisterObjective
L1_1 = "DefeatAllMonsters"
L2_1 = nObjective_DefeatAllMonsters
L0_1(L1_1, L2_1)
L0_1 = nObjective_DefeatAllMonsters
L1_1 = nObjectiveFns
L1_1 = L1_1.Init

function L2_1()
  local L0_2, L1_2, L2_2, L3_2, L4_2, L5_2, L6_2
  L0_2 = nThreadData
  L0_2 = L0_2.CreatePrivateTable
  L0_2 = L0_2()
  L1_2 = nObjective_DefeatAllMonsters
  L1_2 = L1_2.reportFrequencyPercent
  L0_2.reportPercentage = L1_2
  L1_2 = nObjective
  L1_2 = L1_2.SetObjectiveIntData
  L2_2 = kAllPlayers
  L3_2 = 1
  L4_2 = nObjective_DefeatAllMonsters
  L4_2 = L4_2.goldPercentage
  L4_2 = L4_2 * 100
  L5_2 = false
  L6_2 = false
  L1_2(L2_2, L3_2, L4_2, L5_2, L6_2)
end

L0_1[L1_1] = L2_1
L0_1 = nObjective_DefeatAllMonsters
L1_1 = nObjectiveFns
L1_1 = L1_1.HandleEvent

function L2_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2
  L2_2 = nObjectiveEvents
  L2_2 = L2_2.Death
  if A0_2 == L2_2 then
    L2_2 = nObjective
    L2_2 = L2_2.GetObjectiveEventGUIDData
    L3_2 = A1_2
    L4_2 = 1
    L2_2 = L2_2(L3_2, L4_2)
    L3_2 = nGameDirector
    L3_2 = L3_2.GetKillPercent
    L3_2 = L3_2()
    L3_2 = L3_2 * 100
    L4_2 = nThreadData
    L4_2 = L4_2.GetPrivateTable
    L4_2 = L4_2()
    if L4_2 ~= nil then
      L5_2 = L4_2.reportPercentage
      if L3_2 >= L5_2 then
        L5_2 = nObjective
        L5_2 = L5_2.SetObjectiveIntData
        L6_2 = kAllPlayers
        L7_2 = 0
        L8_2 = L4_2.reportPercentage
        L9_2 = true
        L10_2 = true
        L5_2(L6_2, L7_2, L8_2, L9_2, L10_2)
        L5_2 = L4_2.reportPercentage
        L6_2 = nObjective_DefeatAllMonsters
        L6_2 = L6_2.reportFrequencyPercent
        L5_2 = L5_2 + L6_2
        L4_2.reportPercentage = L5_2
    end
    else
      L5_2 = nObjective
      L5_2 = L5_2.SetObjectiveIntData
      L6_2 = kAllPlayers
      L7_2 = 0
      L8_2 = L3_2
      L9_2 = true
      L10_2 = false
      L5_2(L6_2, L7_2, L8_2, L9_2, L10_2)
    end
  else
    L2_2 = nObjectiveEvents
    L2_2 = L2_2.FullClear
    if A0_2 == L2_2 then
      L2_2 = nObjective
      L2_2 = L2_2.SetObjectiveIntData
      L3_2 = kAllPlayers
      L4_2 = 0
      L5_2 = 100
      L6_2 = true
      L7_2 = true
      L2_2(L3_2, L4_2, L5_2, L6_2, L7_2)
    end
  end
end

L0_1[L1_1] = L2_1
L0_1 = nObjective_DefeatAllMonsters
L1_1 = nObjectiveFns
L1_1 = L1_1.ObjectiveStatus

function L2_1(A0_2)
  local L1_2, L2_2
  L1_2 = nGameDirector
  L1_2 = L1_2.GetKillPercent
  L1_2 = L1_2()
  L2_2 = nObjective_DefeatAllMonsters
  L2_2 = L2_2.goldPercentage
  if L1_2 >= L2_2 then
    L2_2 = nObjectiveStatus
    L2_2 = L2_2.Gold
    return L2_2
  else
    L2_2 = nObjective_DefeatAllMonsters
    L2_2 = L2_2.silverPercentage
    if L1_2 >= L2_2 then
      L2_2 = nObjectiveStatus
      L2_2 = L2_2.Silver
      return L2_2
    else
      L2_2 = nObjective_DefeatAllMonsters
      L2_2 = L2_2.bronzePercentage
      if L1_2 >= L2_2 then
        L2_2 = nObjectiveStatus
        L2_2 = L2_2.Bronze
        return L2_2
      else
        L2_2 = nObjectiveStatus
        L2_2 = L2_2.Failed
        return L2_2
      end
    end
  end
end

L0_1[L1_1] = L2_1
