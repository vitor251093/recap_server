local L0_1, L1_1
L0_1 = require
L1_1 = "Lua!GlobalDefinitions.lua"
L0_1(L1_1)

function L0_1(A0_2, A1_2, A2_2)
  local L3_2, L4_2
  L3_2 = nThreadData
  L3_2 = L3_2.GetPrivateTable
  L3_2 = L3_2()
  if L3_2 ~= nil then
    L4_2 = L3_2[A0_2]
    if L4_2 == nil then
      L4_2 = {}
      L3_2[A0_2] = L4_2
    end
    L4_2 = L3_2[A0_2]
    L4_2[A1_2] = A2_2
  end
end

Record = L0_1

function L0_1(A0_2, A1_2)
  local L2_2, L3_2, L4_2
  L2_2 = nThreadData
  L2_2 = L2_2.GetPrivateTable
  L2_2 = L2_2()
  if L2_2 ~= nil then
    L3_2 = L2_2[A0_2]
    L3_2 = L3_2[A1_2]
    return L3_2
  else
    L3_2 = nDebug
    L3_2 = L3_2.LogToConsole
    L4_2 = "table gone"
    L3_2(L4_2)
  end
  L3_2 = nil
  return L3_2
end

Lookup = L0_1
