local L0_1, L1_1, L2_1, L3_1, L4_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)
L0_1 = {}
nCondition_Distance = L0_1
L0_1 = nCondition_Distance
L0_1.namespace = "nCondition_Distance"
L0_1 = nCondition_Distance
L0_1.conditionType = 0
L0_1 = nCondition_Distance
L1_1 = {}
L2_1 = {}
L2_1.name = "Distance"
L3_1 = kReflectionType_float
L2_1.type = L3_1
L2_1.value = "10.0"
L3_1 = {}
L3_1.name = "GreaterThan"
L4_1 = kReflectionType_bool
L3_1.type = L4_1
L3_1.value = "false"
L1_1[1] = L2_1
L1_1[2] = L3_1
L0_1.properties = L1_1
L0_1 = nCondition
L0_1 = L0_1.RegisterCondition
L1_1 = "Distance"
L2_1 = nCondition_Distance
L0_1(L1_1, L2_1)
L0_1 = nCondition_Distance

function L1_1(A0_2)
  local L1_2, L2_2, L3_2, L4_2, L5_2, L6_2
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
      L3_2 = nGameObject
      L3_2 = L3_2.GetObjectDistance
      L4_2 = A0_2
      L5_2 = L1_2
      L3_2 = L3_2(L4_2, L5_2)
      L4_2 = nCondition
      L4_2 = L4_2.GetProperty
      L5_2 = A0_2
      L6_2 = "GreaterThan"
      L4_2 = L4_2(L5_2, L6_2)
      if L4_2 then
        if L2_2 <= L3_2 then
          L5_2 = true
          return L5_2
        end
      elseif L2_2 >= L3_2 then
        L5_2 = true
        return L5_2
      end
  end
  else
    L2_2 = false
    return L2_2
  end
  L2_2 = false
  return L2_2
end

L0_1[1] = L1_1
