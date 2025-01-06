local L0_1, L1_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)

function L0_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2, L5_2
  
  function L2_2()
    local L0_3, L1_3, L2_3, L3_3, L4_3, L5_3, L6_3, L7_3
    L0_3 = nAbility
    L0_3 = L0_3.GetAgentID
    L0_3 = L0_3()
    L1_3 = nThreadData
    L1_3 = L1_3.GetPrivateTable
    L1_3 = L1_3()
    if L1_3 == nil then
      L2_3 = nThreadData
      L2_3 = L2_3.CreatePrivateTable
      L2_3 = L2_3()
      L1_3 = L2_3
    end
    L2_3 = "modifier_"
    L3_3 = A0_2
    L2_3 = L2_3 .. L3_3
    L3_3 = nAttribute
    L3_3 = L3_3.AddAttributeModifier
    L4_3 = L0_3
    L5_3 = A0_2
    L6_3 = nAbility
    L6_3 = L6_3.GetRankedValue
    L7_3 = A1_2
    L6_3, L7_3 = L6_3(L7_3)
    L3_3 = L3_3(L4_3, L5_3, L6_3, L7_3)
    L1_3[L2_3] = L3_3
  end
  
  function L3_2()
    local L0_3, L1_3, L2_3, L3_3, L4_3, L5_3, L6_3, L7_3
    L0_3 = nAbility
    L0_3 = L0_3.GetAgentID
    L0_3 = L0_3()
    L1_3 = nThreadData
    L1_3 = L1_3.GetPrivateTable
    L1_3 = L1_3()
    L2_3 = "modifier_"
    L3_3 = A0_2
    L2_3 = L2_3 .. L3_3
    L3_3 = nAttribute
    L3_3 = L3_3.RemoveAttributeModifier
    L4_3 = L0_3
    L5_3 = L1_3[L2_3]
    L3_3(L4_3, L5_3)
    L3_3 = nModifier
    L3_3 = L3_3.GetMyStackCount
    L3_3 = L3_3()
    L4_3 = nAbility
    L4_3 = L4_3.GetRankedValue
    L5_3 = A1_2
    L4_3 = L4_3(L5_3)
    L3_3 = L3_3 * L4_3
    L4_3 = nAttribute
    L4_3 = L4_3.AddAttributeModifier
    L5_3 = L0_3
    L6_3 = A0_2
    L7_3 = L3_3
    L4_3 = L4_3(L5_3, L6_3, L7_3)
    L1_3[L2_3] = L4_3
  end
  
  L4_2 = L2_2
  L5_2 = L3_2
  return L4_2, L5_2
end

CreateStackingAttributeFunctions = L0_1

