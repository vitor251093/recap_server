local L0_1, L1_1, L2_1, L3_1, L4_1, L5_1, L6_1, L7_1, L8_1, L9_1, L10_1, L11_1, L12_1, L13_1, L14_1, L15_1, L16_1, L17_1, L18_1, L19_1
L0_1 = {}
nLootRules = L0_1
L0_1 = nLootRules
L0_1.GoldMultiplier = 6
L0_1 = nLootRules
L0_1.SilverMultiplier = 3
L0_1 = nLootRules
L0_1.BronzeMultiplier = 1
L0_1 = nLootRules
L0_1.NoMedalMultiplier = 0
L0_1 = nLootRules
L1_1 = {}
L2_1 = 0
L3_1 = 0
L4_1 = 2
L5_1 = 4
L6_1 = 6
L7_1 = 8
L8_1 = 10
L9_1 = 12
L10_1 = 14
L11_1 = 16
L12_1 = 18
L13_1 = 20
L14_1 = 21
L15_1 = 22
L16_1 = 24
L17_1 = 26
L18_1 = 28
L19_1 = 30
L1_1[1] = L2_1
L1_1[2] = L3_1
L1_1[3] = L4_1
L1_1[4] = L5_1
L1_1[5] = L6_1
L1_1[6] = L7_1
L1_1[7] = L8_1
L1_1[8] = L9_1
L1_1[9] = L10_1
L1_1[10] = L11_1
L1_1[11] = L12_1
L1_1[12] = L13_1
L1_1[13] = L14_1
L1_1[14] = L15_1
L1_1[15] = L16_1
L1_1[16] = L17_1
L1_1[17] = L18_1
L1_1[18] = L19_1
L0_1.EpicChance = L1_1
L0_1 = nLootRules
L0_1.ChainBonusPerAdditionalPlanet = 4
L0_1 = nLootRules

function L1_1(A0_2, A1_2, A2_2, A3_2, A4_2, A5_2, A6_2, A7_2)
  local L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2
  L8_2 = math
  L8_2 = L8_2.min
  L9_2 = A0_2
  L10_2 = 4
  L8_2 = L8_2(L9_2, L10_2)
  L9_2 = nLootRules
  L9_2 = L9_2.GoldMultiplier
  L9_2 = A2_2 * L9_2
  L10_2 = nLootRules
  L10_2 = L10_2.SilverMultiplier
  L10_2 = A3_2 * L10_2
  L9_2 = L9_2 + L10_2
  L10_2 = nLootRules
  L10_2 = L10_2.BronzeMultiplier
  L10_2 = A4_2 * L10_2
  L9_2 = L9_2 + L10_2
  L10_2 = nLootRules
  L10_2 = L10_2.NoMedalMultiplier
  L10_2 = A5_2 * L10_2
  L9_2 = L9_2 + L10_2
  L9_2 = L9_2 / A0_2
  L10_2 = math
  L10_2 = L10_2.min
  L11_2 = A7_2 + 1
  L11_2 = L9_2 * L11_2
  L12_2 = 100
  L10_2 = L10_2(L11_2, L12_2)
  L9_2 = L10_2
  L10_2 = nLootRules
  L10_2 = L10_2.ChainBonusPerAdditionalPlanet
  L11_2 = A0_2 - 1
  L10_2 = L10_2 * L11_2
  L9_2 = L9_2 + L10_2
  if A6_2 then
    L9_2 = L9_2 * 1.5
  end
  L10_2 = math
  L10_2 = L10_2.floor
  L11_2 = L9_2
  L10_2 = L10_2(L11_2)
  L11_2 = L9_2 - L10_2
  if 0.5 <= L11_2 then
    L12_2 = math
    L12_2 = L12_2.ceil
    L13_2 = L9_2
    L12_2 = L12_2(L13_2)
    L9_2 = L12_2
  else
    L9_2 = L10_2
  end
  L12_2 = nLootRules
  L12_2 = L12_2.EpicChance
  L12_2 = L12_2[A1_2]
  L12_2 = L9_2 * L12_2
  L12_2 = L12_2 / 100
  L13_2 = math
  L13_2 = L13_2.floor
  L14_2 = L12_2
  L13_2 = L13_2(L14_2)
  L14_2 = L12_2 - L13_2
  if 0.5 <= L14_2 then
    L15_2 = math
    L15_2 = L15_2.ceil
    L16_2 = L12_2
    L15_2 = L15_2(L16_2)
    L12_2 = L15_2
  else
    L12_2 = L13_2
  end
  L15_2 = math
  L15_2 = L15_2.min
  L16_2 = L9_2
  L17_2 = 100
  L15_2 = L15_2(L16_2, L17_2)
  L9_2 = L15_2
  L15_2 = math
  L15_2 = L15_2.min
  L16_2 = L12_2
  L17_2 = 100
  L15_2 = L15_2(L16_2, L17_2)
  L12_2 = L15_2
  L15_2 = L8_2
  L16_2 = L9_2
  L17_2 = L12_2
  return L15_2, L16_2, L17_2
end

L0_1[1] = L1_1
L0_1 = nLootRules
L0_1.GoldValue = 4
L0_1 = nLootRules
L0_1.SilverValue = 3
L0_1 = nLootRules
L0_1.BronzeValue = 2
L0_1 = nLootRules
L0_1.NoMedalValue = 1
L0_1 = nLootRules

function L1_1(A0_2, A1_2, A2_2, A3_2)
  local L4_2, L5_2, L6_2, L7_2
  L4_2 = A0_2 + A1_2
  L4_2 = L4_2 + A2_2
  L4_2 = L4_2 + A3_2
  L5_2 = nLootRules
  L5_2 = L5_2.GoldValue
  L5_2 = A0_2 * L5_2
  L6_2 = nLootRules
  L6_2 = L6_2.SilverValue
  L6_2 = A1_2 * L6_2
  L5_2 = L5_2 + L6_2
  L6_2 = nLootRules
  L6_2 = L6_2.BronzeValue
  L6_2 = A2_2 * L6_2
  L5_2 = L5_2 + L6_2
  L6_2 = nLootRules
  L6_2 = L6_2.NoMedalValue
  L6_2 = A3_2 * L6_2
  L5_2 = L5_2 + L6_2
  L6_2 = L5_2 / L4_2
  if L6_2 == 4 then
    L7_2 = nObjectiveStatus
    L7_2 = L7_2.Gold
    return L7_2
  elseif 3 <= L6_2 then
    L7_2 = nObjectiveStatus
    L7_2 = L7_2.Silver
    return L7_2
  elseif 2 <= L6_2 then
    L7_2 = nObjectiveStatus
    L7_2 = L7_2.Bronze
    return L7_2
  else
    L7_2 = nObjectiveStatus
    L7_2 = L7_2.Failed
    return L7_2
  end
end

L0_1[2] = L1_1
