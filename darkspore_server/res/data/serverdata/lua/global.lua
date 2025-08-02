local L0_1, L1_1, L2_1, L3_1, L4_1, L5_1, L6_1, L7_1
L0_1 = require
L1_1 = "GlobalDefinitions"
L0_1(L1_1)
L0_1 = nSporeLabs
if L0_1 == nil then
  L0_1 = {}
  nSporeLabs = L0_1
end
L0_1 = nSporeLabs
L1_1 = nUtil
L1_1 = L1_1.GetAsset
L2_1 = "LuaJobObject.Noun"
L1_1 = L1_1(L2_1)
L0_1.jobObject = L1_1

function L0_1(A0_2, A1_2, A2_2, A3_2, A4_2, A5_2, A6_2, A7_2)
  local L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2
  L8_2 = true
  while L8_2 do
    L9_2 = nAbility
    L9_2 = L9_2.IsAbilityRunning
    L10_2 = A1_2
    L9_2 = L9_2(L10_2)
    if not L9_2 then
      L9_2 = nGameObject
      L9_2 = L9_2.MarkForDelete
      L10_2 = A0_2
      L9_2(L10_2)
      L8_2 = false
    else
      L9_2 = nDebug
      L9_2 = L9_2.DrawBox
      L10_2 = A2_2
      L11_2 = A3_2
      L12_2 = A4_2
      L13_2 = A5_2
      L14_2 = A6_2
      L15_2 = A7_2
      L9_2(L10_2, L11_2, L12_2, L13_2, L14_2, L15_2)
    end
    L9_2 = coroutine
    L9_2 = L9_2.yield
    L9_2()
  end
end

function L1_1(A0_2, A1_2, A2_2, A3_2, A4_2, A5_2)
  local L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2
  L6_2 = true
  while L6_2 do
    L7_2 = nAbility
    L7_2 = L7_2.IsAbilityRunning
    L8_2 = A1_2
    L7_2 = L7_2(L8_2)
    if not L7_2 then
      L7_2 = nGameObject
      L7_2 = L7_2.MarkForDelete
      L8_2 = A0_2
      L7_2(L8_2)
      L6_2 = false
    else
      L7_2 = nDebug
      L7_2 = L7_2.DrawCircle
      L8_2 = A2_2
      L9_2 = A3_2
      L10_2 = A4_2
      L11_2 = 0
      L12_2 = 0
      L13_2 = 1
      L14_2 = A5_2
      L7_2(L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2)
    end
    L7_2 = coroutine
    L7_2 = L7_2.yield
    L7_2()
  end
end

function L2_1(A0_2, A1_2, A2_2, A3_2, A4_2, A5_2)
  local L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2
  L6_2 = true
  while L6_2 do
    L7_2 = nObjectManager
    L7_2 = L7_2.IsValidObject
    L8_2 = A1_2
    L7_2 = L7_2(L8_2)
    if not L7_2 then
      L7_2 = nGameObject
      L7_2 = L7_2.MarkForDelete
      L8_2 = A0_2
      L7_2(L8_2)
      L6_2 = false
    else
      L7_2 = nDebug
      L7_2 = L7_2.DrawCircle
      L8_2 = A2_2
      L9_2 = A3_2
      L10_2 = A4_2
      L11_2 = 0
      L12_2 = 0
      L13_2 = 1
      L14_2 = A5_2
      L7_2(L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2)
    end
    L7_2 = coroutine
    L7_2 = L7_2.yield
    L7_2()
  end
end

function L3_1(A0_2, A1_2, A2_2, A3_2, A4_2, A5_2, A6_2, A7_2, A8_2)
  local L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2
  L9_2 = true
  while L9_2 do
    L10_2 = nObjectManager
    L10_2 = L10_2.IsValidObject
    L11_2 = A1_2
    L10_2 = L10_2(L11_2)
    if not L10_2 then
      L10_2 = nGameObject
      L10_2 = L10_2.MarkForDelete
      L11_2 = A0_2
      L10_2(L11_2)
      L9_2 = false
    else
      L10_2 = nDebug
      L10_2 = L10_2.DrawOrientedBox
      L11_2 = A2_2
      L12_2 = A3_2
      L13_2 = A4_2
      L14_2 = A5_2
      L15_2 = A6_2
      L16_2 = A7_2
      L17_2 = A8_2
      L10_2(L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2)
    end
    L10_2 = coroutine
    L10_2 = L10_2.yield
    L10_2()
  end
end

function L4_1(A0_2, A1_2, A2_2)
  local L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2
  L3_2 = true
  while L3_2 do
    L4_2 = nAbility
    L4_2 = L4_2.IsAbilityRunning
    L5_2 = A1_2
    L4_2 = L4_2(L5_2)
    if not L4_2 then
      L4_2 = nGameObject
      L4_2 = L4_2.MarkForDelete
      L5_2 = A0_2
      L4_2(L5_2)
      L3_2 = false
    else
      L4_2 = nDebug
      L4_2 = L4_2.SetColor
      L5_2 = 1
      L6_2 = 0
      L7_2 = 0
      L4_2(L5_2, L6_2, L7_2)
      L4_2 = nDebug
      L4_2 = L4_2.SetAlpha
      L5_2 = 0.25
      L4_2(L5_2)
      L4_2 = math
      L4_2 = L4_2.deg
      L5_2 = A2_2.halfAngle
      L5_2 = L5_2 * 2
      L4_2 = L4_2(L5_2)
      L5_2 = nDebug
      L5_2 = L5_2.FillArc
      L6_2 = A2_2.x
      L7_2 = A2_2.y
      L8_2 = A2_2.z
      L9_2 = 0
      L10_2 = 0
      L11_2 = 1
      L12_2 = A2_2.facingX
      L13_2 = A2_2.facingY
      L14_2 = A2_2.facingZ
      L15_2 = A2_2.length
      L16_2 = L4_2
      L5_2(L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2)
    end
    L4_2 = coroutine
    L4_2 = L4_2.yield
    L4_2()
  end
