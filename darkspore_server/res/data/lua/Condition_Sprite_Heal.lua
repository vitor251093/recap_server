local L0_1, L1_1, L2_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_Sprite_Heal = L0_1
L0_1 = nCondition_Sprite_Heal
L0_1.namespace = "nCondition_Sprite_Heal"
L0_1 = nCondition_Sprite_Heal
L0_1.conditionType = 0
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "SpriteHealTargeting"
L2_1 = nCondition_Sprite_Heal
L0_1(L1_1, L2_1)
L0_1 = nCondition_Sprite_Heal

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2
  L1_2 = nGameObject
  L1_2 = L1_2.GetPosition
  L2_2 = A0_2
  L1_2, L2_2, L3_2 = L1_2(L2_2)
  L4_2 = 20
  L5_2 = nGameObject
  L5_2 = L5_2.GetTeam
  L6_2 = A0_2
  L5_2 = L5_2(L6_2)
  L6_2 = nGameObject
  L6_2 = L6_2.GetOwnerID
  L7_2 = A0_2
  L6_2 = L6_2(L7_2)
  L7_2 = kObjIDNone
  L8_2 = 100
  L9_2 = nObjectManager
  L9_2 = L9_2.GetObjectsInRadius_SortedByDistance
  L10_2 = L1_2
  L11_2 = L2_2
  L12_2 = L3_2
  L13_2 = L4_2
  L14_2 = kType_Creature
  L9_2 = L9_2(L10_2, L11_2, L12_2, L13_2, L14_2)
  L10_2 = ipairs
  L11_2 = L9_2
  L10_2, L11_2, L12_2 = L10_2(L11_2)
  for L13_2, L14_2 in L10_2, L11_2, L12_2 do
    if L14_2 ~= A0_2 then
      L15_2 = nGameObject
      L15_2 = L15_2.IsAlive
      L16_2 = L14_2
      L15_2 = L15_2(L16_2)
      if L15_2 then
        L15_2 = nGameObject
        L15_2 = L15_2.GetTeam
        L16_2 = L14_2
        L15_2 = L15_2(L16_2)
        if L15_2 == L5_2 then
          L15_2 = nGameObject
          L15_2 = L15_2.GetHitPoints
          L16_2 = L14_2
          L15_2 = L15_2(L16_2)
          L16_2 = nGameObject
          L16_2 = L16_2.GetMaxHitPoints
          L17_2 = L14_2
          L16_2 = L16_2(L17_2)
          if L15_2 < L16_2 then
            L15_2 = nil
            if L14_2 == L6_2 then
              L15_2 = 1
            else
              L16_2 = nPlayer
              L16_2 = L16_2.IsPlayerControlledObject
              L17_2 = L14_2
              L16_2 = L16_2(L17_2)
              if L16_2 then
                L15_2 = 2
              else
                L16_2 = nGameObject
                L16_2 = L16_2.GetOwnerID
                L17_2 = L14_2
                L16_2 = L16_2(L17_2)
                if L16_2 == L6_2 then
                  L15_2 = 3
                else
                  L15_2 = 4
                end
              end
            end
            if L8_2 > L15_2 then
              L7_2 = L14_2
              L8_2 = L15_2
            end
          end
        end
      end
    end
  end
  L10_2 = kObjIDNone
  if L7_2 ~= L10_2 then
    L10_2 = true
    L11_2 = 0
    L12_2 = 0
    L13_2 = 0
    L14_2 = L7_2
    return L10_2, L11_2, L12_2, L13_2, L14_2
  end
  L10_2 = false
  return L10_2
end

L0_1[1] = L1_1
