local L0_1, L1_1, L2_1, L3_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nTargetUtils = L0_1

function L0_1(A0_2, A1_2, A2_2, A3_2, A4_2, A5_2, A6_2, A7_2)
  local L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2, L19_2, L20_2, L21_2
  L8_2 = nGameObject
  L8_2 = L8_2.GetTeam
  L9_2 = A0_2
  L8_2 = L8_2(L9_2)
  L9_2 = kObjIDNone
  if A7_2 == true then
    L10_2 = nObjectManager
    L10_2 = L10_2.GetObjectsInRadius
    L11_2 = A2_2
    L12_2 = A3_2
    L13_2 = A4_2
    L14_2 = A6_2
    L15_2 = kType_Creature
    L10_2 = L10_2(L11_2, L12_2, L13_2, L14_2, L15_2)
    L11_2 = 1
    L12_2 = #L10_2
    if 1 < L12_2 then
      L12_2 = math
      L12_2 = L12_2.random
      L13_2 = 1
      L14_2 = #L10_2
      L12_2 = L12_2(L13_2, L14_2)
      L11_2 = L12_2
    end
    L12_2 = ipairs
    L13_2 = L10_2
    L12_2, L13_2, L14_2 = L12_2(L13_2)
    for L15_2, L16_2 in L12_2, L13_2, L14_2 do
      L17_2 = L15_2 + L11_2
      L18_2 = #L10_2
      if L17_2 > L18_2 then
        L18_2 = #L10_2
        L17_2 = L17_2 - L18_2
      end
      L18_2 = L10_2[L17_2]
      if L18_2 ~= A0_2 and L18_2 ~= A1_2 then
        L19_2 = A5_2[L18_2]
        if L19_2 == nil then
          L19_2 = nGameObject
          L19_2 = L19_2.ValidateHostileTarget
          L20_2 = L8_2
          L21_2 = L18_2
          L19_2 = L19_2(L20_2, L21_2)
          if L19_2 then
            L9_2 = L18_2
            break
          end
        end
      end
    end
  else
    L10_2 = nObjectManager
    L10_2 = L10_2.GetObjectsInRadius_SortedByDistance
    L11_2 = A2_2
    L12_2 = A3_2
    L13_2 = A4_2
    L14_2 = A6_2
    L15_2 = kType_Creature
    L10_2 = L10_2(L11_2, L12_2, L13_2, L14_2, L15_2)
    L11_2 = ipairs
    L12_2 = L10_2
    L11_2, L12_2, L13_2 = L11_2(L12_2)
    for L14_2, L15_2 in L11_2, L12_2, L13_2 do
      if L15_2 ~= A0_2 and L15_2 ~= A1_2 then
        L16_2 = A5_2[L15_2]
        if L16_2 == nil then
          L16_2 = nGameObject
          L16_2 = L16_2.ValidateHostileTarget
          L17_2 = L8_2
          L18_2 = L15_2
          L16_2 = L16_2(L17_2, L18_2)
          if L16_2 then
            L9_2 = L15_2
            break
          end
        end
      end
    end
  end
  return L9_2
end

function L1_1(A0_2, A1_2, A2_2, A3_2, A4_2, A5_2, A6_2, A7_2, A8_2)
  local L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2
  if A3_2 ~= nil then
    L9_2 = {}
    L9_2.asset = A3_2
    L9_2.objectId = A1_2
    L10_2 = nEvent
    L10_2 = L10_2.Notify
    L11_2 = L9_2
    L10_2(L11_2)
  end
  L9_2 = nil
  L10_2 = type
  L11_2 = A4_2
  L10_2 = L10_2(L11_2)
  if L10_2 == "table" then
    L10_2 = A8_2 + 1
    L11_2 = #A4_2
    if L10_2 > L11_2 then
      L10_2 = #A4_2
    end
    L9_2 = A4_2[L10_2]
  else
    L9_2 = A4_2
  end
  if L9_2 ~= nil then
    L10_2 = kObjIDNone
    if A2_2 ~= L10_2 then
      L10_2 = {}
      L10_2.asset = L9_2
      L10_2.objectId = A2_2
      L10_2.secondaryObjectId = A1_2
      L11_2 = nEvent
      L11_2 = L11_2.Notify
      L12_2 = L10_2
      L11_2(L12_2)
    end
  end
  if A5_2 ~= nil then
    L10_2 = A5_2
    L11_2 = A0_2
    L12_2 = A1_2
    L13_2 = A7_2
    L14_2 = A6_2
    L15_2 = A8_2
    L10_2(L11_2, L12_2, L13_2, L14_2, L15_2)
  end
