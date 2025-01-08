local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nAffix_EnemyIncreased_Speed = L0_1
L0_1 = nAffix_EnemyIncreased_Speed
L0_1.namespace = "nAffix_EnemyIncreased_Speed"
L0_1 = nAffix_EnemyIncreased_Speed
L1_1 = nUtil
L1_1 = L1_1.ToGUID
L2_1 = "0x09e6b33a"
L1_1 = L1_1(L2_1)
L0_1.localizedText = L1_1
L0_1 = nAffix_EnemyIncreased_Speed
L1_1 = nUtil
L1_1 = L1_1.SPID
L2_1 = "NoSlowing"
L1_1 = L1_1(L2_1)
L0_1.objective = L1_1
L0_1 = nAffix_EnemyIncreased_Speed
L0_1.handledEvents = 0
L0_1 = nAffix_EnemyIncreased_Speed
L1_1 = nUtil
L1_1 = L1_1.SPID
L2_1 = "SpeedIncreasedModifier"
L1_1 = L1_1(L2_1)
L0_1.modifier = L1_1
L0_1 = nAffix
L0_1 = L0_1.RegisterAffix
L1_1 = "EnemyIncreasedSpeed"
L2_1 = nAffix_EnemyIncreased_Speed
L0_1(L1_1, L2_1)
L0_1 = nAffix_EnemyIncreased_Speed
L1_1 = nAffixFns
L1_1 = L1_1.Tick

function L2_1()
  local L0_2, L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2
  while true do
    L0_2 = nObjectManager
    L0_2 = L0_2.GetObjectsOfType
    L1_2 = kType_Creature
    L0_2 = L0_2(L1_2)
    L1_2 = ipairs
    L2_2 = L0_2
    L1_2, L2_2, L3_2 = L1_2(L2_2)
    for L4_2, L5_2 in L1_2, L2_2, L3_2 do
      L6_2 = nGameObject
      L6_2 = L6_2.GetOwnerID
      L7_2 = L5_2
      L6_2 = L6_2(L7_2)
      L7_2 = nGameObject
      L7_2 = L7_2.IsAlive
      L8_2 = L5_2
      L7_2 = L7_2(L8_2)
      if L7_2 then
        L7_2 = nPlayer
        L7_2 = L7_2.IsPlayerControlledObject
        L8_2 = L5_2
        L7_2 = L7_2(L8_2)
        if not L7_2 then
          L7_2 = nPlayer
          L7_2 = L7_2.IsPlayerControlledObject
          L8_2 = L6_2
          L7_2 = L7_2(L8_2)
          if not L7_2 then
            L7_2 = nGameObject
            L7_2 = L7_2.IsModifierActive
            L8_2 = L5_2
            L9_2 = nAffix_EnemyIncreased_Speed
            L9_2 = L9_2.modifier
            L7_2 = L7_2(L8_2, L9_2)
            if not L7_2 then
              L7_2 = nModifier
              L7_2 = L7_2.RequestModifier
              L8_2 = L5_2
              L9_2 = L5_2
              L10_2 = nAffix_EnemyIncreased_Speed
              L10_2 = L10_2.modifier
              L7_2(L8_2, L9_2, L10_2)
            end
          end
        end
      end
    end
    L1_2 = coroutine
    L1_2 = L1_2.yield
    L1_2()
  end
end

L0_1[L1_1] = L2_1
L0_1 = nAffix_EnemyIncreased_Speed
L1_1 = nAffixFns
L1_1 = L1_1.HandleEvent

function L2_1(A0_2, A1_2)
end

L0_1[L1_1] = L2_1