end

L5_1 = nClient

function L6_1(A0_2, A1_2, A2_2)
  local L3_2, L4_2, L5_2, L6_2, L7_2
  L3_2 = _G
  L3_2 = L3_2[A0_2]
  L4_2 = L3_2.DrawReticle
  if L4_2 then
    L5_2 = L3_2
    L4_2 = L3_2.DrawReticle
    L6_2 = A1_2
    L7_2 = A2_2
    L4_2(L5_2, L6_2, L7_2)
  end
end

L5_1.TryToDrawReticle = L6_1
L5_1 = nAbility

function L6_1(A0_2, A1_2, A2_2, A3_2, A4_2, A5_2, A6_2)
  local L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2
  L7_2 = nDebug
  L7_2 = L7_2.IsAbilityDebugEnabled
  L7_2 = L7_2()
  if L7_2 then
    L7_2 = nObjectManager
    L7_2 = L7_2.CreateObject
    L8_2 = nSporeLabs
    L8_2 = L8_2.jobObject
    L9_2 = 0
    L10_2 = 0
    L11_2 = 0
    L7_2 = L7_2(L8_2, L9_2, L10_2, L11_2)
    L8_2 = nObjectManager
    L8_2 = L8_2.IsValidObject
    L9_2 = L7_2
    L8_2 = L8_2(L9_2)
    if L8_2 then
      L8_2 = nThread
      L8_2 = L8_2.CreateThreadForObject
      L9_2 = L7_2
      L10_2 = L0_1
      L11_2 = L7_2
      L12_2 = A0_2
      L13_2 = A1_2
      L14_2 = A2_2
      L15_2 = A3_2
      L16_2 = A4_2
      L17_2 = A5_2
      L18_2 = A6_2
      L8_2(L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2)
    end
  end
end

L5_1.DebugDrawDamageBox = L6_1
L5_1 = nAbility

function L6_1(A0_2, A1_2, A2_2, A3_2, A4_2)
  local L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2
  L5_2 = nDebug
  L5_2 = L5_2.IsAbilityDebugEnabled
  L5_2 = L5_2()
  if L5_2 then
    L5_2 = nObjectManager
    L5_2 = L5_2.CreateObject
    L6_2 = nSporeLabs
    L6_2 = L6_2.jobObject
    L7_2 = 0
    L8_2 = 0
    L9_2 = 0
    L5_2 = L5_2(L6_2, L7_2, L8_2, L9_2)
    L6_2 = nObjectManager
    L6_2 = L6_2.IsValidObject
    L7_2 = L5_2
    L6_2 = L6_2(L7_2)
    if L6_2 then
      L6_2 = nThread
      L6_2 = L6_2.CreateThreadForObject
      L7_2 = L5_2
      L8_2 = L1_1
      L9_2 = L5_2
      L10_2 = A0_2
      L11_2 = A1_2
      L12_2 = A2_2
      L13_2 = A3_2
      L14_2 = A4_2
      L6_2(L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2)
    end
  end
end

L5_1.DebugDrawDamageArea = L6_1
L5_1 = nAbility

function L6_1(A0_2, A1_2, A2_2, A3_2, A4_2)
  local L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2
  L5_2 = nDebug
  L5_2 = L5_2.IsAbilityDebugEnabled
  L5_2 = L5_2()
  if L5_2 then
    L5_2 = nObjectManager
    L5_2 = L5_2.CreateObject
    L6_2 = nSporeLabs
    L6_2 = L6_2.jobObject
    L7_2 = 0
    L8_2 = 0
    L9_2 = 0
    L5_2 = L5_2(L6_2, L7_2, L8_2, L9_2)
    L6_2 = nObjectManager
    L6_2 = L6_2.IsValidObject
    L7_2 = L5_2
    L6_2 = L6_2(L7_2)
    if L6_2 then
      L6_2 = nThread
      L6_2 = L6_2.CreateThreadForObject
      L7_2 = L5_2
      L8_2 = L2_1
      L9_2 = L5_2
      L10_2 = A0_2
      L11_2 = A1_2
      L12_2 = A2_2
      L13_2 = A3_2
      L14_2 = A4_2
      L6_2(L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2)
    end
  end
end

L5_1.DebugDrawDamageAreaForObject = L6_1
L5_1 = nAbility

function L6_1(A0_2, A1_2, A2_2, A3_2, A4_2, A5_2, A6_2, A7_2)
  local L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2, L19_2, L20_2
  L8_2 = nDebug
  L8_2 = L8_2.IsAbilityDebugEnabled
  L8_2 = L8_2()
  if L8_2 then
    L8_2 = nObjectManager
    L8_2 = L8_2.CreateObject
    L9_2 = nSporeLabs
    L9_2 = L9_2.jobObject
    L10_2 = 0
    L11_2 = 0
    L12_2 = 0
    L8_2 = L8_2(L9_2, L10_2, L11_2, L12_2)
    L9_2 = nObjectManager
    L9_2 = L9_2.IsValidObject
    L10_2 = L8_2
    L9_2 = L9_2(L10_2)
    if L9_2 then
      L9_2 = nThread
      L9_2 = L9_2.CreateThreadForObject
      L10_2 = L8_2
      L11_2 = L3_1
      L12_2 = L8_2
      L13_2 = A0_2
      L14_2 = A1_2
      L15_2 = A2_2
      L16_2 = A3_2
      L17_2 = A4_2
      L18_2 = A5_2
      L19_2 = A6_2
      L20_2 = A7_2
      L9_2(L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2, L18_2, L19_2, L20_2)
    end
  end