end

L2_1 = nTargetUtils

function L3_1(A0_2, A1_2, A2_2, A3_2, A4_2, A5_2, A6_2, A7_2, A8_2, A9_2, A10_2)
  local L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2, L19_2, L20_2, L21_2, L22_2, L23_2, L24_2, L25_2, L26_2, L27_2, L28_2, L29_2, L30_2
  L11_2 = L1_1
  L12_2 = A0_2
  L13_2 = A1_2
  L14_2 = A0_2
  L15_2 = A4_2
  L16_2 = A5_2
  L17_2 = A7_2
  L18_2 = A8_2
  L19_2 = A9_2
  L20_2 = 0
  L11_2(L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2, L19_2, L20_2)
  L11_2 = A1_2
  L12_2 = {}
  L12_2[L11_2] = true
  L13_2 = 1
  L14_2 = A3_2
  L15_2 = 1
  for L16_2 = L13_2, L14_2, L15_2 do
    L17_2 = nGameObject
    L17_2 = L17_2.GetPosition
    L18_2 = L11_2
    L17_2, L18_2, L19_2 = L17_2(L18_2)
    L20_2 = nThread
    L20_2 = L20_2.WaitForXSeconds
    L21_2 = A6_2
    L22_2 = A9_2
    L20_2(L21_2, L22_2)
    L20_2 = L0_1
    L21_2 = A0_2
    L22_2 = L11_2
    L23_2 = L17_2
    L24_2 = L18_2
    L25_2 = L19_2
    L26_2 = L12_2
    L27_2 = A2_2
    L28_2 = A10_2
    L20_2 = L20_2(L21_2, L22_2, L23_2, L24_2, L25_2, L26_2, L27_2, L28_2)
    L21_2 = kObjIDNone
    if L20_2 ~= L21_2 then
      L21_2 = L1_1
      L22_2 = A0_2
      L23_2 = L20_2
      L24_2 = L11_2
      L25_2 = A4_2
      L26_2 = A5_2
      L27_2 = A7_2
      L28_2 = A8_2
      L29_2 = A9_2
      L30_2 = L16_2
      L21_2(L22_2, L23_2, L24_2, L25_2, L26_2, L27_2, L28_2, L29_2, L30_2)
      L12_2[L20_2] = true
      L11_2 = L20_2
    else
      break
    end
  end
end

L2_1.ChainHitTargets = L3_1
L2_1 = nTargetUtils

function L3_1(A0_2, A1_2, A2_2, A3_2)
  local L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2
  L4_2 = nGameObject
  L4_2 = L4_2.GetPosition
  L5_2 = A0_2
  L4_2, L5_2, L6_2 = L4_2(L5_2)
  L7_2 = nGameObject
  L7_2 = L7_2.GetFacing
  L8_2 = A0_2
  L7_2, L8_2, L9_2 = L7_2(L8_2)
  L10_2 = nGameObject
  L10_2 = L10_2.GetFootprintRadius
  L11_2 = A0_2
  L10_2 = L10_2(L11_2)
  L11_2 = A1_2
  if A3_2 == nil or A3_2 == false then
    L12_2 = L7_2 * L10_2
    L4_2 = L4_2 + L12_2
    L12_2 = L8_2 * L10_2
    L5_2 = L5_2 + L12_2
    L12_2 = L9_2 * L10_2
    L6_2 = L6_2 + L12_2
  else
    L11_2 = A1_2 + L10_2
  end
  L12_2 = math
  L12_2 = L12_2.rad
  L13_2 = A2_2
  L12_2 = L12_2(L13_2)
  L12_2 = L12_2 / 2
  L13_2 = {}
  L13_2.x = L4_2
  L13_2.y = L5_2
  L13_2.z = L6_2
  L13_2.facingX = L7_2
  L13_2.facingY = L8_2
  L13_2.facingZ = L9_2
  L13_2.length = L11_2
  L13_2.halfAngle = L12_2
  return L13_2
end

L2_1.MakeArc = L3_1
L2_1 = nTargetUtils

