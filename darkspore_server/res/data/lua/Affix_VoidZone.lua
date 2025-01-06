local L0_1, L1_1, L2_1, L3_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nAffix_VoidZone = L0_1
L0_1 = nAffix_VoidZone
L0_1.namespace = "nAffix_VoidZone"
L0_1 = nAffix_VoidZone
L1_1 = nUtil
L1_1 = L1_1.ToGUID
L2_1 = "0x09f677f6"
L1_1 = L1_1(L2_1)
L0_1.localizedText = L1_1
L0_1 = nAffix_VoidZone
L1_1 = kInvalidGUID
L0_1.objective = L1_1
L0_1 = nAffix_VoidZone
L1_1 = nObjectiveEvents
L1_1 = L1_1.ActivateAffix
L0_1.handledEvents = L1_1
L0_1 = nAffix_VoidZone
L1_1 = nUtil
L1_1 = L1_1.GetAsset
L2_1 = "BlackHoleEffect.Noun"
L1_1 = L1_1(L2_1)
L0_1.effectObject = L1_1
L0_1 = nAffix_VoidZone
L0_1.initialSpawnChance = 0.2
L0_1 = nAffix_VoidZone
L0_1.spawnChanceRamp = 0.1
L0_1 = nAffix_VoidZone
L0_1.damageRadius = 6
L0_1 = nAffix_VoidZone
L1_1 = {}
L2_1 = 6
L3_1 = 12
L1_1[1] = L2_1
L1_1[2] = L3_1
L0_1.damagePerTick = L1_1
L0_1 = nAffix_VoidZone
L0_1.damageTickRate = 2
L0_1 = nAffix_VoidZone
L1_1 = nDamageTypes
L1_1 = L1_1.Supernatural
L0_1.damageType = L1_1
L0_1 = nAffix_VoidZone
L1_1 = nDamageSources
L1_1 = L1_1.Energy
L0_1.damageSource = L1_1
L0_1 = nAffix_VoidZone
L0_1.damageCoefficient = 1
L0_1 = nAffix_VoidZone
L1_1 = nDescriptors
L1_1 = L1_1.IsEnergyDamage
L0_1.descriptors = L1_1
L0_1 = nAffix
L0_1 = L0_1.RegisterAffix
L1_1 = "VoidZones"
L2_1 = nAffix_VoidZone
L0_1(L1_1, L2_1)

function L0_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2
  L2_2 = nGameObject
  L2_2 = L2_2.GetPosition
  L3_2 = A0_2
  L2_2, L3_2, L4_2 = L2_2(L3_2)
  while true do
    L5_2 = nThread
    L5_2 = L5_2.WaitForXSeconds
    L6_2 = A1_2.damageTickRate
    L5_2(L6_2)
    L5_2 = nObjectManager
    L5_2 = L5_2.GetObjectsInRadius
    L6_2 = L2_2
    L7_2 = L3_2
    L8_2 = L4_2
    L9_2 = A1_2.damageRadius
    L10_2 = nSporeLabs
    L10_2 = L10_2.damageableObjectTypes
    L5_2 = L5_2(L6_2, L7_2, L8_2, L9_2, L10_2)
    L6_2 = ipairs
    L7_2 = L5_2
    L6_2, L7_2, L8_2 = L6_2(L7_2)
    for L9_2, L10_2 in L6_2, L7_2, L8_2 do
      L11_2 = nPlayer
      L11_2 = L11_2.IsPlayerControlledObject
      L12_2 = L10_2
      L11_2 = L11_2(L12_2)
      if L11_2 then
        L11_2 = nGameObject
        L11_2 = L11_2.IsAlive
        L12_2 = L10_2
        L11_2 = L11_2(L12_2)
        if L11_2 then
          L11_2 = nGameObject
          L11_2 = L11_2.TakeDamage
          L12_2 = kInvalidGUID
          L13_2 = L10_2
          L14_2 = A1_2.damagePerTick
          L15_2 = A1_2.damageType
          L16_2 = A1_2.damageSource
          L17_2 = A1_2.damageCoefficient
          L18_2 = A1_2.descriptors
          L11_2(L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2)
        end
      end
    end
  end
