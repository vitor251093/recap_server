local L0_1, L1_1
L0_1 = require
L1_1 = "Lua!Global.lua"
L0_1(L1_1)
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = require
L1_1 = "Lua!Vector.lua"
L0_1(L1_1)
L0_1 = require
L1_1 = "Lua!TargetUtils.lua"
L0_1(L1_1)
L0_1 = Class
L0_1 = L0_1.newClass
L0_1 = L0_1()
nDNA_Follow = L0_1
L0_1 = nDNA_Follow
L0_1.namespace = "nDNA_Follow"
L0_1 = nDNA_Follow

function L1_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2
  L2_2 = nObjectManager
  L2_2 = L2_2.IsValidObject
  L3_2 = A1_2
  L2_2 = L2_2(L3_2)
  if L2_2 then
    L2_2 = nGameObject
    L2_2 = L2_2.IsAlive
    L3_2 = A1_2
    L2_2 = L2_2(L3_2)
    if L2_2 then
      L2_2 = nGameObject
      L2_2 = L2_2.GetIsStealthed
      L3_2 = A1_2
      L2_2 = L2_2(L3_2)
      if not L2_2 then
        L2_2 = nPlayer
        L2_2 = L2_2.IsPlayerControlledObject
        L3_2 = A1_2
        L2_2 = L2_2(L3_2)
        if L2_2 then
          return A1_2
        end
      end
    end
  end
  L2_2 = nGameObject
  L2_2 = L2_2.GetTeam
  L3_2 = A0_2
  L2_2 = L2_2(L3_2)
  L3_2 = nGameObject
  L3_2 = L3_2.GetPosition
  L4_2 = A0_2
  L3_2, L4_2, L5_2 = L3_2(L4_2)
  L6_2 = nObjectManager
  L6_2 = L6_2.GetObjectsInRadius_SortedByDistance
  L7_2 = L3_2
  L8_2 = L4_2
  L9_2 = L5_2
  L10_2 = 10
  L6_2 = L6_2(L7_2, L8_2, L9_2, L10_2)
  L7_2 = ipairs
  L8_2 = L6_2
  L7_2, L8_2, L9_2 = L7_2(L8_2)
  for L10_2, L11_2 in L7_2, L8_2, L9_2 do
    if A0_2 ~= L11_2 then
      L12_2 = nPlayer
      L12_2 = L12_2.IsPlayerControlledObject
      L13_2 = L11_2
      L12_2 = L12_2(L13_2)
      if L12_2 then
        L12_2 = nGameObject
        L12_2 = L12_2.GetIsStealthed
        L13_2 = L11_2
        L12_2 = L12_2(L13_2)
        if not L12_2 then
          return L11_2
        end
      end
    end
  end
  L7_2 = kObjIDNone
  return L7_2
end

L0_1.homingTargetValidator = L1_1
L0_1 = nDNA_Follow

function L1_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2
  L2_2 = coroutine
  L2_2 = L2_2.yield
  L2_2()
  L2_2 = kObjIDNone
  if A0_2 ~= L2_2 then
    L2_2 = kObjIDNone
    if A1_2 ~= L2_2 then
      L2_2 = nGameObject
      L2_2 = L2_2.GetObjectDirection
      L3_2 = A1_2
      L4_2 = A0_2
      L2_2, L3_2, L4_2 = L2_2(L3_2, L4_2)
      L5_2 = {}
      L6_2 = {}
      L7_2 = L2_2
      L8_2 = L3_2
      L9_2 = L4_2
      L6_2[1] = L7_2
      L6_2[2] = L8_2
      L6_2[3] = L9_2
      L5_2.mDirection = L6_2
      L5_2.mSpeed = 1
      L5_2.mRange = 1000
      L5_2.mSpinRate = 0
      L5_2.mEccentricity = 0
      L5_2.mAcceleration = 20
      L5_2.mTurnAcceleration = 20
      L6_2 = nProjectileFlags
      L6_2 = L6_2.kHoming
      L5_2.mProjectileFlags = L6_2
      L5_2.mHomingDelay = 0
      L5_2.mIgnoreGroundCollide = true
      L6_2 = nThread
      L6_2 = L6_2.WaitForProjectile
      L7_2 = nil
      L8_2 = A0_2
      L9_2 = L5_2
      L10_2 = A1_2
      L11_2 = nDNA_Follow
      L11_2 = L11_2.homingTargetValidator
      L6_2(L7_2, L8_2, L9_2, L10_2, L11_2)
      L6_2 = nThread
      L6_2 = L6_2.WaitForXSeconds
      L7_2 = 0.03
      L6_2(L7_2)
      L6_2 = nGameObject
      L6_2 = L6_2.DNAPickup
      L7_2 = A0_2
      L8_2 = A1_2
      L6_2(L7_2, L8_2)
    end
  end
end

L0_1.triggerThread = L1_1
L0_1 = nDNA_Follow

function L1_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2
  L2_2 = nGameObject
  L2_2 = L2_2.GetTriggerOwner
  L3_2 = A0_2
  L2_2 = L2_2(L3_2)
  L3_2 = nObjectManager
  L3_2 = L3_2.IsValidObject
  L4_2 = A1_2
  L3_2 = L3_2(L4_2)
  if L3_2 then
    L3_2 = nGameObject
    L3_2 = L3_2.IsAlive
    L4_2 = A1_2
    L3_2 = L3_2(L4_2)
    if L3_2 then
      L3_2 = nPlayer
      L3_2 = L3_2.IsPlayerControlledObject
      L4_2 = A1_2
      L3_2 = L3_2(L4_2)
      if L3_2 then
        L3_2 = nThread
        L3_2 = L3_2.CreateThreadForObject
        L4_2 = L2_2
        L5_2 = nDNA_Follow
        L5_2 = L5_2.triggerThread
        L6_2 = L2_2
        L7_2 = A1_2
        L3_2(L4_2, L5_2, L6_2, L7_2)
      end
    end
  end
end

L0_1.main = L1_1