function L3_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2
  if A1_2 ~= nil then
    L2_2 = kObjIDNone
    if A1_2 ~= L2_2 then
      L2_2 = nObjectManager
      L2_2 = L2_2.IsValidObject
      L3_2 = A1_2
      L2_2 = L2_2(L3_2)
      if L2_2 then
        goto lbl_14
      end
    end
  end
  L2_2 = false
  do return L2_2 end
  ::lbl_14::
  L2_2 = nGameObject
  L2_2 = L2_2.GetPosition
  L3_2 = A1_2
  L2_2, L3_2, L4_2 = L2_2(L3_2)
  L5_2 = nGameObject
  L5_2 = L5_2.GetFootprintRadius
  L6_2 = A1_2
  L5_2 = L5_2(L6_2)
  L6_2 = math
  L6_2 = L6_2.abs
  L7_2 = A0_2.z
  L7_2 = L4_2 - L7_2
  L6_2 = L6_2(L7_2)
  if 20 < L6_2 then
    L6_2 = false
    return L6_2
  end
  L6_2 = nMathUtil
  L6_2 = L6_2.CircleIntersectsArc
  L7_2 = L2_2
  L8_2 = L3_2
  L9_2 = L5_2
  L10_2 = A0_2.x
  L11_2 = A0_2.y
  L12_2 = A0_2.facingX
  L13_2 = A0_2.facingY
  L14_2 = A0_2.length
  L15_2 = A0_2.halfAngle
  L15_2 = L15_2 * 2
  return L6_2(L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2)
end

L2_1.IsObjectInArc = L3_1
L2_1 = nTargetUtils

function L3_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2
  L1_2 = nObjectManager
  L1_2 = L1_2.GetObjectsInRadius
  L2_2 = A0_2.x
  L3_2 = A0_2.y
  L4_2 = A0_2.z
  L5_2 = A0_2.length
  L1_2 = L1_2(L2_2, L3_2, L4_2, L5_2)
  L2_2 = {}
  L3_2 = ipairs
  L4_2 = L1_2
  L3_2, L4_2, L5_2 = L3_2(L4_2)
  for L6_2, L7_2 in L3_2, L4_2, L5_2 do
    L8_2 = nTargetUtils
    L8_2 = L8_2.IsObjectInArc
    L9_2 = A0_2
    L10_2 = L7_2
    L8_2 = L8_2(L9_2, L10_2)
    if L8_2 then
      L8_2 = table
      L8_2 = L8_2.insert
      L9_2 = L2_2
      L10_2 = L7_2
      L8_2(L9_2, L10_2)
    end
  end
  return L2_2
end

L2_1.FindObjectsInArc = L3_1
L2_1 = nTargetUtils

function L3_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2
  L2_2 = nTargetUtils
  L2_2 = L2_2.FindObjectsInArc
  L3_2 = A0_2
  L2_2 = L2_2(L3_2)
  L3_2 = kObjIDNone
  L4_2 = 1000
  L5_2 = nGameObject
  L5_2 = L5_2.GetTeam
  L6_2 = A1_2
  L5_2 = L5_2(L6_2)
  L6_2 = ipairs
  L7_2 = L2_2
  L6_2, L7_2, L8_2 = L6_2(L7_2)
  for L9_2, L10_2 in L6_2, L7_2, L8_2 do
    L11_2 = nGameObject
    L11_2 = L11_2.ValidateHostileTarget
    L12_2 = L5_2
    L13_2 = L10_2
    L11_2 = L11_2(L12_2, L13_2)
    if L11_2 then
      L11_2 = nGameObject
      L11_2 = L11_2.GetObjectDistance
      L12_2 = A1_2
      L13_2 = L10_2
      L11_2 = L11_2(L12_2, L13_2)
      L12_2 = A0_2.length
      if L11_2 > L12_2 then
        L11_2 = 1
      else
        L12_2 = A0_2.length
        L11_2 = L11_2 / L12_2
      end
      L12_2 = nGameObject
      L12_2 = L12_2.GetObjectAngleRad
      L13_2 = A1_2
      L14_2 = L10_2
      L12_2 = L12_2(L13_2, L14_2)
      L13_2 = math
      L13_2 = L13_2.pi
      if L12_2 > L13_2 then
        L13_2 = math
        L13_2 = L13_2.pi
        L13_2 = 2 * L13_2
        L12_2 = L13_2 - L12_2
      end
      L13_2 = A0_2.halfAngle
      if L12_2 > L13_2 then
        L12_2 = 1
      else
        L13_2 = A0_2.halfAngle
        L12_2 = L12_2 / L13_2
      end
      L13_2 = L11_2 + L12_2
      if L4_2 > L13_2 then
        L3_2 = L10_2
        L4_2 = L13_2
      end
    end
  end
  return L3_2
end

L2_1.FindBestTargetInArc = L3_1
L2_1 = nTargetUtils