end

L5_1.DebugDrawDamageBoxForObject = L6_1
L5_1 = nAbility

function L6_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2
  L2_2 = nDebug
  L2_2 = L2_2.IsAbilityDebugEnabled
  L2_2 = L2_2()
  if L2_2 then
    L2_2 = nObjectManager
    L2_2 = L2_2.CreateObject
    L3_2 = nSporeLabs
    L3_2 = L3_2.jobObject
    L4_2 = 0
    L5_2 = 0
    L6_2 = 0
    L2_2 = L2_2(L3_2, L4_2, L5_2, L6_2)
    L3_2 = nObjectManager
    L3_2 = L3_2.IsValidObject
    L4_2 = L2_2
    L3_2 = L3_2(L4_2)
    if L3_2 then
      L3_2 = nThread
      L3_2 = L3_2.CreateThreadForObject
      L4_2 = L2_2
      L5_2 = L4_1
      L6_2 = L2_2
      L7_2 = A0_2
      L8_2 = A1_2
      L3_2(L4_2, L5_2, L6_2, L7_2, L8_2)
    end
  end
end

L5_1.DebugDrawDamageArc = L6_1
L5_1 = nAbility

function L6_1(A0_2, A1_2, A2_2, A3_2)
  local L4_2, L5_2, L6_2, L7_2, L8_2, L9_2
  L4_2 = _G
  L4_2 = L4_2[A0_2]
  L5_2 = nil
  L6_2 = L4_2.TranslateToken
  if L6_2 then
    L6_2 = L4_2.TranslateToken
    L7_2 = A1_2
    L8_2 = A2_2
    L9_2 = A3_2
    L6_2 = L6_2(L7_2, L8_2, L9_2)
    L5_2 = L6_2
  end
  if L5_2 == nil then
    if A1_2 == "minDamage" then
      L6_2 = L4_2.damage
      if L6_2 then
        L6_2 = type
        L7_2 = L4_2.damage
        L6_2 = L6_2(L7_2)
        if L6_2 == "table" then
          L6_2 = A2_2
          L7_2 = L4_2.damage
          L7_2 = #L7_2
          if L6_2 > L7_2 then
            L7_2 = L4_2.damage
            L6_2 = #L7_2
          end
          L7_2 = L4_2.damage
          L7_2 = L7_2[L6_2]
          L5_2 = L7_2[1]
        else
          L5_2 = L4_2.damage
        end
      end
    elseif A1_2 == "maxDamage" then
      L6_2 = L4_2.damage
      if L6_2 then
        L6_2 = type
        L7_2 = L4_2.damage
        L6_2 = L6_2(L7_2)
        if L6_2 == "table" then
          L6_2 = A2_2
          L7_2 = L4_2.damage
          L7_2 = #L7_2
          if L6_2 > L7_2 then
            L7_2 = L4_2.damage
            L6_2 = #L7_2
          end
          L7_2 = L4_2.damage
          L7_2 = L7_2[L6_2]
          L5_2 = L7_2[2]
        else
          L5_2 = L4_2.damage
        end
      end
    elseif A1_2 == "radius" then
      L6_2 = L4_2.radius
      if L6_2 then
        L6_2 = type
        L7_2 = L4_2.radius
        L6_2 = L6_2(L7_2)
        if L6_2 == "table" then
          L6_2 = L4_2.radius
          L6_2 = #L6_2
          if L6_2 == 5 then
            L6_2 = L4_2.radius
            L5_2 = L6_2[A2_2]
          end
        else
          L5_2 = L4_2.radius
        end
      end
    elseif A1_2 == "maxStackCount" then
      L6_2 = GetRankedValueHelper
      L7_2 = L4_2.maxStackCount
      L8_2 = A2_2
      L6_2 = L6_2(L7_2, L8_2)
      L5_2 = L6_2
    end
  end
  return L5_2
end

L5_1.TranslateToken = L6_1

function L5_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2
  L2_2 = ipairs
  L3_2 = A1_2
  L2_2, L3_2, L4_2 = L2_2(L3_2)
  for L5_2, L6_2 in L2_2, L3_2, L4_2 do
    L7_2 = #A0_2
    L7_2 = L7_2 + 1
    A0_2[L7_2] = L6_2
  end
end

L6_1 = nAbility

function L7_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2
  L2_2 = nGameObject
  L2_2 = L2_2.SetStealthType
  L3_2 = A0_2
  L4_2 = A1_2
  L2_2(L3_2, L4_2)
  L2_2 = nAbility
  L2_2 = L2_2.GetStealthingPets
  L3_2 = A0_2
  L2_2 = L2_2(L3_2)
  if L2_2 ~= nil then
    L3_2 = ipairs
    L4_2 = L2_2
    L3_2, L4_2, L5_2 = L3_2(L4_2)
    for L6_2, L7_2 in L3_2, L4_2, L5_2 do
      L8_2 = nGameObject
      L8_2 = L8_2.SetStealthType
      L9_2 = L7_2
      L10_2 = A1_2
      L8_2(L9_2, L10_2)
    end
  end
end

L6_1.SetStealth = L7_1
L6_1 = nAbility

