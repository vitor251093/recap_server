local L0_1, L1_1, L2_1, L3_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = require
L1_1 = "Lua!NavigationUtils.lua"
L0_1(L1_1)
L0_1 = {}
nAffix_MeteorShower = L0_1
L0_1 = nAffix_MeteorShower
L0_1.namespace = "nAffix_MeteorShower"
L0_1 = nAffix_MeteorShower
L1_1 = nUtil
L1_1 = L1_1.ToGUID
L2_1 = "0x09f677f6"
L1_1 = L1_1(L2_1)
L0_1.localizedText = L1_1
L0_1 = nAffix_MeteorShower
L1_1 = kInvalidGUID
L0_1.objective = L1_1
L0_1 = nAffix_MeteorShower
L1_1 = nObjectiveEvents
L1_1 = L1_1.ActivateAffix
L0_1.handledEvents = L1_1
L0_1 = nAffix_MeteorShower
L0_1.damageRadius = 3
L0_1 = nAffix_MeteorShower
L1_1 = {}
L2_1 = 24
L3_1 = 36
L1_1[1] = L2_1
L1_1[2] = L3_1
L0_1.damage = L1_1
L0_1 = nAffix_MeteorShower
L1_1 = nDamageTypes
L1_1 = L1_1.Elements
L0_1.damageType = L1_1
L0_1 = nAffix_MeteorShower
L1_1 = nDamageSources
L1_1 = L1_1.Energy
L0_1.damageSource = L1_1
L0_1 = nAffix_MeteorShower
L1_1 = nDescriptors
L1_1 = L1_1.IsEnergyDamage
L0_1.descriptors = L1_1
L0_1 = nAffix_MeteorShower
L1_1 = nUtil
L1_1 = L1_1.GetAsset
L2_1 = "LuaJobObject.Noun"
L1_1 = L1_1(L2_1)
L0_1.jobObject = L1_1
L0_1 = nAffix_MeteorShower
L1_1 = nUtil
L1_1 = L1_1.GetAsset
L2_1 = "gameplay_meteor_effect.ServerEventDef"
L1_1 = L1_1(L2_1)
L0_1.meteorAsset = L1_1
L0_1 = nAffix_MeteorShower
L0_1.timeToHit = 0.3
L0_1 = nAffix_MeteorShower
L1_1 = nUtil
L1_1 = L1_1.GetAsset
L2_1 = "Ability_Fireball.Noun"
L1_1 = L1_1(L2_1)
L0_1.positionTestAsset = L1_1
L0_1 = nAffix_MeteorShower
L0_1.spawnRadius = 16
L0_1 = nAffix_MeteorShower
L0_1.timeBetweenMeteors = 1
L0_1 = nAffix
L0_1 = L0_1.RegisterAffix
L1_1 = "MeteorShower"
L2_1 = nAffix_MeteorShower
L0_1(L1_1, L2_1)