function L3_1(A0_2, A1_2, A2_2, A3_2, A4_2, A5_2, A6_2)
  local L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2
  L7_2 = nGameObject
  L7_2 = L7_2.GetTeam
  L8_2 = A0_2
  L7_2 = L7_2(L8_2)
  L8_2 = nObjectManager
  L8_2 = L8_2.GetObjectsInRadius
  L9_2 = A1_2
  L10_2 = A2_2
  L11_2 = A3_2
  L12_2 = A4_2
  L8_2 = L8_2(L9_2, L10_2, L11_2, L12_2)
  L9_2 = ipairs
  L10_2 = L8_2
  L9_2, L10_2, L11_2 = L9_2(L10_2)
  for L12_2, L13_2 in L9_2, L10_2, L11_2 do
    L14_2 = nGameObject
    L14_2 = L14_2.ValidateHostileTarget
    L15_2 = L7_2
    L16_2 = L13_2
    L14_2 = L14_2(L15_2, L16_2)
    if L14_2 then
      if A6_2 then
        L14_2 = nGameObject
        L14_2 = L14_2.GetNPCType
        L15_2 = L13_2
        L14_2 = L14_2(L15_2)
        L15_2 = nNPCType
        L15_2 = L15_2.Boss
        if L14_2 == L15_2 then
          goto lbl_39
        end
      end
      L14_2 = nModifier
      L14_2 = L14_2.RequestModifier
      L15_2 = L13_2
      L16_2 = A0_2
      L17_2 = A5_2
      L14_2(L15_2, L16_2, L17_2)
    end
    ::lbl_39::
  end
end

L2_1.ApplyModifierToEnemiesInArea = L3_1
L2_1 = nTargetUtils

function L3_1(A0_2, A1_2, A2_2, A3_2, A4_2)
  local L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2
  L5_2 = {}
  L6_2 = nGameObject
  L6_2 = L6_2.GetTeam
  L7_2 = A0_2
  L6_2 = L6_2(L7_2)
  L7_2 = nObjectManager
  L7_2 = L7_2.GetObjectsInRadius
  L8_2 = A1_2
  L9_2 = A2_2
  L10_2 = A3_2
  L11_2 = A4_2
  L7_2 = L7_2(L8_2, L9_2, L10_2, L11_2)
  L8_2 = ipairs
  L9_2 = L7_2
  L8_2, L9_2, L10_2 = L8_2(L9_2)
  for L11_2, L12_2 in L8_2, L9_2, L10_2 do
    L13_2 = nGameObject
    L13_2 = L13_2.ValidateHostileTarget
    L14_2 = L6_2
    L15_2 = L12_2
    L13_2 = L13_2(L14_2, L15_2)
    if L13_2 then
      L13_2 = table
      L13_2 = L13_2.insert
      L14_2 = L5_2
      L15_2 = L12_2
      L13_2(L14_2, L15_2)
    end
  end
  return L5_2
end

L2_1.GetTargetsInRadius = L3_1
L2_1 = nTargetUtils

function L3_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2
  L2_2 = nGameObject
  L2_2 = L2_2.GetPosition
  L3_2 = A0_2
  L2_2, L3_2, L4_2 = L2_2(L3_2)
  L5_2 = nTargetUtils
  L5_2 = L5_2.GetTargetsInRadius
  L6_2 = A0_2
  L7_2 = L2_2
  L8_2 = L3_2
  L9_2 = L4_2
  L10_2 = A1_2
  return L5_2(L6_2, L7_2, L8_2, L9_2, L10_2)
end

L2_1.GetTargetsAroundAttacker = L3_1
L2_1 = nTargetUtils

function L3_1(A0_2, A1_2, A2_2, A3_2, A4_2)
  local L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2
  L5_2 = {}
  L6_2 = nGameObject
  L6_2 = L6_2.GetTeam
  L7_2 = A0_2
  L6_2 = L6_2(L7_2)
  L7_2 = nObjectManager
  L7_2 = L7_2.GetObjectsInRadius
  L8_2 = A1_2
  L9_2 = A2_2
  L10_2 = A3_2
  L11_2 = A4_2
  L7_2 = L7_2(L8_2, L9_2, L10_2, L11_2)
  L8_2 = ipairs
  L9_2 = L7_2
  L8_2, L9_2, L10_2 = L8_2(L9_2)
  for L11_2, L12_2 in L8_2, L9_2, L10_2 do
    if L12_2 ~= A0_2 then
      L13_2 = nGameObject
      L13_2 = L13_2.ValidateFriendlyTarget
      L14_2 = L6_2
      L15_2 = L12_2
      L13_2 = L13_2(L14_2, L15_2)
      if L13_2 then
        L13_2 = table
        L13_2 = L13_2.insert
        L14_2 = L5_2
        L15_2 = L12_2
        L13_2(L14_2, L15_2)
      end
    end
  end
  return L5_2