function L7_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2
  L1_2 = {}
  L2_2 = nModifier
  L2_2 = L2_2.GetModifiersMatchingDescriptor
  L3_2 = A0_2
  L4_2 = 0
  L2_2 = L2_2(L3_2, L4_2)
  if L2_2 ~= nil then
    L3_2 = ipairs
    L4_2 = L2_2
    L3_2, L4_2, L5_2 = L3_2(L4_2)
    for L6_2, L7_2 in L3_2, L4_2, L5_2 do
      L8_2 = nAbility
      L8_2 = L8_2.GetAbilityNamespace
      L9_2 = L7_2
      L8_2 = L8_2(L9_2)
      L9_2 = _G
      L9_2 = L9_2[L8_2]
      L10_2 = L9_2.GetStealthingPets
      if L10_2 ~= nil then
        L10_2 = nModifier
        L10_2 = L10_2.CallFunctionInContext
        L11_2 = L7_2
        L12_2 = L9_2.GetStealthingPets
        L10_2 = L10_2(L11_2, L12_2)
        if L10_2 ~= nil then
          L11_2 = L5_1
          L12_2 = L1_2
          L13_2 = L10_2
          L11_2(L12_2, L13_2)
        end
      end
    end
  end
  return L1_2
end

L6_1.GetStealthingPets = L7_1
L6_1 = nAbility

function L7_1(A0_2)
  local L1_2, L2_2, L3_2
  L1_2 = 0
  L2_2 = _G
  L2_2 = L2_2[A0_2]
  L3_2 = L2_2.animationSequence
  if L3_2 ~= nil then
    L3_2 = L2_2.animationSequence
    L3_2 = L3_2.selectionMethod
    return L3_2
  end
  L3_2 = 0
  return L3_2
end

L6_1.GetAnimSequenceType = L7_1
L6_1 = nAbility

function L7_1(A0_2)
  local L1_2, L2_2, L3_2
  L1_2 = 0
  L2_2 = _G
  L2_2 = L2_2[A0_2]
  L3_2 = L2_2.animationSequence
  if L3_2 ~= nil then
    L3_2 = L2_2.animationSequence
    L3_2 = #L3_2
    return L3_2
  end
  L3_2 = 1
  return L3_2
end

L6_1.GetNumAnims = L7_1
L6_1 = nAbility

function L7_1(A0_2, A1_2, A2_2, A3_2, A4_2, A5_2, A6_2, A7_2)
  local L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2
  L8_2 = 0
  L9_2 = _G
  L9_2 = L9_2[A0_2]
  L10_2 = nAbilityFns
  L10_2 = L10_2.GetWarmupData
  L10_2 = L9_2[L10_2]
  if L10_2 then
    L10_2 = nAbilityFns
    L10_2 = L10_2.GetWarmupData
    L10_2 = L9_2[L10_2]
    L11_2 = A1_2
    L12_2 = A2_2
    L13_2 = A3_2
    L14_2 = A4_2
    L15_2 = A5_2
    L16_2 = A6_2
    L17_2 = A7_2
    L10_2 = L10_2(L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2)
    L11_2 = type
    L12_2 = L10_2
    L11_2 = L11_2(L12_2)
    if L11_2 == "string" then
      L11_2 = nUtil
      L11_2 = L11_2.SPID
      L12_2 = L10_2
      L11_2 = L11_2(L12_2)
      L8_2 = L11_2
    else
      L8_2 = L10_2
    end
  else
    L10_2 = L9_2.animationSequence
    if L10_2 ~= nil then
      L10_2 = nil
      L11_2 = L9_2.animationSequence
      L11_2 = L11_2.selectionMethod
      L12_2 = nAbilityAnimationSelection
      L12_2 = L12_2.Sequence
      if L11_2 == L12_2 then
        L11_2 = L9_2.animationSequence
        L12_2 = A7_2 + 1
        L11_2 = L11_2[L12_2]
        L10_2 = L11_2.animationstate
      else
        L11_2 = L9_2.animationSequence
        L11_2 = L11_2.selectionMethod
        L12_2 = nAbilityAnimationSelection
        L12_2 = L12_2.Random
        if L11_2 == L12_2 then
          L11_2 = L9_2.animationSequence
          L12_2 = A7_2 + 1
          L11_2 = L11_2[L12_2]
          L10_2 = L11_2.animationstate
        end
      end
      L11_2 = type
      L12_2 = L10_2
      L11_2 = L11_2(L12_2)
      if L11_2 == "string" then
        L11_2 = nUtil
        L11_2 = L11_2.SPID
        L12_2 = L10_2
        L11_2 = L11_2(L12_2)
        L8_2 = L11_2
      else
        L8_2 = L10_2
      end
    else
      L10_2 = L9_2.animationstate
      if L10_2 ~= nil then
        L8_2 = L9_2.animationstate
      end
    end
  end
  return L8_2
end

L6_1.GetWarmupData_New = L7_1
L6_1 = nAbility

function L7_1(A0_2, A1_2, A2_2, A3_2, A4_2, A5_2, A6_2, A7_2)
  local L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2
  L8_2 = 0
  L9_2 = _G
  L9_2 = L9_2[A0_2]
  L10_2 = nAbilityFns
  L10_2 = L10_2.GetWarmupData
  L10_2 = L9_2[L10_2]
  if L10_2 then
    L10_2 = nAbilityFns
    L10_2 = L10_2.GetWarmupData
    L10_2 = L9_2[L10_2]
    L11_2 = A1_2
    L12_2 = A2_2
    L13_2 = A3_2
    L14_2 = A4_2
    L15_2 = A5_2
    L16_2 = A6_2
    L17_2 = A7_2
    L10_2 = L10_2(L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2)
    L11_2 = type
    L12_2 = L10_2
    L11_2 = L11_2(L12_2)
    if L11_2 == "string" then
      L11_2 = nUtil
      L11_2 = L11_2.SPID
      L12_2 = L10_2
      L11_2 = L11_2(L12_2)
      L8_2 = L11_2
    else
      L8_2 = L10_2
    end
  else
    L10_2 = L9_2.animationstate
    if L10_2 ~= nil then
      L8_2 = L9_2.animationstate
    end
  end
  return L8_2