function L0_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2, L19_2, L20_2, L21_2, L22_2
  L1_2 = nGameObject
  L1_2 = L1_2.GetPosition
  L2_2 = A0_2
  L1_2, L2_2, L3_2 = L1_2(L2_2)
  while true do
    L4_2 = GetRandomSpawnPosition
    L5_2 = nAffix_MeteorShower
    L5_2 = L5_2.positionTestAsset
    L6_2 = L1_2
    L7_2 = L2_2
    L8_2 = L3_2
    L9_2 = 0
    L10_2 = nAffix_MeteorShower
    L10_2 = L10_2.spawnRadius
    L4_2, L5_2, L6_2, L7_2 = L4_2(L5_2, L6_2, L7_2, L8_2, L9_2, L10_2)
    if L4_2 then
      L8_2 = {}
      L9_2 = nAffix_MeteorShower
      L9_2 = L9_2.meteorAsset
      L8_2.asset = L9_2
      L9_2 = {}
      L10_2 = L5_2
      L11_2 = L6_2
      L12_2 = L7_2
      L9_2[1] = L10_2
      L9_2[2] = L11_2
      L9_2[3] = L12_2
      L8_2.position = L9_2
      L9_2 = nEvent
      L9_2 = L9_2.Notify
      L10_2 = L8_2
      L9_2(L10_2)
      L9_2 = nThread
      L9_2 = L9_2.WaitForXSeconds
      L10_2 = nAffix_MeteorShower
      L10_2 = L10_2.timeToHit
      L9_2(L10_2)
      L9_2 = nObjectManager
      L9_2 = L9_2.GetObjectsInRadius
      L10_2 = L5_2
      L11_2 = L6_2
      L12_2 = L7_2
      L13_2 = nAffix_MeteorShower
      L13_2 = L13_2.damageRadius
      L14_2 = nSporeLabs
      L14_2 = L14_2.damageableObjectTypes
      L9_2 = L9_2(L10_2, L11_2, L12_2, L13_2, L14_2)
      L10_2 = ipairs
      L11_2 = L9_2
      L10_2, L11_2, L12_2 = L10_2(L11_2)
      for L13_2, L14_2 in L10_2, L11_2, L12_2 do
        L15_2 = nPlayer
        L15_2 = L15_2.IsPlayerControlledObject
        L16_2 = L14_2
        L15_2 = L15_2(L16_2)
        if L15_2 then
          L15_2 = nGameObject
          L15_2 = L15_2.IsAlive
          L16_2 = L14_2
          L15_2 = L15_2(L16_2)
          if L15_2 then
            L15_2 = nGameObject
            L15_2 = L15_2.TakeDamage
            L16_2 = kInvalidGUID
            L17_2 = L14_2
            L18_2 = nAffix_MeteorShower
            L18_2 = L18_2.damage
            L19_2 = nAffix_MeteorShower
            L19_2 = L19_2.damageType
            L20_2 = nAffix_MeteorShower
            L20_2 = L20_2.damageSource
            L21_2 = nAffix_MeteorShower
            L21_2 = L21_2.damageCoefficient
            L22_2 = nAffix_MeteorShower
            L22_2 = L22_2.descriptors
            L15_2(L16_2, L17_2, L18_2, L19_2, L20_2, L21_2, L22_2)
          end
        end
      end
    end
    L8_2 = nThread
    L8_2 = L8_2.WaitForXSeconds
    L9_2 = nAffix_MeteorShower
    L9_2 = L9_2.timeBetweenMeteors
    L8_2(L9_2)
  end
end

L1_1 = nAffix_MeteorShower
L2_1 = nAffixFns
L2_1 = L2_1.Tick

function L3_1()
  local L0_2, L1_2
  L0_2 = nThread
  L0_2 = L0_2.WaitForever
  L0_2()
end

L1_1[L2_1] = L3_1
L1_1 = nAffix_MeteorShower
L2_1 = nAffixFns
L2_1 = L2_1.HandleEvent

function L3_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2, L19_2, L20_2, L21_2, L22_2
  L2_2 = nObjectiveEvents
  L2_2 = L2_2.ActivateAffix
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
    L4_2 = nAffix
    L4_2 = L4_2.IsAffixPointValid
    L5_2 = L2_2
    L4_2 = L4_2(L5_2)
    if L4_2 then
      L4_2 = nGameObject
      L4_2 = L4_2.GetPosition
      L5_2 = L3_2
      L4_2, L5_2, L6_2 = L4_2(L5_2)
      L7_2 = nGameObject
      L7_2 = L7_2.GetOrientation
      L8_2 = L3_2
      L7_2, L8_2, L9_2, L10_2 = L7_2(L8_2)
      L11_2 = nObjectManager
      L11_2 = L11_2.CreateObject
      L12_2 = nAffix_MeteorShower
      L12_2 = L12_2.jobObject
      L13_2 = L4_2
      L14_2 = L5_2
      L15_2 = L6_2
      L16_2 = L7_2
      L17_2 = L8_2
      L18_2 = L9_2
      L19_2 = L10_2
      L20_2 = 1
      L21_2 = nUtil
      L21_2 = L21_2.ToGUID
      L22_2 = "0x0"
      L21_2, L22_2 = L21_2(L22_2)
      L11_2 = L11_2(L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2, L19_2, L20_2, L21_2, L22_2)
      L12_2 = nObjectManager
      L12_2 = L12_2.IsValidObject
      L13_2 = L11_2
      L12_2 = L12_2(L13_2)
      if L12_2 then
        L12_2 = nThread
        L12_2 = L12_2.CreateThreadForObject
        L13_2 = L11_2
        L14_2 = L0_1
        L15_2 = L11_2
        L12_2(L13_2, L14_2, L15_2)
      end
      L12_2 = nAffix
      L12_2 = L12_2.SetAffixPointInvalid
      L13_2 = L2_2
      L12_2(L13_2)
    end
  end
end

L1_1[L2_1] = L3_1