end

L2_1.GetAlliesInRadius = L3_1
L2_1 = nTargetUtils

function L3_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2
  L2_2 = nGameObject
  L2_2 = L2_2.GetPosition
  L3_2 = A0_2
  L2_2, L3_2, L4_2 = L2_2(L3_2)
  L5_2 = nTargetUtils
  L5_2 = L5_2.GetAlliesInRadius
  L6_2 = A0_2
  L7_2 = L2_2
  L8_2 = L3_2
  L9_2 = L4_2
  L10_2 = A1_2
  return L5_2(L6_2, L7_2, L8_2, L9_2, L10_2)
end

L2_1.GetAlliesAroundCaster = L3_1
L2_1 = nTargetUtils

function L3_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2
  L2_2 = nGameObject
  L2_2 = L2_2.GetPosition
  L3_2 = A0_2
  L2_2, L3_2, L4_2 = L2_2(L3_2)
  L5_2 = nGameObject
  L5_2 = L5_2.GetPosition
  L6_2 = A1_2
  L5_2, L6_2, L7_2 = L5_2(L6_2)
  L8_2 = nObjectManager
  L8_2 = L8_2.GetObjectsAlongLine
  L9_2 = L2_2
  L10_2 = L3_2
  L11_2 = L4_2
  L12_2 = L5_2
  L13_2 = L6_2
  L14_2 = L7_2
  L15_2 = kType_Creature
  L8_2 = L8_2(L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2)
  return L8_2
end

L2_1.GetCreaturesBetweenObjects = L3_1
L2_1 = nTargetUtils

function L3_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2
  L2_2 = nTargetUtils
  L2_2 = L2_2.GetCreaturesBetweenObjects
  L3_2 = A0_2
  L4_2 = A1_2
  L2_2 = L2_2(L3_2, L4_2)
  L3_2 = nGameObject
  L3_2 = L3_2.GetTeam
  L4_2 = A0_2
  L3_2 = L3_2(L4_2)
  L4_2 = {}
  L5_2 = ipairs
  L6_2 = L2_2
  L5_2, L6_2, L7_2 = L5_2(L6_2)
  for L8_2, L9_2 in L5_2, L6_2, L7_2 do
    L10_2 = nGameObject
    L10_2 = L10_2.ValidateHostileTarget
    L11_2 = L3_2
    L12_2 = L9_2
    L10_2 = L10_2(L11_2, L12_2)
    if L10_2 then
      L10_2 = table
      L10_2 = L10_2.insert
      L11_2 = L4_2
      L12_2 = L9_2
      L10_2(L11_2, L12_2)
    end
  end
  return L4_2
end

L2_1.GetEnemiesBetweenObjects = L3_1
L2_1 = nTargetUtils