end

L6_1.GetWarmupData = L7_1
L6_1 = nMathUtil

function L7_1(A0_2, A1_2, A2_2)
  local L3_2, L4_2
  L3_2 = 1 - A2_2
  L3_2 = L3_2 * A0_2
  L4_2 = A2_2 * A1_2
  L3_2 = L3_2 + L4_2
  return L3_2
end

L6_1.Lerp = L7_1
L6_1 = nMathUtil

function L7_1(A0_2, A1_2, A2_2)
  if A0_2 < A1_2 then
    return A1_2
  end
  if A2_2 < A0_2 then
    return A2_2
  end
  return A0_2
end

L6_1.Clamp = L7_1
L6_1 = nSporeLabs

function L7_1(A0_2)
  local L1_2, L2_2
  L1_2 = nObjectManager
  L1_2 = L1_2.IsValidObject
  L2_2 = A0_2
  L1_2 = L1_2(L2_2)
  if L1_2 == false then
    L1_2 = false
    return L1_2
  end
  L1_2 = nGameObject
  L1_2 = L1_2.IsCombatant
  L2_2 = A0_2
  return L1_2(L2_2)
end

L6_1.CanBeDamaged = L7_1
L6_1 = nPhysics

function L7_1(A0_2, A1_2, A2_2, A3_2, A4_2, A5_2, A6_2)
  local L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2, L16_2, L17_2
  L7_2 = nObjectManager
  L7_2 = L7_2.GetObjectsInRadius
  L8_2 = A0_2
  L9_2 = A1_2
  L10_2 = A2_2
  L11_2 = A3_2
  L7_2 = L7_2(L8_2, L9_2, L10_2, L11_2)
  L8_2 = ipairs
  L9_2 = L7_2
  L8_2, L9_2, L10_2 = L8_2(L9_2)
  for L11_2, L12_2 in L8_2, L9_2, L10_2 do
    L13_2 = nPhysics
    L13_2 = L13_2.IsDynamic
    L14_2 = L12_2
    L13_2 = L13_2(L14_2)
    if L13_2 then
      L13_2 = nPhysics
      L13_2 = L13_2.ApplyImpulse
      L14_2 = L12_2
      L15_2 = A4_2
      L16_2 = A5_2
      L17_2 = A6_2
      L13_2(L14_2, L15_2, L16_2, L17_2)
    end
  end
end

L6_1.ApplyImpulseInRange = L7_1
L6_1 = table

function L7_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2
  L1_2 = {}
  
  function L2_2(A0_3)
    local L1_3, L2_3, L3_3, L4_3, L5_3, L6_3, L7_3, L8_3, L9_3
    L1_3 = type
    L2_3 = A0_3
    L1_3 = L1_3(L2_3)
    if L1_3 ~= "table" then
      return A0_3
    else
      L1_3 = L1_2
      L1_3 = L1_3[A0_3]
      if L1_3 then
        L1_3 = L1_2
        L1_3 = L1_3[A0_3]
        return L1_3
      end
    end
    L1_3 = {}
    L2_3 = L1_2
    L2_3[A0_3] = L1_3
    L2_3 = pairs
    L3_3 = A0_3
    L2_3, L3_3, L4_3 = L2_3(L3_3)
    for L5_3, L6_3 in L2_3, L3_3, L4_3 do
      L7_3 = L2_2
      L8_3 = L5_3
      L7_3 = L7_3(L8_3)
      L8_3 = L2_2
      L9_3 = L6_3
      L8_3 = L8_3(L9_3)
      L1_3[L7_3] = L8_3
    end
    L2_3 = setmetatable
    L3_3 = L1_3
    L4_3 = getmetatable
    L5_3 = A0_3
    L4_3, L5_3, L6_3, L7_3, L8_3, L9_3 = L4_3(L5_3)
    return L2_3(L3_3, L4_3, L5_3, L6_3, L7_3, L8_3, L9_3)
  end
  
  L3_2 = L2_2
  L4_2 = A0_2
  return L3_2(L4_2)
end

L6_1.deepcopy = L7_1
L6_1 = table

function L7_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2
  L2_2 = pairs
  L3_2 = A0_2
  L2_2, L3_2, L4_2 = L2_2(L3_2)
  for L5_2, L6_2 in L2_2, L3_2, L4_2 do
    if L6_2 == A1_2 then
      L7_2 = true
      return L7_2
    end
  end
  L2_2 = false
  return L2_2
end

L6_1.contains = L7_1
L6_1 = table

function L7_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2
  L2_2 = pairs
  L3_2 = A0_2
  L2_2, L3_2, L4_2 = L2_2(L3_2)
  for L5_2, L6_2 in L2_2, L3_2, L4_2 do
    if L6_2 == A1_2 then
      return L5_2
    end
  end
  L2_2 = 0
  return L2_2
end

L6_1.find = L7_1
L6_1 = table

function L7_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2
  L2_2 = pairs
  L3_2 = A0_2
  L2_2, L3_2, L4_2 = L2_2(L3_2)
  for L5_2, L6_2 in L2_2, L3_2, L4_2 do
    if L5_2 == A1_2 then
      L7_2 = true
      return L7_2
    end
  end
  L2_2 = false
  return L2_2
end

L6_1.hasIndex = L7_1
L6_1 = table

