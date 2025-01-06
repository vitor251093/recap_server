local L0_1, L1_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)

function L0_1(A0_2)
  local L1_2, L2_2
  L1_2 = nGameObject
  L1_2 = L1_2.GetTeam
  L2_2 = A0_2
  L1_2 = L1_2(L2_2)
  
  function L2_2(A0_3)
    local L1_3, L2_3, L3_3
    L1_3 = nGameObject
    L1_3 = L1_3.ValidateHostileTarget
    L2_3 = L1_2
    L3_3 = A0_3
    L1_3 = L1_3(L2_3, L3_3)
    if L1_3 then
      L1_3 = nGameObject
      L1_3 = L1_3.GetNPCType
      L2_3 = A0_3
      L1_3 = L1_3(L2_3)
      L2_3 = nNPCType
      L2_3 = L2_3.Destructible
      L1_3 = L1_3 ~= L2_3
    end
    return L1_3
  end
  
  return L2_2
end

IsNonDestructableEnemy = L0_1

function L0_1(A0_2)
  local L1_2, L2_2
  L1_2 = nGameObject
  L1_2 = L1_2.GetTeam
  L2_2 = A0_2
  L1_2 = L1_2(L2_2)
  
  function L2_2(A0_3)
    local L1_3, L2_3, L3_3
    L1_3 = nGameObject
    L1_3 = L1_3.ValidateHostileTarget
    L2_3 = L1_2
    L3_3 = A0_3
    return L1_3(L2_3, L3_3)
  end
  
  return L2_2
end

IsEnemy = L0_1

function L0_1(A0_2)
  local L1_2, L2_2
  L1_2 = nGameObject
  L1_2 = L1_2.GetTeam
  L2_2 = A0_2
  L1_2 = L1_2(L2_2)
  
  function L2_2(A0_3)
    local L1_3, L2_3, L3_3
    L1_3 = nGameObject
    L1_3 = L1_3.ValidateFriendlyTarget
    L2_3 = L1_2
    L3_3 = A0_3
    L1_3 = L1_3(L2_3, L3_3)
    if L1_3 then
      L1_3 = nGameObject
      L1_3 = L1_3.GetNPCType
      L2_3 = A0_3
      L1_3 = L1_3(L2_3)
      L2_3 = nNPCType
      L2_3 = L2_3.Destructible
      L1_3 = L1_3 ~= L2_3
    end
    return L1_3
  end
  
  return L2_2
end

IsNonDestructibleFriend = L0_1

function L0_1(A0_2)
  local L1_2, L2_2
  L1_2 = nGameObject
  L1_2 = L1_2.GetTeam
  L2_2 = A0_2
  L1_2 = L1_2(L2_2)
  
  function L2_2(A0_3)
    local L1_3, L2_3, L3_3
    L1_3 = nGameObject
    L1_3 = L1_3.ValidateFriendlyTarget
    L2_3 = L1_2
    L3_3 = A0_3
    return L1_3(L2_3, L3_3)
  end
  
  return L2_2
end

IsFriend = L0_1

function L0_1(A0_2)
  local L1_2
  
  function L1_2(A0_3)
    local L1_3
    L1_3 = A0_2
    L1_3 = L1_3 ~= A0_3
    return L1_3
  end
  
  return L1_2
end

IsNot = L0_1

function L0_1(A0_2, A1_2, A2_2, A3_2)
  local L4_2, L5_2, L6_2, L7_2, L8_2, L9_2
  L4_2 = nThreadData
  L4_2 = L4_2.GetPrivateTable
  L4_2 = L4_2()
  L5_2 = {}
  L4_2.auraEffectModifierIds = L5_2
  L5_2 = L4_2.auraEffectModifierIds
  
  function L6_2(A0_3, A1_3)
    local L2_3, L3_3, L4_3, L5_3, L6_3, L7_3, L8_3, L9_3
    L2_3 = A2_2
    if L2_3 ~= nil then
      L2_3 = A2_2
      L3_3 = A1_3
      L2_3 = L2_3(L3_3)
      if L2_3 == false then
        L2_3 = false
        return L2_3
      end
    end
    L2_3 = nGameObject
    L2_3 = L2_3.GetAttributeSnapshot
    L3_3 = A0_2
    L2_3 = L2_3(L3_3)
    L3_3 = A3_2
    if L3_3 == nil then
      L3_3 = nAbility
      L3_3 = L3_3.GetRank
      L3_3 = L3_3()
      A3_2 = L3_3
    end
    L3_3 = L5_2
    L3_3 = L3_3[A1_3]
    if L3_3 ~= nil then
      L3_3 = false
      return L3_3
    end
    L3_3 = L5_2
    L4_3 = nModifier
    L4_3 = L4_3.RequestModifier
    L5_3 = A1_3
    L6_3 = A0_2
    L7_3 = A1_2
    L8_3 = L2_3
    L9_3 = A3_2
    L4_3 = L4_3(L5_3, L6_3, L7_3, L8_3, L9_3)
    L3_3[A1_3] = L4_3
    L3_3 = true
    return L3_3
  end
  
  function L7_2(A0_3, A1_3)
    local L2_3, L3_3, L4_3
    L2_3 = L5_2
    L2_3 = L2_3[A1_3]
    if L2_3 == nil then
      L2_3 = false
      return L2_3
    end
    L2_3 = nModifier
    L2_3 = L2_3.MarkForDelete
    L3_3 = A1_3
    L4_3 = L5_2
    L4_3 = L4_3[A1_3]
    L2_3(L3_3, L4_3)
    L2_3 = L5_2
    L2_3[A1_3] = nil
    L2_3 = true
    return L2_3
  end
  
  L8_2 = L6_2
  L9_2 = L7_2
  return L8_2, L9_2
end

SimpleAuraFns = L0_1

function L0_1()
  local L0_2, L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2, L8_2
  L0_2 = nThreadData
  L0_2 = L0_2.GetPrivateTable
  L0_2 = L0_2()
  L1_2 = pairs
  L2_2 = L0_2.auraEffectModifierIds
  L1_2, L2_2, L3_2 = L1_2(L2_2)
  for L4_2, L5_2 in L1_2, L2_2, L3_2 do
    L6_2 = nModifier
    L6_2 = L6_2.MarkForDelete
    L7_2 = L4_2
    L8_2 = L5_2
    L6_2(L7_2, L8_2)
  end
end

CleanupAuras = L0_1