function L3_1(A0_2, A1_2, A2_2)
  local L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2, L19_2, L20_2, L21_2, L22_2, L23_2
  L3_2 = nGameObject
  L3_2 = L3_2.GetPosition
  L4_2 = A1_2
  L3_2, L4_2, L5_2 = L3_2(L4_2)
  L6_2 = nGameObject
  L6_2 = L6_2.GetPosition
  L7_2 = A0_2
  L6_2, L7_2, L8_2 = L6_2(L7_2)
  L9_2 = nGameObject
  L9_2 = L9_2.GetLinearVelocity
  L10_2 = A1_2
  L9_2, L10_2, L11_2 = L9_2(L10_2)
  L12_2 = nVector
  L12_2 = L12_2.len
  L13_2 = L9_2
  L14_2 = L10_2
  L15_2 = L11_2
  L12_2 = L12_2(L13_2, L14_2, L15_2)
  if L12_2 < 0.01 then
    L12_2 = true
    L13_2 = L3_2
    L14_2 = L4_2
    L15_2 = L5_2
    return L12_2, L13_2, L14_2, L15_2
  end
  L12_2 = L3_2 - L6_2
  L13_2 = L4_2 - L7_2
  L14_2 = L5_2 - L8_2
  L15_2 = A2_2 * A2_2
  L16_2 = nVector
  L16_2 = L16_2.dot
  L17_2 = L9_2
  L18_2 = L10_2
  L19_2 = L11_2
  L20_2 = L9_2
  L21_2 = L10_2
  L22_2 = L11_2
  L16_2 = L16_2(L17_2, L18_2, L19_2, L20_2, L21_2, L22_2)
  L15_2 = L15_2 - L16_2
  L16_2 = nVector
  L16_2 = L16_2.dot
  L17_2 = L9_2
  L18_2 = L10_2
  L19_2 = L11_2
  L20_2 = L12_2
  L21_2 = L13_2
  L22_2 = L14_2
  L16_2 = L16_2(L17_2, L18_2, L19_2, L20_2, L21_2, L22_2)
  L16_2 = -2 * L16_2
  L17_2 = nVector
  L17_2 = L17_2.dot
  L18_2 = L12_2
  L19_2 = L13_2
  L20_2 = L14_2
  L21_2 = L12_2
  L22_2 = L13_2
  L23_2 = L14_2
  L17_2 = L17_2(L18_2, L19_2, L20_2, L21_2, L22_2, L23_2)
  L17_2 = -1 * L17_2
  L18_2 = L16_2 * L16_2
  L19_2 = 4 * L15_2
  L19_2 = L19_2 * L17_2
  L18_2 = L18_2 - L19_2
  if L18_2 < 0 or L15_2 == 0 then
    L19_2 = false
    L20_2 = L3_2
    L21_2 = L4_2
    L22_2 = L5_2
    return L19_2, L20_2, L21_2, L22_2
  end
  L19_2 = math
  L19_2 = L19_2.sqrt
  L20_2 = L18_2
  L19_2 = L19_2(L20_2)
  L19_2 = L16_2 + L19_2
  L20_2 = 2 * L15_2
  L19_2 = L19_2 / L20_2
  L20_2 = true
  L21_2 = L19_2 * L9_2
  L21_2 = L3_2 + L21_2
  L22_2 = L19_2 * L10_2
  L22_2 = L4_2 + L22_2
  L23_2 = L19_2 * L11_2
  L23_2 = L5_2 + L23_2
  return L20_2, L21_2, L22_2, L23_2
end

L2_1.InterceptPoint = L3_1
L2_1 = nTargetUtils

