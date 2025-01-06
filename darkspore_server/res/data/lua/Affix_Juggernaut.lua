local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nAffix_Juggernaut = L0_1
L0_1 = nAffix_Juggernaut
L0_1.namespace = "nAffix_Juggernaut"
L0_1 = nAffix_Juggernaut
L1_1 = kInvalidGUID
L0_1.localizedText = L1_1
L0_1 = nAffix_Juggernaut
L1_1 = kInvalidGUID
L0_1.objective = L1_1
L0_1 = nAffix_Juggernaut
L1_1 = nObjectiveEvents
L1_1 = L1_1.Death
L0_1.handledEvents = L1_1
L0_1 = nAffix_Juggernaut
L1_1 = kInvalidGUID
L0_1.modifier = L1_1
L0_1 = nAffix
L0_1 = L0_1.RegisterAffix
L1_1 = "Juggernaut"
L2_1 = nAffix_Juggernaut
L0_1(L1_1, L2_1)
L0_1 = nAffix_Juggernaut
L1_1 = nAffixFns
L1_1 = L1_1.Tick

function L2_1()
  local L0_2, L1_2
end

L0_1[L1_1] = L2_1
L0_1 = nAffix_Juggernaut
L1_1 = nAffixFns
L1_1 = L1_1.HandleEvent

function L2_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2
  L2_2 = nObjectiveEvents
  L2_2 = L2_2.Death
  if A0_2 == L2_2 then
    L2_2 = nObjective
    L2_2 = L2_2.GetObjectiveEventGUIDData
    L3_2 = A1_2
    L4_2 = 1
    L2_2 = L2_2(L3_2, L4_2)
    L3_2 = nObjective
    L3_2 = L3_2.GetObjectiveEventGUIDData
    L4_2 = A1_2
    L5_2 = 2
    L3_2 = L3_2(L4_2, L5_2)
    L4_2 = nObjective
    L4_2 = L4_2.GetObjectiveEventIntData
    L5_2 = A1_2
    L6_2 = 3
    L4_2 = L4_2(L5_2, L6_2)
    L5_2 = nPlayer
    L5_2 = L5_2.IsPlayerControlledObject
    L6_2 = L2_2
    L5_2 = L5_2(L6_2)
    if L5_2 then
      L5_2 = kAllPlayers
      if L4_2 ~= L5_2 then
        L5_2 = nPlayer
        L5_2 = L5_2.GetPlayerIdForObject
        L6_2 = L2_2
        L5_2 = L5_2(L6_2)
        L6_2 = nPlayer
        L6_2 = L6_2.IsOverdriveActive
        L7_2 = L5_2
        L6_2 = L6_2(L7_2)
        if L6_2 then
          L6_2 = nJuggernaut
          L6_2 = L6_2.RemoveJuggernaut
          L7_2 = L5_2
          L6_2(L7_2)
          L6_2 = nJuggernaut
          L6_2 = L6_2.ApplyJuggernaut
          L7_2 = L4_2
          L6_2(L7_2)
        else
          L6_2 = nPlayer
          L6_2 = L6_2.IsOverdriveActive
          L7_2 = L4_2
          L6_2 = L6_2(L7_2)
          if L6_2 then
            L6_2 = nJuggernaut
            L6_2 = L6_2.ScoreJuggernautKill
            L7_2 = L4_2
            L6_2(L7_2)
          end
        end
      end
    end
  end
end

L0_1[L1_1] = L2_1