function L0_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2
  
  function L1_2()
    local L0_3, L1_3, L2_3, L3_3, L4_3, L5_3, L6_3, L7_3, L8_3
    L0_3 = nAbility
    L0_3 = L0_3.GetAgentID
    L0_3 = L0_3()
    L1_3 = nThreadData
    L1_3 = L1_3.GetPrivateTable
    L1_3 = L1_3()
    if L1_3 == nil then
      L2_3 = nThreadData
      L2_3 = L2_3.CreatePrivateTable
      L2_3 = L2_3()
      L1_3 = L2_3
    end
    L2_3 = "modifier_combatspeed"
    L3_3 = "modifier_noncombatspeed"
    L4_3 = nAttribute
    L4_3 = L4_3.AddAttributeModifier
    L5_3 = L0_3
    L6_3 = nAttributeType
    L6_3 = L6_3.CombatSpeed
    L7_3 = nAbility
    L7_3 = L7_3.GetRankedValue
    L8_3 = A0_2
    L7_3, L8_3 = L7_3(L8_3)
    L4_3 = L4_3(L5_3, L6_3, L7_3, L8_3)
    L1_3[L2_3] = L4_3
    L4_3 = nAttribute
    L4_3 = L4_3.AddAttributeModifier
    L5_3 = L0_3
    L6_3 = nAttributeType
    L6_3 = L6_3.NonCombatSpeed
    L7_3 = nAbility
    L7_3 = L7_3.GetRankedValue
    L8_3 = A0_2
    L7_3, L8_3 = L7_3(L8_3)
    L4_3 = L4_3(L5_3, L6_3, L7_3, L8_3)
    L1_3[L3_3] = L4_3
  end
  
  function L2_2()
    local L0_3, L1_3, L2_3, L3_3, L4_3, L5_3, L6_3, L7_3, L8_3, L9_3
    L0_3 = nAbility
    L0_3 = L0_3.GetAgentID
    L0_3 = L0_3()
    L1_3 = nThreadData
    L1_3 = L1_3.GetPrivateTable
    L1_3 = L1_3()
    L2_3 = "modifier_combatspeed"
    L3_3 = "modifier_noncombatspeed"
    L4_3 = nAttribute
    L4_3 = L4_3.RemoveAttributeModifier
    L5_3 = L0_3
    L6_3 = L1_3[L2_3]
    L4_3(L5_3, L6_3)
    L4_3 = nAttribute
    L4_3 = L4_3.RemoveAttributeModifier
    L5_3 = L0_3
    L6_3 = L1_3[L3_3]
    L4_3(L5_3, L6_3)
    L4_3 = nModifier
    L4_3 = L4_3.GetMyStackCount
    L4_3 = L4_3()
    L5_3 = nAbility
    L5_3 = L5_3.GetRankedValue
    L6_3 = A0_2
    L5_3 = L5_3(L6_3)
    L4_3 = L4_3 * L5_3
    L5_3 = nAttribute
    L5_3 = L5_3.AddAttributeModifier
    L6_3 = L0_3
    L7_3 = nAttributeType
    L7_3 = L7_3.CombatSpeed
    L8_3 = nAbility
    L8_3 = L8_3.GetRankedValue
    L9_3 = A0_2
    L8_3, L9_3 = L8_3(L9_3)
    L5_3 = L5_3(L6_3, L7_3, L8_3, L9_3)
    L1_3[L2_3] = L5_3
    L5_3 = nAttribute
    L5_3 = L5_3.AddAttributeModifier
    L6_3 = L0_3
    L7_3 = nAttributeType
    L7_3 = L7_3.NonCombatSpeed
    L8_3 = nAbility
    L8_3 = L8_3.GetRankedValue
    L9_3 = A0_2
    L8_3, L9_3 = L8_3(L9_3)
    L5_3 = L5_3(L6_3, L7_3, L8_3, L9_3)
    L1_3[L3_3] = L5_3
  end
  
  L3_2 = L1_2
  L4_2 = L2_2
  return L3_2, L4_2
end

CreateStackingSpeedFunctions = L0_1

function L0_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2
  L1_2 = nAbility
  L1_2 = L1_2.GetAgentID
  L1_2 = L1_2()
  L2_2 = nAttribute
  L2_2 = L2_2.AddAttributeModifier
  L3_2 = L1_2
  L4_2 = nAttributeType
  L4_2 = L4_2.MovementSpeedBuff
  L5_2 = nAbility
  L5_2 = L5_2.GetRankedValue
  L6_2 = A0_2
  L5_2, L6_2 = L5_2(L6_2)
  L2_2(L3_2, L4_2, L5_2, L6_2)
end

AutoDestructSpeedModifier = L0_1

function L0_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2
  L1_2 = nAttribute
  L1_2 = L1_2.AddAttributeModifier
  L2_2 = A0_2
  L3_2 = nAttributeType
  L3_2 = L3_2.ImmuneToBanish
  L4_2 = 1
  L1_2(L2_2, L3_2, L4_2)
  L1_2 = nAttribute
  L1_2 = L1_2.AddAttributeModifier
  L2_2 = A0_2
  L3_2 = nAttributeType
  L3_2 = L3_2.CrowdControlDurationDecrease
  L4_2 = 0.5
  L1_2(L2_2, L3_2, L4_2)
  L1_2 = nAttribute
  L1_2 = L1_2.AddAttributeModifier
  L2_2 = A0_2
  L3_2 = nAttributeType
  L3_2 = L3_2.ImmuneToRandomTeleport
  L4_2 = 1
  L1_2(L2_2, L3_2, L4_2)
  L1_2 = nAttribute
  L1_2 = L1_2.AddAttributeModifier
  L2_2 = A0_2
  L3_2 = nAttributeType
  L3_2 = L3_2.ImmuneToKnockback
  L4_2 = 1
  L1_2(L2_2, L3_2, L4_2)
  L1_2 = nModifier
  L1_2 = L1_2.RequestModifier
  L2_2 = A0_2
  L3_2 = A0_2
  L4_2 = nUtil
  L4_2 = L4_2.SPID
  L5_2 = "BossStealthDetect"
  L4_2, L5_2 = L4_2(L5_2)
  L1_2(L2_2, L3_2, L4_2, L5_2)
end

StandardBossSetup = L0_1
