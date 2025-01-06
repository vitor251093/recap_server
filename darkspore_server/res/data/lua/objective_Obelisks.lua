local L0_1, L1_1, L2_1, L3_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nObjective_Obelisks = L0_1
L0_1 = nObjective_Obelisks
L0_1.namespace = "nObjective_Obelisks"
L0_1 = nObjective_Obelisks
L1_1 = nUtil
L1_1 = L1_1.ToGUID
L2_1 = "0x097562ee"
L1_1 = L1_1(L2_1)
L0_1.descriptionText = L1_1
L0_1 = nObjective_Obelisks
L1_1 = nUtil
L1_1 = L1_1.ToGUID
L2_1 = "0x098cd6b8"
L1_1 = L1_1(L2_1)
L0_1.progressText = L1_1
L0_1 = nObjective_Obelisks
L1_1 = nUtil
L1_1 = L1_1.ToGUID
L2_1 = "0x0990d32e"
L1_1 = L1_1(L2_1)
L0_1.errorText = L1_1
L0_1 = nObjective_Obelisks
L1_1 = nObjectiveEvents
L1_1 = L1_1.TouchedObelisk
L0_1.handledEvents = L1_1
L0_1 = nObjective_Obelisks
L1_1 = nUtil
L1_1 = L1_1.SPID
L2_1 = "vo_ship_obelisk_accessed"
L1_1 = L1_1(L2_1)
L0_1.completedVoiceOver = L1_1
L0_1 = nObjective_Obelisks
L1_1 = nUtil
L1_1 = L1_1.SPID
L2_1 = "vo_ship_obelisk_accessed"
L1_1 = L1_1(L2_1)
L0_1.progressVoiceOver = L1_1
L0_1 = nObjective_Obelisks
L0_1.groupObjective = true
L0_1 = nObjective_Obelisks
L0_1.timeObjectiveRequires = true
L0_1 = nObjective_Obelisks
L0_1.goldObelisks = 3
L0_1 = nObjective_Obelisks
L0_1.silverObelisks = 2
L0_1 = nObjective_Obelisks
L0_1.bronzeObelisks = 1
L0_1 = nObjective
L0_1 = L0_1.RegisterObjective
L1_1 = "TouchAllObelisks"
L2_1 = nObjective_Obelisks
L0_1(L1_1, L2_1)

function L0_1()
  local L0_2, L1_2, L2_2, L3_2
  L0_2 = nThreadData
  L0_2 = L0_2.GetPrivateTable
  L0_2 = L0_2()
  if L0_2 == nil then
    L1_2 = nThreadData
    L1_2 = L1_2.CreatePrivateTable
    L1_2 = L1_2()
    L0_2 = L1_2
    L1_2 = nObjectManager
    L1_2 = L1_2.GetNumInteractableObjects
    L2_2 = nUtil
    L2_2 = L2_2.SPID
    L3_2 = "InteractWithObelisk"
    L2_2, L3_2 = L2_2(L3_2)
    L1_2 = L1_2(L2_2, L3_2)
    L0_2.totalObelisks = L1_2
  end
  return L0_2
end

L1_1 = nObjective_Obelisks
L2_1 = nObjectiveFns
L2_1 = L2_1.Init

function L3_1()
  local L0_2, L1_2, L2_2, L3_2, L4_2, L5_2, L6_2
  L0_2 = L0_1
  L0_2 = L0_2()
  L1_2 = nObjective
  L1_2 = L1_2.SetObjectiveIntData
  L2_2 = kAllPlayers
  L3_2 = 1
  L4_2 = L0_2.totalObelisks
  L5_2 = false
  L6_2 = false
  L1_2(L2_2, L3_2, L4_2, L5_2, L6_2)
  L1_2 = nObjective
  L1_2 = L1_2.SetObjectiveIntData
  L2_2 = kAllPlayers
  L3_2 = 2
  L4_2 = L0_2.totalObelisks
  L5_2 = false
  L6_2 = false
  L1_2(L2_2, L3_2, L4_2, L5_2, L6_2)
