local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nObjective_FinishLevelQuickly = L0_1
L0_1 = nObjective_FinishLevelQuickly
L0_1.namespace = "nObjective_FinishLevelQuickly"
L0_1 = nObjective_FinishLevelQuickly
L1_1 = nUtil
L1_1 = L1_1.ToGUID
L2_1 = "0x097562f0"
L1_1 = L1_1(L2_1)
L0_1.descriptionText = L1_1
L0_1 = nObjective_FinishLevelQuickly
L1_1 = nUtil
L1_1 = L1_1.ToGUID
L2_1 = "0x09d16768"
L1_1 = L1_1(L2_1)
L0_1.progressText = L1_1
L0_1 = nObjective_FinishLevelQuickly
L0_1.groupObjective = true
L0_1 = nObjective_FinishLevelQuickly
L0_1.goldTime = 600
L0_1 = nObjective_FinishLevelQuickly
L0_1.silverTime = 900
L0_1 = nObjective_FinishLevelQuickly
L0_1.bronzeTime = 1200
L0_1 = nObjective
L0_1 = L0_1.RegisterObjective
L1_1 = "FinishLevelQuickly"
L2_1 = nObjective_FinishLevelQuickly
L0_1(L1_1, L2_1)
L0_1 = nObjective_FinishLevelQuickly
L1_1 = nObjectiveFns
L1_1 = L1_1.Init

function L2_1()
  local L0_2, L1_2
end

L0_1[L1_1] = L2_1
L0_1 = nObjective_FinishLevelQuickly
L1_1 = nObjectiveFns
L1_1 = L1_1.ObjectiveStatus

function L2_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2
  L1_2 = math
  L1_2 = L1_2.floor
  L2_2 = nGameSimulator
  L2_2 = L2_2.GetGameObjectiveCompletionTime
  L2_2, L3_2, L4_2, L5_2, L6_2, L7_2 = L2_2()
  L1_2 = L1_2(L2_2, L3_2, L4_2, L5_2, L6_2, L7_2)
  L2_2 = nObjective
  L2_2 = L2_2.SetObjectiveIntData
  L3_2 = kAllPlayers
  L4_2 = 0
  L5_2 = L1_2
  L6_2 = false
  L7_2 = false
  L2_2(L3_2, L4_2, L5_2, L6_2, L7_2)
  L2_2 = nObjective_FinishLevelQuickly
  L2_2 = L2_2.goldTime
  if L1_2 <= L2_2 then
    L2_2 = nObjectiveStatus
    L2_2 = L2_2.Gold
    return L2_2
  else
    L2_2 = nObjective_FinishLevelQuickly
    L2_2 = L2_2.silverTime
    if L1_2 <= L2_2 then
      L2_2 = nObjectiveStatus
      L2_2 = L2_2.Silver
      return L2_2
    else
      L2_2 = nObjective_FinishLevelQuickly
      L2_2 = L2_2.bronzeTime
      if L1_2 <= L2_2 then
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