function L3_1(A0_2, A1_2, A2_2, A3_2)
  local L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2, L19_2, L20_2, L21_2, L22_2, L23_2, L24_2, L25_2, L26_2, L27_2, L28_2, L29_2, L30_2, L31_2, L32_2, L33_2, L34_2
  L4_2 = nGameObject
  L4_2 = L4_2.GetFacing
  L5_2 = A0_2
  L4_2, L5_2, L6_2 = L4_2(L5_2)
  L7_2 = nGameObject
  L7_2 = L7_2.GetPosition
  L8_2 = A0_2
  L7_2, L8_2, L9_2 = L7_2(L8_2)
  L10_2 = math
  L10_2 = L10_2.rad
  L11_2 = A3_2
  L10_2 = L10_2(L11_2)
  A3_2 = L10_2
  L10_2 = nTargetUtils
  L10_2 = L10_2.InterceptPoint
  L11_2 = A0_2
  L12_2 = A1_2
  L13_2 = A2_2
  L10_2, L11_2, L12_2, L13_2 = L10_2(L11_2, L12_2, L13_2)
  if L10_2 then
    L14_2 = nVector
    L14_2 = L14_2.direction
    L15_2 = L11_2
    L16_2 = L12_2
    L17_2 = L13_2
    L18_2 = L7_2
    L19_2 = L8_2
    L20_2 = L9_2
    L14_2, L15_2, L16_2 = L14_2(L15_2, L16_2, L17_2, L18_2, L19_2, L20_2)
    L17_2 = math
    L17_2 = L17_2.acos
    L18_2 = nVector
    L18_2 = L18_2.dot
    L19_2 = L4_2
    L20_2 = L5_2
    L21_2 = L6_2
    L22_2 = L14_2
    L23_2 = L15_2
    L24_2 = L16_2
    L18_2, L19_2, L20_2, L21_2, L22_2, L23_2, L24_2, L25_2, L26_2, L27_2, L28_2, L29_2, L30_2, L31_2, L32_2, L33_2, L34_2 = L18_2(L19_2, L20_2, L21_2, L22_2, L23_2, L24_2)
    L17_2 = L17_2(L18_2, L19_2, L20_2, L21_2, L22_2, L23_2, L24_2, L25_2, L26_2, L27_2, L28_2, L29_2, L30_2, L31_2, L32_2, L33_2, L34_2)
    if A3_2 < L17_2 then
      L18_2 = nVector
      L18_2 = L18_2.len
      L19_2 = L11_2
      L20_2 = L12_2
      L21_2 = L13_2
      L22_2 = L7_2
      L23_2 = L8_2
      L24_2 = L9_2
      L18_2 = L18_2(L19_2, L20_2, L21_2, L22_2, L23_2, L24_2)
      L19_2 = A3_2
      L20_2 = nVector
      L20_2 = L20_2.normalize
      L21_2 = nVector
      L21_2 = L21_2.cross
      L22_2 = L4_2
      L23_2 = L5_2
      L24_2 = L6_2
      L25_2 = 0
      L26_2 = 0
      L27_2 = 1
      L21_2, L22_2, L23_2, L24_2, L25_2, L26_2, L27_2, L28_2, L29_2, L30_2, L31_2, L32_2, L33_2, L34_2 = L21_2(L22_2, L23_2, L24_2, L25_2, L26_2, L27_2)
      L20_2, L21_2, L22_2 = L20_2(L21_2, L22_2, L23_2, L24_2, L25_2, L26_2, L27_2, L28_2, L29_2, L30_2, L31_2, L32_2, L33_2, L34_2)
      L23_2 = nVector
      L23_2 = L23_2.dot
      L24_2 = L14_2
      L25_2 = L15_2
      L26_2 = L16_2
      L27_2 = L20_2
      L28_2 = L21_2
      L29_2 = L22_2
      L23_2 = L23_2(L24_2, L25_2, L26_2, L27_2, L28_2, L29_2)
      if 0 < L23_2 then
        L19_2 = L19_2 * -1
      end
      L23_2 = nMathUtil
      L23_2 = L23_2.RotateVectorByAxisAngle
      L24_2 = L4_2
      L25_2 = L5_2
      L26_2 = L6_2
      L27_2 = 0
      L28_2 = 0
      L29_2 = 1
      L30_2 = L19_2
      L23_2, L24_2, L25_2 = L23_2(L24_2, L25_2, L26_2, L27_2, L28_2, L29_2, L30_2)
      L16_2 = L25_2
      L15_2 = L24_2
      L14_2 = L23_2
      L23_2 = L14_2 * L18_2
      L23_2 = L7_2 + L23_2
      L24_2 = L15_2 * L18_2
      L24_2 = L8_2 + L24_2
      L25_2 = L16_2 * L18_2
      L25_2 = L9_2 + L25_2
      return L23_2, L24_2, L25_2
    end
    L18_2 = L11_2
    L19_2 = L12_2
    L20_2 = L13_2
    return L18_2, L19_2, L20_2
  else
    L14_2 = nGameObject
    L14_2 = L14_2.GetLinearVelocity
    L15_2 = A1_2
    L14_2, L15_2, L16_2 = L14_2(L15_2)
    L17_2 = nGameObject
    L17_2 = L17_2.GetPosition
    L18_2 = A1_2
    L17_2, L18_2, L19_2 = L17_2(L18_2)
    L20_2 = nVector
    L20_2 = L20_2.len
    L21_2 = L14_2
    L22_2 = L15_2
    L23_2 = L16_2
    L20_2 = L20_2(L21_2, L22_2, L23_2)
    if L20_2 < 0.1 then
      L20_2 = L17_2
      L21_2 = L18_2
      L22_2 = L19_2
      return L20_2, L21_2, L22_2
    end
    L20_2 = nVector
    L20_2 = L20_2.normalize
    L21_2 = L14_2
    L22_2 = L15_2
    L23_2 = L16_2
    L20_2, L21_2, L22_2 = L20_2(L21_2, L22_2, L23_2)
    L16_2 = L22_2
    L15_2 = L21_2
    L14_2 = L20_2
    L20_2 = nVector
    L20_2 = L20_2.normalize
    L21_2 = nVector
    L21_2 = L21_2.cross
    L22_2 = L4_2
    L23_2 = L5_2
    L24_2 = L6_2
    L25_2 = 0
    L26_2 = 0
    L27_2 = 1
    L21_2, L22_2, L23_2, L24_2, L25_2, L26_2, L27_2, L28_2, L29_2, L30_2, L31_2, L32_2, L33_2, L34_2 = L21_2(L22_2, L23_2, L24_2, L25_2, L26_2, L27_2)
    L20_2, L21_2, L22_2 = L20_2(L21_2, L22_2, L23_2, L24_2, L25_2, L26_2, L27_2, L28_2, L29_2, L30_2, L31_2, L32_2, L33_2, L34_2)
    L23_2 = A3_2
    L24_2 = nVector
    L24_2 = L24_2.dot
    L25_2 = L14_2
    L26_2 = L15_2
    L27_2 = L16_2
    L28_2 = L20_2
    L29_2 = L21_2
    L30_2 = L22_2
    L24_2 = L24_2(L25_2, L26_2, L27_2, L28_2, L29_2, L30_2)
    if 0 < L24_2 then
      L24_2 = math
      L24_2 = L24_2.pi
      L24_2 = L24_2 * 2
      L23_2 = L24_2 - L23_2
    end
    L24_2 = nVector
    L24_2 = L24_2.len
    L25_2 = L17_2
    L26_2 = L18_2
    L27_2 = L19_2
    L28_2 = L7_2
    L29_2 = L8_2
    L30_2 = L9_2
    L24_2 = L24_2(L25_2, L26_2, L27_2, L28_2, L29_2, L30_2)
    L25_2 = nMathUtil
    L25_2 = L25_2.RotateVectorByAxisAngle
    L26_2 = L4_2
    L27_2 = L5_2
    L28_2 = L6_2
    L29_2 = 0
    L30_2 = 0
    L31_2 = 1
    L32_2 = L23_2
    L25_2, L26_2, L27_2 = L25_2(L26_2, L27_2, L28_2, L29_2, L30_2, L31_2, L32_2)
    L28_2 = L25_2 * L24_2
    L28_2 = L7_2 + L28_2
    L29_2 = L26_2 * L24_2
    L29_2 = L8_2 + L29_2
    L30_2 = L27_2 * L24_2
    L27_2 = L9_2 + L30_2
    L26_2 = L29_2
    L25_2 = L28_2
    L28_2 = nDebug
    L28_2 = L28_2.DrawLine
    L29_2 = L7_2
    L30_2 = L8_2
    L31_2 = L9_2
    L32_2 = L25_2
    L33_2 = L26_2
    L34_2 = L27_2
    L28_2(L29_2, L30_2, L31_2, L32_2, L33_2, L34_2)
    L28_2 = L25_2
    L29_2 = L26_2
    L30_2 = L27_2
    return L28_2, L29_2, L30_2
  end
