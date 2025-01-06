local L0_1, L1_1, L2_1, L3_1, L4_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_Needs_Facing_And_Range = L0_1
L0_1 = nCondition_Needs_Facing_And_Range
L0_1.namespace = "nCondition_Needs_Facing_And_Range"
L0_1 = nCondition_Needs_Facing_And_Range
L0_1.conditionType = 0
L0_1 = nCondition_Needs_Facing_And_Range
L1_1 = {}
L2_1 = {}
L2_1.name = "Distance"
L3_1 = kReflectionType_float
L2_1.type = L3_1
L2_1.value = "10.0"
L3_1 = {}
L3_1.name = "Facing"
L4_1 = kReflectionType_float
L3_1.type = L4_1
L3_1.value = "60.0"
L1_1[1] = L2_1
L1_1[2] = L3_1
L0_1.properties = L1_1
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "NeedsFacingAndRange"
L2_1 = nCondition_Needs_Facing_And_Range
L0_1(L1_1, L2_1)
L0_1 = nCondition_Needs_Facing_And_Range

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2, L7_2
  L1_2 = nAgent
  L1_2 = L1_2.GetBestTarget
  L2_2 = A0_2
  L1_2 = L1_2(L2_2)
  L2_2 = kObjIDNone
  if L1_2 ~= L2_2 then
    L2_2 = nObjectManager
    L2_2 = L2_2.IsValidObject
    L3_2 = L1_2
    L2_2 = L2_2(L3_2)
    if L2_2 then
      L2_2 = nCondition
      L2_2 = L2_2.GetProperty
      L3_2 = A0_2
      L4_2 = "Distance"
      L2_2 = L2_2(L3_2, L4_2)
      L3_2 = nCondition
      L3_2 = L3_2.GetProperty
      L4_2 = A0_2
      L5_2 = "Facing"
      L3_2 = L3_2(L4_2, L5_2)
      L4_2 = nGameObject
      L4_2 = L4_2.GetObjectDistance
      L5_2 = A0_2
      L6_2 = L1_2
      L4_2 = L4_2(L5_2, L6_2)
      if L2_2 >= L4_2 then
        L5_2 = nPhysics
        L5_2 = L5_2.IsInLineOfSight
        L6_2 = A0_2
        L7_2 = L1_2
        L5_2 = L5_2(L6_2, L7_2)
        if not L5_2 then
          L5_2 = true
          return L5_2
        end
        L5_2 = nGameObject
        L5_2 = L5_2.GetObjectAngleDeg
        L6_2 = A0_2
        L7_2 = L1_2
        L5_2 = L5_2(L6_2, L7_2)
        if not (L3_2 > L5_2) then
          L6_2 = 360 - L3_2
          if not (L5_2 > L6_2) then
            goto lbl_52
          end
        end
        L6_2 = false
        return L6_2
      end
    end
  end
  ::lbl_52::
  L2_2 = true
  return L2_2
end

L0_1[1] = L1_1