function L7_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2
  L1_2 = #A0_2
  while 1 < L1_2 do
    L2_2 = math
    L2_2 = L2_2.random
    L3_2 = L1_2
    L2_2 = L2_2(L3_2)
    L3_2 = A0_2[L2_2]
    L4_2 = A0_2[L1_2]
    A0_2[L2_2] = L4_2
    A0_2[L1_2] = L3_2
    L1_2 = L1_2 - 1
  end
end

L6_1.shuffle = L7_1
L6_1 = {}
Class = L6_1
L6_1 = Class

function L7_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2
  L1_2 = {}
  L2_2 = {}
  L2_2.__index = L1_2
  
  function L3_2(A0_3)
    local L1_3, L2_3, L3_3, L4_3, L5_3, L6_3, L7_3, L8_3
    L1_3 = {}
    L2_3 = pairs
    L3_3 = A0_3
    L2_3, L3_3, L4_3 = L2_3(L3_3)
    for L5_3, L6_3 in L2_3, L3_3, L4_3 do
      L7_3 = type
      L8_3 = L6_3
      L7_3 = L7_3(L8_3)
      if L7_3 ~= "function" then
        L1_3[L5_3] = L6_3
      end
    end
    L2_3 = setmetatable
    L3_3 = L1_3
    L4_3 = L2_2
    L2_3(L3_3, L4_3)
    return L1_3
  end
  
  L1_2.new = L3_2
  if nil ~= A0_2 then
    L3_2 = setmetatable
    L4_2 = L1_2
    L5_2 = {}
    L5_2.__index = A0_2
    L3_2(L4_2, L5_2)
  end
  
  function L3_2(A0_3)
    local L1_3
    L1_3 = L1_2
    return L1_3
  end
  
  L1_2.class = L3_2
  
  function L3_2(A0_3)
    local L1_3
    L1_3 = A0_2
    return L1_3
  end
  
  L1_2.superClass = L3_2
  
  function L3_2(A0_3, A1_3)
    local L2_3, L3_3, L4_3, L5_3
    L2_3 = false
    L3_3 = L1_2
    while nil ~= L3_3 and false == L2_3 do
      if L3_3 == A1_3 then
        L2_3 = true
      else
        L5_3 = L3_3
        L4_3 = L3_3.superClass
        L4_3 = L4_3(L5_3)
        L3_3 = L4_3
      end
    end
    return L2_3
  end
  
  L1_2.isa = L3_2
  return L1_2
end

L6_1.newClass = L7_1

function L6_1(A0_2, A1_2)
  local L2_2, L3_2
  L2_2 = type
  L3_2 = A0_2
  L2_2 = L2_2(L3_2)
  if L2_2 == "table" then
    L2_2 = #A0_2
    if L2_2 == 0 then
      L2_2 = 0
      return L2_2
    end
    if A1_2 < 1 then
      A1_2 = 1
    end
    L2_2 = #A0_2
    if A1_2 > L2_2 then
      A1_2 = #A0_2
    end
    L2_2 = A0_2[A1_2]
    return L2_2
  end
  return A0_2
end

GetRankedValueHelper = L6_1
L6_1 = nAbility

function L7_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2
  L2_2 = GetRankedValueHelper
  L3_2 = A0_2
  L4_2 = A1_2
  return L2_2(L3_2, L4_2)
end

L6_1.GetRankedValueWithRank = L7_1
L6_1 = nGameObject

function L7_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2
  L2_2 = nGameObject
  L2_2 = L2_2.GetNPCRank
  L3_2 = A0_2
  L2_2 = L2_2(L3_2)
  L3_2 = GetRankedValueHelper
  L4_2 = A1_2
  L5_2 = L2_2
  return L3_2(L4_2, L5_2)
end

L6_1.GetRankedValueNPC = L7_1
L6_1 = nAbility

function L7_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2
  L1_2 = nAbility
  L1_2 = L1_2.GetRank
  L1_2 = L1_2()
  L2_2 = GetRankedValueHelper
  L3_2 = A0_2
  L4_2 = L1_2
  return L2_2(L3_2, L4_2)
end

L6_1.GetRankedValue = L7_1
L6_1 = nAbility

function L7_1(A0_2, A1_2, A2_2)
  local L3_2, L4_2, L5_2, L6_2, L7_2
  L3_2 = 0
  L4_2 = _G
  L4_2 = L4_2[A0_2]
  L5_2 = L4_2.GetManaCost
  if L5_2 then
    L5_2 = L4_2.GetManaCost
    L6_2 = A1_2
    L7_2 = A2_2
    L5_2 = L5_2(L6_2, L7_2)
    L3_2 = L5_2
  else
    L5_2 = L4_2.manaCost
    if L5_2 ~= nil then
      L5_2 = GetRankedValueHelper
      L6_2 = L4_2.manaCost
      L7_2 = A2_2
      L5_2 = L5_2(L6_2, L7_2)
      L3_2 = L5_2
    end
  end
  return L3_2
end

L6_1.GetManaCost = L7_1
L6_1 = nAbility

function L7_1(A0_2, A1_2, A2_2, A3_2)
  local L4_2, L5_2, L6_2, L7_2, L8_2, L9_2
  L4_2 = 0
  L5_2 = _G
  L5_2 = L5_2[A0_2]
  L6_2 = L5_2.GetDuration
  if L6_2 then
    L6_2 = L5_2.GetDuration
    L7_2 = A1_2
    L8_2 = A2_2
    L9_2 = A3_2
    L6_2 = L6_2(L7_2, L8_2, L9_2)
    L4_2 = L6_2
  else
    L6_2 = L5_2.duration
    if L6_2 ~= nil then
      L6_2 = GetRankedValueHelper
      L7_2 = L5_2.duration
      L8_2 = A3_2
      L6_2 = L6_2(L7_2, L8_2)
      L4_2 = L6_2
    end
  end
  return L4_2