end

L2_1.InterceptPointMaxAngle = L3_1
L2_1 = nTargetUtils

function L3_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2
  L2_2 = nGameObject
  L2_2 = L2_2.GetTeam
  L3_2 = A0_2
  L2_2 = L2_2(L3_2)
  L3_2 = nGameObject
  L3_2 = L3_2.ValidateHostileTarget
  L4_2 = L2_2
  L5_2 = A1_2
  L3_2 = L3_2(L4_2, L5_2)
  if not L3_2 then
    L3_2 = false
    return L3_2
  end
  L3_2 = nPlayer
  L3_2 = L3_2.IsPlayerControlledObject
  L4_2 = A1_2
  L3_2 = L3_2(L4_2)
  if not L3_2 then
    L3_2 = false
    return L3_2
  end
  L3_2 = nAttribute
  L3_2 = L3_2.GetAttributeValue
  L4_2 = A1_2
  L5_2 = nAttributeType
  L5_2 = L5_2.OnLockdown
  L3_2 = L3_2(L4_2, L5_2)
  if L3_2 ~= 0 then
    L3_2 = false
    return L3_2
  end
  L3_2 = nPlayer
  L3_2 = L3_2.GetPlayerControlledObjects
  L3_2 = L3_2()
  L4_2 = 0
  L5_2 = ipairs
  L6_2 = L3_2
  L5_2, L6_2, L7_2 = L5_2(L6_2)
  for L8_2, L9_2 in L5_2, L6_2, L7_2 do
    L10_2 = nAttribute
    L10_2 = L10_2.GetAttributeValue
    L11_2 = L9_2
    L12_2 = nAttributeType
    L12_2 = L12_2.OnLockdown
    L10_2 = L10_2(L11_2, L12_2)
    if L10_2 ~= 0 then
      L4_2 = L4_2 + 1
    end
  end
  L5_2 = #L3_2
  L5_2 = L5_2 - 2
  if L4_2 > L5_2 then
    L5_2 = false
    return L5_2
  end
  L5_2 = nGameDirector
  L5_2 = L5_2.IsHordeActive
  L5_2 = L5_2()
  if L5_2 then
    L5_2 = false
    return L5_2
  end
  L5_2 = true
  return L5_2
end

L2_1.CanCageTarget = L3_1