end

L1_1[L2_1] = L3_1
L1_1 = nObjective_Obelisks
L2_1 = nObjectiveFns
L2_1 = L2_1.HandleEvent

function L3_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2
  L2_2 = nObjectiveEvents
  L2_2 = L2_2.TouchedObelisk
  if A0_2 == L2_2 then
    L2_2 = nObjective
    L2_2 = L2_2.GetObjectiveEventGUIDData
    L3_2 = A1_2
    L4_2 = 0
    L2_2 = L2_2(L3_2, L4_2)
    L3_2 = nGameObject
    L3_2 = L3_2.HasInteractableUsesLeft
    L4_2 = L2_2
    L3_2 = L3_2(L4_2)
    if L3_2 then
      L3_2 = nGameObject
      L3_2 = L3_2.IncrementNumTimesUsed
      L4_2 = L2_2
      L3_2(L4_2)
      L3_2 = L0_1
      L3_2 = L3_2()
      L4_2 = L3_2.numTouched
      if L4_2 == nil then
        L3_2.numTouched = 1
      else
        L4_2 = L3_2.numTouched
        L4_2 = L4_2 + 1
        L3_2.numTouched = L4_2
      end
      L4_2 = nObjective
      L4_2 = L4_2.SetObjectiveIntData
      L5_2 = kAllPlayers
      L6_2 = 0
      L7_2 = L3_2.numTouched
      L8_2 = false
      L9_2 = false
      L4_2(L5_2, L6_2, L7_2, L8_2, L9_2)
      L4_2 = nObjective
      L4_2 = L4_2.SetObjectiveIntData
      L5_2 = kAllPlayers
      L6_2 = 1
      L7_2 = L3_2.totalObelisks
      L8_2 = false
      L9_2 = false
      L4_2(L5_2, L6_2, L7_2, L8_2, L9_2)
      L4_2 = nObjective
      L4_2 = L4_2.SetObjectiveIntData
      L5_2 = kAllPlayers
      L6_2 = 2
      L7_2 = L3_2.totalObelisks
      L8_2 = L3_2.numTouched
      L7_2 = L7_2 - L8_2
      L8_2 = true
      L9_2 = true
      L4_2(L5_2, L6_2, L7_2, L8_2, L9_2)
    end
  end
end

L1_1[L2_1] = L3_1
L1_1 = nObjective_Obelisks
L2_1 = nObjectiveFns
L2_1 = L2_1.ObjectiveStatus

function L3_1(A0_2)
  local L1_2, L2_2, L3_2
  L1_2 = L0_1
  L1_2 = L1_2()
  L2_2 = L1_2.numTouched
  if L2_2 ~= nil then
    L2_2 = L1_2.numTouched
    L3_2 = nObjective_Obelisks
    L3_2 = L3_2.goldObelisks
    if L2_2 >= L3_2 then
      L2_2 = nObjectiveStatus
      L2_2 = L2_2.Gold
      return L2_2
  end
  else
    L2_2 = L1_2.numTouched
    if L2_2 ~= nil then
      L2_2 = L1_2.numTouched
      L3_2 = nObjective_Obelisks
      L3_2 = L3_2.silverObelisks
      if L2_2 >= L3_2 then
        L2_2 = nObjectiveStatus
        L2_2 = L2_2.Silver
        return L2_2
    end
    else
      L2_2 = L1_2.numTouched
      if L2_2 ~= nil then
        L2_2 = L1_2.numTouched
        L3_2 = nObjective_Obelisks
        L3_2 = L3_2.bronzeObelisks
        if L2_2 >= L3_2 then
          L2_2 = nObjectiveStatus
          L2_2 = L2_2.Bronze
          return L2_2
      end
      else
        L2_2 = nObjectiveStatus
        L2_2 = L2_2.Failed
        return L2_2
      end
    end
  end
end

L1_1[L2_1] = L3_1