end

L6_1.GetDuration = L7_1
L6_1 = nAbility

function L7_1(A0_2, A1_2, A2_2, A3_2)
  local L4_2, L5_2, L6_2, L7_2, L8_2
  L4_2 = 0
  L5_2 = A0_2.GetTimeToRelease
  if L5_2 then
    L5_2 = A0_2.GetTimeToRelease
    L6_2 = A1_2
    L7_2 = A0_2
    L8_2 = A3_2
    L5_2 = L5_2(L6_2, L7_2, L8_2)
    L4_2 = L5_2
  else
    L5_2 = A0_2.animationSequence
    if L5_2 ~= nil then
      L5_2 = A0_2.animationSequence
      L5_2 = L5_2.selectionMethod
      L6_2 = nAbilityAnimationSelection
      L6_2 = L6_2.Sequence
      if L5_2 == L6_2 then
        L5_2 = A0_2.animationSequence
        L6_2 = A3_2 + 1
        L5_2 = L5_2[L6_2]
        L4_2 = L5_2.release
      else
        L5_2 = A0_2.animationSequence
        L5_2 = L5_2.selectionMethod
        L6_2 = nAbilityAnimationSelection
        L6_2 = L6_2.Random
        if L5_2 == L6_2 then
          L5_2 = A0_2.animationSequence
          L6_2 = A3_2 + 1
          L5_2 = L5_2[L6_2]
          L4_2 = L5_2.release
        else
          L5_2 = A0_2.animationSequence
          L5_2 = L5_2.selectionMethod
          L6_2 = nAbilityAnimationSelection
          L6_2 = L6_2.Rank
          if L5_2 == L6_2 then
            L5_2 = A0_2.animationSequence
            L5_2 = L5_2[A2_2]
            L4_2 = L5_2.release
          else
            L5_2 = nDebug
            L5_2 = L5_2.Assert
            L6_2 = 0
            L5_2(L6_2)
          end
        end
      end
    else
      L5_2 = A0_2.timetorelease
      if L5_2 ~= nil then
        L5_2 = type
        L6_2 = A0_2.timetorelease
        L5_2 = L5_2(L6_2)
        if L5_2 == "table" then
          L5_2 = GetRankedValueHelper
          L6_2 = A0_2.timetorelease
          L7_2 = A2_2
          L5_2 = L5_2(L6_2, L7_2)
          L4_2 = L5_2
        else
          L4_2 = A0_2.timetorelease
        end
      end
    end
  end
  return L4_2
end

L6_1.GetTimeToReleaseLua = L7_1
L6_1 = nAbility

function L7_1(A0_2, A1_2, A2_2, A3_2)
  local L4_2, L5_2, L6_2, L7_2, L8_2, L9_2
  L4_2 = _G
  L4_2 = L4_2[A0_2]
  L5_2 = nAbility
  L5_2 = L5_2.GetTimeToReleaseLua
  L6_2 = L4_2
  L7_2 = A1_2
  L8_2 = A2_2
  L9_2 = A3_2
  return L5_2(L6_2, L7_2, L8_2, L9_2)
end

L6_1.GetTimeToRelease = L7_1
L6_1 = nAbility

function L7_1()
  local L0_2, L1_2
  L0_2 = nAbility
  L0_2 = L0_2.GetRank
  L0_2 = L0_2()
  L0_2 = L0_2 == 3
  return L0_2
end

L6_1.IsInOverdrive = L7_1
L6_1 = nAbility

function L7_1(A0_2)
  local L1_2, L2_2
  L1_2 = nGameObject
  L1_2 = L1_2.GetNPCType
  L2_2 = A0_2
  L1_2 = L1_2(L2_2)
  L2_2 = nNPCType
  L2_2 = L2_2.Minion
  if L1_2 ~= L2_2 then
    L1_2 = nGameObject
    L1_2 = L1_2.GetNPCType
    L2_2 = A0_2
    L1_2 = L1_2(L2_2)
    L2_2 = nNPCType
    L2_2 = L2_2.Lieutenant
    if L1_2 ~= L2_2 then
      L1_2 = nGameObject
      L1_2 = L1_2.GetNPCType
      L2_2 = A0_2
      L1_2 = L1_2(L2_2)
      L2_2 = nNPCType
      L2_2 = L2_2.Captain
      if L1_2 ~= L2_2 then
        L1_2 = nGameObject
        L1_2 = L1_2.GetNPCType
        L2_2 = A0_2
        L1_2 = L1_2(L2_2)
        L2_2 = nNPCType
        L2_2 = L2_2.Agent
        if L1_2 ~= L2_2 then
          L1_2 = nGameObject
          L1_2 = L1_2.GetNPCType
          L2_2 = A0_2
          L1_2 = L1_2(L2_2)
          L2_2 = nNPCType
          L2_2 = L2_2.Boss
          if L1_2 ~= L2_2 then
            goto lbl_43
          end
        end
      end
    end
  end
  L1_2 = true
  do return L1_2 end
  ::lbl_43::
  L1_2 = false
  return L1_2
end

L6_1.IsNPC = L7_1

function L6_1(A0_2)
  local L1_2, L2_2, L3_2
  L1_2 = 25
  L2_2 = 1.0333
  L3_2 = L2_2 ^ A0_2
  L3_2 = L1_2 * L3_2
  return L3_2
end

GetCrystalPoints = L6_1

function L6_1(A0_2)
  local L1_2
  L1_2 = nTuning
  L1_2 = L1_2.CrystalBonus
  L1_2 = L1_2()
  L1_2 = A0_2 * L1_2
  return L1_2
end

GetCrystalBonus = L6_1
L6_1 = nGameObject