end

L1_1 = nAffix_VoidZone
L2_1 = nAffixFns
L2_1 = L2_1.Tick

function L3_1()
  local L0_2, L1_2
  L0_2 = nThreadData
  L0_2 = L0_2.CreatePrivateTable
  L0_2 = L0_2()
  L1_2 = nAffix_VoidZone
  L1_2 = L1_2.initialSpawnChance
  L0_2.spawnChance = L1_2
  L1_2 = nThread
  L1_2 = L1_2.WaitForever
  L1_2()
end

L1_1[L2_1] = L3_1
L1_1 = nAffix_VoidZone
L2_1 = nAffixFns
L2_1 = L2_1.HandleEvent

function L3_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2, L19_2, L20_2, L21_2, L22_2, L23_2, L24_2
  L2_2 = nObjectiveEvents
  L2_2 = L2_2.ActivateAffix
  if A0_2 == L2_2 then
    L2_2 = nThreadData
    L2_2 = L2_2.GetPrivateTable
    L2_2 = L2_2()
    L3_2 = nObjective
    L3_2 = L3_2.GetObjectiveEventGUIDData
    L4_2 = A1_2
    L5_2 = 1
    L3_2 = L3_2(L4_2, L5_2)
    L4_2 = nObjective
    L4_2 = L4_2.GetObjectiveEventGUIDData
    L5_2 = A1_2
    L6_2 = 2
    L4_2 = L4_2(L5_2, L6_2)
    L5_2 = math
    L5_2 = L5_2.random
    L5_2 = L5_2()
    L6_2 = L2_2.spawnChance
    if L5_2 < L6_2 then
      L6_2 = nAffix
      L6_2 = L6_2.IsAffixPointValid
      L7_2 = L3_2
      L6_2 = L6_2(L7_2)
      if L6_2 then
        L6_2 = nGameObject
        L6_2 = L6_2.GetPosition
        L7_2 = L4_2
        L6_2, L7_2, L8_2 = L6_2(L7_2)
        L9_2 = nGameObject
        L9_2 = L9_2.GetOrientation
        L10_2 = L4_2
        L9_2, L10_2, L11_2, L12_2 = L9_2(L10_2)
        L13_2 = nObjectManager
        L13_2 = L13_2.CreateObject
        L14_2 = nAffix_VoidZone
        L14_2 = L14_2.effectObject
        L15_2 = L6_2
        L16_2 = L7_2
        L17_2 = L8_2
        L18_2 = L9_2
        L19_2 = L10_2
        L20_2 = L11_2
        L21_2 = L12_2
        L22_2 = 1
        L23_2 = nUtil
        L23_2 = L23_2.ToGUID
        L24_2 = "0x0"
        L23_2, L24_2 = L23_2(L24_2)
        L13_2 = L13_2(L14_2, L15_2, L16_2, L17_2, L18_2, L19_2, L20_2, L21_2, L22_2, L23_2, L24_2)
        L14_2 = nObjectManager
        L14_2 = L14_2.IsValidObject
        L15_2 = L13_2
        L14_2 = L14_2(L15_2)
        if L14_2 then
          L14_2 = nThread
          L14_2 = L14_2.CreateThreadForObject
          L15_2 = L13_2
          L16_2 = L0_1
          L17_2 = L13_2
          L18_2 = nAffix_VoidZone
          L14_2(L15_2, L16_2, L17_2, L18_2)
        end
        L14_2 = nAffix
        L14_2 = L14_2.SetAffixPointInvalid
        L15_2 = L3_2
        L14_2(L15_2)
        L14_2 = nAffix_VoidZone
        L14_2 = L14_2.initialSpawnChance
        L2_2.spawnChance = L14_2
    end
    else
      L6_2 = L2_2.spawnChance
      L7_2 = nAffix_VoidZone
      L7_2 = L7_2.spawnChanceRamp
      L6_2 = L6_2 + L7_2
      L2_2.spawnChance = L6_2
    end
  end
end

L1_1[L2_1] = L3_1