function L7_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2
  L2_2 = nGameObject
  L2_2 = L2_2.GetType
  L3_2 = A0_2
  L2_2 = L2_2(L3_2)
  L3_2 = ipairs
  L4_2 = A1_2
  L3_2, L4_2, L5_2 = L3_2(L4_2)
  for L6_2, L7_2 in L3_2, L4_2, L5_2 do
    if L2_2 == L7_2 then
      L8_2 = true
      return L8_2
    end
  end
  L3_2 = false
  return L3_2
end

L6_1.MatchesAnyType = L7_1
L6_1 = nGameObject

function L7_1(A0_2)
  local L1_2, L2_2, L3_2
  L1_2 = nGameObject
  L1_2 = L1_2.GetOwnerID
  L2_2 = A0_2
  L1_2 = L1_2(L2_2)
  L2_2 = kObjIDNone
  if L1_2 ~= L2_2 then
    L2_2 = nPlayer
    L2_2 = L2_2.IsPlayerControlledObject
    L3_2 = L1_2
    L2_2 = L2_2(L3_2)
    if L2_2 then
      L2_2 = true
      return L2_2
    end
  end
  L2_2 = false
  return L2_2
end

L6_1.IsPet = L7_1
L6_1 = nLocomotion

function L7_1(A0_2, A1_2, A2_2)
  local L3_2, L4_2, L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2, L15_2
  L3_2 = nGameObject
  L3_2 = L3_2.GetPosition
  L4_2 = A0_2
  L3_2, L4_2, L5_2 = L3_2(L4_2)
  L6_2 = math
  L6_2 = L6_2.random
  L6_2 = L6_2()
  L6_2 = L6_2 * 2
  L7_2 = math
  L7_2 = L7_2.pi
  L6_2 = L6_2 * L7_2
  L7_2 = nMathUtil
  L7_2 = L7_2.RotateVectorByAxisAngle
  L8_2 = 1
  L9_2 = 0
  L10_2 = 0
  L11_2 = 0
  L12_2 = 0
  L13_2 = 1
  L14_2 = L6_2
  L7_2, L8_2, L9_2 = L7_2(L8_2, L9_2, L10_2, L11_2, L12_2, L13_2, L14_2)
  L10_2 = math
  L10_2 = L10_2.random
  L10_2 = L10_2()
  L11_2 = A2_2 - A1_2
  L10_2 = L10_2 * L11_2
  L10_2 = A1_2 + L10_2
  L11_2 = L7_2 * L10_2
  L7_2 = L11_2 + L3_2
  L11_2 = L8_2 * L10_2
  L8_2 = L11_2 + L4_2
  L11_2 = L9_2 * L10_2
  L9_2 = L11_2 + L5_2
  L11_2 = nLocomotion
  L11_2 = L11_2.GetClosestPosition
  L12_2 = A0_2
  L13_2 = L7_2
  L14_2 = L8_2
  L15_2 = L9_2
  L11_2, L12_2, L13_2 = L11_2(L12_2, L13_2, L14_2, L15_2)
  L9_2 = L13_2
  L8_2 = L12_2
  L7_2 = L11_2
  L11_2 = L7_2
  L12_2 = L8_2
  L13_2 = L9_2
  return L11_2, L12_2, L13_2
end

L6_1.FindRandomPosition = L7_1
L6_1 = nLocomotion

function L7_1(A0_2, A1_2, A2_2, A3_2, A4_2)
  local L5_2, L6_2, L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2
  L5_2 = math
  L5_2 = L5_2.random
  L5_2 = L5_2()
  L5_2 = L5_2 * 2
  L6_2 = math
  L6_2 = L6_2.pi
  L5_2 = L5_2 * L6_2
  L6_2 = nMathUtil
  L6_2 = L6_2.RotateVectorByAxisAngle
  L7_2 = 1
  L8_2 = 0
  L9_2 = 0
  L10_2 = 0
  L11_2 = 0
  L12_2 = 1
  L13_2 = L5_2
  L6_2, L7_2, L8_2 = L6_2(L7_2, L8_2, L9_2, L10_2, L11_2, L12_2, L13_2)
  L9_2 = math
  L9_2 = L9_2.random
  L9_2 = L9_2()
  L10_2 = A4_2 - A3_2
  L9_2 = L9_2 * L10_2
  L9_2 = A3_2 + L9_2
  L10_2 = L6_2 * L9_2
  L6_2 = L10_2 + A0_2
  L10_2 = L7_2 * L9_2
  L7_2 = L10_2 + A1_2
  L10_2 = L8_2 * L9_2
  L8_2 = L10_2 + A2_2
  L10_2 = nLocomotion
  L10_2 = L10_2.GetClosestPositionFromPoint
  L11_2 = L6_2
  L12_2 = L7_2
  L13_2 = L8_2
  L10_2, L11_2, L12_2 = L10_2(L11_2, L12_2, L13_2)
  L8_2 = L12_2
  L7_2 = L11_2
  L6_2 = L10_2
  L10_2 = L6_2
  L11_2 = L7_2
  L12_2 = L8_2
  return L10_2, L11_2, L12_2
end

L6_1.FindRandomPositionFromPoint = L7_1
L6_1 = nUtil

function L7_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2
  L1_2 = math
  L1_2 = L1_2.floor
  L2_2 = A0_2
  L1_2 = L1_2(L2_2)
  L2_2 = A0_2 - L1_2
  if 0.5 <= L2_2 then
    L3_2 = math
    L3_2 = L3_2.ceil
    L4_2 = A0_2
    L3_2 = L3_2(L4_2)
    A0_2 = L3_2
  else
    A0_2 = L1_2
  end
  return A0_2
end

L6_1.Round = L7_1
